// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Declaring variables
unsigned long words;
unsigned int hash_v;

// TODO: Choose number of buckets in hash table
// const unsigned int N = 10000;
#define N 10000

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int l = strlen(word);
    char w[LENGTH + 1];

    for (int i = 0; i < l; i++)
    {
        w[i] = word[i];
        w[i] = tolower(w[i]);
    }
    w[l] = '\0';

    node *n = table[hash(w)];

    while (n != NULL)
    {
        if (strcmp(w, n -> word) == 0)
        {
            return true;
        }
        n = n -> next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    hash_v = 0;
    // Hash function posted on reddit by delipity
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        hash_v = (hash_v << 2) ^ word[i];
    }
    return hash_v % N;
    //return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Opening the file of the dictionary
    FILE *file = fopen(dictionary, "r");

    // If there is errors opening it
    if (file == NULL)
    {
        printf("Unable to open");
        return false;
    }

    char buffer[LENGTH + 1];
    words = 0;

    // To scan words and put them in a node stack memory
    while (fscanf(file, "%s", buffer) != EOF)
    {
        // To calculate hash number
        hash_v = hash(buffer);

        // To use stack memory
        node *n = malloc(sizeof(node));

        // To copy the word to a value from node
        strcpy(n -> word, buffer);
        n -> next = table[hash_v];

        // Assigning the head as a linked node to the passing node
        table[hash_v] = n;
        words++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (words > 0)
    {
        return words;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *n = table[i];
        while (n != NULL)
        {
            node *n_ = n;
            n = n -> next;
            free(n_);
        }

        if (n == NULL && i == N - 1)
        {
            return true;
        }
    }
    return false;
}
