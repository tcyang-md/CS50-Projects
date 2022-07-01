#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    int BLOCK_SIZE = 512;
    int filecount = 0;
    FILE *img_p = NULL;
    int count = 0;


    BYTE buffer[BLOCK_SIZE];

    while (fread(&buffer, BLOCK_SIZE, 1, file) == 1)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (
                buffer[3] == 0xe0 ||
                buffer[3] == 0xe1 ||
                buffer[3] == 0xe2 ||
                buffer[3] == 0xe3 ||
                buffer[3] == 0xe4 ||
                buffer[3] == 0xe5 ||
                buffer[3] == 0xe6 ||
                buffer[3] == 0xe7 ||
                buffer[3] == 0xe8 ||
                buffer[3] == 0xe9 ||
                buffer[3] == 0xea ||
                buffer[3] == 0xeb ||
                buffer[3] == 0xec ||
                buffer[3] == 0xed ||
                buffer[3] == 0xee ||
                buffer[3] == 0xef
            )
           )
        {
            if (count == 1)
            {
                fclose(img_p);
            }
            else
            {
                count = 1;
            }

            char filename[8];
            sprintf(filename, "%03d.jpg", filecount);
            img_p = fopen(filename, "a");
            filecount++;
        }

        if (count == 1)
        {
            // write 512 bytes to file once we start finding jpgs
            fwrite(&buffer, BLOCK_SIZE, 1, img_p);
        }

    }

    fclose(file);
    fclose(img_p);

    return 0;
}