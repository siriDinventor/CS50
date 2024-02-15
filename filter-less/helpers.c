#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int red = 0;
    int green = 0;
    int blue = 0;
    int mean = 0;
    for (int i = 0; i < height; i++)
    {
        //to iterate for height
        for (int j = 0; j < width; j++)
        {
            //to iterate over width
            red = image[i][j].rgbtRed;
            green = image[i][j].rgbtGreen;
            blue = image[i][j].rgbtBlue;
            mean = round((red + green + blue) / 3.0);
            image[i][j].rgbtRed = mean;
            image[i][j].rgbtGreen = mean;
            image[i][j].rgbtBlue = mean;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int red = 0;
    int green = 0;
    int blue = 0;
    for (int i = 0; i < height; i++)
    {
        //to iterate for height
        for (int j = 0; j < width; j++)
        {
            //to iterate over width
            red = image[i][j].rgbtRed;
            green = image[i][j].rgbtGreen;
            blue = image[i][j].rgbtBlue;
            int sepiaRed = round(.393 * red + .769 * green + .189 * blue);
            int sepiaGreen = round(.349 * red + .686 * green + .168 * blue);
            int sepiaBlue = round(.272 * red + .534 * green + .131 * blue);
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        //to iterate for height
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
    return;
}

// Blur image

void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a temporary image to store blurred values
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Initialize averages and count of pixels
            float redAvg = 0;
            float greenAvg = 0;
            float blueAvg = 0;
            int count = 0;

            // Iterate over the surrounding pixels
            for (int ii = i - 1; ii <= i + 1; ii++)
            {
                for (int jj = j - 1; jj <= j + 1; jj++)
                {
                    // Check if the surrounding pixel is within bounds
                    if (ii >= 0 && ii < height && jj >= 0 && jj < width)
                    {
                        redAvg += image[ii][jj].rgbtRed;
                        greenAvg += image[ii][jj].rgbtGreen;
                        blueAvg += image[ii][jj].rgbtBlue;
                        count++;
                    }
                }
            }

            // Calculate the averages
            redAvg /= count;
            greenAvg /= count;
            blueAvg /= count;

            // Update the temporary image with the blurred values
            temp[i][j].rgbtRed = round(redAvg);
            temp[i][j].rgbtGreen = round(greenAvg);
            temp[i][j].rgbtBlue = round(blueAvg);
        }
    }

    // Copy the values from the temporary image back to the original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
}



