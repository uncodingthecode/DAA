#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function declarations
void strassenMultiply(double** A, double** B, double** C, int size);
void multiplyMatrices(double** A, double** B, double** C, int size);
void add(double** A, double** B, double** C, int size);
void subtract(double** A, double** B, double** C, int size);
double** createMatrix(int size);
void freeMatrix(double** mat, int size);

int main() {
    // Example matrices
    int size = 2;

    double** A = createMatrix(size);
    double** B = createMatrix(size);
    double** C_strassen = createMatrix(size);
    double** C_naive = createMatrix(size);

    // Initialize matrices
    A[0][0] = 1; A[0][1] = 2;
    A[1][0] = 3; A[1][1] = 4;

    B[0][0] = 5; B[0][1] = 6;
    B[1][0] = 7; B[1][1] = 8;

    printf("Matrix A:\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%.2f ", A[i][j]);
        }
        printf("\n");
    }

    printf("\nMatrix B:\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%.2f ", B[i][j]);
        }
        printf("\n");
    }

    // Naive multiplication
    multiplyMatrices(A, B, C_naive, size);
    printf("\nNaive Multiplication Result:\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%.2f ", C_naive[i][j]);
        }
        printf("\n");
    }

    // Strassen's multiplication
    strassenMultiply(A, B, C_strassen, size);
    printf("\nStrassen's Multiplication Result:\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%.2f ", C_strassen[i][j]);
        }
        printf("\n");
    }

    // Free memory
    freeMatrix(A, size);
    freeMatrix(B, size);
    freeMatrix(C_naive, size);
    freeMatrix(C_strassen, size);

    return 0;
}

// --------------------------
// Creates a dynamically allocated square matrix
double** createMatrix(int size) {
    double** mat = (double**)malloc(size * sizeof(double*));
    for (int i = 0; i < size; i++) {
        mat[i] = (double*)malloc(size * sizeof(double));
    }
    return mat;
}

// --------------------------
// Frees dynamically allocated matrix
void freeMatrix(double** mat, int size) {
    for (int i = 0; i < size; i++) {
        free(mat[i]);
    }
    free(mat);
}

// --------------------------
// Adds two matrices: C = A + B
void add(double** A, double** B, double** C, int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            C[i][j] = A[i][j] + B[i][j];
}

// --------------------------
// Subtracts two matrices: C = A - B
void subtract(double** A, double** B, double** C, int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            C[i][j] = A[i][j] - B[i][j];
}

