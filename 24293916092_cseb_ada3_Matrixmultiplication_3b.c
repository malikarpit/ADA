#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int **allocate_matrix(int n) {
    int **matrix = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int *)malloc(n * sizeof(int));
    }
    return matrix;
}

void free_matrix(int **matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void initialize_matrix(int **matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = rand() % 10;
        }
    }
}

void add_matrices(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void split_matrix(int **P, int **C, int row, int col, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = P[i + row][j + col];
        }
    }
}

void combine_matrices(int **C, int **P, int row, int col, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            P[i + row][j + col] = C[i][j];
        }
    }
}

void multiply_iterative(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}
void multiply_recursive(int **A, int **B, int **C, int n) {
    if (n <= 16) {
        multiply_iterative(A, B, C, n);
        return;
    }

    int new_n = n / 2;

    int **A11 = allocate_matrix(new_n);
    int **A12 = allocate_matrix(new_n);
    int **A21 = allocate_matrix(new_n);
    int **A22 = allocate_matrix(new_n);

    int **B11 = allocate_matrix(new_n);
    int **B12 = allocate_matrix(new_n);
    int **B21 = allocate_matrix(new_n);
    int **B22 = allocate_matrix(new_n);

    int **C11 = allocate_matrix(new_n);
    int **C12 = allocate_matrix(new_n);
    int **C21 = allocate_matrix(new_n);
    int **C22 = allocate_matrix(new_n);

    int **Temp1 = allocate_matrix(new_n);
    int **Temp2 = allocate_matrix(new_n);

    split_matrix(A, A11, 0, 0, new_n);
    split_matrix(A, A12, 0, new_n, new_n);
    split_matrix(A, A21, new_n, 0, new_n);
    split_matrix(A, A22, new_n, new_n, new_n);

    split_matrix(B, B11, 0, 0, new_n);
    split_matrix(B, B12, 0, new_n, new_n);
    split_matrix(B, B21, new_n, 0, new_n);
    split_matrix(B, B22, new_n, new_n, new_n);
  
    multiply_recursive(A11, B11, Temp1, new_n);
    multiply_recursive(A12, B21, Temp2, new_n);
    add_matrices(Temp1, Temp2, C11, new_n);

    multiply_recursive(A11, B12, Temp1, new_n);
    multiply_recursive(A12, B22, Temp2, new_n);
    add_matrices(Temp1, Temp2, C12, new_n);

    multiply_recursive(A21, B11, Temp1, new_n);
    multiply_recursive(A22, B21, Temp2, new_n);
    add_matrices(Temp1, Temp2, C21, new_n);

    multiply_recursive(A21, B12, Temp1, new_n);
    multiply_recursive(A22, B22, Temp2, new_n);
    add_matrices(Temp1, Temp2, C22, new_n);

    combine_matrices(C11, C, 0, 0, new_n);
    combine_matrices(C12, C, 0, new_n, new_n);
    combine_matrices(C21, C, new_n, 0, new_n);
    combine_matrices(C22, C, new_n, new_n, new_n);

    free_matrix(A11, new_n); free_matrix(A12, new_n); free_matrix(A21, new_n); free_matrix(A22, new_n);
    free_matrix(B11, new_n); free_matrix(B12, new_n); free_matrix(B21, new_n); free_matrix(B22, new_n);
    free_matrix(C11, new_n); free_matrix(C12, new_n); free_matrix(C21, new_n); free_matrix(C22, new_n);
    free_matrix(Temp1, new_n); free_matrix(Temp2, new_n);
}

int main() {
    srand(time(NULL));

    printf("%-10s %-15s\n", "Size (n)", "Time (sec)");

    for (int n = 2; n <= 256; n *= 2) {
        int **A = allocate_matrix(n);
        int **B = allocate_matrix(n);
        int **C = allocate_matrix(n);

        initialize_matrix(A, n);
        initialize_matrix(B, n);

        clock_t start = clock();
        multiply_recursive(A, B, C, n);
        clock_t end = clock();

        double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
        printf("%-10d %-15f\n", n, time_spent);

        free_matrix(A, n);
        free_matrix(B, n);
        free_matrix(C, n);
    }

    return 0;
}

