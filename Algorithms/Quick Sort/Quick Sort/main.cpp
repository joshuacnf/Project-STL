#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

#define N 100007

template <typename T> inline void swap_(T &x, T &y)
{
    T z = x; x = y; y = z;
}

template <typename iter, typename compare_func>
void qsort_(iter s, iter e, compare_func comp){
    iter pos = s; e--;
    for(iter i = s; i != e; i++)
        if(comp(*i, *e))
        {
            swap_(*pos, *i);
            pos++;
        }
    swap_(*pos, *e);
    if(s < pos - 1) qsort_(s, pos, comp);
    if(pos + 1 < e) qsort_(pos + 1, e + 1, comp);
}

template <typename iter>
void qsort_(iter s, iter e){
    iter pos = s; e--;
    for(iter i = s; i != e; i++)
        if(*i < *e)
        {
            swap_(*pos, *i);
            pos++;
        }
    swap_(*pos, *e);
    if(s < pos - 1) qsort_(s, pos);
    if(pos + 1 < e) qsort_(pos + 1, e + 1);
}

bool comp(const int &x, const int &y)
{
    return x > y;
}

int A[N] = {0}, B[N] = {0};

void init()
{
    for (int i = 0; i < N; i++)
        A[i] = B[i] = rand() % (N << 1);
}

bool test1()
{
    qsort_(A, A + N);
    sort(B, B + N);
    for (int i = 0; i < N; i++)
        if (A[i] != B[i])
            return false;
    return true;
}

bool test2()
{
    qsort_(A, A + N, comp);
    sort(B, B + N, comp);
    for (int i = 0; i < N; i++)
        if (A[i] != B[i])
            return false;
    return true;
}

int main(){
    init();
    if (test1())
        printf("Passed\n");
    else printf("Failed\n");
    
    init();
    if (test2())
        printf("Passed\n");
    else printf("Failed\n");
    return 0;
}