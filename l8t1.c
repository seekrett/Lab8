// This program constructs a hash table.

// include statements
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLESIZE 100

// Define {key, value} structure
typedef struct {
    // attributes
    char key;
    char value;
} KeyValuePair;
// name of struct

// Define the Hash Table structure
typedef struct {
    // attributes
    KeyValuePair** items;
    int size;
    int count;
} HashTable;
// name of struct

// Create {key, value} pairs
KeyValuePair* createKeyValuePair(const char* key, const char* value) {
    // allocate memory
    KeyValuePair* pair = (KeyValuePair*) malloc(sizeof(KeyValuePair));

    // similar to class.attribute
    pair->key = strdup(key);
    pair->value = strdup(value);
    return pair;
}

// Create the Hash Table. [Hint: you need to allocate memory for the Hash Table, and set all {key, value}
// pairs to NULL since they are not used) 
HashTable* createHashTable() {
    // allocate memory
    HashTable* hashtable = (HashTable*) malloc(sizeof(HashTable));

    // set all pairs to NULL
    for (int i = 0; i < TABLESIZE; i++) {
        hashtable->items[i] = NULL;
    }

    return hashtable;
}

// Define a function to free up the memory of a {key, value} pair. 
void freePair(KeyValuePair* pair) {
    // check if NULL
    if (pair) {
        free(pair->key);
        free(pair->value);
        free(pair);
    }
}