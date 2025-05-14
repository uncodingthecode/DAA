#include <stdio.h>
#include <stdlib.h>
//include exclude wala
// Function to sort array (optional for optimization)
int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

// Utility function to print subset
void printSubset(int subset[], int size) {
    printf("Subset found: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", subset[i]);
    }
    printf("\n");
}

// Recursive backtracking function
void subsetSumUtil(int arr[], int n, int target, int* subset, int subsetSize, int index) {
    // Base case: subset sums to target
    if (target == 0) {
        printSubset(subset, subsetSize);
        return;
    }

    // Base case: exceeded target or reached end
    if (index == n || target < 0) {
        return;
    }

    // Include current element
    subset[subsetSize] = arr[index];
    subsetSumUtil(arr, n, target - arr[index], subset, subsetSize + 1, index + 1);

    // Exclude current element
    subsetSumUtil(arr, n, target, subset, subsetSize, index + 1);
}

// Main function to find all subsets with sum equal to target
void subsetSum(int arr[], int n, int target) {
    // Optional: Sort to help pruning
    qsort(arr, n, sizeof(int), compare);

    int* subset = (int*)malloc(n * sizeof(int));
    printf("Finding all subsets that sum to %d:\n", target);
    subsetSumUtil(arr, n, target, subset, 0, 0);
    free(subset);
}

// Driver program
int main() {
    int arr[] = {3, 34, 8, 12, 2, 11, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 10;

    subsetSum(arr, n, target);

    return 0;
}








// 1) Input:
// - arr[]: array of integers (positive and possibly duplicates)
// - target: desired subset sum
// - n: size of array

// 2) Algorithm:
// - Backtracking with recursion
// - Two choices per element: include or exclude
// - Optional sorting helps prune impossible paths early

// 3) Time Complexity:
// Best Case: O(n) if found immediately
// Worst Case: O(2^n), all subsets explored
// Avg Case: exponential due to recursive branching

// 4) Advantages / Disadvantages:
// + Simple and intuitive backtracking approach
// + Works well for small n or when solution exists early
// - Inefficient for large n due to exponential time
// - No space optimization for large subsets

// 5) Recurrence Relation:
// T(n) = T(n-1) + T(n-1) + O(1)
// Each call branches into two subproblems (include/exclude)

// 6) Formula Used:
// None specific; uses basic arithmetic for sum check

// 7) Summary (2 lines):
// Finds all subsets that sum to target using recursive backtracking.
// Efficient for small input sizes but not scalable for large arrays.