#include <stdio.h>
#include <stdlib.h>

// Define maximum number of vertices
#define MAX_VERTICES 100

// Structure to represent an Edge in the graph
typedef struct {
    int src, dest, weight;
} Edge;

// Structure to represent a Graph
typedef struct {
    int V, E;
    Edge* edge;
} Graph;

// Create a graph with V vertices and E edges
Graph* createGraph(int V, int E) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->E = E;
    graph->edge = (Edge*)malloc(E * sizeof(Edge));
    return graph;
}

// Find set of an element i (with path compression)
int find(int parent[], int i) {
    if (parent[i] != i)
        parent[i] = find(parent, parent[i]); // Path compression
    return parent[i];
}

// Union of two sets using rank
void Union(int parent[], int rank[], int x, int y) {
    int rootX = find(parent, x);
    int rootY = find(parent, y);

    if (rootX == rootY) return;

    // Union by rank
    if (rank[rootX] < rank[rootY])
        parent[rootX] = rootY;
    else if (rank[rootX] > rank[rootY])
        parent[rootY] = rootX;
    else {
        parent[rootY] = rootX;
        rank[rootX]++;
    }
}

// Comparator function for qsort to sort edges by weight
int compareEdges(const void* a, const void* b) {
    Edge* edge1 = (Edge*)a;
    Edge* edge2 = (Edge*)b;
    return edge1->weight - edge2->weight;
}

// Kruskal's algorithm to find MST
void kruskalMST(Graph* graph) {
    int V = graph->V;
    Edge result[V];  // Stores the resultant MST
    int e = 0;       // Index for result[]
    int i = 0;       // Index for sorted edges

    // Step 1: Sort all edges in non-decreasing order of weight
    qsort(graph->edge, graph->E, sizeof(graph->edge[0]), compareEdges);

    // Allocate memory for DSU structures
    int* parent = (int*)malloc(V * sizeof(int));
    int* rank = (int*)malloc(V * sizeof(int));

    // Initialize each vertex as its own parent
    for (int v = 0; v < V; v++) {
        parent[v] = v;
        rank[v] = 0;
    }

    // Step 2: Pick edges one by one from sorted list
    while (e < V - 1 && i < graph->E) {
        Edge next_edge = graph->edge[i++];

        int x = find(parent, next_edge.src);
        int y = find(parent, next_edge.dest);

        // If including this edge doesn't cause a cycle
        if (x != y) {
            result[e++] = next_edge;
            Union(parent, rank, x, y);
        }
    }

    // Print the MST
    printf("Edges of MST:\n");
    int totalWeight = 0;
    for (i = 0; i < e; i++) {
        printf("%d -- %d == %d\n", result[i].src, result[i].dest, result[i].weight);
        totalWeight += result[i].weight;
    }
    printf("Total Weight of MST: %d\n", totalWeight);

    free(parent);
    free(rank);
}

// Main driver function
int main() {
    /* Let us create the following graph
         2    3
     (0)--(1)--(2)
      |   / \   |
     6| 8/   \5 |7
      | /     \ |
     (3)-------(4)
            9          */
    int V = 5;  // Number of vertices
    int E = 7;  // Number of edges
    Graph* graph = createGraph(V, E);

    // Add edges
    graph->edge[0].src = 0;
    graph->edge[0].dest = 1;
    graph->edge[0].weight = 2;

    graph->edge[1].src = 0;
    graph->edge[1].dest = 3;
    graph->edge[1].weight = 6;

    graph->edge[2].src = 1;
    graph->edge[2].dest = 2;
    graph->edge[2].weight = 3;

    graph->edge[3].src = 1;
    graph->edge[3].dest = 3;
    graph->edge[3].weight = 8;

    graph->edge[4].src = 1;
    graph->edge[4].dest = 4;
    graph->edge[4].weight = 5;

    graph->edge[5].src = 2;
    graph->edge[5].dest = 4;
    graph->edge[5].weight = 7;

    graph->edge[6].src = 3;
    graph->edge[6].dest = 4;
    graph->edge[6].weight = 9;

    // Run Kruskal's algorithm
    kruskalMST(graph);

    // Free allocated memory
    free(graph->edge);
    free(graph);

    return 0;
}


















//gcc -std=c99 kruskal_mst.c -o kruskal_mst
//./kruskal_mst



// 1) Input:
// - Undirected weighted graph represented as a list of edges
// - Each edge contains source, destination, and weight
// - Number of vertices (V) and edges (E)

// 2) Algorithm:
// Kruskal’s Minimum Spanning Tree (MST):
// - Sort all edges by weight in increasing order
// - Use Disjoint Set Union (DSU) to detect cycles
// - Pick smallest edges that don’t form cycle until V-1 edges selected

// 3) Time Complexity:
// Best/Avg/Worst Case: O(E log E) due to sorting edges
// DSU operations are nearly O(1) per operation with path compression & union by rank

// 4) Space Complexity:
// - O(V + E), for storing parent/rank arrays and edge list

// 5) Advantages / Disadvantages:
// + Simple and intuitive
// + Efficient for sparse graphs
// + Works well with DSU optimizations
// - Not ideal for dense graphs (Prim's is often better)
// - Extra memory for DSU structures

// 6) Recurrence Relation:
// Sorting step dominates: T(E) = O(E log E)
// MST selection: O(E * α(V)), where α is inverse Ackermann function (~constant)

// 7) Summary (2 lines):
// Constructs minimum spanning tree using greedy approach and DSU.
// Efficient and optimal for graphs with moderate number of edges.