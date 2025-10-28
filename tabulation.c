#include <stdio.h>
#include <stdlib.h> 

int fib_tabulation(int n) {

    if (n == 0) {
        return 0;
    }

    int *dp = (int *)malloc((n + 1) * sizeof(int));
    if (dp == NULL) {
        printf("Memory allocation failed\n");
        return -1; 
    }

    dp[0] = 0;
    dp[1] = 1;

    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    int result = dp[n];

    free(dp);

    return result;
}

int main() {
    int n ;
    printf("Enter the position of Fibonacci number to find: ");
    scanf("%d", &n);
    printf("Using Tabulation:\n");
    int result = fib_tabulation(n);
    if (result != -1) {
        printf("The Fibonacci number at position %d is %d\n", n, result);
    }
    
    return 0;
}
