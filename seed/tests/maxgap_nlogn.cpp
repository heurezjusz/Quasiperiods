#include "../maxgap_nlogn.h"
#include <cstdio>

int main() {
    int n, x0;
    scanf("%d", &n);
    MaxGap mg, m_, m__;

    scanf("%d\n", &x0);
    mg.init(n, x0);

    for (int x, i = 1; i < n; ++i) {
        scanf("%d", &x);
        if (i % 3 == 1)
            m_.init(n, x);
        else {
            m__.init(n, x);
            m_.join(m__);
        }
        if (i % 3 == 0) {
            mg.join(m_);
            printf("%d\n", mg.max_gap());
        }
    }
}
