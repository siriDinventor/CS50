import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    return render_template("index.html")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide stock symbol", 400)

        shares = request.form.get("shares")

        # Ensure shares is a positive integer
        if not shares.isdigit() or int(shares) <= 0:
            return apology("number of shares must be a positive integer", 400)

        # Get stock information using the lookup function
        symbol = request.form.get("symbol")
        quantity = int(shares)
        quote_info = lookup(symbol)

        if quote_info is None:
            return apology("invalid stock symbol", 400)

        stock_price = quote_info["price"]
        total_price = stock_price * quantity
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        cash_amount = cash[0]["cash"]

        if int(cash_amount) < total_price:
            return apology("Insufficient Balance", 400)

        updated_cash = cash_amount - total_price
        db.execute("UPDATE users SET cash = ? WHERE id = ?", updated_cash, session["user_id"])
        bought = db.execute("SELECT * FROM portfolio WHERE user_id = ? AND symbol = ?", session["user_id"], symbol)
        if len(bought) < 1:
            db.execute("INSERT INTO portfolio (user_id, symbol, shares, price, total, cash) VALUES (?, ?, ?, ?, ?, ?)",
                       session["user_id"], symbol, quantity, stock_price, total_price, updated_cash)
        else:
            initial_t_price = bought[0]["total"]
            initial_shares = bought[0]["shares"]
            db.execute("UPDATE portfolio SET shares = ?, total = ?, cash = ? WHERE user_id = ? AND symbol = ?",
                       quantity + initial_shares, initial_t_price + total_price, updated_cash, session["user_id"], symbol)

        # Log the transaction
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price) VALUES (?, ?, ?, ?)",
                   session["user_id"], symbol, quantity, stock_price)

        portfolio = get_portfolio(session["user_id"])
        flash("Bought!")
        return render_template("index.html", portfolio=portfolio)
    else:
        stocks = db.execute("SELECT symbol FROM portfolio WHERE user_id = ?", session["user_id"])
        return render_template("buy.html", stocks=stocks)




@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = get_transaction_history(session["user_id"])
    return render_template("transactions.html", transactions=transactions)



@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide stock symbol", 400)

        # Get stock information using the lookup function
        symbol = request.form.get("symbol")
        quote_info = lookup(symbol)

        if quote_info is None:
            return apology("invalid stock symbol", 400)

        # Render the quoted.html template with the stock information
        return render_template("quoted.html", quote_info=quote_info)

    else:
        # Render the quote.html template for GET requests
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)
        elif not request.form.get("confirmation"):
            return apology("must provide password confirmation", 400)

        username = request.form.get("username")
        unhashed_password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Check if password and confirmation match
        if unhashed_password != confirmation:
            return apology("passwords do not match", 400)

        existing_user = db.execute("SELECT * FROM users WHERE username = ?", username)
        if existing_user:
            return apology("passwords do not match", 400)

        # Hash the password
        hashed_password = generate_password_hash(unhashed_password)

        # Insert user into the database
        user_id = db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hashed_password)

        # Log the user in by storing their ID in the session
        session["user_id"] = user_id

        # Redirect to the home page or any desired destination after registration
        return redirect("/")

    else:
        return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Ensure symbol and shares are submitted
        if not symbol:
            return apology("must provide stock symbol", 400)
        if not shares:
            return apology("must provide number of shares", 400)

        # Ensure shares is a positive integer
        if not shares.isdigit() or int(shares) <= 0:
            return apology("number of shares must be a positive integer", 400)

        # Get user's stocks
        stocks = db.execute("SELECT symbol FROM portfolio WHERE user_id = ?", session["user_id"])

        # Ensure the selected stock is in user's portfolio
        if symbol not in [stock["symbol"] for stock in stocks]:
            return apology("you don't own this stock", 400)

        # Get stock information using the lookup function
        quote_info = lookup(symbol)

        if quote_info is None:
            return apology("invalid stock symbol", 400)

        stock_price = quote_info["price"]
        quantity = int(shares)
        total_price = stock_price * quantity

        # Get user's stock details
        stock_details = db.execute("SELECT * FROM portfolio WHERE user_id = ? AND symbol = ?", session["user_id"], symbol)
        current_shares = stock_details[0]["shares"]
        current_cash = stock_details[0]["cash"]

        # Ensure user has enough shares to sell
        if current_shares < quantity:
            return apology("not enough shares to sell", 400)

        # Update user's portfolio
        new_shares = current_shares - quantity
        new_cash = current_cash + total_price

        if new_shares == 0:
            # Remove the stock from the portfolio if all shares are sold
            db.execute("DELETE FROM portfolio WHERE user_id = ? AND symbol = ?", session["user_id"], symbol)
        else:
            # Update the portfolio with remaining shares and cash
            db.execute("UPDATE portfolio SET shares = ?, total = ?, cash = ? WHERE user_id = ? AND symbol = ?",
                       new_shares, stock_price * new_shares, new_cash, session["user_id"], symbol)

        # Log the transaction
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price) VALUES (?, ?, ?, ?)",
                   session["user_id"], symbol, -quantity, stock_price)

        portfolio = get_portfolio(session["user_id"])
        print(portfolio)
        flash("Sold!")
        return render_template("index.html", portfolio=portfolio)

    else:
        # Get user's stocks for the sell form
        stocks = db.execute("SELECT symbol FROM portfolio WHERE user_id = ?", session["user_id"])
        print(stocks)
        return render_template("sell.html", stocks=stocks)


def get_portfolio(user_id):
    """Get user's portfolio"""
    return db.execute("SELECT * FROM portfolio WHERE user_id = ?", user_id)


def get_transaction_history(user_id):
    """Get user's transaction history"""
    return db.execute("SELECT * FROM transactions WHERE user_id = ?", user_id)
