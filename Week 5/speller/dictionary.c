// Implements a dictionary's functionality
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <strings.h>
#include <string.h>
#include "dictionary.h"

FILE * file;
int num_words = 0;
char ch;


// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int hash_key = hash(word);

    node *tmp = table[hash_key];

    while (tmp != NULL)
    {
        if (strcasecmp(word, tmp->word) == 0)
        {
            return true;
        }

        tmp = tmp->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    char word_buffer[LENGTH + 1];
    file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    else
    {
        while (fscanf(file, "%s\n", word_buffer) != EOF)
        {
            node *new_word = malloc(sizeof(node));
            if (new_word == NULL)
            {
                return false;
            }

            strcpy(new_word->word, word_buffer);

            int scramble = hash(new_word->word);

            if (table[scramble] == NULL)
            {
                table[scramble] = new_word;
                new_word->next = NULL;
            }
            else
            {
                new_word->next = table[scramble];
                table[scramble] = new_word;

            }
            num_words++;
        }
        fclose(file);

        return true;
    }
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    // if the file is empty
    return num_words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];

        while(cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }

        if (cursor == NULL)
        {
            return true;
        }
    }
    return false;
}
