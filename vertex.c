#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node{
    int vertex;
    struct Node* next;
};

struct Graph{
    int V;
    struct Node** adj;
};

struct Node* newNode(int v){
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->vertex = v;
    new_node->next = NULL;
    return new_node;
}

struct Graph* createGraph(int V){
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->adj = (struct Node**)malloc(V * sizeof(struct Node*));
    for (int i = 0; i < V; i++)
        graph->adj[i] = NULL;
    return graph;
}

void addEdge(struct Graph* graph, int v, int w){
    struct Node* new_node = newNode(w);
    new_node->next = graph->adj[v];
    graph->adj[v] = new_node;
    new_node = newNode(v);
    new_node->next = graph->adj[w];
    graph->adj[w] = new_node;
}

void printVertexCover(struct Graph* graph){
    bool* visited = (bool*)malloc(graph->V * sizeof(bool));
    for (int i = 0; i < graph->V; i++)
        visited[i] = false;

    printf("Vertex Cover: ");
    for (int u = 0; u < graph->V; u++){
        if (!visited[u]){
            struct Node* temp = graph->adj[u];
            while (temp != NULL){
                int v = temp->vertex;
                if (!visited[v]){
                    printf("%d %d ", u, v);
                    visited[u] = true;
                    visited[v] = true;
                    break;
                }
                temp = temp->next;
            }
        }
    }
    printf("\n");
    free(visited);
}

int main(){
    struct Graph* g = createGraph(7);
    addEdge(g, 0, 1);
    addEdge(g, 0, 2);
    addEdge(g, 1, 3);
    addEdge(g, 3, 4);
    addEdge(g, 4, 5);
    addEdge(g, 5, 6);
    printVertexCover(g);
    return 0;
}








































// 1) Input:
// - Undirected graph (V vertices, E edges)
// - Graph can be represented using adjacency list/matrix
// - Goal: Find a set of vertices such that every edge is incident to at least one vertex in the set

// 2) Algorithm:
// Approximate (Greedy):
// - Traverse all edges
// - If both endpoints are unvisited, add both to the cover
// - Mark them as visited

// 3) Time Complexity:
// Approximate: O(V + E), visiting each vertex and edge once
// Exact (Brute Force): O(2^V), checks all subsets

// 4) Space Complexity:
// O(V + E) for adjacency list and visited array

// 5) Advantages / Disadvantages:
// Approximate:
// + Fast and simple
// - May not return minimum cover
// Exact:
// + Guarantees minimum cover
// - Exponential time for large graphs

// 6) Recurrence Relation:
// Not applicable for greedy
// For exact solution (recursion/backtracking):
// VC(G) = min(1 + VC(G - {u}), 1 + VC(G - {v})) for edge (u, v)

// 7) Summary (2 lines):
// Finds a vertex set covering all edges in a graph.
// Greedy approach is fast but approximate; exact is slow but optimal.
