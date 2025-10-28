#include <stdio.h>
#include <stdlib.h>

struct Item {
    int value;
    int weight;
};

int compare(const void* a, const void* b) {
    struct Item* itemA = (struct Item*)a;
    struct Item* itemB = (struct Item*)b;
    double ratioA = (double)itemA->value / itemA->weight;
    double ratioB = (double)itemB->value / itemB->weight;
    if (ratioA < ratioB) {
        return 1;
    } else if (ratioA > ratioB) {
        return -1;
    } else {
        return 0;
    }
}

double fractionalKnapsack(int W, struct Item arr[], int n) {
    qsort(arr, n, sizeof(struct Item), compare);

    int currentWeight = 0;
    double finalValue = 0.0;

    for (int i = 0; i < n; i++) {
        if (currentWeight + arr[i].weight <= W) {
            currentWeight += arr[i].weight;
            finalValue += arr[i].value;
        } else {
            int remain = W - currentWeight;
            finalValue += arr[i].value * ((double)remain / arr[i].weight);
            break;
        }
    }
    return finalValue;
}

int main() {
    int W;
    int n;
    printf("Enter the maximum weight of knapsack: ");
    scanf("%d", &W);
    printf("Enter the number of items: ");
    scanf("%d", &n);
    struct Item arr[100]; 
    printf("Enter items with weight and value as {w,p} (e.g., 10,60):\n");

    for (int i = 0; i < n; i++) {
        printf("Item %d: ", i + 1);
        scanf("%d,%d", &arr[i].weight, &arr[i].value);
    }

    printf("\nMaximum value we can obtain = %f\n", fractionalKnapsack(W, arr, n));
    return 0;
}