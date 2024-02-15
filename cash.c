#include <cs50.h>
#include <stdio.h>

int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // Ask how many cents the customer is owed
    int cents = get_cents();

    // Calculate the number of quarters to give the customer
    int quarters = calculate_quarters(cents);
    cents = cents - quarters * 25;

    // Calculate the number of dimes to give the customer
    int dimes = calculate_dimes(cents);
    cents = cents - dimes * 10;

    // Calculate the number of nickels to give the customer
    int nickels = calculate_nickels(cents);
    cents = cents - nickels * 5;

    // Calculate the number of pennies to give the customer
    int pennies = calculate_pennies(cents);
    cents = cents - pennies * 1;

    // Sum coins
    int coins = quarters + dimes + nickels + pennies;

    // Print total number of coins to give the customer
    printf("Change owned: %i\n", coins);
}

int get_cents(void)
{
    int cents;
    do
    {
        cents = get_int("How much is your Change: ");
        //Calculate the Cents that the customers are owed
    }
    while (cents < 1);
    return cents;
}

int calculate_quarters(int cents)
{
    int count = 0; //Calculate the Quarters owed
    while (cents >= 25)
    {
        cents -= 25;
        count ++;
    }
    return count;
}

int calculate_dimes(int cents)
{
    int count = 0; //Calculate the DIMES owed
    while (cents >= 10)
    {
        cents -= 10;
        count ++;
    }
    return count;
}

int calculate_nickels(int cents)
{
    int count = 0; //Calculate the NICKELS owed
    while (cents >= 5)
    {
        cents -= 5;
        count ++;
    }
    return count;
}

int calculate_pennies(int cents)
{
    return cents;
}
