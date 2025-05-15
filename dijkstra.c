#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Node structure for adjacency list
typedef struct Node {
    int dest, weight;
    struct Node* next;
} Node;

typedef struct {
    int V;
    Node** adj;
} Graph;

Node* newNode(int dest, int weight) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->dest = dest;
    node->weight = weight;
    node->next = NULL;
    return node;
}

Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->adj = (Node**)malloc(V * sizeof(Node*));
    for (int i = 0; i < V; ++i)
        graph->adj[i] = NULL;
    return graph;
}

void addEdge(Graph* graph, int src, int dest, int weight) {
    Node* node = newNode(dest, weight);
    node->next = graph->adj[src];
    graph->adj[src] = node;
}

typedef struct {
    int vertex, dist;
} MinHeapNode;

typedef struct {
    int size, capacity;
    int* pos;
    MinHeapNode* array;
} MinHeap;

MinHeap* createMinHeap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->capacity = capacity;
    heap->size = 0;
    heap->pos = (int*)malloc(capacity * sizeof(int));
    heap->array = (MinHeapNode*)malloc(capacity * sizeof(MinHeapNode));
    return heap;
}

void swapMinHeapNode(MinHeapNode* a, MinHeapNode* b) {
    MinHeapNode t = *a;
    *a = *b;
    *b = t;
}

void heapify(MinHeap* heap, int i) {
    int smallest = i, l = 2*i+1, r = 2*i+2;

    if (l < heap->size && heap->array[l].dist < heap->array[smallest].dist)
        smallest = l;
    if (r < heap->size && heap->array[r].dist < heap->array[smallest].dist)
        smallest = r;

    if (smallest != i) {
        heap->pos[heap->array[smallest].vertex] = i;
        heap->pos[heap->array[i].vertex] = smallest;
        swapMinHeapNode(&heap->array[i], &heap->array[smallest]);
        heapify(heap, smallest);
    }
}

int isEmpty(MinHeap* heap) {
    return heap->size == 0;
}

MinHeapNode extractMin(MinHeap* heap) {
    MinHeapNode root = heap->array[0];
    MinHeapNode lastNode = heap->array[heap->size - 1];
    heap->array[0] = lastNode;

    heap->pos[root.vertex] = heap->size-1;
    heap->pos[lastNode.vertex] = 0;

    --heap->size;
    heapify(heap, 0);

    return root;
}

void decreaseKey(MinHeap* heap, int v, int dist) {
    int i = heap->pos[v];
    heap->array[i].dist = dist;

    while (i && heap->array[i].dist < heap->array[(i-1)/2].dist) {
        heap->pos[heap->array[i].vertex] = (i-1)/2;
        heap->pos[heap->array[(i-1)/2].vertex] = i;
        swapMinHeapNode(&heap->array[i], &heap->array[(i-1)/2]);
        i = (i-1)/2;
    }
}

void dijkstra(Graph* graph, int src) {
    int V = graph->V;
    int dist[V];

    MinHeap* heap = createMinHeap(V);

    for (int v = 0; v < V; v++) {
        dist[v] = INT_MAX;
        heap->array[v] = (MinHeapNode){v, INT_MAX};
        heap->pos[v] = v;
    }

    heap->array[src].dist = 0;
    dist[src] = 0;
    decreaseKey(heap, src, 0);
    heap->size = V;

    while (!isEmpty(heap)) {
        MinHeapNode minNode = extractMin(heap);
        int u = minNode.vertex;

        Node* temp = graph->adj[u];
        while (temp) {
            int v = temp->dest;

            if (heap->pos[v] < heap->size && dist[u] != INT_MAX &&
                dist[u] + temp->weight < dist[v]) {
                dist[v] = dist[u] + temp->weight;
                decreaseKey(heap, v, dist[v]);
            }
            temp = temp->next;
        }
    }

    printf("Vertex\tDistance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d\t\t%d\n", i, dist[i]);
}

int main() {
    Graph* graph = createGraph(5);
    addEdge(graph, 0, 1, 9);
    addEdge(graph, 0, 2, 6);
    addEdge(graph, 0, 3, 5);
    addEdge(graph, 0, 4, 3);
    addEdge(graph, 2, 1, 2);
    addEdge(graph, 2, 3, 4);
    addEdge(graph, 2, 4, 2);
    addEdge(graph, 3, 1, 1);
    addEdge(graph, 4, 1, 7);

    printf("\nRunning Dijkstra's Algorithm:\n");
    dijkstra(graph, 0);

    return 0;
}


















































/*
1) Input:
- Directed graph with weighted edges
- For Dijkstra: all edge weights must be positive
- Source vertex for shortest path calculation

2) Algorithm:
- Min-heap based greedy approach
- Always selects closest unvisited node
- Updates distances of adjacent nodes

3) Time Complexity:
Dijkstra: O(E log V) with min-heap

4) Space Complexity:
O(V + E), for heap and adjacency list

5) Advantages / Disadvantages:
+ Fast with heap optimization
- Fails with negative edge weights

6) Recurrence Relation:
Not applicable (greedy with priority queue)

7) Summary (2 lines):
Implements Dijkstra for graphs with positive edges.
Finds shortest paths using greedy heap-based updates.
*/
