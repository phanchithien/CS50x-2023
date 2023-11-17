#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{

    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // handle key
    int len_key = 26;
    string key = argv[1];
    string invalid_key = "Key must contain 26 characters.";
    if (strlen(key) != len_key)
    {
        printf("%s\n", invalid_key);
        return 1;
    }
    for (int i = 0; i < len_key; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("%s\n", invalid_key);
            return 1;
        }
        for (int j = i + 1; j < len_key; j++)
        {
            if (key[i] == key[j])
            {
                printf("%s\n", invalid_key);
                return 1;
            }
        }
    }

    // encode
    string plaintext = get_string("plaintext: ");
    string ciphertext = plaintext;

    for (int i = 0; i < strlen(plaintext); i++)
    {
        if (isalpha(plaintext[i]))
        {
            if (isupper(plaintext[i]))
            {
                ciphertext[i] = toupper(key[plaintext[i] - 65]);
            }
            else
            {
                ciphertext[i] = tolower(key[plaintext[i] - 97]);
            }
        }
        else
        {
            ciphertext[i] = plaintext[i]; // not alphabet
        }
    }

    printf("ciphertext: %s\n", ciphertext);

    return 0;
}

void handle_key(string key) {}