#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 512

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // check usage
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // open raw_file
    char *infile = argv[1];

    FILE *raw_file = fopen(infile, "r");
    if (raw_file == NULL)
    {
        printf("Could not open %s\n", infile);
        return 2;
    }

    // create buffer
    BYTE *buffer = malloc(BLOCK_SIZE * sizeof(BYTE));
    int number_of_file = -1;
    // loop raw_file
    while (fread(buffer, 1, BLOCK_SIZE, raw_file))
    {
        // new jpeg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            number_of_file++;
            // create file name
            char filename[10];
            sprintf(filename, "%03i.jpg", number_of_file);

            // open filename to write
            FILE *out_file = fopen(filename, "w");
            if (out_file == NULL)
            {
                printf("Could not open %s\n", filename);
                return 3;
            }
            fwrite(buffer, BLOCK_SIZE, 1, out_file);
            fclose(out_file);
        }
        else
        {
            if (number_of_file >= 0)
            {
                // create file name
                char filename[10];
                sprintf(filename, "%03i.jpg", number_of_file);

                // open filename to write
                FILE *out_file = fopen(filename, "a");
                if (out_file == NULL)
                {
                    printf("Could not open %s\n", filename);
                    return 3;
                }
                fwrite(buffer, BLOCK_SIZE, 1, out_file);
                fclose(out_file);
            }
        }
    }

    // close
    free(buffer);
    fclose(raw_file);
}