#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        int min_idx = i;
        for (int j = i+1; j < n; j++) {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }
        int temp = arr[min_idx]; arr[min_idx] = arr[i]; arr[i] = temp;
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
        selectionSort(temp, n);
    }

    clock_t end = clock();
    double avg_time = ((double)(end - start)) / (CLOCKS_PER_SEC * runs);

    printf("Average time (Selection Sort) for %d elements over %d runs: %f seconds\n", n, runs, avg_time);

    free(arr);
    free(temp);
    return 0;
}
