#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long fib_array[100];

long long fibo(int n){
    if (n==0) return 0 ;
    if (n==1) return 1 ;
    if (fib_array[n]!=0){
        return fib_array[n];
    }
    else {
        fib_array[n]=fibo(n-1)+fibo(n-2);
        return fib_array[n];
    }
}
int main(){
    int n;
    scanf("%d",&n);
    printf("%lld\n",fibo(n));
    return 0;
}
