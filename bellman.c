#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int src, dest, weight;
} Edge;

typedef struct {
    int V, E;
    Edge* edges;
} Graph;

Graph* createGraph(int V, int E) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->E = E;
    graph->edges = (Edge*)malloc(E * sizeof(Edge));
    return graph;
}

void BellmanFord(Graph* graph, int src) {
    int V = graph->V, E = graph->E;
    int dist[V];

    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX;
    dist[src] = 0;

    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = graph->edges[j].src;
            int v = graph->edges[j].dest;
            int w = graph->edges[j].weight;

            if (dist[u] != INT_MAX && dist[u] + w < dist[v])
                dist[v] = dist[u] + w;
        }
    }

    for (int j = 0; j < E; j++) {
        int u = graph->edges[j].src;
        int v = graph->edges[j].dest;
        int w = graph->edges[j].weight;

        if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
            printf("Graph contains a negative weight cycle\n");
            return;
        }
    }

    printf("Vertex\tDistance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d\t\t%d\n", i, dist[i]);
}

int main() {
    int V = 5, E = 8;
    Graph* graph = createGraph(V, E);

    graph->edges[0] = (Edge){0, 1, 2};
    graph->edges[1] = (Edge){0, 2, 4};
    graph->edges[2] = (Edge){1, 2, 1};
    graph->edges[3] = (Edge){1, 3, 5};
    graph->edges[4] = (Edge){2, 4, 3};
    graph->edges[5] = (Edge){3, 2, -3};
    graph->edges[6] = (Edge){3, 1, 1};
    graph->edges[7] = (Edge){4, 3, -2}; // change to -4 to create a negative cycle

    printf("\nRunning Bellman-Ford Algorithm:\n");
    BellmanFord(graph, 0);

    return 0;
}































/*
1) Input:
- Directed graph with weighted edges
- For Bellman-Ford: can have negative edges (and detects cycles)
- Source vertex for shortest path calculation

2) Algorithm:
- Relax all edges V-1 times
- Detects negative weight cycles with extra pass

3) Time Complexity:
Bellman-Ford: O(V * E)

4) Space Complexity:
O(V + E), for distance array and edge list

5) Advantages / Disadvantages:
+ Handles negative edges
+ Detects negative cycles
- Slower than Dijkstra (O(V*E))

6) Recurrence Relation:
dist[v] = min(dist[v], dist[u] + weight(u, v)) for each edge (u, v)

7) Summary (2 lines):
Uses Bellman-Ford for graphs with negative edges or cycle detection.
Relaxes edges repeatedly to find shortest paths.
*/
