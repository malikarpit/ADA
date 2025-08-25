#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int binarySearch(int arr[], int n, int key) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == key) {
            return mid;
        } else if (arr[mid] < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

void generateRandomArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000000;
    } 
}

int main() {
    int n, key;

    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    srand(time(0));
    generateRandomArray(arr, n);

    qsort(arr, n, sizeof(int), compare);

    printf("Enter the key to search: ");
    scanf("%d", &key);

    int result = binarySearch(arr, n, key);
    if (result != -1) {
        printf("Element found at index %d\n", result);
    } else {
        printf("Element not found\n");
    }

    clock_t start = clock();
    for (int i = 0; i < 100000; i++) {
        binarySearch(arr, n, key);
    }
    clock_t end = clock();

    double time_spent = (double)(end - start) / (CLOCKS_PER_SEC * 10000.0);
    printf("Time taken to search %d elements (averaged over 10000 runs): %f seconds\n", n, time_spent);

    free(arr);
    return 0;
}
