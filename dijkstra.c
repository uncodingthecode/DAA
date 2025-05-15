#include <stdio.h>
#include <limits.h>

#define V 5  // Number of vertices

int minDistance(int dist[], int sptSet[]) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (!sptSet[v] && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

void printSolution(int dist[]) {
    printf("Vertex \t Distance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d \t %d\n", i, dist[i]);
}

void dijkstra(int graph[V][V], int src) {
    int dist[V];     // Output array. dist[i] will hold the shortest distance from src to i
    int sptSet[V];   // sptSet[i] will be true if vertex i is included in shortest path tree

    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = 0;

    dist[src] = 0; // Distance from source to itself is always 0

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet);
        sptSet[u] = 1; // Mark the picked vertex as processed

        for (int v = 0; v < V; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    printSolution(dist);
}

int main() {
    int graph[V][V] = {
        {0, 10, 0, 0, 5},
        {0, 0, 1, 0, 2},
        {0, 0, 0, 4, 0},
        {7, 0, 6, 0, 0},
        {0, 3, 9, 2, 0}
    };

    dijkstra(graph, 0); // Starting from vertex 0

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
