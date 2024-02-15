#include <cs50.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>


// each of our text files contains 1000 words
#define LISTSIZE 1000

// values for colors and score (EXACT == right letter, right place; CLOSE == right letter, wrong place; WRONG == wrong letter)
#define EXACT 2
#define CLOSE 1
#define WRONG 0

// ANSI color codes for boxed in letters
#define GREEN   "\e[38;2;255;255;255;1m\e[48;2;106;170;100;1m"
#define YELLOW  "\e[38;2;255;255;255;1m\e[48;2;201;180;88;1m"
#define RED     "\e[38;2;255;255;255;1m\e[48;2;220;20;60;1m"
#define RESET   "\e[0;39m"

// user-defined function prototypes
string get_guess(int wordsize);
int check_word(string guess, int wordsize, int status[], string choice);
void print_word(string guess, int wordsize, int status[]);

int main(int argc, string argv[])
{
    // ensure proper usage
    // TODO #1

    int wordsize = 0;
    int key;

    // ensure argv[1] is either 5, 6, 7, or 8 and store that value in wordsize instead
    // TODO #2
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
        if (key < 5 || key > 8)
        {
            printf("Error: wordsize must be either 5, 6, 7, or 8 \n");
            return 1;
        }
        wordsize = key;
    }
    // open correct file, each file has exactly LISTSIZE words
    char wl_filename[6];
    sprintf(wl_filename, "%i.txt", wordsize);
    FILE *wordlist = fopen(wl_filename, "r");
    if (wordlist == NULL)
    {
        printf("Error opening file %s.\n", wl_filename);
        return 1;
    }

    // load word file into an array of size LISTSIZE
    char options[LISTSIZE][wordsize + 1];

    for (int i = 0; i < LISTSIZE; i++)
    {
        fscanf(wordlist, "%s", options[i]);
    }

    // pseudorandomly select a word for this game
    srand(time(NULL));
    string choice = options[rand() % LISTSIZE];

    // allow one more guess than the length of the word
    int guesses = wordsize + 1;
    bool won = false;

    // print greeting, using ANSI color codes to demonstrate
    printf(GREEN"This is WORDLE50"RESET"\n");
    printf("You have %i tries to guess the %i-letter word I'm thinking of\n", guesses, wordsize);

    // main game loop, one iteration for each guess
    for (int i = 0; i < guesses; i++)
    {
        // obtain user's guess
        string guess = get_guess(wordsize);

        // array to hold guess status, initially set to zero
        int status[wordsize];

        // set all elements of status array initially to 0, aka WRONG
        // TODO #4
        status[i] = 0;


        // Calculate score for the guess
        int score = check_word(guess, wordsize, status, choice);

        printf("Guess %i: ", i + 1);

        // Print the guessf
        print_word(guess, wordsize, status);

        // if they guessed it exactly right, set terminate loop
        if (score == EXACT * wordsize)
        {
            won = true;
            break;
        }
    }

    // Print the game's result
    // TODO #7

    // TODO #7: Print Game Result
    if (won)
    {
        printf("Congratulations! You guessed the word: %s\n", choice);
    }
    else
    {
        printf("Sorry, you've run out of guesses. The word was: %s\n", choice);
    }

    // that's all folks!
    return 0;
}

string get_guess(int wordsize)
{

    // ensure users actually provide a guess that is the correct length
    // TODO #3
    string guess = get_string("Input a %i-letter word: ", wordsize);
    int i = 0;
    int n = strlen(guess);
    do
    {
        if (n != wordsize)
        {
            guess = get_string("Input a %i-letter word: ", wordsize);
            i++;
        }
        else
        {
            i = 5;
        }
    }
    while (i < 5);


    return guess;
}

int check_word(string guess, int wordsize, int status[], string choice)
{
    int score = 0;

    // compare guess to choice and score points as appropriate, storing points in status
    // TODO #5

    // HINTS
    // iterate over each letter of the guess
    // iterate over each letter of the choice
    // compare the current guess letter to the current choice letter
    // if they're the same position in the word, score EXACT points (green) and break so you don't compare that letter further
    // if it's in the word, but not the right spot, score CLOSE point (yellow)
    // keep track of the total score by adding each individual letter's score from above
    // TODO #5: Compare Guess and Choice
    for (int i = 0; i < wordsize; i++)
    {
        printf("%c", choice[i]);
        if (guess[i] == choice[i])
        {
            status[i] = EXACT; // Exact match
        }
        else
        {
            // Check if the current guess letter is in the choice
            for (int j = 0; j < wordsize; j++)
            {
                if (guess[i] == choice[j] && status[j] != EXACT)
                {
                    status[i] = CLOSE; // Close match
                    break;
                }
            }
        }
        if (status[i] == 0)
        {
            status[i] = WRONG; // Wrong letter
        }
        score += status[i];
    }

    return score;
}

void print_word(string guess, int wordsize, int status[])
{
    // print word character-for-character with correct color coding, then reset terminal font to normal
    // TODO #6

    // TODO #6: Print Word with Color Coding
    for (int i = 0; i < wordsize; i++)
    {
        switch (status[i])
        {
            case EXACT:
                printf(GREEN "%c" RESET, guess[i]); // Exact match (green)
                break;
            case CLOSE:
                printf(YELLOW "%c" RESET, guess[i]); // Close match (yellow)
                break;
            case WRONG:
                printf(RED "%c" RESET, guess[i]); // Wrong letter (red)
                break;
        }
    }

    printf("\n");
    return;
}
