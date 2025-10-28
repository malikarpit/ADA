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

        multiply_iterative(A, B, C, n);

        clock_t end = clock();

        double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
        printf("%-10d %-15f\n", n, time_spent);

        free_matrix(A, n);
        free_matrix(B, n);
        free_matrix(C, n);
    }

    return 0;
}
