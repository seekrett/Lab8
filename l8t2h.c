#include <stdio.h>
#include <stdlib.h>

// Simple hash table implementation for this specific problem
#define HASH_SIZE 100

typedef struct HashNode {
    int key;    // The number from array
    int value;  // Its index in array
    struct HashNode* next;
} HashNode;

// Hash function (simple modulo for demonstration)
int hash(int key) {
    return abs(key) % HASH_SIZE;
}

// Insert into hash table
void insert(HashNode** hashTable, int key, int value) {
    int index = hash(key);
    HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
    newNode->key = key;
    newNode->value = value;
    newNode->next = hashTable[index];
    hashTable[index] = newNode;
}

// Search in hash table
int search(HashNode** hashTable, int key) {
    int index = hash(key);
    HashNode* current = hashTable[index];
    while (current != NULL) {
        if (current->key == key) {
            return current->value; // Return the index
        }
        current = current->next;
    }
    return -1; // Not found
}

// Free hash table memory
void freeHashTable(HashNode** hashTable) {
    for (int i = 0; i < HASH_SIZE; i++) {
        HashNode* current = hashTable[i];
        while (current != NULL) {
            HashNode* temp = current;
            current = current->next;
            free(temp);
        }
    }
}

int twoSumHash(int* nums, int numsSize, int target, int* index1, int* index2) {
    HashNode* hashTable[HASH_SIZE] = {NULL};
    
    for (int i = 0; i < numsSize; i++) {
        int complement = target - nums[i];
        int complementIndex = search(hashTable, complement);
        
        if (complementIndex != -1) {
            *index1 = complementIndex;
            *index2 = i;
            freeHashTable(hashTable);
            return 1; // Success
        }
        
        insert(hashTable, nums[i], i);
    }
    
    freeHashTable(hashTable);
    return 0; // No solution found
}

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