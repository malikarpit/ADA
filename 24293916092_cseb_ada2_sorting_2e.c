#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j]; arr[j] = arr[j+1]; arr[j+1] = temp;
            }
        }
    }
}

int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int *arr = malloc(n * sizeof(int));
    int *temp = malloc(n * sizeof(int));

    srand(time(NULL));
    for (int i = 0; i < n; i++) arr[i] = rand() % 100000;

    int runs = 10000;
    clock_t start = clock();

    for (int r = 0; r < runs; r++) {
        for (int i = 0; i < n; i++) temp[i] = arr[i];
        bubbleSort(temp, n);
    }

    clock_t end = clock();
    double avg_time = ((double)(end - start)) / (CLOCKS_PER_SEC * runs);

    printf("Average time (Bubble Sort) for %d elements over %d runs: %f seconds\n", n, runs, avg_time);

    free(arr);
    free(temp);
    return 0;
}
