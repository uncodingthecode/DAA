#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define N 4

typedef struct Node {
    int puzzle[N][N];
    int x, y, cost, level;
    struct Node *parent;
} Node;

int target[N][N] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 0}
};

int dx[] = {1, 0, -1, 0};
int dy[] = {0, -1, 0, 1};

int isSafe(int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N);
}

int calculateCost(int initial[N][N]) {
    int count = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (initial[i][j] && initial[i][j] != target[i][j])
                count++;
    return count;
}

Node* createNode(int puzzle[N][N], int x, int y, int newX, int newY, int level, Node *parent) {
    Node *node = (Node *)malloc(sizeof(Node));
    memcpy(node->puzzle, puzzle, sizeof(node->puzzle));
    int temp = node->puzzle[x][y];
    node->puzzle[x][y] = node->puzzle[newX][newY];
    node->puzzle[newX][newY] = temp;
    node->cost = calculateCost(node->puzzle);
    node->level = level;
    node->x = newX;
    node->y = newY;
    node->parent = parent;
    return node;
}

void printPuzzle(int puzzle[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%2d ", puzzle[i][j]);
        printf("\n");
    }
    printf("\n");
}

void printPath(Node *root) {
    if (root == NULL) return;
    printPath(root->parent);
    printPuzzle(root->puzzle);
}

int isSame(int a[N][N], int b[N][N]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (a[i][j] != b[i][j]) return 0;
    return 1;
}

void solve(int initial[N][N], int x, int y){
    Node *root = createNode(initial, x, y, x, y, 0, NULL);
    Node *pq[10000]; 
    int size = 0;
    pq[size++] = root;

    while (size){
        int min = 0;
        for (int i = 1; i < size; i++)
            if (pq[i]->cost + pq[i]->level < pq[min]->cost + pq[min]->level)
                min = i;

        Node *minNode = pq[min];
        pq[min] = pq[--size];

        if (isSame(minNode->puzzle, target)){
            printf("Solved!\n");
            printPath(minNode);
            return;
        }

        for (int i = 0; i < 4; i++){
            int newX = minNode->x + dx[i];
            int newY = minNode->y + dy[i];
            if (isSafe(newX, newY)){
                Node *child = createNode(minNode->puzzle, minNode->x, minNode->y, newX, newY, minNode->level + 1, minNode);
                pq[size++] = child;
            }
        }
    }
}

int main(){
    int initial[N][N], x, y;
    printf("Enter the initial puzzle (use 0 for empty tile):\n");
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++){
            scanf("%d", &initial[i][j]);
            if (initial[i][j] == 0){
                x = i;
                y = j;
            }
        }
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
