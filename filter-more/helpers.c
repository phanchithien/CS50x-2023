#include "helpers.h"
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE average_color = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = average_color;
            image[i][j].rgbtGreen = average_color;
            image[i][j].rgbtRed = average_color;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // swap
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float red = 0.0;
            float blue = 0.0;
            float green = 0.0;
            float counter = 1.0;
            red = red + image[i][j].rgbtRed;
            blue = blue + image[i][j].rgbtBlue;
            green = green + image[i][j].rgbtGreen;
            if (i - 1 >= 0)
            {
                red = red + image[i - 1][j].rgbtRed;
                blue = blue + image[i - 1][j].rgbtBlue;
                green = green + image[i - 1][j].rgbtGreen;
                counter++;
                if (j - 1 >= 0)
                {
                    red = red + image[i - 1][j - 1].rgbtRed;
                    blue = blue + image[i - 1][j - 1].rgbtBlue;
                    green = green + image[i - 1][j - 1].rgbtGreen;
                    counter++;
                }
                if (j + 1 < width)
                {
                    red = red + image[i - 1][j + 1].rgbtRed;
                    blue = blue + image[i - 1][j + 1].rgbtBlue;
                    green = green + image[i - 1][j + 1].rgbtGreen;
                    counter++;
                }
            }
            if (i + 1 < height)
            {
                red = red + image[i + 1][j].rgbtRed;
                blue = blue + image[i + 1][j].rgbtBlue;
                green = green + image[i + 1][j].rgbtGreen;
                counter++;
                if (j - 1 >= 0)
                {
                    red = red + image[i + 1][j - 1].rgbtRed;
                    blue = blue + image[i + 1][j - 1].rgbtBlue;
                    green = green + image[i + 1][j - 1].rgbtGreen;
                    counter++;
                }
                if (j + 1 < width)
                {
                    red = red + image[i + 1][j + 1].rgbtRed;
                    blue = blue + image[i + 1][j + 1].rgbtBlue;
                    green = green + image[i + 1][j + 1].rgbtGreen;
                    counter++;
                }
            }
            if (j - 1 >= 0)
            {
                red = red + image[i][j - 1].rgbtRed;
                blue = blue + image[i][j - 1].rgbtBlue;
                green = green + image[i][j - 1].rgbtGreen;
                counter++;
            }
            if (j + 1 < width)
            {
                red = red + image[i][j + 1].rgbtRed;
                blue = blue + image[i][j + 1].rgbtBlue;
                green = green + image[i][j + 1].rgbtGreen;
                counter++;
            }

            // assign average
            temp[i][j].rgbtRed = round(red / counter);
            temp[i][j].rgbtBlue = round(blue / counter);
            temp[i][j].rgbtGreen = round(green / counter);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int Gx_red = 0;
            int Gx_green = 0;
            int Gx_blue = 0;
            int Gy_red = 0;
            int Gy_green = 0;
            int Gy_blue = 0;
            if (y - 1 >= 0)
            {
                Gy_red = Gy_red - 2 * image[y - 1][x].rgbtRed;
                Gy_green = Gy_green - 2 * image[y - 1][x].rgbtGreen;
                Gy_blue = Gy_blue - 2 * image[y - 1][x].rgbtBlue;

                if (x - 1 >= 0)
                {
                    Gx_red = Gx_red - 1 * image[y - 1][x - 1].rgbtRed;
                    Gx_green = Gx_green - 1 * image[y - 1][x - 1].rgbtGreen;
                    Gx_blue = Gx_blue - 1 * image[y - 1][x - 1].rgbtBlue;

                    Gy_red = Gy_red - 1 * image[y - 1][x - 1].rgbtRed;
                    Gy_green = Gy_green - 1 * image[y - 1][x - 1].rgbtGreen;
                    Gy_blue = Gy_blue - 1 * image[y - 1][x - 1].rgbtBlue;
                }

                if (x + 1 < width)
                {
                    Gx_red = Gx_red + image[y - 1][x + 1].rgbtRed;
                    Gx_green = Gx_green + image[y - 1][x + 1].rgbtGreen;
                    Gx_blue = Gx_blue + image[y - 1][x + 1].rgbtBlue;

                    Gy_red = Gy_red - 1 * image[y - 1][x + 1].rgbtRed;
                    Gy_green = Gy_green - 1 * image[y - 1][x + 1].rgbtGreen;
                    Gy_blue = Gy_blue - 1 * image[y - 1][x + 1].rgbtBlue;
                }
            }
            if (y + 1 < height)
            {
                Gy_red = Gy_red + 2 * image[y + 1][x].rgbtRed;
                Gy_green = Gy_green + 2 * image[y + 1][x].rgbtGreen;
                Gy_blue = Gy_blue + 2 * image[y + 1][x].rgbtBlue;

                if (x - 1 >= 0)
                {
                    Gx_red = Gx_red - 1 * image[y + 1][x - 1].rgbtRed;
                    Gx_green = Gx_green - 1 * image[y + 1][x - 1].rgbtGreen;
                    Gx_blue = Gx_blue - 1 * image[y + 1][x - 1].rgbtBlue;

                    Gy_red = Gy_red + image[y + 1][x - 1].rgbtRed;
                    Gy_green = Gy_green + image[y + 1][x - 1].rgbtGreen;
                    Gy_blue = Gy_blue + image[y + 1][x - 1].rgbtBlue;
                }
                if (x + 1 < width)
                {
                    Gx_red = Gx_red + image[y + 1][x + 1].rgbtRed;
                    Gx_green = Gx_green + image[y + 1][x + 1].rgbtGreen;
                    Gx_blue = Gx_blue + image[y + 1][x + 1].rgbtBlue;

                    Gy_red = Gy_red + image[y + 1][x + 1].rgbtRed;
                    Gy_green = Gy_green + image[y + 1][x + 1].rgbtGreen;
                    Gy_blue = Gy_blue + image[y + 1][x + 1].rgbtBlue;
                }
            }
            if (x - 1 >= 0)
            {
                Gx_red = Gx_red - 2 * image[y][x - 1].rgbtRed;
                Gx_green = Gx_green - 2 * image[y][x - 1].rgbtGreen;
                Gx_blue = Gx_blue - 2 * image[y][x - 1].rgbtBlue;
            }
            if (x + 1 < height)
            {
                Gx_red = Gx_red + 2 * image[y][x + 1].rgbtRed;
                Gx_green = Gx_green + 2 * image[y][x + 1].rgbtGreen;
                Gx_blue = Gx_blue + 2 * image[y][x + 1].rgbtBlue;
            }
            int red = round(sqrt(Gx_red * Gx_red + Gy_red * Gy_red));
            int green = round(sqrt(Gx_green * Gx_green + Gy_green * Gy_green));
            int blue = round(sqrt(Gx_blue * Gx_blue + Gy_blue * Gy_blue));
            temp[y][x].rgbtRed = (red >= 255) ? 255 : red;
            temp[y][x].rgbtGreen = (green >= 255) ? 255 : green;
            temp[y][x].rgbtBlue = (blue >= 255) ? 255 : blue;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
        }
    }

    return;
}
