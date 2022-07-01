#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    int width = 1;

    // ask for height repeatedly
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // traverse rows
    for (int i = 0; i < height; i++)
    {
        // traverse rows
        for (int j = 0; j < height - width; j++)
        {
            printf(" ");
        }

        // hashes
        for (int k = 0; k < width; k++)
        {
            printf("#");
        }

        printf("  ");

        for (int l = 0; l < width; l++)
        {
            printf("#");
        }
        
        // increment counter for num hashes
        width++;
        printf("\n");
    }

}