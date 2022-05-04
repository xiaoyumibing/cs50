#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            int blue = image[i][j].rgbtBlue;
            int green = image[i][j].rgbtGreen;
            int red = image[i][j].rgbtRed;

            //How to ensure the accurate display of the
            //result of integer division operation
            int average = round((float)(blue + green + red) / 3);

            // set the new values
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            int originalBlue = image[i][j].rgbtBlue;
            int originalGreen = image[i][j].rgbtGreen;
            int originalRed = image[i][j].rgbtRed;

            int sepiaRed = round((float)(.393 * originalRed + .769 * originalGreen + .189 * originalBlue));
            int sepiaGreen = round((float)(.349 * originalRed + .686 * originalGreen + .168 * originalBlue));
            int sepiaBlue = round((float)(.272 * originalRed + .534 * originalGreen + .131 * originalBlue));

            // using condition expresssion is better than define a new function
            // true is 0
            image[i][j].rgbtBlue = (image[i][j].rgbtBlue < 255) ? sepiaBlue : 255;
            image[i][j].rgbtRed = (image[i][j].rgbtRed < 255) ? sepiaRed : 255;
            image[i][j].rgbtGreen = (image[i][j].rgbtGreen < 255) ? sepiaGreen : 255;
        }
    }
    return;
}


// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width/2; j++)
        {
            RGBTRIPLE change_image;
            change_image = image[i][j];
            image[i][j] = image[i][width-1-j];
            image[i][width-1-j] = change_image;
        }
    }
    return;
}

// Blur image
//先求sum, 设置追踪变量count,最后avg=sum/count
//这个逻辑难点在于相加数的下标与sum（即image[i][j]）的逻辑，还有什么时候count才能++
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //temp is more professional
    RGBTRIPLE temp[height][width];
    for(int i = 0;i < height; i++)
    {
        for(int j = 0;j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    for(int row = 0;row < height; row ++)
    {
        for(int col = 0;col < width; col ++)
        {
            int sum_green = 0;
            int sum_blue = 0;
            int sum_red = 0;
            int count = 0;

            //这个嵌套的for循环内row,col都是不变的
            for(int i = -1;i < 2;i ++)
            {
                for(int j = -1;j < 2;j ++)
                {
                    if(row+i<0 || col+j<0 || row+i>height-1 || col+j>width-1)
                    {
                        continue;
                    }
                    sum_green += temp[row+i][col+j].rgbtGreen;
                    sum_blue += temp[row+i][col+j].rgbtBlue;
                    sum_red += temp[row+i][col+j].rgbtRed;
                    count ++;
                }
            }
            image[row][col].rgbtGreen = round((float)(sum_green/count));
            image[row][col].rgbtRed = round((float)sum_red/count);
            image[row][col].rgbtBlue = round((float)sum_blue/count);
        }
    }
    return;
}
