/* Na podstawie rozwiązania zadania Rotacje na drzewie (18 OI) autorstwa Tomasza
 * Kociumaki */
#include "maxgap.h"

#include <algorithm>
#include <climits>
#include <cstdio>
using namespace std;
using namespace maxgap;
typedef long long LL;


node::node(int no, int x) : no(no), maxgap(-1), left(nullptr), right(nullptr) {
    if (x == -1) {
        mn = INT_MAX;
        mx = INT_MIN;
    } else
        mn = mx = x;
};

void node::update() {
    if (left == nullptr) {
        maxgap = -1;
        return;
    }
    mn = min(mn, left->mn);
    mx = max(mx, right->mx);
    maxgap = max(max(left->maxgap, right->maxgap), mx - mn);
}

int sz;

inline int clz(int x) {
    return x ? __builtin_clz(x) : 0;
}

inline int lca(node* x, node* y) {
    int n = x->no;
    int m = y->no;
    if (n < m)
        swap(n, m);
    n >>= (__builtin_clz(m) - __builtin_clz(n));
    if (n == m)
        return n;
    return n >>= (__builtin_clz(1) + 1 - __builtin_clz(n ^ m));
}

inline bool leftOf(node* x, node* y) {
    int n = x->no;
    int m = y->no;
    m >>= (__builtin_clz(n) - __builtin_clz(m) - 1);
    return !(m & 1);
}


node* merge(node* A, node* B) {
    if (A == nullptr)
        return nullptr;
    if (A->no == B->no) {
        A->left = merge(A->left, B->left);
        A->right = merge(A->right, B->right);
        delete B;
        A->update();
        return A;
    } else {
        int no = lca(A, B);
        if (no == B->no) {
            if (leftOf(B, A)) {  // tak jakby A->right == nullptr
                B->left = merge(A, B->left);
            } else {  // tak jakby A->left == nullptr
                B->right = merge(A, B->right);
            }
            B->update();
            return B;
        } else if (no == A->no) {
            if (leftOf(A, B)) {  // tak jakby B->right == nullptr
                A->left = merge(A->left, B);
            } else {  // tak jakby B->left == nullptr
                A->right = merge(A->right, B);
            }
            A->update();
            return A;
        } else {
            node* nd = new node(no);
            if (leftOf(nd, A)) {  // tak jakby A.right == B.left == nullptr
                nd->left = A;
                nd->right = B;
            } else {
                nd->left = B;
                nd->right = A;
            }
            nd->update();
            return nd;
        }
    }
}


void MaxGap::init(int n, int, int x) {
    base = 1 << (32 - clz(n - 1));
    if (x != -1) {
        root = new node(base + x, x);
    } else
        root = nullptr;
}


void MaxGap::join(MaxGap const& other) {
root = merge(root, other.root);
}
