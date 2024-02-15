#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        //to iterate for height
        for (int j = 0; j < width; j++)
        {
            //to iterate over width
            if (image[i][j].rgbtRed == 0x00 && image[i][j].rgbtGreen == 0x00 && image[i][j].rgbtBlue == 0x00) // checks if a pixel is black
            {
                image[i][j].rgbtRed = 0xff; // turn a particular pixel red
            }
        }
    }
}
