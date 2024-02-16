#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // To pass argument as a local global variable
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }
    // Opening it with fopen
    FILE *file = fopen(argv[1], "r");

    // If there is a mistake opening the file
    if (file == NULL)
    {
        printf("Could not open.\n");
        return 2;
    }

    // Creating variables needed to write, read and name images
    FILE *img = NULL;
    BYTE buffer[512];
    char filename[8];
    int counter = 0;

    while (fread(&buffer, sizeof(BYTE), 512, file) == 512)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (counter != 0)
            {
                fclose(img);
            }
            sprintf(filename, "%03i.jpg", counter);
            img = fopen(filename, "w");
            fwrite(&buffer, sizeof(BYTE), 512, img);
            counter++;
        }
        else if (counter > 0)
        {
            fwrite(&buffer, sizeof(BYTE), 512, img);
        }
    }
    // Closing files
    fclose(img);
    fclose(file);
}