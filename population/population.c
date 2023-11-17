#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int start_size;
    do
    {
        start_size = get_int("start size? ");
    }
    while (start_size < 9);

    // TODO: Prompt for end size
    int end_size;
    do
    {
        end_size = get_int("end size? ");
    }
    while (end_size < start_size);

    // TODO: Calculate number of years until we reach threshold
    int required_years = 0;
    int cal_size = start_size;
    while (cal_size < end_size)
    {
        cal_size = cal_size + (cal_size / 3) - (cal_size / 4);
        required_years++;
    }

    // TODO: Print number of years
    // printf("%i\n", start_size);
    // printf("%i\n", end_size);
    printf("Years: %i\n", required_years);
}
