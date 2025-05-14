// C program for implementation of selection sort
#include <stdio.h>

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
      
        // Assume the current position holds
        // the minimum element
        int min_idx = i;
        
        // Iterate through the unsorted portion
        // to find the actual minimum
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
              
                // Update min_idx if a smaller element is found
                min_idx = j;
            }
        }
        
        // Move minimum element to its
        // correct position
        int temp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = temp;
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {64, 25, 12, 22, 11};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("Original array: ");
    printArray(arr, n);
    
    selectionSort(arr, n);
    
    printf("Sorted array: ");
    printArray(arr, n);
    
    return 0;
}
























// 1) Input:
// - An array of integers (arr[]) of size 'n'

// 2) Algorithm:
// Selection Sort:
// - Repeatedly find minimum element from unsorted part
// - Swap it with the first unsorted element
// - Move boundary of sorted/unsorted sections

// 3) Time Complexity:
// Best/Avg/Worst Case: O(n^2)
// Two nested loops: outer runs n times, inner ~n/2 comparisons

// 4) Space Complexity:
// - O(1), in-place sorting with only constant extra space

// 5) Advantages / Disadvantages:
// + Simple and easy to implement
// + Minimal swaps (only O(n))
// + Good for small datasets
// - Inefficient for large datasets due to quadratic time

// 6) Recurrence Relation:
// T(n) = T(n-1) + O(n), where O(n) is time to find min in remaining array
// Solves to T(n) = O(n^2)

// 7) Summary (2 lines):
// Efficient in swaps but inefficient in comparisons.
// Best suited for small arrays or memory-constrained systems.
