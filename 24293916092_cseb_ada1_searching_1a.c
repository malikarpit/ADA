#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int linearSearch(int arr[], int n, int key) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == key) {
            return i;
        }
    }
    return -1;
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

    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 10000;  
    }

    printf("Enter the key to search: ");
    scanf("%d", &key);

    int result = linearSearch(arr, n, key);
    
    clock_t start = clock();
    for (int i = 0; i < 10000; i++) {
        linearSearch(arr, n, key);
    }
    clock_t end = clock();

    double time_spent = (double)(end - start) / (CLOCKS_PER_SEC * 10000.0);
    printf("Time taken to search %d elements (averaged over 10000 runs): %f seconds\n", n, time_spent);

    free(arr);
    return 0;
}
