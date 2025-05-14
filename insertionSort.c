// C program for implementation of Insertion Sort
#include <stdio.h>

/* Function to sort array using insertion sort */
void insertionSort(int arr[], int n)
{
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;

        /* Move elements of arr[0..i-1], that are
           greater than key, to one position ahead
           of their current position */
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

/* A utility function to print array of size n */
void printArray(int arr[], int n)
{
    for (int i = 0; i < n; ++i)
        printf("%d ", arr[i]);
    printf("\n");
}

// Driver method
int main()
{
    int arr[] = { 12, 11, 13, 5, 6 };
    int n = sizeof(arr) / sizeof(arr[0]);

    insertionSort(arr, n);
    printArray(arr, n);

    return 0;
}













// 1) Input:
// - An array of integers (arr[]) of size n

// 2) Algorithm:
// - Start from the second element
// - Insert current element into correct position in sorted prefix (left side)
// - Shift larger elements to the right to make space

// 3) Time Complexity:
// Best Case: O(n) — already sorted
// Worst Case: O(n^2) — reverse sorted
// Average Case: O(n^2)

// 4) Space Complexity:
// - O(1), in-place sorting with no extra memory

// 5) Advantages / Disadvantages:
// + Simple and easy to implement
// + Efficient for small or nearly sorted arrays
// + Stable and in-place
// - Inefficient for large datasets

// 6) Recurrence Relation:
// T(n) = T(n-1) + O(n), where O(n) is time to insert nth element

// 7) Summary (2 lines):
// Efficient for small or nearly-sorted data.
// Simple comparison-based in-place sorting algorithm with quadratic time.
