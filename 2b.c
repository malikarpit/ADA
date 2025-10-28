#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            int temp = arr[i]; arr[i] = arr[j]; arr[j] = temp;
        }
    }
    int temp = arr[i + 1]; arr[i + 1] = arr[high]; arr[high] = temp;
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
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
        quickSort(temp, 0, n - 1);
    }

    clock_t end = clock();
    double avg_time = ((double)(end - start)) / (CLOCKS_PER_SEC * runs);

    printf("Average time (Quick Sort) for %d elements over %d runs: %f seconds\n", n, runs, avg_time);

    free(arr);
    free(temp);
    return 0;
}
