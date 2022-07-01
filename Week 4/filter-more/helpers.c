#include "helpers.h"
#include <stdio.h>
#include <math.h>

int calc_g(int gx_val, int gy_val);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // traverse the entire image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // get avg
            int avg = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);

            // assign new values
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // make a temp image of the original
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // assign old image values to the temp
            temp[i][j].rgbtBlue = image[i][j].rgbtBlue;
            temp[i][j].rgbtGreen = image[i][j].rgbtGreen;
            temp[i][j].rgbtRed = image[i][j].rgbtRed;
        }
    }

    // go through the entire original image, but this time starting from right to left, up to down
    for (int i = 0; i < height; i++)
    {
        // keeps track of where on the temp image we are that is counting down
        int back_counter = width - 1;

        for (int j = 0; j < width; j++)
        {
            // assign image values to the temp values on the other side
            image[i][j].rgbtBlue = temp[i][back_counter].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][back_counter].rgbtGreen;
            image[i][j].rgbtRed = temp[i][back_counter].rgbtRed;

            back_counter--;
        }
    }

    return;
}

// Blur image
// in corner
// top left [0][0]
// top right [0][width-1]
// bottom left [height-1][0]
// bottom right [height-1][width-1]

// on edge
// on top edge ------ [0][x]
// on right edge ---- [x][width-1]
// on bottom edge --- [height-1][x]
// on left edge ----- [x][0]
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    // traverse entire image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // for each pixel
            float sumBlue = 0;
            float sumGreen = 0;
            float sumRed = 0;
            int numPix = 0;

            // check in a 3x3 around the pixel
            for (int adj_i = -1; adj_i < 2; adj_i++)
            {
                for (int adj_j = -1; adj_j < 2; adj_j++)
                {
                    if ((i + adj_i < 0 || i + adj_i >= height) || (j + adj_j < 0 || j + adj_j >= width))
                    {
                        // out of bounds where 3x3 check is negative or over width
                    }
                    else
                    {
                        // increase the sum
                        sumBlue += image[i + adj_i][j + adj_j].rgbtBlue;
                        sumGreen += image[i + adj_i][j + adj_j].rgbtGreen;
                        sumRed += image[i + adj_i][j + adj_j].rgbtRed;
                        numPix++;
                    }
                }
            }

            // update the center pixel
            temp[i][j].rgbtBlue = round(sumBlue / numPix);
            temp[i][j].rgbtGreen = round(sumGreen / numPix);
            temp[i][j].rgbtRed = round(sumRed / numPix);

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

void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    int gx_mat [3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1},
    };

    int gy_mat [3][3] =
    {
        {-1, -2, -1},
        { 0,  0,  0},
        { 1,  2,  1},
    };

    // traverse entire image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int gx_red = 0;
            int gx_green = 0;
            int gx_blue = 0;

            int gy_red = 0;
            int gy_green = 0;
            int gy_blue = 0;

            int mat_i = 0;
            int mat_j = 0;

            // calculate gx
            for (int adj_i = -1; adj_i < 2; adj_i++)
            {
                for (int adj_j = -1; adj_j < 2; adj_j++)
                {
                    if ((i + adj_i < 0 || i + adj_i >= height) || (j + adj_j < 0 || j + adj_j >= width))
                    {
                        // out of bounds where 3x3 check is negative or over width
                    }
                    else
                    {
                        gx_red += gx_mat[mat_i][mat_j] * image[i + adj_i][j + adj_j].rgbtRed;
                        gx_blue += gx_mat[mat_i][mat_j] * image[i + adj_i][j + adj_j].rgbtBlue;
                        gx_green += gx_mat[mat_i][mat_j] * image[i + adj_i][j + adj_j].rgbtGreen;

                        gy_red += gy_mat[mat_i][mat_j] * image[i + adj_i][j + adj_j].rgbtRed;
                        gy_blue += gy_mat[mat_i][mat_j] * image[i + adj_i][j + adj_j].rgbtBlue;
                        gy_green += gy_mat[mat_i][mat_j] * image[i + adj_i][j + adj_j].rgbtGreen;
                    }
                    mat_j++;
                }
                mat_i++;
                mat_j = 0;
            }

            // // calculate gy
            // mat_i = 0;
            // mat_j = 0;

            // for (int adj_i = -1; adj_i < 2; adj_i++)
            // {
            //     for (int adj_j = -1; adj_j < 2; adj_j++)
            //     {
            //         if ((i + adj_i < 0 || i + adj_i >= height) || (j + adj_j < 0 || j + adj_j >= width))
            //         {
            //             // out of bounds where 3x3 check is negative or over width
            //             mat_j++;
            //         }
            //         else
            //         {
            //             gy_red += gy_mat[mat_i][mat_j] * image[i + adj_i][j + adj_j].rgbtRed;
            //             gy_blue += gy_mat[mat_i][mat_j] * image[i + adj_i][j + adj_j].rgbtBlue;
            //             gy_green += gy_mat[mat_i][mat_j] * image[i + adj_i][j + adj_j].rgbtGreen;
            //             mat_j++;
            //         }
            //     }
            //     mat_i++;
            //     mat_j = 0;
            // }

            // sqrt(gx^2 + gy^2) <- make sure this is rounded to nearest int, capped at 255
            temp[i][j].rgbtRed = calc_g(gx_red, gy_red);
            temp[i][j].rgbtGreen = calc_g(gx_green, gy_green);
            temp[i][j].rgbtBlue = calc_g(gx_blue, gy_blue);
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

int calc_g(int gx_val, int gy_val)
{
    if (round(sqrt(gx_val * gx_val + gy_val * gy_val)) > 255)
    {
        return 255;
    }
    else
    {
        return round(sqrt(gx_val * gx_val + gy_val * gy_val));
    }
        
}