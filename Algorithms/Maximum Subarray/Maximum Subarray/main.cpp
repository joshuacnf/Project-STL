#include <cstdio>
using namespace std;

#define N 100003
#define INF 0x7ffffff

int A[N] = {0}, n, T;

template <typename T> inline T max_(const T &x, const T &y) { return x > y? x: y; }

struct subarray{
    int sum, l, r;
    inline subarray(){}
    inline subarray(const int &sum_, const int &l_, const int &r_): sum(sum_), l(l_), r(r_){}
    bool operator >(const subarray &y)const{
        return sum > y.sum;
    }
}ans;

void init(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
        scanf("%d", A + i);
}

subarray CROSS_MID_MAXIMUM_SUBARRAY(const int &l, const int &mid, const int &r){
    int lb, rb, lsum = -INF, rsum = -INF;
    int sum = 0;
    for(int i = mid; i >= l; i--){
        sum += A[i];
        if(sum >= lsum) lsum = sum, lb = i;
    }
    sum = 0;
    for(int i = mid + 1; i <= r; i++){
        sum += A[i];
        if(sum >= rsum) rsum = sum, rb = i;
    }
    return subarray(lsum + rsum, lb, rb);
}

subarray MAXIMUM_SUBARRAY(int l, int r){
    if(l == r) return subarray(A[l], l, r);
    int mid = (l + r) >> 1;
    return max_(max_(MAXIMUM_SUBARRAY(l, mid), MAXIMUM_SUBARRAY(mid + 1, r)),
                CROSS_MID_MAXIMUM_SUBARRAY(l, mid, r));
}

int main(){
    scanf("%d", &T);
    for(int i = 1; i <= T; i++){
        init();
        printf("Case %d:\n", i);
        ans = MAXIMUM_SUBARRAY(1, n);
        printf("%d %d %d\n", ans.sum, ans.l, ans.r);
        if(i < T) printf("\n");
    }
    return 0;
}