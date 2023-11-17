#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long number;
    number = get_long("Number: ");
    int from_last = 0;
    int from_second_last = 0;
    int first_two_digit;
    int i = 0;
    while (number > 0)
    {
        if (i % 2 == 0)
        {
            from_last += number % 10;
        }
        else
        {
            int each_one_from_second_last = (number % 10) * 2;
            if (each_one_from_second_last >= 10)
            {
                from_second_last += (each_one_from_second_last % 10) + (each_one_from_second_last / 10);
            }
            else
            {
                from_second_last += each_one_from_second_last;
            }
        }
        if (9 < number && number < 100)
        {
            first_two_digit = number;
        }
        number = number / 10;
        i++;
    }
    int length = i;
    int sum = from_last + from_second_last;
    int last_digit = sum % 10;
    if (last_digit != 0)
    {
        printf("INVALID\n");
    }
    else if (length == 15 && (first_two_digit == 34 || first_two_digit == 37))
    {
        printf("AMEX\n");
    }
    else if (length == 16 && first_two_digit <= 55 && first_two_digit >= 51)
    {
        printf("MASTERCARD\n");
    }
    else if ((length == 16 || length == 13) && (first_two_digit) / 10 == 4)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}