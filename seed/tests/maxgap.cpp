#include "../maxgap.h"
#include <cstdio>

int main() {
    int n, l, x0;
    scanf("%d", &n);
    l = n / 6;
    MaxGap mg, m_;

    scanf("%d\n", &x0);
    mg.init(n, 6, x0);
    if (mg.max_gap() < l)
        puts(".");
    else
        printf("%d\n", mg.max_gap());

    for (int x, i = 1; i < n; ++i) {
        scanf("%d", &x);
        m_.init(n, 6, x);
        mg.join(m_);
        if (mg.max_gap() < l)
            puts(".");
        else
            printf("%d\n", mg.max_gap());
    }
}
