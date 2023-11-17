#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int main(void)
{
    string text = get_string("Text: ");
    float num_letters = count_letters(text);
    float num_words = count_words(text);
    float num_sentences = count_sentences(text);
    float L = (num_letters * 100) / num_words;
    float S = (num_sentences * 100) / num_words;
    float index = 0.0588 * L - 0.296 * S - 15.8;
    int index_round = round(index);
    if (index_round < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index_round >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index_round);
    }
}

int count_letters(string text)
{
    int sum = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            sum++;
        }
    }
    return sum;
}

int count_words(string text)
{
    int sum = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (isspace(text[i]))
        {
            if (!isspace(text[i - 1]))
            {
                sum++;
            }
        }
    }
    return sum + 1;
}

int count_sentences(string text)
{
    int sum = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sum++;
        }
    }
    return sum;
}