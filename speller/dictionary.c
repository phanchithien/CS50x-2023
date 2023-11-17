// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>

#include "dictionary.h"

// TODO: Choose number of buckets in hash table
const unsigned int N = LENGTH * (26 * (26 + 2)); // 26 + 2 because possibly apostrophes and null.

// Hash table
node *table[N];

int sum = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int index = hash(word);
    node *current = table[index]->next;
    while (current != NULL)
    {
        if (strcasecmp(current->word, word) == 0)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    int word0_upper = toupper(word[0]);
    int word1_upper = toupper(word[1]);
    if (word1_upper == 0) // char "null"
    {
        return strlen(word) * ((toupper(word[0]) - 'A') * 28 + 28);
    }
    else if (word1_upper == 92) // char "\"
    {
        return strlen(word) * ((toupper(word[0]) - 'A') * 28 + 27);
    }
    return strlen(word) * ((toupper(word[0]) - 'A') * 28 + (toupper(word[1]) - 'A'));
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    for (int i = 0; i < N; i++)
    {
        table[i] = malloc(sizeof(node));
        table[i]->next = NULL;
    }
    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) == 1)
    {
        int index = hash(word);
        node *new = malloc(sizeof(node));
        if (new == NULL)
        {
            unload();
            return false;
        }
        sum++;
        strcpy(new->word, word);
        new->next = table[index]->next;
        table[index]->next = new;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return sum;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        unloader(table[i]);
    }
    return true;
}

void unloader(node *current)
{
    if (current == NULL)
    {
        return;
    }
    node *tmp = current->next;
    free(current);
    current = tmp;
    unloader(current);
}
