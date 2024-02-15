#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

// Function prototypes
int count_word(string text);
int count_sentence(string text);
int count_letters(string text);

int main(void)
{
    // Get input text from the user
    string text = get_string("Text: ");

    // Count the number of letters, sentences, and words in the text
    int letters_count = count_letters(text);
    int sentence = count_sentence(text);
    int words = count_word(text);

    // Calculate average letters per 100 words (L) and average sentences per 100 words (S)
    float L = (100.0 * letters_count) / words;
    float S = (100.0 * sentence) / words;

    // Compute the Coleman-Liau index
    int grade = round(0.0588 * L - 0.296 * S - 15.8);

    // Determine and print the grade level
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}

// Function to count the number of letters in the text
int count_letters(string text)
{
    int letters_count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        char letter = text[i];
        if (isalpha(letter))
        {
            letters_count++;
        }
    }
    // Return the count of letters
    return letters_count;
}

// Function to count the number of sentences in the text
int count_sentence(string text)
{
    int sentence = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        char letter = text[i];
        if (letter == '?' || letter == '!' || letter == '.')
        {
            sentence++;
        }
    }
    // Return the count of sentences
    return sentence;
}

// Function to count the number of words in the text
int count_word(string text)
{
    int words = 0;
    bool in_word = false;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        char letter = text[i];

        if (isalpha(letter))
        {
            // If we are not in a word, increment the word count
            if (!in_word)
            {
                words++;
                in_word = true;
            }
        }
        else if (isspace(letter))
        {
            // If it's a space, we are not in a word
            in_word = false;
        }
    }

    // Return the count of words
    return words;
}
