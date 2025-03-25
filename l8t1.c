// This program constructs a hash table

// include statements
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLESIZE 500

// Define {key, value} structure
typedef struct {
    char* key;
    char* value;
} KeyValuePair;

// Define the Hash Table structure
typedef struct {
    KeyValuePair** items;
    int size;
    int count;
} HashTable;

// Create {key, value} pairs
KeyValuePair* createKeyValuePair(const char* key, const char* value) {
    // Allocate memory for KeyValuePair
    KeyValuePair* pair = (KeyValuePair*) malloc(sizeof(KeyValuePair));

    // Allocate memory for the key and value strings
    pair->key = strdup(key);
    pair->value = strdup(value);
    return pair;
}

// Create the Hash Table
HashTable* createHashTable() {
    // Allocate memory for the HashTable
    HashTable* hashtable = (HashTable*) malloc(sizeof(HashTable));
    hashtable->size = TABLESIZE;
    hashtable->count = 0;

    // Allocate memory for the array of items
    hashtable->items = (KeyValuePair**) malloc(sizeof(KeyValuePair*) * TABLESIZE);

    // Initialize all table slots to NULL
    for (int i = 0; i < TABLESIZE; i++) {
        hashtable->items[i] = NULL;
    }

    return hashtable;
}

// Free up the memory of a {key, value} pair
void freeKeyValuePair(KeyValuePair* pair) {
    if (pair) {
        free(pair->key);
        free(pair->value);
        free(pair);
    }
}

// Free up the memory of the Hash Table
void freeHashTable(HashTable* hashtable) {
    // Free each item in the hash table
    for (int i = 0; i < TABLESIZE; i++) {
        if (hashtable->items[i]) {
            freeKeyValuePair(hashtable->items[i]);
        }
    }
    // Free the array of items
    free(hashtable->items);
    // Free the hash table itself
    free(hashtable);
}

// Hash function to get the index for a {key, value} pair in the Hash Table
unsigned int hashFunction(const char* key) {
    unsigned long int value = 0;
    unsigned int keyLength = strlen(key);

    for (unsigned int i = 0; i < keyLength; ++i) {
        value = value * 37 + key[i];
    }

    // Wrap around to fit within table size
    return value % TABLESIZE;
}

// Insert function to insert a {key, value} pair into the Hash Table
void insert(HashTable* hashtable, const char* key, const char* value) {
    unsigned int i = hashFunction(key);

    // Create a {key, value} pair
    if (hashtable->items[i] == NULL) {
        // No collision, insert directly
        hashtable->items[i] = createKeyValuePair(key, value);
    } else {
        // Collision handling
        if (strcmp(hashtable->items[i]->key, key) == 0) {
            // Update value if key already exists
            free(hashtable->items[i]->value);
            hashtable->items[i]->value = strdup(value);
        } else {
            // Collision detected, print error message
            printf("Collision at index %d for key: %s. Overflow error!\n", i, key);
        }
    }
}

// Delete a {key, value} pair from the Hash Table
void delete(HashTable* hashtable, const char* key) {
    unsigned int i = hashFunction(key);

    if (hashtable->items[i] != NULL && strcmp(hashtable->items[i]->key, key) == 0) {
        // Key found, free the memory and set to NULL
        freeKeyValuePair(hashtable->items[i]);
        hashtable->items[i] = NULL;
    } else {
        printf("Key not found: %s\n", key);
    }
}

// Search function to check if the key exists or not, return value if found
char* search(HashTable* hashtable, const char* key) {
    unsigned int i = hashFunction(key);

    if (hashtable->items[i] != NULL && strcmp(hashtable->items[i]->key, key) == 0) {
        return hashtable->items[i]->value;
    }

    return NULL;
}

// Function to display the search result
void displaySearchResult(HashTable* hashtable, const char* key) {
    char* value = search(hashtable, key);
    if (value) {
        printf("KEY: %s\tVALUE: %s\n", key, value);
    } else {
        printf("KEY: %s not found\n", key);
    }
}

// Display the entire Hash Table
void displayHashTable(HashTable* hashtable) {
    printf("INDEX\tKEY\tVALUE\n");
    for (int i = 0; i < TABLESIZE; i++) {
        if (hashtable->items[i] != NULL) {
            printf("%d\t%s\t%s\n", i, hashtable->items[i]->key, hashtable->items[i]->value);
        }
    }
}

// Main function for testing
int main() {
    HashTable* hashtable = createHashTable();

    // Insert key-value pairs
    insert(hashtable, "name", "Alice");
    insert(hashtable, "age", "25");
    insert(hashtable, "city", "Wonderland");

    // Display the hash table contents
    printf("--- HASH TABLE CONTENTS ---\n");
    displayHashTable(hashtable);

    // Display search results
    printf("--- SEARCH RESULTS ---\n");
    displaySearchResult(hashtable, "name");
    displaySearchResult(hashtable, "age");
    displaySearchResult(hashtable, "country");

    // Delete a key-value pair and display the table again
    delete(hashtable, "age");
    printf("--- HASH TABLE CONTENTS (modified) ---\n");
    displayHashTable(hashtable);

    // Free up memory used by the hash table
    freeHashTable(hashtable);

    return 0;
}
