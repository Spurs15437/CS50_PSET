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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // 纯黑边框
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

    int GGX[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int GGY[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

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
            float tempB = 0;
            float tempG = 0;
            float tempR = 0;

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

            // float count = 0.0;
            RGBTRIPLE onepointandeight[3][3] = {{temp_middle[image_local[0].y][image_local[0].x], temp_middle[image_local[1].y][image_local[1].x], temp_middle[image_local[2].y][image_local[2].x]}, {temp_middle[image_local[3].y][image_local[3].x], temp_middle[image_local[4].y][image_local[4].x], temp_middle[image_local[5].y][image_local[5].x]}, {temp_middle[image_local[6].y][image_local[6].x], temp_middle[image_local[7].y][image_local[7].x], temp_middle[image_local[8].y][image_local[8].x]}};
            float GxB = 0, GyB = 0;
            float GxG = 0, GyG = 0;
            float GxR = 0, GyR = 0;

            for (int ii = 0; ii < 3; ii++)
            {
                for (int jj = 0; jj < 3; jj++)
                {
                    GxB = GxB + GGX[ii][jj] * onepointandeight[ii][jj].rgbtBlue;
                    GyB = GyB + GGY[ii][jj] * onepointandeight[ii][jj].rgbtBlue;

                    GxG = GxG + GGX[ii][jj] * onepointandeight[ii][jj].rgbtGreen;
                    GyG = GyG + GGY[ii][jj] * onepointandeight[ii][jj].rgbtGreen;

                    GxR = GxR + GGX[ii][jj] * onepointandeight[ii][jj].rgbtRed;
                    GyR = GyR + GGY[ii][jj] * onepointandeight[ii][jj].rgbtRed;
                }
            }

            float temB = sqrt((pow(GxB, 2) + pow(GyB, 2)));
            float temG = sqrt((pow(GxG, 2) + pow(GyG, 2)));
            float temR = sqrt((pow(GxR, 2) + pow(GyR, 2)));

            int finalB = round(temB);
            int finalG = round(temG);
            int finalR = round(temR);

            if (finalB > 255)
            {
                finalB = 255;
            }

            if (finalG > 255)
            {
                finalG = 255;
            }

            if (finalR > 255)
            {
                finalR = 255;
            }

            image[i - 1][j - 1].rgbtBlue = finalB;
            image[i - 1][j - 1].rgbtGreen = finalG;
            image[i - 1][j - 1].rgbtRed = finalR;
        }
    }

    return;
}
