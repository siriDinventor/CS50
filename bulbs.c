#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);
int binary_conv(char letter);
int ascii_conv(string text);

int main(void)
{
    string text = get_string("Message: ");
    ascii_conv(text);

}
int ascii_conv(text)
{
    char letter;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        // letter.toupp
        letter = text[i];
        binary_conv(letter);
    }
    
}
int binary_conv(letter)
{
    int bit;
    for (int i = BITS_IN_BYTE - 1; i >= 0; i--)
    {
        bit = (letter >> i) & 1;  // Extract each bit
        print_bulb(bit);
    }
    printf(" ");


}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
