// C program for Merge Sort
#include <stdio.h>
#include <stdlib.h>

// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temp arrays
    int L[n1], R[n2];

    // Copy data to temp arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge the temp arrays back into arr[l..r
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[],
    // if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[],
    // if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// l is for left index and r is right index of the
// sub-array of arr to be sorted
void mergeSort(int arr[], int l, int r)
{
    if (l < r) {
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

// Function to print an array
void printArray(int A[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}

// Driver code
int main()
{
    int arr[] = { 12, 11, 13, 5, 6, 7 };
    int arr_size = sizeof(arr) / sizeof(arr[0]);

    printf("Given array is \n");
    printArray(arr, arr_size);

    mergeSort(arr, 0, arr_size - 1);

    printf("\nSorted array is \n");
    printArray(arr, arr_size);
    return 0;
}

















// 1) Input:
// - An array of integers (arr[]) of size 'size'
// - Left and right indices to define subarray range

// 2) Algorithm:
// Merge Sort:
// - Divide: Split array into two halves
// - Conquer: Recursively sort each half
// - Combine: Merge two sorted halves into one sorted array

// 3) Time Complexity:
// Best/Avg/Worst Case: O(n log n)
// - Always splits in O(log n), merging takes O(n)

// 4) Space Complexity:
// - O(n), due to temporary arrays used in merge step
// - O(log n) auxiliary space for recursion stack

// 5) Advantages / Disadvantages:
// + Stable sort (preserves input order of equal elements)
// + Guaranteed O(n log n) performance
// + Good for linked lists and large datasets
// - Extra memory usage (not in-place)
// - Slower than quicksort in practice for small arrays

// 6) Recurrence Relation:
// T(n) = 2T(n/2) + O(n)
// Solves to T(n) = O(n log n)

// 7) Summary (2 lines):
// Efficient, stable sorting algorithm with guaranteed O(n log n) time.
// Uses divide-and-conquer approach with extra memory for merging.