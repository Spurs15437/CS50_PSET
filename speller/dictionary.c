// Implements a dictionary's functionality
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <cs50.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

int dic_word_count = 0;
// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int afterhashnum = hash(word);
    node *n = table[afterhashnum];
    do
    {
        if (!strcasecmp(n -> word, word))
        {
            return true;
        }
        else
        {
            n = n -> next;
        }
    }
    while (n != NULL);
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

    // do some explain, the dictionary is the filename

    // do we need 初始化所有的table指针？
    // for (int i = 0; i < N; i++)
    // {
    //     table[i] = NULL;
    // }

    FILE *dic = fopen(dictionary, "r");
    if (dic == NULL)
    {
        return false;
    }
    char temp[LENGTH + 1];
    while (fgets(temp, LENGTH + 2, dic) != NULL)
    {
        dic_word_count++;
        char *find = strchr(temp, '\n');
        if (find)
        {
            *find = '\0';
        }
        node *buffer = malloc(sizeof(node));
        if (buffer == NULL)
        {
            return false;
        }
        // memset(buffer -> word, '\0', LENGTH + 1);
        strcpy(buffer -> word, temp);
        // buffer -> next = NULL;
        int hash_num = hash(temp);
        buffer -> next = table[hash_num];
        table[hash_num] = buffer;
    }
    // free(temp);
    fclose(dic);
    return true;
//     FILE *dict = fopen(dictionary, "r");
//     if (dict == NULL)
//     {
//         return false;
//     }
//
//     int dict_size = 0;
//     char word[LENGTH + 1];
//     while (fscanf(dict, "%s", word) != EOF)
//     {
//         node *n = malloc(sizeof(node));
//         if (n == NULL)
//         {
//             return false;
//         }
//         strcpy(n->word, word);
//         int num = hash(word);
//         n->next = table[num];
//         table[num] = n;
//         dict_size++;
//     }
//
//     fclose(dict);
//     return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return dic_word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    node *temp_node = NULL;
    for (int i = 0; i < N; i++)
    {
        // temp_node = table[i];
        while (table[i] != NULL)
        {
            temp_node = table[i];
            table[i] = table[i] -> next;
            free(temp_node);
            temp_node = NULL;
            // table[i] = temp
        }
        // free(table[i]);
    }
    return true;
}
