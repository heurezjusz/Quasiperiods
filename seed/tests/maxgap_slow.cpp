#include <cstdio>
#include <algorithm>
#include "../structs/structs.hpp"
using namespace std;
const int maxN = 1e6 + 10;

bool B[maxN];
int n, L;

int max_gap() {
    int res = -1, last = -1;
    for(int i = 0; i <= n; ++i)
        if(B[i]) {
            res = max(i - last, res);
            last = i;
        }
    return res;
}

int main() {
    scanf("%d", &n);
    L = 1 + n / INV_EPS;
    B[n] = 1;
    for(int x, i = 0; i < n; ++i) {
        scanf("%d", &x);
        B[x] = 1;
        x = max_gap();
        if(x < L) puts(".");
        else printf("%d\n", x);
    }
}