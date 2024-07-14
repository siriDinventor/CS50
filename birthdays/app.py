import os
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_sqlalchemy import SQLAlchemy

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure SQLALCHEMY Library to use SQLite database
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///birthdays.db'
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
db = SQLAlchemy(app)

class Birthday(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    name = db.Column(db.String(80), nullable=False)
    month = db.Column(db.Integer, nullable=False)
    day = db.Column(db.Integer, nullable=False)

    def __repr__(self):
        return f'<Birthday {self.name}, {self.month}/{self.day}>'

@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")

        # Add the user's entry into the database
        if name and month and day:
            new_birthday = Birthday(name=name, month=int(month), day=int(day))
            db.session.add(new_birthday)
            db.session.commit()

        return redirect("/")

    else:
        # Display the entries in the database on index.html
        birthdays = Birthday.query.all()
        return render_template("index.html", birthdays=birthdays)

if __name__ == "__main__":
    with app.app_context():
        db.create_all()
    app.run(debug=True)

