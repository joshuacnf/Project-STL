#include <cstdio>
using namespace std;

#define N 1003

int A[N] = {0}, T[N] = {0}, n, ans = 0;

void merge(const int &l, const int &mid, const int &r){
    for(int i = l; i <= r; i++) T[i] = A[i];
    int i = l, j = mid + 1, k = l;
    while(i <= mid && j <= r){
        if(T[i] < T[j]) A[k++] = T[i++];
        else if(T[i] > T[j]) A[k++] = T[j++], ans += mid - i + 1;
        else A[k++] = T[i++], A[k++] = T[j++];
    }
    while(i <= mid) A[k++] = T[i++];
    while(j <= r) A[k++] = T[j++];
}

void inversion(int l, int r){
    if(l >= r) return;
    int mid = (l + r) >> 1;
    inversion(l, mid);
    inversion(mid + 1, r);
    merge(l, mid, r);
}

int main(){
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
        scanf("%d", &A[i]);
    inversion(0, n - 1);
    printf("%d\n", ans);
    return 0;
}