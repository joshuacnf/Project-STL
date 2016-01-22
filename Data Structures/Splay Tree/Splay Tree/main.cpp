#include <cstdio>
#include <cstring>
using namespace std;

#define MAXN 500009
#define INF 5003

inline int getint()
{
    int ans(0), sgn(0); char w = getchar();
    while(w < '0' || '9' < w) {sgn = (w == '-'); w = getchar();}
    while('0' <= w && w <= '9')
    {
        ans = ans * 10 + w - '0';
        w = getchar();
    }
    return sgn ? -ans : ans;
}

inline int max_(const int &x, const int &y) { return x > y? x: y; }
template <typename T> inline void swap_(T &x, T &y) { T z = x; x = y; y = z; }

struct node;
node *nil = 0;

struct node
{
    node *l, *r, *p;
    int size, val, sum, lms, rms, mc, ms;
    bool rev, cov;
    node(){}
    node(const int &val_)
    {
        l = r = p = nil;
        size = 1;
        val = sum = mc = val_;
        lms = rms = ms = max_(0, val_);
        rev = cov = 0;
    }
    
    inline bool right()
    {
        return this == p->r;
    }
    
    inline node *link(bool right, node *v)
    {
        right? r = v: l = v;
        if(v != nil) v->p = this;
        return this;
    }
    
    inline void reverse()
    {
        rev ^= 1;
        swap_(l, r); swap_(lms, rms);
    }
    
    inline void cover(const int &val_)
    {
        cov = 1;
        mc = val = val_; sum = size * val;
        lms = rms = ms = max_(0, sum);
    }
    
    inline void pushdown()
    {
        if(rev)
        {
            rev = 0;
            if(l != nil) l->reverse();
            if(r != nil) r->reverse();
        }
        if(cov)
        {
            cov = 0;
            if(l != nil) l->cover(val);
            if(r != nil) r->cover(val);
        }
    }
    
    inline void update()
    {
        size = l->size + r->size + 1;
        sum = l->sum + r->sum + val;
        lms = max_(l->lms, l->sum + val + r->lms);
        rms = max_(r->rms, r->sum + val + l->rms);
        mc = max_(val, max_(l->mc, r->mc));
        ms = max_(max_(l->ms, r->ms), l->rms + val + r->lms);
    }
};

struct MemoryPond
{
    node pond[MAXN]; node *stack_[MAXN]; int i, j;
    MemoryPond(): i(0), j(0) {}
    
    inline node *newNode(const int &val)
    {
        node *v;
        if(!j)
            v = &pond[i++];
        else
        {
            v = stack_[j--];
            if(v->l != nil) dispose(v->l);
            if(v->r != nil) dispose(v->r);
        }
        return &(*v = node(val));
    }
    
    inline void dispose(node* v)
    {
        stack_[++j] = v;
    }
};

struct SplayTree
{
    node *root;
    MemoryPond memPond;
    
    SplayTree(): root(0)
    {
        nil = memPond.newNode(0);
        nil -> size = 0;
        nil -> mc = -INF;
    }
    
    inline void rot(node *v)
    {
        node *u = v->p, *q = u->p;
        if(v == u->l)
            v->link(1, u->link(0, v->r));
        else v->link(0, u->link(1, v->l));
        u->update();
        if(q == nil) root = v, v->p = nil;
        else q->link(u == q->r, v);
    }
    
    inline void splay(node *v, node *tar)
    {
        while(v->p != tar && v->p->p != tar)
            if(v->right() == v->p->right())
                rot(v->p), rot(v);
            else rot(v), rot(v);
        if(v->p->p == tar) rot(v);
        v->update();
    }
    
    inline node* kth(int k)
    {
        node *v = root;
        while(v->pushdown(), v->l->size + 1 != k)
            if(v->l->size >= k)
                v = v->l;
            else k -= v->l->size + 1, v = v->r;
        splay(v, nil);
        return v;
    }
    
    inline node* select(int s, int e)
    {
        node *p = kth(s), *q = kth(e);
        splay(p, q);
        return p->r;
    }
    
    inline node* buildTree(int *s, int *e)
    {
        int *mid = s + ((e - s) >> 1);
        node *u = memPond.newNode(*mid);
        if(s <= mid - 1) u->link(0, buildTree(s, mid - 1));
        if(mid + 1 <= e) u->link(1, buildTree(mid + 1, e));
        u->update();
        return u;
    }
    
    inline void insert(int pos, int *s, int *e)
    {
        select(pos, pos + 1);
        root->l->link(1, buildTree(s, e));
        splay(root->l->r, nil);
    }
    
    inline void del(int pos, int tot)
    {
        memPond.dispose(select(pos - 1, pos + tot));
        root->l->r = nil;
        splay(root->l, nil);
    }
    
    inline void cover(int pos, int tot, int val)
    {
        node *v = select(pos - 1, pos + tot);
        v->cover(val); v->pushdown();
        splay(v, nil);
    }
    
    inline void reverse(int pos, int tot)
    {
        node *v = select(pos - 1, pos + tot);
        v->reverse(); v->pushdown();
        splay(v, nil);
    }
    
    inline int getSum(int pos, int tot)
    {
        return select(pos - 1, pos + tot)->sum;
    }
    
    inline int maxSum()
    {
        return root->ms? root->ms: root->mc;
    }
    
    inline void init(int *A, int n)
    {
        root = buildTree(A, A + n + 1);
    }
};

SplayTree T;
int A[MAXN] = {0}, n, m;

int main()
{
    char cmd[10];
    int pos, tot, c;
    n = getint(); m = getint();
    for(int i = 1; i <= n; i++)
        A[i] = getint();
    A[0] =  A[n + 1] = -INF;
    T.init(A, n);
    for(int i = 0; i < m; i++)
    {
        scanf("%s", cmd);
        switch (cmd[2])
        {
            case 'S':
                pos = getint(); tot = getint();
                for(int i = 0; i < tot; i++) A[i] = getint();
                T.insert(pos + 1, A, A + tot - 1);
                break;
            case 'L':
                pos = getint(); tot = getint();
                T.del(pos + 1, tot);
                break;
            case 'K':
                pos = getint(); tot = getint(); c = getint();
                T.cover(pos + 1, tot, c);
                break;
            case 'V':
                pos = getint(); tot = getint();
                T.reverse(pos + 1, tot);
                break;
            case 'T':
                pos = getint(); tot = getint();
                printf("%d\n", tot? T.getSum(pos + 1, tot): 0);
                break;
            case 'X':
                printf("%d\n", T.maxSum());
                break;
        }
    }
    return 0;
}