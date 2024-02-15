#include <stdio.h>
#include <cs50.h>

void pyramid(int n);

int main(void)
{
    int height = get_int("How high should the block be? "); // get user input
    if (height <= 0)
    {
        int min_height = get_int("Input a positive number or higher: "); // for input that is too low
        pyramid(min_height);
    }
    else if (height > 8)
    {
        int min_height = get_int("Input a lower number: "); // for input that is too high
        pyramid(min_height);
    }
    else
    {
        pyramid(height); // for appropriate input
    }
}

void pyramid(int n)
{
    string answer = "";
    // creates right-handed pyramid
    for (int i = 0; i < n; i++)
    {
        // for the space that pushes the pyramid to the right that reduces as we go down
        for (int j = 0; j < n - i - 1; j++)
        {
            answer += " ";
        }
        for (int k = 0; k <= i; k++)
        {
            answer += "#";
        }
        answer += " ";
        for (int j = 0; j <= i; j++)
        {
            answer += "#"
        }

        answer += "\n";  // is used to insert new line
    }
    printf(answer);
}
