#include <cstdio>
using namespace std;

#define N 1003

int A[N]={0},n;

void init(){
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
        scanf("%d", &A[i]);
}

void INSERTION_SORT(int *A, int *END){
    for(int *i = A; i != END; i++){
        int key = *i; int *j;
        for(j = i-1; j != A - 1 && *j > key; j--)
            *(j + 1) = *j;
        *(j + 1) = key;
    }
    for(int *i = A; i != END; i++)
        printf("%d ", *i);
    printf("\n");
}

int main(){
    init();
    INSERTION_SORT(A, A+n);
    return 0;
}