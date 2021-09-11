// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 100000;

// Hash table
node *table[N];

// Size of dictionary, word counter
int dictSize = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // Use hash() on word to get the hash value
    int hashValue = hash(word);

    // Access the index in the hash table
    node *n = table[hashValue];

    // Traverse linked list to see if word is in the list
    while (n != NULL)
    {
        if (strcasecmp(word, n->word) == 0)
        {
            return true;
        }

        n = n->next;
    }

    return false;
}

// Hashes word to a number
int PRIME[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
unsigned int hash(const char *word)
{
    // TODO
    // Sum of the word to start at 0
    long sum = 0;

    // Iterate through the word
    for (int i = 0; i < strlen(word); i++)
    {
        sum += PRIME[tolower(word[i])];
    }
    return sum % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open dictionary file
    FILE *dictPointer = fopen(dictionary, "r");

    // Check if NULL - return false
    if (dictionary == NULL)
    {
        printf("Unable to open %s\n", dictionary);
        return false;
    }

    // Initialise word store array
    char nextWord[LENGTH + 1];

    // Scan through file
    while (fscanf(dictPointer, "%s", nextWord) != EOF)
    {
        // Create new node and allocate memory for each word
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }

        // Copy words into nodes
        strcpy(n->word, nextWord);

        // Get the hash value
        int hashValue = hash(nextWord);

        // Inset node into hash table at the hash values location
        n->next = table[hashValue];
        table[hashValue] = n;
        dictSize++;
    }

    // Close file
    fclose(dictPointer);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return dictSize;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // Iterate over has table and free nodes in each linked list
    for (int i = 0; i < N; i++)
    {
        // Pointer
        node *n = table[i];

        // Loop through linked list
        while (n != NULL)
        {
            // Temp pointer that is equal to the original pointer
            node *tmp = n;

            // Point orginal pointer to the next node
            n = n->next;

            // Free temp pointer
            free(tmp);
        }

        if (n == NULL && i == N - 1)
        {
            return true;
        }
    }
    return false;
}
