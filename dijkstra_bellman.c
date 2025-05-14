#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// ================== Data Structures ===================

// For Dijkstra's algorithm (adjacency list + min-heap)
typedef struct AdjListNode {
    int dest;
    int weight;
} AdjListNode;

typedef struct AdjList {
    AdjListNode* head;
} AdjList;

typedef struct {
    int V;
    AdjList* array;
} Graph;

// For Bellman-Ford
typedef struct {
    int src, dest, weight;
} Edge;

typedef struct {
    int V, E;
    Edge* edge;
} BellmanGraph;

// ================== Helper Functions ===================

// Create a new adjacency list node
AdjListNode* createAdjNode(int dest, int weight) {
    AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    return newNode;
}

// Create a graph with V vertices
Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->array = (AdjList*)malloc(V * sizeof(AdjList));
    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;
    return graph;
}

// Add an edge to the graph
void addEdge_Dijkstra(Graph* graph, int src, int dest, int weight) {
    // Add edge from src to dest
    AdjListNode* newNode = createAdjNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
}

// Create Bellman-Ford graph
BellmanGraph* createBellmanGraph(int V, int E) {
    BellmanGraph* graph = (BellmanGraph*)malloc(sizeof(BellmanGraph));
    graph->V = V;
    graph->E = E;
    graph->edge = (Edge*)malloc(E * sizeof(Edge));
    return graph;
}

// ================== Dijkstra's Algorithm ===================

typedef struct {
    int v;
    int dist;
} HeapNode;

typedef struct {
    int size;
    int capacity;
    int* pos;
    HeapNode* array;
} MinHeap;

MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->pos = (int*)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (HeapNode*)malloc(capacity * sizeof(HeapNode));
    return minHeap;
}

void swapHeapNode(HeapNode* a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left].dist < minHeap->array[smallest].dist)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right].dist < minHeap->array[smallest].dist)
        smallest = right;

    if (smallest != idx) {
        minHeap->pos[minHeap->array[smallest].v] = idx;
        minHeap->pos[minHeap->array[idx].v] = smallest;
        swapHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

HeapNode extractMin(MinHeap* minHeap) {
    if (minHeap->size == 0)
        return (HeapNode){-1, INT_MAX};

    HeapNode root = minHeap->array[0];
    HeapNode lastNode = minHeap->array[minHeap->size - 1];

    minHeap->array[0] = lastNode;
    minHeap->pos[root.v] = minHeap->size - 1;
    minHeap->pos[lastNode.v] = 0;

    --minHeap->size;
    minHeapify(minHeap);

    return root;
}

void decreaseKey(MinHeap* minHeap, int v, int dist) {
    int i = minHeap->pos[v];
    minHeap->array[i].dist = dist;

    while (i && minHeap->array[i].dist < minHeap->array[(i - 1) / 2].dist) {
        minHeap->pos[minHeap->array[i].v] = (i - 1) / 2;
        minHeap->pos[minHeap->array[(i - 1) / 2].v] = i;
        swapHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int isEmpty(MinHeap* minHeap) {
    return minHeap->size == 0;
}

void dijkstra(Graph* graph, int src) {
    int V = graph->V;
    int* dist = (int*)malloc(V * sizeof(int));
    MinHeap* minHeap = createMinHeap(V);

    for (int v = 0; v < V; ++v) {
        dist[v] = INT_MAX;
        minHeap->array[v].v = v;
        minHeap->array[v].dist = INT_MAX;
        minHeap->pos[v] = v;
    }

    dist[src] = 0;
    decreaseKey(minHeap, src, 0);

    minHeap->size = V;

    while (!isEmpty(minHeap)) {
        HeapNode u = extractMin(minHeap);
        int uIndex = u.v;

        AdjListNode* crawl = graph->array[uIndex].head;
        while (crawl != NULL) {
            int v = crawl->dest;
            int weight = crawl->weight;

            if (dist[uIndex] != INT_MAX && dist[uIndex] + weight < dist[v]) {
                dist[v] = dist[uIndex] + weight;
                decreaseKey(minHeap, v, dist[v]);
            }
            crawl = crawl->next;
        }
    }

    printf("Vertex\tDistance from Source\n");
    for (int i = 0; i < V; ++i)
        printf("%d \t\t %d\n", i, dist[i]);

    free(dist);
    free(minHeap->array);
    free(minHeap->pos);
    free(minHeap);
}

// ================== Bellman-Ford Algorithm ===================

void BellmanFord(BellmanGraph* graph, int src) {
    int V = graph->V;
    int E = graph->E;
    int* dist = (int*)malloc(V * sizeof(int));

    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX;
    dist[src] = 0;

    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = graph->edge[j].src;
            int v = graph->edge[j].dest;
            int weight = graph->edge[j].weight;

            if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
                dist[v] = dist[u] + weight;
        }
    }

    bool hasNegativeCycle = false;
    for (int j = 0; j < E; j++) {
        int u = graph->edge[j].src;
        int v = graph->edge[j].dest;
        int weight = graph->edge[j].weight;

        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            hasNegativeCycle = true;
            break;
        }
    }

    if (hasNegativeCycle)
        printf("Graph contains negative weight cycle.\n");
    else {
        printf("Vertex\tDistance from Source\n");
        for (int i = 0; i < V; ++i)
            printf("%d \t\t %d\n", i, dist[i]);
    }

    free(dist);
}

