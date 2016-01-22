#include <cstdio>
using namespace std;

#define N 1000003

int A[N] = {0}, T[N] = {0}, n = 0;

void init(){
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
        scanf("%d", &A[i]);
}

void MERGE(const int &s, const int &mid, const int &e){
    for(int i = s; i <= e; i++) T[i] = A[i];
    int i = s, j = mid+1, k = s;
    while(i <= mid && j <= e)
        if(T[i] < T[j])
            A[k++] = T[i++];
        else A[k++] = T[j++];
    while(i <= mid) A[k++] = T[i++];
    while(j <= e) A[k++] = T[j++];
}

void MERGE_SORT(const int &s, const int &e){
    if(s >= e) return;
    int mid = (s + e) >> 1;
    MERGE_SORT(s, mid);
    MERGE_SORT(mid + 1, e);
    MERGE(s, mid, e);
}

void print(){
    for(int i = 0; i < n; i++)
        printf("%d ", A[i]);
    printf("\n");
}

int main(){
    init();
    MERGE_SORT(0, n - 1);
    print();
    return 0;
}