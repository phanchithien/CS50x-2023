#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    for (int i = height; i > 0; i--)
    {
        for (int j = 1; j <= height; j++)
        {
            if (j >= i)
            {
                printf("#");
            }
            else
            {
                printf(" ");
            }
        }

        printf("  ");

        for (int k = height; k > 0; k--)
        {
            if (k >= i)
            {
                printf("#");
            }
            else
            {
                continue;
            }
        }
        printf("\n");
    }
}