#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void encrypt(string text, int key);

int main(int argc, string argv[])
{
    int key = 0;
    string text;

    if (argc != 2)
    {
        printf("Usage: ./caesar key \n");
        return 1;
        // Ensure user inputs a command-line argument
    }
    else
    {
        // Check if the provided key is a non-negative integer
        for (int i = 0; argv[1][i] != '\0'; i++)
        {
            // Check if it is a non-numeric character
            if (!isdigit(argv[1][i]))
            {
                printf("Usage: ./caesar key \n");
                return 1;
            }
        }

        key = atoi(argv[1]);
        text = get_string("plaintext: ");
        encrypt(text, key);
    }

    return 0;
}

void encrypt(string text, int key)
{
    char letter;
    printf("ciphertext: ");

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        letter = text[i];
        if (letter == 32)
        {
            printf(" ");  // Space character
        }
        else if (letter == 33)
        {
            printf("!");  // Exclamation mark
        }
        else if (letter == 44)
        {
            printf(",");  // Comma
        }
        else
        {
            letter = letter + key;
            while ((letter < 97 && letter > 90) || letter < 65 || letter > 122)
            {
                // Wrap around if exceeded ASCII value range
                letter = letter - 26;
            }
            printf("%c", letter);
        }
    }
    printf("\n");
}