// --------------------------
// Naive matrix multiplication: C = A * B
void multiplyMatrices(double** A, double** B, double** C, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            C[i][j] = 0;
            for (int k = 0; k < size; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// --------------------------
// Recursive Strassen's Matrix Multiplication
void strassenMultiply(double** A, double** B, double** C, int size) {
    if (size == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int half = size / 2;

    // Create submatrices
    double** A11 = createMatrix(half);
    double** A12 = createMatrix(half);
    double** A21 = createMatrix(half);
    double** A22 = createMatrix(half);

    double** B11 = createMatrix(half);
    double** B12 = createMatrix(half);
    double** B21 = createMatrix(half);
    double** B22 = createMatrix(half);

    double** C11 = createMatrix(half);
    double** C12 = createMatrix(half);
    double** C21 = createMatrix(half);
    double** C22 = createMatrix(half);

    double** M1 = createMatrix(half);
    double** M2 = createMatrix(half);
    double** M3 = createMatrix(half);
    double** M4 = createMatrix(half);
    double** M5 = createMatrix(half);
    double** M6 = createMatrix(half);
    double** M7 = createMatrix(half);

    double** AResult = createMatrix(half);
    double** BResult = createMatrix(half);

    // Split A and B into submatrices
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            A11[i][j] = A[i][j];                    // Top-left
            A12[i][j] = A[i][j + half];             // Top-right
            A21[i][j] = A[i + half][j];             // Bottom-left
            A22[i][j] = A[i + half][j + half];       // Bottom-right

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + half];
            B21[i][j] = B[i + half][j];
            B22[i][j] = B[i + half][j + half];
        }
    }

    // Compute the 7 products using Strassen's formulas
    add(A11, A22, AResult, half);
    add(B11, B22, BResult, half);
    strassenMultiply(AResult, BResult, M1, half); // M1 = (A11 + A22)(B11 + B22)

    add(A21, A22, AResult, half);
    strassenMultiply(AResult, B11, M2, half); // M2 = (A21 + A22) * B11

    subtract(B12, B22, BResult, half);
    strassenMultiply(A11, BResult, M3, half); // M3 = A11 * (B12 - B22)

    subtract(B21, B11, BResult, half);
    strassenMultiply(A22, BResult, M4, half); // M4 = A22 * (B21 - B11)

    add(A11, A12, AResult, half);
    strassenMultiply(AResult, B22, M5, half); // M5 = (A11 + A12) * B22

    subtract(A21, A11, AResult, half);
    add(B11, B12, BResult, half);
    strassenMultiply(AResult, BResult, M6, half); // M6 = (A21 - A11) * (B11 + B12)

    subtract(A12, A22, AResult, half);
    add(B21, B22, BResult, half);
    strassenMultiply(AResult, BResult, M7, half); // M7 = (A12 - A22) * (B21 + B22)

    // Combine results into C
    add(M1, M4, C11, half);
    subtract(C11, M5, C11, half);
    add(C11, M7, C11, half);

    add(M3, M5, C12, half);
    add(M2, M4, C21, half);

    add(M1, M3, C22, half);
    subtract(C22, M2, C22, half);
    add(C22, M6, C22, half);

    // Merge submatrices back into result
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            C[i][j] = C11[i][j];
            C[i][j + half] = C12[i][j];
            C[i + half][j] = C21[i][j];
            C[i + half][j + half] = C22[i][j];
        }
    }

    // Free all temporary matrices
    freeMatrix(A11, half);
    freeMatrix(A12, half);
    freeMatrix(A21, half);
    freeMatrix(A22, half);
    freeMatrix(B11, half);
    freeMatrix(B12, half);
    freeMatrix(B21, half);
    freeMatrix(B22, half);
    freeMatrix(C11, half);
    freeMatrix(C12, half);
    freeMatrix(C21, half);
    freeMatrix(C22, half);
    freeMatrix(M1, half);
    freeMatrix(M2, half);
    freeMatrix(M3, half);
    freeMatrix(M4, half);
    freeMatrix(M5, half);
    freeMatrix(M6, half);
    freeMatrix(M7, half);
    freeMatrix(AResult, half);
    freeMatrix(BResult, half);
}



























// 1) Input:
// - Two square matrices A and B of size n x n
// - n must be a power of 2 (for recursive splitting)

// 2) Algorithm:
// Strassen’s Divide-and-Conquer Matrix Multiplication:
// - Divides each matrix into four submatrices
// - Computes 7 products using special combinations
// - Combines results to form final product matrix
// - Base case: single element multiplication

// 3) Time Complexity:
// Best/Avg/Worst Case: O(n^log2(7)) ≈ O(n^2.81)
// Faster than standard O(n^3) due to fewer multiplications

// 4) Space Complexity:
// - O(n^2), due to temporary submatrices
// - Additional memory for M1–M7 intermediate matrices

// 5) Advantages / Disadvantages:
// + Asymptotically faster than naive method
// + Useful for large matrices
// - Higher constant factor makes it slower for small n
// - Uses more memory due to recursive splitting
// - Not numerically stable like standard method

// 6) Recurrence Relation:
// T(n) = 7T(n/2) + O(n^2)
// Solves to T(n) = O(n^log2(7)) ≈ O(n^2.81)

// 7) Summary (2 lines):
// Reduces matrix multiplication time using divide-and-conquer.
// Efficient for large matrices but uses extra space and has higher overhead.