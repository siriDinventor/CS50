#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1
    if (argc < 2)
    {
        printf("./reverse input.wav output.wav\n");
        return 1;
    }

    // Open input file for reading
    // TODO #2
    char *infile = argv[optind];
    char *outfile = argv[optind + 1];

    // Open input file
    FILE *inptr = fopen(infile, "rb");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 4;
    }

    // Read header
    // TODO #3
    WAVHEADER b_input;
    fread(&b_input, sizeof(WAVHEADER), 1, inptr);

    // Use check_format to ensure WAV format
    // TODO #4
    if (check_format(b_input) == 0)
    {
        printf("The file is in WAV format.\n");
    }
    else
    {
        printf("The file is not in WAV format.\n");
    }

    // Open output file for writing
    // TODO #5

    FILE *outptr = fopen(outfile, "wb");
    if (outptr == NULL)
    {
        printf("Could not create %s.\n", outfile);
        return 5;
    }

    // Write header to file
    // TODO #6

    fwrite(&b_input, sizeof(WAVHEADER), 1, outptr);
    // Use get_block_size to calculate size of block
    // TODO #7
    long block_size = get_block_size(b_input);

    // Write reversed audio to file
    // TODO #8
    // Write reversed audio to file
    // TODO #8
    // Declare an array to store each block we read in
    BYTE buffer[block_size];

    // Move Pointer to the End (takes in the pointer, the offset amount of 0, and moves it the end of the file)
    fseek(inptr, 0, SEEK_END);

    // Finding the Buffer Audio Size (excluding the header)
    long audio_size = ftell(inptr) - sizeof(WAVHEADER);
    int audio_block = (int) audio_size / block_size;

    // Iterate through the input file audio data
    // Maintain the order of the channels for each audio block (Reversed)
    for (int i = audio_block - 1; i >= 0; i--)
    {
        // Starting From End of the File (Block by Block Transferring)
        fseek(inptr, sizeof(WAVHEADER) + i * block_size, SEEK_SET);
        fread(buffer, block_size, 1, inptr);
        fwrite(buffer, block_size, 1, outptr);
    }
    // Close the files
    fclose(inptr);
    fclose(outptr);
    return 0;

}

int check_format(WAVHEADER header)
{
    char string[5] = ""; // Initialize an array to store characters
    for (int i = 0; i < 4; i++)
    {
        string[i] = header.format[i];
    }
    string[4] = '\0'; // Null-terminate the string
    if (strcmp(string, "WAVE") == 0)
    {
        return 0;
    }
    return 1;
}



int get_block_size(WAVHEADER header)
{
    DWORD block = (DWORD)header.bitsPerSample * header.numChannels;
    // TODO #7
    return block / 8;
}

