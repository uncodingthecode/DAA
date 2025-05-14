#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 4
#define INF 99999

// Goal state
int goal[N][N] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 0}
};

// Direction arrays for moving blank tile
int row[] = {1, -1, 0, 0};
int col[] = {0, 0, 1, -1};

// Node structure
typedef struct Node {
    int mat[N][N];
    int x, y;           // Position of blank tile
    int g;              // Moves so far
    int h;              // Heuristic value
    int f;              // f = g + h
    int move;           // last move direction (optional)
    struct Node* parent;
} Node;

// Heap node
typedef struct MinHeap {
    int size;
    int capacity;
    Node** array;
} MinHeap;

// Create new node
Node* newNode(int mat[N][N], int x, int y, int newX, int newY, int g, Node* parent) {
    Node* node = (Node*)malloc(sizeof(Node));
    memcpy(node->mat, mat, sizeof(node->mat));

    node->mat[x][y] = node->mat[newX][newY];
    node->mat[newX][newY] = 0;

    node->x = newX;
    node->y = newY;

    node->g = g;
    node->parent = parent;
    return node;
}

// Heuristic function: Manhattan distance
int calculateHeuristic(int mat[N][N]) {
    int count = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (mat[i][j] && mat[i][j] != goal[i][j])
                count += abs(i - ((mat[i][j] - 1) / 4)) +
                         abs(j - ((mat[i][j] - 1) % 4));
        }
    }
    return count;
}

// Check if valid move
int isSafe(int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N);
}

// Print matrix
void printMatrix(int mat[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%2d ", mat[i][j]);
        printf("\n");
    }
    printf("\n");
}

// Compare two matrices
int compareMatrices(int mat1[N][N], int mat2[N][N]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (mat1[i][j] != mat2[i][j])
                return 0;
    return 1;
}

// Heap functions
MinHeap* createMinHeap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->capacity = capacity;
    heap->size = 0;
    heap->array = (Node**)malloc(capacity * sizeof(Node*));
    return heap;
}

void swap(Node** a, Node** b) {
    Node* temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(MinHeap* heap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap->size &&
        heap->array[left]->f < heap->array[smallest]->f)
        smallest = left;

    if (right < heap->size &&
        heap->array[right]->f < heap->array[smallest]->f)
        smallest = right;

    if (smallest != idx) {
        swap(&heap->array[smallest], &heap->array[idx]);
        minHeapify(heap, smallest);
    }
}

void insertMinHeap(MinHeap* heap, Node* node) {
    heap->array[heap->size++] = node;
    int i = heap->size - 1;
    while (i > 0 && heap->array[(i - 1) / 2]->f > heap->array[i]->f) {
        swap(&heap->array[i], &heap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

Node* extractMin(MinHeap* heap) {
    Node* temp = heap->array[0];
    heap->array[0] = heap->array[heap->size - 1];
    heap->size--;
    minHeapify(heap, 0);
    return temp;
}

// Function to check if this node already exists in closed list
int isInClosedList(Node* node, Node** closedList, int closedCount) {
    for (int i = 0; i < closedCount; i++) {
        if (compareMatrices(node->mat, closedList[i]->mat))
            return 1;
    }
    return 0;
}

// Main function to solve the puzzle
void solve(int initial[N][N], int x, int y) {
    // Create root node
    Node* root = (Node*)malloc(sizeof(Node));
    memcpy(root->mat, initial, sizeof(initial));
    root->x = x;
    root->y = y;
    root->g = 0;
    root->h = calculateHeuristic(initial);
    root->f = root->g + root->h;
    root->parent = NULL;

    // Priority Queue
    MinHeap* openList = createMinHeap(1000);
    insertMinHeap(openList, root);

    // Closed list to avoid revisiting
    Node** closedList = (Node**)malloc(1000 * sizeof(Node*));
    int closedCount = 0;

    while (openList->size != 0) {
        Node* curr = extractMin(openList);

        if (curr->h == 0) {
            // Solution found
            printf("Solution Found:\n");
            Node* path[100];
            int steps = 0;
            while (curr) {
                path[steps++] = curr;
                curr = curr->parent;
            }

            for (int i = steps - 1; i >= 0; i--) {
                printMatrix(path[i]->mat);
                printf("Move Count: %d\n", path[i]->g);
            }

            free(curr);
            break;
        }

        if (isInClosedList(curr, closedList, closedCount)) {
            free(curr);
            continue;
        }

        closedList[closedCount++] = curr;

        for (int i = 0; i < 4; i++) {
            int newX = curr->x + row[i];
            int newY = curr->y + col[i];

            if (isSafe(newX, newY)) {
                Node* child = newNode(curr->mat, curr->x, curr->y, newX, newY, curr->g + 1, curr);
                child->h = calculateHeuristic(child->mat);
                child->f = child->g + child->h;

                if (!isInClosedList(child, closedList, closedCount)) {
                    insertMinHeap(openList, child);
                } else {
                    free(child);
                }
            }
        }
    }

    // Free memory
    for (int i = 0; i < closedCount; i++) {
        free(closedList[i]);
    }
    free(closedList);
}

// Driver program
int main() {
    // Initial state (can be changed)
    int initial[N][N] = {
        {1, 2, 3, 4},
        {5, 6, 0, 8},
        {9, 10, 7, 12},
        {13, 14, 11, 15}
    };

    // Find blank tile
    int x = 1, y = 2;

    printf("Initial State:\n");
    printMatrix(initial);

    printf("Goal State:\n");
    printMatrix(goal);

    printf("Solving...\n\n");

    solve(initial, x, y);

    return 0;
}

















// 1) Input:
// - initial[N][N]: 4x4 matrix with numbers 0–15 (0 = blank)
// - x, y: starting position of blank tile (0)

// 2) Algorithm:
// A* search using Manhattan distance heuristic
// - Min-heap (priority queue) for open nodes
// - Closed list to avoid revisiting states
// - Expand lowest f = g (moves so far) + h (heuristic cost)

// 3) Time Complexity:
// Best/Avg/Worst: O(b^d), b ~2–4, d = solution depth  O(n^2)
// Worst is exponential due to state space (~16! / 2 possible boards)
//space O(n)

// 4) Advantages & Disadvantages:
// + Finds shortest path (admissible heuristic)
// + Works well on solvable puzzles
// - High memory usage
// - Slower for deep solutions

// 5) Recurrence Relation:
// T(n) = T(n - 1) + O(b^d)
// n = number of explored nodes, b = branching factor, d = solution depth

// 6) Heuristic Formula Used:
// h(n) = Σ |i - gx| + |j - gy| for all tiles
// where (gx, gy) = goal position of tile at (i,j)

// 7) Summary (2 lines):
// Solves 15-puzzle using A* and Manhattan distance.
// Optimal but can be slow/memory-heavy for complex puzzles.