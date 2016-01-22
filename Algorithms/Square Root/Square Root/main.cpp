#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;

#define N 1003

inline float sqrt_(const float &x){
    float ans=x;
    for(int i = 0; i < 10; i++)
        ans = ans - ans / 2 + x / (ans * 2.0);
    return ans;
}

float A[N], ans[N], ans2[N];

int main(){
    for(int i = 0; i < N; i++)
        A[i] = rand() / (INT32_MAX * 1.0) * 10000;
    
    time_t s = clock();
    for(int i = 0; i < N; i++)
        ans[i] = sqrt(A[i]);
    printf("%lf\n", (clock() - s) / (CLOCKS_PER_SEC * 1.0));
    
    s = clock();
    for(int i = 0; i < N; i++)
        ans2[i] = sqrt_(A[i]);
    printf("%lf\n", (clock() - s) / (CLOCKS_PER_SEC * 1.0));
    
    //for(int i = 0; i < N; i++)
      //  printf("%f\n", ans[i] - ans2[i]);
    
    return 0;
}