#include <stdio.h>

void swap(int* a, int* b);

// Partition function
int partition(int arr[], int low, int high) {
    
    // Choose the pivot
    int pivot = arr[high];
    
    // Index of smaller element and indicates 
    // the right position of pivot found so far
    int i = low - 1;

    // Traverse arr[low..high] and move all smaller
    // elements to the left side. Elements from low to 
    // i are smaller after every iteration
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    
    // Move pivot after smaller elements and
    // return its position
    swap(&arr[i + 1], &arr[high]);  
    return i + 1;
}

// The QuickSort function implementation
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        
        // pi is the partition return index of pivot
        int pi = partition(arr, low, high);

        // Recursion calls for smaller elements
        // and greater or equals elements
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int main() {
    int arr[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    quickSort(arr, 0, n - 1);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    
    return 0;
}





















// 1) Input:
// - An array of integers (arr[]) of size 'n'
// - Range of indices to sort: low and high

// 2) Algorithm:
// QuickSort:
// - Divide and Conquer approach
// - Pick pivot (last element), partition array around pivot
// - Recursively sort left and right partitions

// 3) Time Complexity:
// Best Case: O(n log n) — balanced partition
// Worst Case: O(n^2) — already sorted or reverse-sorted input
// Avg Case: O(n log n)

// 4) Space Complexity:
// - O(log n) average (due to recursion stack)
// - Not in-place if stack space considered

// 5) Advantages / Disadvantages:
// + Fast in practice with small memory footprint
// + In-place sorting (no extra memory needed)
// - Unstable sort (doesn’t preserve order of equal elements)
// - Worst-case performance is poor without randomization

// 6) Recurrence Relation:
// Best/Avg Case: T(n) = T(k) + T(n-k-1) + O(n), where k = pivot index
// Worst Case: T(n) = T(n-1) + O(n) → O(n^2)

// 7) Summary (2 lines):
// Efficient divide-and-conquer sorting algorithm.
// Fast in practice but degrades to O(n²) for bad pivots.