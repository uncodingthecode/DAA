#include <stdio.h>
#define size 8

int solutionCount = 0;
void displayChess(int board[size][size]){
    for (int row = 0; row < size; row++){
        for (int col = 0; col < size; col++)
            if (board[row][col] == 1)
                printf("Q ");
            else
                printf(". ");
        printf("\n");
    }
    printf("\n");
}

int validPlace(int board[size][size], int crntRow, int crntCol){
    for (int i = 0; i < crntCol; i++)
        if (board[crntRow][i])
            return 0;

    for (int i = crntRow, j = crntCol; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return 0;

    for (int i = crntRow, j = crntCol; i < size && j >= 0; i++, j--)
        if (board[i][j])
            return 0;

    return 1;
}

void solveProblem(int board[size][size], int crntCol){
    if (crntCol >= size){
        solutionCount++;
        printf("Solution %d:\n", solutionCount);
        displayChess(board);
        return;
    }

    for (int i = 0; i < size; i++) {
        if (validPlace(board, i, crntCol)){
            board[i][crntCol] = 1;
            solveProblem(board, crntCol + 1);
            board[i][crntCol] = 0;  // Backtrack
        }
    }
}

int display(){
    int board[size][size] = {0};

    solveProblem(board, 0);

    if (solutionCount == 0){
        printf("No solutions exist.\n");
        return 0;
    }

    printf("Total number of solutions: %d\n", solutionCount);
    return 1;
}

int main(){
    display();
    return 0;
}
