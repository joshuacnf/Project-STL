#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;

#define N 103   //max size of the matrix: N * N

int n, m;   //actual size of the M matrix: n * m

struct vec  //n-dimension column vector
{
    double v[N];
    
    vec() { memset(v, 0, sizeof(v)); }
    
    vec& operator =(const vec &u)
    {
        memcpy(v, u.v, sizeof(u.v));
        return *this;
    }
    
    vec operator +(const vec &u) const
    {
        vec ans;
        for (int i = 0; i < n; i++)
            ans.v[i] = v[i] + u.v[i];
        return ans;
    }
    
    vec& operator +=(const vec &u)
    {
        for (int i = 0; i < n; i++)
            v[i] += u.v[i];
        return *this;
    }
    
    vec operator -(const vec &u) const
    {
        vec ans;
        for (int i = 0; i < n; i++)
            ans.v[i] = v[i] - u.v[i];
        return ans;
    }
    
    vec& operator -=(const vec &u)
    {
        for (int i = 0; i < n; i++)
            v[i] -= u.v[i];
        return *this;
    }
    
    vec operator *(const double &k) const   //scalar multiplication
    {
        vec ans;
        for (int i = 0; i < n; i++)
            ans.v[i] = v[i] * k;
        return ans;
    }
    
    double operator *(const vec &u) const   //dot product
    {
        double ans = 0;
        for (int i = 0; i < n; i++)
            ans += v[i] * u.v[i];
        return ans;
    }
    
    double normalize()
    {
        double norm = sqrt((*this) * (*this));
        for (int i = 0; i < n; i++)
            v[i] /= norm;
        return norm;
    }
};

vec M[N], Q[N], R[N];

void init()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%lf", &M[j].v[i]);
}

void QR()
{
    for (int j = 0; j < m; j++)
    {
        vec Rj; //the jth column vector in R
        for (int i = 0; i < j; i++)
            Rj.v[i] = Q[i] * M[j];
        
        for (int i = 0; i < j; i++)
            M[j] -=  Q[i] * Rj.v[i];    //the equation in Gram-Schmidt process
        
        Rj.v[j] = M[j].normalize();
        Q[j] = M[j];
        R[j] = Rj;
    }
}

void print()
{
    printf("Q:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            printf("%.2lf ", Q[j].v[i]);
        printf("\n");
    }
    
    printf("\nR:\n");
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
            printf("%.2lf ", R[j].v[i]);
        printf("\n");
    }
}

int main()
{
    init();
    QR();
    print();
}