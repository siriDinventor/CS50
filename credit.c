#include <cs50.h>
#include <stdio.h>

int get_credit(void);

int main(void)
{
    string answer = "";
    long credit = get_credit();
    string stringEquivalent = credit.ToString();

    if (stringEquivalent.StartsWith("4"))
    {
        answer += "This is a Visa Number \n";
    }
    else if (stringEquivalent.StartsWith("34") || stringEquivalent.StartsWith("37"))
    {
        answer += "All American Express \n";
    }
    else if (stringEquivalent.StartsWith("51") || stringEquivalent.StartsWith("52") || stringEquivalent.StartsWith("53") || stringEquivalent.StartsWith("54") || stringEquivalent.StartsWith("55"))
    {
        answer += "Master Card \n";
    }
    else
    {
        answer += "Invalid Number;
    }

}


int get_credit(void)
{
    long credit;
    do
    {
        credit = get_long("Your credit Card Number: ");
        //To get Credit Card Number
    }
    while (credit < 1);

}