#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to perform encryption
void encrypt(string text, string key);

int main(int argc, string argv[])
{
    string key;
    string text;

    // Check for correct number of command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else
    {
        // Get the key from command-line arguments
        key = argv[1];
        int n = strlen(key);

        // Check key length
        if (n != 26)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }

        // Validate key characters
        for (int i = 0; i < n; i++)
        {
            // Check for non-alphabetical characters
            if (!isalpha(key[i]))
            {
                printf("Key must only contain alphabetical characters.\n");
                return 1;
            }

            // Check for repeated characters
            for (int j = i + 1; j < n; j++)
            {
                if (toupper(key[i]) == toupper(key[j]))
                {
                    printf("Do not repeat characters in key.\n");
                    return 1;
                }
            }
        }

        // Get plaintext from user
        text = get_string("plaintext: ");
        // Encrypt the text using the key
        encrypt(text, key);
    }

    return 0;
}

// Function to perform the encryption
void encrypt(string text, string key)
{
    char letter;
    int index;
    printf("ciphertext: ");

    // Loop through each character in the input text
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        letter = text[i];

        // Check if the character is alphabetical
        if (isalpha(letter))
        {
            if (isupper(letter))
            {
                // Convert uppercase letter to index in key
                index = letter - 'A';
                // Substitute with corresponding key letter and adjust case
                letter = key[index];
                letter = toupper(letter);
            }
            else
            {
                // Convert lowercase letter to index in key
                index = letter - 'a';
                // Substitute with corresponding key letter and adjust case
                letter = key[index];
                letter = tolower(letter);
            }
        }
        // Print the character
        printf("%c", letter);
    }
    printf("\n");
}
