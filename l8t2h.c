#include <stdio.h>
#include <stdlib.h>

#define TABLESIZE 500

// Modified to store integers for the two sum problem
typedef struct {
    int key;    // The number from array (original key)
    int value;  // Its index in array (original value)
} KeyValuePair;

// Hash Table structure remains the same
typedef struct {
    KeyValuePair** items;
    int size;
    int count;
} HashTable;

// Create {key, value} pairs - modified for integers
KeyValuePair* createKeyValuePair(int key, int value) {
    KeyValuePair* pair = (KeyValuePair*) malloc(sizeof(KeyValuePair));
    pair->key = key;
    pair->value = value;
    return pair;
}

// Create the Hash Table - unchanged
HashTable* createHashTable() {
    HashTable* hashtable = (HashTable*) malloc(sizeof(HashTable));
    hashtable->size = TABLESIZE;
    hashtable->count = 0;
    hashtable->items = (KeyValuePair**) malloc(sizeof(KeyValuePair*) * TABLESIZE);
    
    for (int i = 0; i < TABLESIZE; i++) {
        hashtable->items[i] = NULL;
    }
    return hashtable;
}

// Free up memory - simplified since we don't have strings now
void freeKeyValuePair(KeyValuePair* pair) {
    free(pair);
}

// Free Hash Table - unchanged
void freeHashTable(HashTable* hashtable) {
    for (int i = 0; i < TABLESIZE; i++) {
        if (hashtable->items[i]) {
            freeKeyValuePair(hashtable->items[i]);
        }
    }
    free(hashtable->items);
    free(hashtable);
}

// Hash function modified for integer keys
unsigned int hashFunction(int key) {
    // Simple hash function for integers
    return abs(key) % TABLESIZE;
}

// Insert function modified for integers
void insert(HashTable* hashtable, int key, int value) {
    unsigned int i = hashFunction(key);

    if (hashtable->items[i] == NULL) {
        // No collision, insert directly
        hashtable->items[i] = createKeyValuePair(key, value);
    } else {
        // Collision handling - in this problem, we can assume unique numbers
        printf("Collision at index %d for key: %d. Overflow error!\n", i, key);
    }
}

// Search function modified for integers, returns value (index) if found, -1 otherwise
int search(HashTable* hashtable, int key) {
    unsigned int i = hashFunction(key);

    if (hashtable->items[i] != NULL && hashtable->items[i]->key == key) {
        return hashtable->items[i]->value;
    }
    return -1;
}

// Two Sum solution using the hash table
int twoSumHash(int* nums, int numsSize, int target, int* index1, int* index2) {
    HashTable* hashtable = createHashTable();
    
    for (int i = 0; i < numsSize; i++) {
        int complement = target - nums[i];
        int complementIndex = search(hashtable, complement);
        
        if (complementIndex != -1) {
            *index1 = complementIndex;
            *index2 = i;
            freeHashTable(hashtable);
            return 1; // Success
        }
        
        insert(hashtable, nums[i], i);
    }
    
    freeHashTable(hashtable);
    return 0; // No solution found
}

// Main function for testing the two sum solution
int main() {
    int nums[] = {2, 7, 11, 15};
    int target = 9;
    int index1, index2;
    
    if (twoSumHash(nums, 4, target, &index1, &index2)) {
        printf("Solution found at indices: [%d, %d]\n", index1, index2);
    } else {
        printf("No solution found.\n");
    }
    
    return 0;
}