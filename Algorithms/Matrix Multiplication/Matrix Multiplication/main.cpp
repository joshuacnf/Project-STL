#include <cstdio>
using namespace std;

#define N 0x10

int A[N][N] = {0}, B[N][N] = {0}, C[N][N] = {0}, n;

void init(){
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            scanf("%d", &A[i][j]);
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            scanf("%d", &B[i][j]);
}

void MATRIX_MULTIPLICATION(int r1, int c1, int r2, int c2, int k){
    if(k == 1){
        C[r1][c2] += A[r1][c1] * B[r2][c2];
        return;
    }
    int k2 = k >> 1;
    
    MATRIX_MULTIPLICATION(r1, c1, r2, c2, k2);
    MATRIX_MULTIPLICATION(r1, c1 + k2, r2 + k2, c2, k2);
    
    MATRIX_MULTIPLICATION(r1, c1, r2, c2 + k2, k2);
    MATRIX_MULTIPLICATION(r1, c1 + k2, r2 + k2, c2 + k2, k2);
    
    MATRIX_MULTIPLICATION(r1 + k2, c1, r2, c2, k2);
    MATRIX_MULTIPLICATION(r1 + k2, c1 + k2, r2 + k2, c2, k2);
    
    MATRIX_MULTIPLICATION(r1 + k2, c1, r2, c2 + k2, k2);
    MATRIX_MULTIPLICATION(r1 + k2, c1 + k2, r2 + k2, c2 + k2, k2);
    
    return;
}

void print(){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++)
            printf("%d ", C[i][j]);
        printf("\n");
    }
}

int main(){
    init();
    MATRIX_MULTIPLICATION(0, 0, 0, 0, n);
    print();
}