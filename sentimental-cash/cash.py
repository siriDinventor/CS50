def get_cents():
    while True:
        try:
            # Prompt the user for the amount of change and convert it to cents
            cents = float(input("How much is your change: ")) * 100

            # Check if the entered value is non-negative
            if cents >= 0:
                return int(cents)  # Return the valid input as an integer
            else:
                print("Please enter a non-negative value.")
        except ValueError:
            # Handle non-numeric input with a message
            print("Please enter a valid number.")


def calculate_quarters(cents):
    count = 0
    # Calculate the number of quarters
    while cents >= 25:
        cents -= 25
        count += 1
    return count


def calculate_dimes(cents):
    count = 0
    # Calculate the number of dimes
    while cents >= 10:
        cents -= 10
        count += 1
    return count


def calculate_nickels(cents):
    count = 0
    # Calculate the number of nickels
    while cents >= 5:
        cents -= 5
        count += 1
    return count


def calculate_pennies(cents):
    # The remaining cents after calculating quarters, dimes, and nickels are pennies
    return cents


def main():
    cents = get_cents()  # Get the amount of change from the user

    quarters = calculate_quarters(cents)
    cents -= quarters * 25

    dimes = calculate_dimes(cents)
    cents -= dimes * 10

    nickels = calculate_nickels(cents)
    cents -= nickels * 5

    pennies = calculate_pennies(cents)

    coins = quarters + dimes + nickels + pennies

    # Print the total number of coins to give the customer
    print(f"Change owned: {coins}")


if __name__ == "__main__":
    main()
