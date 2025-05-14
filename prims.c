#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define V 5  // Number of vertices

// ================== Array-Based Version ===================

int minKey(int key[], int mstSet[]) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++)
        if (mstSet[v] == 0 && key[v] < min)
            min = key[v], min_index = v;
    return min_index;
}

void printMST_Array(int parent[], int graph[V][V]) {
    printf("Edge \tWeight\n");
    for (int i = 1; i < V; i++)
        printf("%d - %d \t%d\n", parent[i], i, graph[i][parent[i]]);
}

void primMST_Array(int graph[V][V]) {
    int parent[V];
    int key[V];
    int mstSet[V];

    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        mstSet[i] = 0;
    }

    key[0] = 0;
    parent[0] = -1;

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

    printMST_Array(parent, graph);
}

// ================== Heap-Based Version ===================

typedef struct {
    int vertex;
    int weight;
} Node;

typedef struct {
    int size;
    Node* heap;
} MinHeap;

int* pos;

void swap(Node* a, Node* b) {
    Node temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size &&
        minHeap->heap[left].weight < minHeap->heap[smallest].weight)
        smallest = left;

    if (right < minHeap->size &&
        minHeap->heap[right].weight < minHeap->heap[smallest].weight)
        smallest = right;

    if (smallest != idx) {
        pos[minHeap->heap[smallest].vertex] = idx;
        pos[minHeap->heap[idx].vertex] = smallest;
        swap(&minHeap->heap[smallest], &minHeap->heap[idx]);
        minHeapify(minHeap, smallest);
    }
}

Node extractMin(MinHeap* minHeap) {
    if (minHeap->size == 0)
        return (Node){-1, -1};

    Node root = minHeap->heap[0];
    Node lastNode = minHeap->heap[minHeap->size - 1];
    pos[root.vertex] = -1;
    pos[lastNode.vertex] = 0;
    minHeap->heap[0] = lastNode;
    minHeap->size--;
    minHeapify(minHeap);
    return root;
}

void decreaseKey(MinHeap* minHeap, int v, int newWeight) {
    int i = pos[v];
    minHeap->heap[i].weight = newWeight;

    while (i && minHeap->heap[i].weight < minHeap->heap[(i - 1) / 2].weight) {
        pos[minHeap->heap[i].vertex] = (i - 1) / 2;
        pos[minHeap->heap[(i - 1) / 2].vertex] = i;
        swap(&minHeap->heap[i], &minHeap->heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->size = 0;
    minHeap->heap = (Node*)malloc(capacity * sizeof(Node));
    return minHeap;
}

typedef struct {
    int dest;
    int weight;
} AdjListNode;

typedef struct {
    AdjListNode* head;
} AdjList;

typedef struct {
    int V;
    AdjList* array;
} Graph;

Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->array = (AdjList*)malloc(V * sizeof(AdjList));
    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;
    return graph;
}

void addEdge(Graph* graph, int src, int dest, int weight) {
    AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    newNode->dest = src;
    newNode->weight = weight;
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

void printMST_Heap(int parent[], int key[]) {
    printf("Edge \tWeight\n");
    for (int i = 1; i < V; i++)
        printf("%d - %d \t%d\n", parent[i], i, key[i]);
}

void primMST_Heap(Graph* graph) {
    int V_graph = graph->V;
    int* parent = (int*)malloc(V_graph * sizeof(int));
    int* key = (int*)malloc(V_graph * sizeof(int));
    pos = (int*)malloc(V_graph * sizeof(int));

    MinHeap* minHeap = createMinHeap(V_graph);

    for (int v = 0; v < V_graph; ++v) {
        key[v] = INT_MAX;
        minHeap->heap[v].vertex = v;
        minHeap->heap[v].weight = key[v];
        pos[v] = v;
    }

    minHeap->size = V_graph;
    key[0] = 0;
    decreaseKey(minHeap, 0, key[0]);

    while (minHeap->size > 0) {
        Node u = extractMin(minHeap);
        AdjListNode* pCrawl = graph->array[u.vertex].head;

        while (pCrawl != NULL) {
            int v = pCrawl->dest;
            if (pos[v] != -1 && pCrawl->weight < key[v]) {
                key[v] = pCrawl->weight;
                parent[v] = u.vertex;
                decreaseKey(minHeap, v, key[v]);
            }
            pCrawl = pCrawl->next;
        }
    }

    printMST_Heap(parent, key);

    free(parent);
    free(key);
    free(pos);
    free(minHeap->heap);
    free(minHeap);
}

// ================== Main Function with User Choice ===================

int main() {
    int choice;

    printf("Choose Implementation:\n");
    printf("1. Array-based Prim's (Adjacency Matrix)\n");
    printf("2. Heap-based Prim's (Min-Heap + Adjacency List)\n");
    printf("Enter choice (1 or 2): ");
    scanf("%d", &choice);

    if (choice == 1) {
        int graph[V][V] = {
            {0, 2, 0, 6, 0},
            {2, 0, 3, 8, 5},
            {0, 3, 0, 0, 7},
            {6, 8, 0, 0, 9},
            {0, 5, 7, 9, 0}
        };

        printf("\nRunning Array-based Prim's Algorithm:\n");
        primMST_Array(graph);
    } else if (choice == 2) {
        Graph* graph = createGraph(V);
        addEdge(graph, 0, 1, 2);
        addEdge(graph, 0, 3, 6);
        addEdge(graph, 1, 2, 3);
        addEdge(graph, 1, 3, 8);
        addEdge(graph, 1, 4, 5);
        addEdge(graph, 2, 4, 7);
        addEdge(graph, 3, 4, 9);

        printf("\nRunning Heap-based Prim's Algorithm:\n");
        primMST_Heap(graph);
    } else {
        printf("Invalid choice.\n");
    }

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