// ================== Main Menu Driver ===================

int main() {
    int choice;
    printf("Choose the type of graph:\n");
    printf("1. Graph with all positive edges (Use Dijkstra's)\n");
    printf("2. Graph with positive/negative edges (Use Bellman-Ford)\n");
    printf("3. Graph with negative weight cycle (Use Bellman-Ford)\n");
    printf("Enter choice (1, 2 or 3): ");
    scanf("%d", &choice);

    if (choice == 1) {
        // Graph: All positive weights
        int V = 5;
        Graph* graph = createGraph(V);

        addEdge_Dijkstra(graph, 0, 1, 9);
        addEdge_Dijkstra(graph, 0, 2, 6);
        addEdge_Dijkstra(graph, 0, 3, 5);
        addEdge_Dijkstra(graph, 0, 4, 3);
        addEdge_Dijkstra(graph, 2, 1, 2);
        addEdge_Dijkstra(graph, 2, 3, 4);
        addEdge_Dijkstra(graph, 2, 4, 2);
        addEdge_Dijkstra(graph, 3, 1, 1);
        addEdge_Dijkstra(graph, 3, 4, 4);
        addEdge_Dijkstra(graph, 4, 1, 7);

        printf("\nRunning Dijkstra's Algorithm:\n");
        dijkstra(graph, 0);  // Start from vertex 0

    } else if (choice == 2 || choice == 3) {
        // Bellman-Ford graphs
        int V = 5;
        int E = 8;
        BellmanGraph* graph = createBellmanGraph(V, E);

        // Edges for both cases
        graph->edge[0].src = 0;
        graph->edge[0].dest = 1;
        graph->edge[0].weight = 2;

        graph->edge[1].src = 0;
        graph->edge[1].dest = 2;
        graph->edge[1].weight = 4;

        graph->edge[2].src = 1;
        graph->edge[2].dest = 2;
        graph->edge[2].weight = 1;

        graph->edge[3].src = 1;
        graph->edge[3].dest = 3;
        graph->edge[3].weight = 5;

        graph->edge[4].src = 2;
        graph->edge[4].dest = 4;
        graph->edge[4].weight = 3;

        graph->edge[5].src = 3;
        graph->edge[5].dest = 2;
        graph->edge[5].weight = -3;

        graph->edge[6].src = 3;
        graph->edge[6].dest = 1;
        graph->edge[6].weight = 1;

        graph->edge[7].src = 4;
        graph->edge[7].dest = 3;
        graph->edge[7].weight = -2;

        if (choice == 2) {
            printf("\nRunning Bellman-Ford Algorithm (no negative cycle):\n");
            BellmanFord(graph, 0);
        } else {
            // Introduce a negative cycle
            graph->edge[7].weight = -4;
            printf("\nRunning Bellman-Ford Algorithm (with negative cycle):\n");
            BellmanFord(graph, 0);
        }

    } else {
        printf("Invalid choice!\n");
    }

    return 0;
}














Running Dijkstra's Algorithm:
Vertex	Distance from Source
0 			0
1 			6
2 			4
3 			5
4 			2









// 1) Input:
// - Directed graph with weighted edges
// - For Dijkstra: all edge weights must be positive
// - For Bellman-Ford: can have negative edges (and detects cycles)
// - Source vertex for shortest path calculation

// 2) Algorithm:
// Dijkstra:
// - Min-heap based greedy approach
// - Always selects closest unvisited node
// - Updates distances of adjacent nodes
// Bellman-Ford:
// - Relax all edges V-1 times
// - Detects negative weight cycles with extra pass

// 3) Time Complexity:
// Dijkstra: O(E log V) with min-heap
// Bellman-Ford: O(V * E)
// Best Case: Same as worst (no early exit)
// Worst/Avg Case: As above due to full traversal required

// 4) Space Complexity:
// Dijkstra: O(V + E), for heap and adjacency list
// Bellman-Ford: O(V + E), for distance array and edge list

// 5) Advantages / Disadvantages:
// Dijkstra:
// + Fast with heap optimization
// - Fails with negative edge weights
// Bellman-Ford:
// + Handles negative edges
// + Detects negative cycles
// - Slower than Dijkstra (O(V*E))

// 6) Recurrence Relation:
// Dijkstra: Not applicable (greedy with priority queue)
// Bellman-Ford:
// dist[v] = min(dist[v], dist[u] + weight(u, v)) for each edge (u, v)

// 7) Summary (2 lines):
// Implements Dijkstra for graphs with positive edges.
// Uses Bellman-Ford for graphs with negative edges or cycle detection.