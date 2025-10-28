#include <stdio.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int knapSack(int W, int wt[], int val[], int n) {
    int i, w;
    int K[n + 1][W + 1];

    for (i = 0; i <= n; i++) {
        for (w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                K[i][w] = 0;
            else if (wt[i - 1] <= w)
                K[i][w] = max(val[i - 1] + K[i - 1][w - wt[i - 1]], K[i - 1][w]);
            else
                K[i][w] = K[i - 1][w];
        }
    }

    return K[n][W];
}

int main() {
    int W, n, i;
    printf("Enter the maximum weight of knapsack: ");
    scanf("%d", &W);

    printf("Enter the number of items: ");
    scanf("%d", &n);

    int val[n], wt[n];

    printf("Enter items with weight and value as {w,p} (e.g., 10,60):\n");
    for (i = 0; i < n; i++) {
        printf("Item %d: ", i + 1);
        scanf("%d,%d", &wt[i], &val[i]);
    }

    printf("\nMaximum value we can obtain = %d\n", knapSack(W, wt, val, n));

    return 0;
}
