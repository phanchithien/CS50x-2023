#include <cs50.h>
#include <stdint.h>
#include <stdio.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Inproper usage.\n");
        return 1;
    }

    // Open file
    string filename = argv[1];
    FILE *file = fopen(filename, "r");

    // Check if file exists
    if (file == NULL)
    {
        printf("No such file found.\n");
        return 1;
    }

    uint8_t buffer[4];
    uint8_t signature[] = {37, 80, 68, 70};
    bool isPdf = true;
    fread(buffer, 1, 4, file);

    for (int i = 0; i < sizeof(buffer); i++)
    {
        if (buffer[i] != signature[i])
        {
            isPdf = false;
        }
        printf("%i ", buffer[i]);
    }
    printf("\n");
    if (isPdf) {
        printf("This is pdf file.\n");
    } else {
        printf("This is not pdf file.\n");
    }

    fclose(file);
    return 0;
}