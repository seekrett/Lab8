// This program returns indices of two numbers in an array of integers such
// that they add up to a specific target.

// include statements
#include <stdio.h>

// finds two numbers that add up to the target
// returns 1 if found, 0 if not
int twoSumNested(int* nums, int numsSize, int target, int* index1, int* index2) {
    // Outer loop goes through each element
    for (int i = 0; i < numsSize - 1; i++) {
        // Inner loop checks all elements after current one
        for (int j = i + 1; j < numsSize; j++) {
            // Check if pair sums to target
            if (nums[i] + nums[j] == target) {
                *index1 = i;
                *index2 = j;
                return 1; // Success
            }
        }
    }
    return 0; // No solution found
}

int main() {
    int nums[] = {2, 7, 11, 15};
    int target = 9;
    int index1, index2;
    
    if (twoSumNested(nums, 4, target, &index1, &index2)) {
        printf("Solution found at indices: [%d, %d]\n", index1, index2);
    } else {
        printf("No solution found.\n");
    }
    
    return 0;
}