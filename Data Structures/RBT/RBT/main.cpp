#include <cstdio>
#include <cstring>
using namespace std;

#define N 100007    //the maximum size of the RedBlack Tree

template <typename T> struct stack_{
    T s[N]; int size;
    
    inline stack_(): size(0) {}
    
    inline void push(const T &x){
        s[size++]=x;
    }
    
    inline void pop(){
        size--;
    }
    
    inline T top(){
        return s[size - 1];
    }
    
    inline int count(){
        return size;
    }
};

template <typename T> struct memoryPool{
    T nodes[N]; int nodes_it;
    stack_<T*> recycle;
    
    inline memoryPool(): nodes_it(0) {}
    
    inline T* newNode(){
        T *p;
        if (recycle.count()){
            p = recycle.top();
            recycle.pop();
        }
        else p = &nodes[nodes_it++];
        return p;
    }
    
    inline void deleteNode(T *p){
        recycle.push(p);
    }
};

template <typename keyType> struct RedBlackTree{
#define RED 0
#define BLACK 1
    
    struct node{
        keyType key;
        node *l,*r,*p;
        bool color;
    };
    memoryPool<node> pool;
    
    node *root, *nil;
    
    inline RedBlackTree(){
        nil = pool.newNode();
        nil->color = BLACK, nil->l = nil->r = nil->p = 0;
        root=nil;
    }
    
    inline node *newNode(const keyType &key){
        node *p = pool.newNode();
        p -> key = key, p->l = p->r = nil, p->color = RED;
        return p;
    }
    
    void RB_INSERT(node *z){
        node *y = nil, *x = root;
        while(x != nil){
            y = x;
            if(z->key < x->key)
                x = x->l;
            else x = x->r;
        }
        z->p = y;
        if(y == nil)
            root = z;
        else if(z->key < y->key)
            y->l = z;
        else y->r = z;
        RB_INSERT_FIXUP(z);
    }
    
    void RB_DELETE(node *z){
        node *y = z, *x;    //y: the node deleted or moved, x: used to save the original position of y
        bool y_original_color = y->color;   //save the original color of y
        if(z->l == nil){
            x = z->r;
            RB_TRANSPLANT(z, z->r);
        }
        else if(z->r == nil){
            x = z->l;
            RB_TRANSPLANT(z, z->l);
        }
        else{
            y = TREE_MINIMUM(z->r);
            y_original_color = y->color;
            x = y->r;
            if(y->p == z)
                x->p = y;
            else{
                RB_TRANSPLANT(y, y->r);
                y->r = z->r;
                y->r->p = y;
            }
            RB_TRANSPLANT(z, y);
            y->l = z->l;
            y->l->p = y;
            y->color = z->color;
        }
        
        if(y_original_color == BLACK)
            RB_DELETE_FIXUP(x);
        pool.deleteNode(z);
    }
    
    node *TREE_MINIMUM(node *z){
        while(z->l != nil)
            z = z->l;
        return z;
    }
    
    node *TREE_MAXIMUM(node *z){
        while(z->r != nil)
            z = z->r;
        return z;
    }
    
    void RB_INSERT_FIXUP(node *z){
        node *y;
        while(z->p->color == RED){
            if(z->p == z->p->p->l){
                y = z->p->p->r;
                if(y->color == RED){
                    z->p->color = y->color = BLACK;
                    z->p->p->color = RED;
                    z = z->p->p;
                }
                else{
                    if(z == z->p->r){
                        z = z->p;
                        LEFT_ROTATE(z);
                    }
                    z->p->color = BLACK;
                    z->p->p->color = RED;
                    RIGHT_ROTATE(z->p->p);
                }
            }
            else{
                y = z->p->p->l;
                if(y->color == RED){
                    z->p->color = y->color = BLACK;
                    z->p->p->color = RED;
                    z = z->p->p;
                }
                else{
                    if(z == z->p->l){
                        z = z->p;
                        RIGHT_ROTATE(z);
                    }
                    z->p->color  = BLACK;
                    z->p->p->color = RED;
                    LEFT_ROTATE(z->p->p);
                }
            }
        }
        root->color = BLACK;
    }
    
    void RB_DELETE_FIXUP(node *x){
        node *w;    //w: the brother of x
        while(x != root && x->color == BLACK){
            if(x == x->p->l){
                w = x->p->r;
                if(w->color == RED){
                    w->color = BLACK;
                    x->p->color = RED;
                    LEFT_ROTATE(x->p);
                    w = x->p->r;
                }
                
                if(w->l->color == BLACK && w->r->color == BLACK){
                    w->color = RED;
                    x = x->p;
                }
                else if(w->l->color == RED && w->r->color == BLACK){
                    w->color = RED;
                    w->l->color = BLACK;
                    RIGHT_ROTATE(w);
                    w = x->p->r;
                }
                else{
                    w->color = x->p->color;
                    w->r->color = BLACK;
                    x->p->color = BLACK;
                    LEFT_ROTATE(x->p);
                    x = root;   //to break from the while loop
                }
            }
            else{
                w = x->p->l;
                if(w->color == RED){
                    w->color = BLACK;
                    x->p->color = RED;
                    RIGHT_ROTATE(x->p);
                    w = x->p->l;
                }
                
                if(w->l->color == BLACK && w->r->color == BLACK){
                    w->color = RED;
                    x = x->p;
                }
                else if(w->r->color == RED && w->l->color == BLACK){
                    w->color = RED;
                    w->r->color = BLACK;
                    LEFT_ROTATE(w);
                    w = x->p->l;
                }
                else{
                    w->color = x->p->color;
                    w->l->color = BLACK;
                    x->p->color = BLACK;
                    RIGHT_ROTATE(x->p);
                    x = root;   //to break from the while loopr
                }
            }
        }
        x->color = BLACK;
    }
    
    inline void LEFT_ROTATE(node *x){//rotate the tree with root x left
        node *y = x->r;
        x->r = y->l;
        if(x->r != nil) x->r->p = x;
        y->p = x->p;
        if(x->p == nil) root = y;
        else if(x == x->p->l) x->p->l = y;
        else x->p->r = y;
        y->l = x;
        x->p = y;
    }
    
    inline void RIGHT_ROTATE(node *x){//rotate the tree with root x right
        node *y = x->l;
        x->l = y->r;
        if(x->l != nil) x->l->p = x;
        y->p = x->p;
        if(x->p == nil) root = y;
        else if(x == x->p->l) x->p->l = y;
        else x->p->r = y;
        y->r = x;
        x->p = y;
    }
    
    inline void RB_TRANSPLANT(node *u, node *v){//RB_TRANSPLANT: used to replace root u's subtree with root v's subtree
        if(u == root)
            root = v;
        else if(u ==  u->p->l)
            u->p->l = v;
        else u->p->r = v;
        v->p = u->p;
    }
#undef RED
#undef BLACK
};

struct client{
    int k, p;
    inline client():k(0), p(0) {}
    
    bool operator <(const client &B){
        return p < B.p;
    }
};

RedBlackTree<client> RBT;   //declaration of a RedBlack Tree: RedBlackTree<type> Name;

int main(){
    int cmd; client c;
    RedBlackTree<client>::node *node;
    
    while(scanf("%d", &cmd) && cmd){
        switch(cmd){
            case 0: break;
            case 1: scanf("%d%d", &c.k, &c.p); RBT.RB_INSERT(RBT.newNode(c)); break;
            case 2: if(RBT.root == RBT.nil) printf("0\n"); else { node = RBT.TREE_MAXIMUM(RBT.root); RBT.RB_DELETE(node); printf("%d\n", node->key.k); } break;
            case 3: if(RBT.root == RBT.nil) printf("0\n"); else { node = RBT.TREE_MINIMUM(RBT.root); RBT.RB_DELETE(node); printf("%d\n", node->key.k); } break;
        }
    }
    return 0;
}//Poj3481
