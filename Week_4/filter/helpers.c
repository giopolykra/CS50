#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //loop over rows
    for (int i = 0; i < height; i++)
    {
        //loop over columns
        for (int j = 0 ; j < width; j++)
        {
            int sum = image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed;
            float average = roundf(sum/ 3.0);

            image[i][j].rgbtBlue = (int) average;
            image[i][j].rgbtGreen = (int) average;
            image[i][j].rgbtRed = (int) average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    //loop over rows
    for (int i = 0; i < height; i++)
    {
        //loop over columns
        for (int j = 0 ; j < width; j++)
        {
            float sepia_Red = .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue;
            float sepia_Green = .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue;
            float sepia_Blue = .272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue;

            sepia_Red = roundf(sepia_Red);
            sepia_Green = roundf(sepia_Green);
            sepia_Blue = roundf(sepia_Blue);

            if (sepia_Red > 255)
            {
                sepia_Red = 255;
            }
            if (sepia_Green > 255)
            {
                sepia_Green = 255;
            }
            if (sepia_Blue > 255)
            {
                sepia_Blue = 255;
            }
            image[i][j].rgbtRed = sepia_Red;
            image[i][j].rgbtGreen = sepia_Green;
            image[i][j].rgbtBlue = sepia_Blue;

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //loop over rows
    for (int i = 0; i < height; i++)
    {
        //loop over columns
        for (int j = 0 ; j < (roundf(width / 2)); j++)
        {
            //save the left side of the image on temporary variables
            int tmp_l_red = image[i][j].rgbtRed;
            int tmp_l_green = image[i][j].rgbtGreen;
            int tmp_l_blue = image[i][j].rgbtBlue;

            //save the right side of the image on temporary variables
            int tmp_r_red = image[i][width - 1 - j].rgbtRed;
            int tmp_r_green = image[i][width - 1 - j].rgbtGreen;
            int tmp_r_blue = image[i][width - 1 - j].rgbtBlue;

            //put right side on the left
            image[i][j].rgbtRed = tmp_r_red;
            image[i][j].rgbtGreen = tmp_r_green;
            image[i][j].rgbtBlue = tmp_r_blue;

            //put left side on the right
            image[i][width - 1 - j].rgbtRed = tmp_l_red;
            image[i][width - 1 - j].rgbtGreen = tmp_l_green;
            image[i][width - 1 - j].rgbtBlue = tmp_l_blue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //loop over rows
    for (int i = 0; i < height; i++)
    {
        for (int j = 0 ; j < (roundf(width / 2)); j++)
        {
            int sum_red = image[i][j].rgbtRed;
            int sum_green = image[i][j].rgbtGreen;
            int sum_blue = image[i][j].rgbtBlue;
            int pixels = 1;

            //inside points
            if ((i > 0) && (i < height - 1) && (j < width - 1) && (j > 0))
            {
                sum_red += image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed \
                           + image[i][j - 1].rgbtRed  + image[i][j + 1].rgbtRed \
                           + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed;
                sum_green += image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen \
                             + image[i][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen \
                             + image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen;
                sum_blue += image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue \
                            + image[i][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue \
                            + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue;
                pixels += 8;
            }
            //left column
            if ((i > 0) && (i < height - 1) && (j == 0))
            {
                sum_red +=  image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed \
                            +image[i][j + 1].rgbtRed \
                            + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed;
                sum_green += image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen \
                             + image[i][j + 1].rgbtGreen \
                             + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen;
                sum_blue +=  image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue \
                             + image[i][j + 1].rgbtBlue \
                             + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue;
                pixels += 5;

            }
            //right column
            if ((i > 0) && (i < height - 1) && (j == width - 1))
            {
                sum_red = image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed \
                          + image[i][j - 1].rgbtRed \
                          + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed;
                sum_green = image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen\
                            + image[i][j - 1].rgbtGreen \
                            + image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen;
                sum_blue = image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue\
                           + image[i][j - 1].rgbtBlue \
                           + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue;
                pixels += 5;
            }
            //top row
            if ((i == 0)  && (j < width - 1) && (j > 0))
            {
                sum_red = image[i][j - 1].rgbtRed  + image[i][j + 1].rgbtRed \
                          + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed;
                sum_green = image[i][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen \
                            + image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen;
                sum_blue = image[i][j - 1].rgbtBlue  + image[i][j + 1].rgbtBlue \
                           + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue;
                pixels += 5;
            }
            //bottom row
            if ((i == height - 1) && (j < width - 1) && (j > 0))
            {
                sum_red = image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed \
                          + image[i][j - 1].rgbtRed  + image[i][j + 1].rgbtRed;
                sum_green = image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen \
                            + image[i][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen;
                sum_blue = image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue \
                           + image[i][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue;
                pixels += 5;
            }
            //top left corner
            if ((i == 0) && (j == 0))
            {
                sum_red += image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed;
                sum_green += image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen;
                sum_blue += image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue;
                pixels += 3;
            }
            //top right corner
            if ((i == 0) && (j == width - 1))
            {
                sum_red += image[i][j - 1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed;
                sum_green += image[i][j - 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen;
                sum_blue += image[i][j - 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue;
                pixels += 3;
            }
            //bottom left corner
            if ((i == height - 1) && (j == 0))
            {
                sum_red +=  image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j + 1].rgbtRed;
                sum_green += image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j + 1].rgbtGreen ;
                sum_blue +=  image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j + 1].rgbtBlue;
                pixels += 3;
            }
            //bottom right corner
            if ((i == height - 1) && (j == width - 1))
            {
                sum_red += image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i][j - 1].rgbtRed;
                sum_green += image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i][j - 1].rgbtGreen ;
                sum_blue += image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i][j - 1].rgbtBlue;
                pixels += 3;
            }

            float average_Red = roundf(sum_red / pixels);
            float average_Green = roundf(sum_green / pixels);
            float average_Blue = roundf(sum_blue / pixels);
            image[i][j].rgbtRed = (int) average_Red;
            image[i][j].rgbtGreen = (int) average_Green;
            image[i][j].rgbtBlue = (int) average_Blue;
        }
    }
    return;
}
