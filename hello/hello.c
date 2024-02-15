#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string name = get_string("What's your name? ");//uses cs50 package to get user input of name
    printf("Hello, %s\n", name); //Prints hello with the input

}
wget https://cdn.cs50.net/2022/fall/psets/1/mario-less.zip