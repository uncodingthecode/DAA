#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define V 5  // Number of vertices

int minKey(int key[], int mstSet[]) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++)
        if (mstSet[v] == 0 && key[v] < min)
            min = key[v], min_index = v;
    return min_index;
}

void printMST(int parent[], int graph[V][V]) {
    printf("Edge \tWeight\n");
    for (int i = 1; i < V; i++)
        printf("%d - %d \t%d\n", parent[i], i, graph[i][parent[i]]);
}

void primMST(int graph[V][V]) {
    int parent[V];   // Stores constructed MST
    int key[V];      // Used to pick minimum weight edge
    int mstSet[V];   // To represent set of vertices included in MST

    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        mstSet[i] = 0;
    }

    key[0] = 0;      // Start from the first vertex
    parent[0] = -1;  // First node is always the root

    for (int count = 0; count < V - 1; count++) {
        int u = minKey(key, mstSet);
        mstSet[u] = 1;

        for (int v = 0; v < V; v++) {
            if (graph[u][v] && mstSet[v] == 0 && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    printMST(parent, graph);
}

int main() {
    int graph[V][V] = {
        {0, 2, 0, 6, 0},
        {2, 0, 3, 8, 5},
        {0, 3, 0, 0, 7},
        {6, 8, 0, 0, 9},
        {0, 5, 7, 9, 0}
    };
    printf("Running Array-based Prim's Algorithm:\n");
    primMST(graph);
    return 0;
}






















//gcc -std=c99 prim.c -o prim
//./prim






// 1) Input:
// - Undirected weighted graph:
//   a) For array version: V x V adjacency matrix
//   b) For heap version: adjacency list with edge weights
// - V = number of vertices

// 2) Algorithm:
// Prim's Minimum Spanning Tree:
// Array-based:
// - Use key[] to store min edge weight to connect vertex
// - Use mstSet[] to track included vertices
// - Pick minimum key in O(V) time each iteration → O(V^2)
// Heap-based:
// - Min-heap (priority queue) to extract min key in O(log V)
// - Adjacency list traversal per node → total O(E log V)

// 3) Time Complexity:
// Array-based: O(V^2), good for dense graphs
// Heap-based: O(E log V), better for sparse graphs

// 4) Space Complexity:
// Array-based: O(V), due to arrays only
// Heap-based: O(V + E), due to adjacency list and heap

// 5) Advantages / Disadvantages:
// Array-based:
// + Simple and fast for small/dense graphs
// - Slower for large/sparse graphs due to O(V^2)
// Heap-based:
// + Faster for sparse graphs (O(E log V))
// + More complex with memory management

// 6) Recurrence Relation:
// Array version: T(V) = V * V = O(V^2)
// Heap version: T(V) = O(V log V) + O(E log V) = O((V + E) log V)

// 7) Summary (2 lines):
// Implements two versions of Prim's algorithm for MST.
// Array-based is simpler; heap-based is more efficient for sparse graphs.
