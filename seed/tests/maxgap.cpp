#include <cstdio>
#include "../structs/structs.hpp"

int main() {
    int n, l, x0;
    scanf("%d", &n);
    l = 1 + n / INV_EPS;
    MaxGap mg, m_;

    scanf("%d\n", &x0);
    mg.init(n, x0);
    printf("%d\n", mg.max_gap());

    for(int x, i = 1; i < n; ++i) {
        scanf("%d", &x);
        m_.init(n, x);
        mg.join(m_);
        if(mg.max_gap() < l) puts(".");
        else printf("%d\n", mg.max_gap());
    }
}