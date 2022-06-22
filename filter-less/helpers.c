#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE temp_middle;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp_middle = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = temp_middle;
            image[i][j].rgbtGreen = temp_middle;
            image[i][j].rgbtRed = temp_middle;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int originalBlue, tempBlue;
    int originalGreen, tempGreen;
    int originalRed, tempRed;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // temp_middle = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3);
            originalBlue = image[i][j].rgbtBlue;
            originalGreen = image[i][j].rgbtGreen;
            originalRed = image[i][j].rgbtRed;

            tempRed = round(0.393 * originalRed + 0.769 * originalGreen + 0.189 * originalBlue);
            tempGreen = round(0.349 * originalRed + 0.686 * originalGreen + 0.168 * originalBlue);
            tempBlue = round(0.272 * originalRed + 0.534 * originalGreen + 0.131 * originalBlue);

            if (tempRed > 255)
            {
                tempRed = 255;
            }
            else if (tempRed < 0)
            {
                tempRed = 0;
            }
            image[i][j].rgbtRed = tempRed;

            if (tempGreen > 255)
            {
                tempGreen = 255;
            }
            else if (tempGreen < 0)
            {
                tempGreen = 0;
            }
            image[i][j].rgbtGreen = tempGreen;

            if (tempBlue > 255)
            {
                tempBlue = 255;
            }
            else if (tempBlue < 0)
            {
                tempBlue = 0;
            }
            image[i][j].rgbtBlue = tempBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE originalBlue;
    BYTE originalGreen;
    BYTE originalRed;
    for (int i = 0; i < height; i++)
    {
        if (width % 2 == 0)
        {
            for (int j = 0; j < (width / 2); j++)
            {
                originalBlue = image[i][j].rgbtBlue;
                image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
                image[i][width - j - 1].rgbtBlue = originalBlue;

                originalGreen = image[i][j].rgbtGreen;
                image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
                image[i][width - j - 1].rgbtGreen = originalGreen;

                originalRed = image[i][j].rgbtRed;
                image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
                image[i][width - j - 1].rgbtRed = originalRed;
            }
        }
        else
        {
            for (int j = 0; j < (width / 2); j++)
            {
                originalBlue = image[i][j].rgbtBlue;
                image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
                image[i][width - j - 1].rgbtBlue = originalBlue;

                originalGreen = image[i][j].rgbtGreen;
                image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
                image[i][width - j - 1].rgbtGreen = originalGreen;

                originalRed = image[i][j].rgbtRed;
                image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
                image[i][width - j - 1].rgbtRed = originalRed;
            }
        }

    }
    return;
}

// 做除法要四舍五入的时候要用浮点
// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp_middle[height + 2][width + 2];

    for (int i = 0; i < height + 2; i++)
    {
        for (int j = 0; j < width + 2; j++)
        {
            temp_middle[i][j].rgbtBlue = 0;
            temp_middle[i][j].rgbtGreen = 0;
            temp_middle[i][j].rgbtRed = 0;
        }
    }

    for (int i = 1; i < height + 1; i++)
    {
        for (int j = 1; j < width + 1; j++)
        {
            temp_middle[i][j] = image[i - 1][j - 1];
        }
    }

    typedef struct
    {
        int x;
        int y;
    }
    location;
    location image_local[9];



    for (int i = 1; i < height + 1; i++)
    {
        for (int j = 1; j < width + 1; j++)
        {
            int tempB = 0;
            int tempG = 0;
            int tempR = 0;

            image_local[0].x = j - 1;
            image_local[0].y = i - 1;

            image_local[1].x = j;
            image_local[1].y = i - 1;

            image_local[2].x = j + 1;
            image_local[2].y = i - 1;

            image_local[3].x = j - 1;
            image_local[3].y = i;

            image_local[4].x = j;
            image_local[4].y = i;

            image_local[5].x = j + 1;
            image_local[5].y = i;

            image_local[6].x = j - 1;
            image_local[6].y = i + 1;

            image_local[7].x = j;
            image_local[7].y = i + 1;

            image_local[8].x = j + 1;
            image_local[8].y = i + 1;

            float count = 0.0;

            for (int k = 0; k < 9; k++)
            {

                if (!(image_local[k].x == 0 || image_local[k].x == width + 1 || image_local[k].y == 0 || image_local[k].y == height + 1))
                {
                    count++;
                }
                tempB = temp_middle[image_local[k].y][image_local[k].x].rgbtBlue + tempB;
                tempG = temp_middle[image_local[k].y][image_local[k].x].rgbtGreen + tempG;
                tempR = temp_middle[image_local[k].y][image_local[k].x].rgbtRed + tempR;
            }

            image[i - 1][j - 1].rgbtBlue = round(tempB / count);
            image[i - 1][j - 1].rgbtGreen = round(tempG / count);
            image[i - 1][j - 1].rgbtRed = round(tempR / count);
        }
    }
    return;
}
