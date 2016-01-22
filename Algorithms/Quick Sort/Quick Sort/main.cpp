#include <cstdio>
using namespace std;

#define N 50007

template <typename T> inline void swap_(T &x, T &y) {
    if(x != y) x ^= y, y ^= x, x ^= y;
}

int A[N] = {0}, n;

void QUICK_SORT(const int &l, const int &r){
    swap_(A[(l + r) >> 1], A[r]);
    
    int pos = l;
    for(int i = l; i < r; i++)
        if(A[i] < A[r]){
            swap_(A[pos], A[i]);
            pos++;
        }
    swap_(A[pos], A[r]);
    if(l < pos - 1) QUICK_SORT(l, pos - 1);
    if(pos + 1 < r) QUICK_SORT(pos + 1, r);
}

int main(){
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
        scanf("%d", &A[i]);
    QUICK_SORT(0, n - 1);
    for(int i = 0; i < n; i++)
        printf("%d\n", A[i]);
    return 0;
}