#include <cstdio>
using namespace std;

#define N 1003

int A[N] = {0}, n, x;

int horner(){
    int y = 0;
    for(int i = n; i >= 0; i--)
        y = A[i] + x * y;
    return y;
}

int horner_recursive(const int &i){
    if(i > n) return 0;
    return A[i] + x * horner_recursive(i + 1);
}

int main(){
    scanf("%d", &n);
    for(int i = 0; i <= n; i++)
        scanf("%d", &A[i]);
    scanf("%d", &x);
    printf("%d\n", horner());
    printf("%d\n", horner_recursive(0));
    return 0;
}