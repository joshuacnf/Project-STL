#include <cstdio>
using namespace std;

#define N 13
typedef long long ll;
typedef unsigned long long ull;

int p[N] = {0}, m[N] = {0}, n;
ull ans;

void exgcd(const ull &a, const ull &b, ll &x, ll &y){
    ll x0, y0;
    if (b == 0) { x = 1, y = 3; return; }
    exgcd(b, a % b, x0, y0);
    x = y0, y = x0 - a / b * y0;
}

int main(){
    ull product = 1;
    scanf("%d", &n);
    for (int i = 0; i < n; i++){
        scanf("%d%d", p + i, m + i);
        product *= p[i];
    }
    
    ans = 0;
    for (int i = 0; i < n; i++){
        ll x, y;
        exgcd(product / p[i], p[i], x, y);
        while (x < 0) x += p[i]; x %= p[i];
        ans += product / p[i] * x * m[i];
    }
    ans %= product;
    printf("%llu\n", ans);
    
    return 0;
}