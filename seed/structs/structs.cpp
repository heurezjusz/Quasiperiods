#include "structs.hpp"
#include <algorithm>
#include <cassert>
using namespace std;

/* ========================= MaxGap ========================= */
void MaxGap::init(int n, int x) {
    N = n;
    L = N / INV_EPS + 1;

    for(int i = 0; i < INV_EPS; ++i)
        mn[i] = mx[i] = -1;
    max_gap_ = N + 1;

    if(x != -1) {
        int pos = x;
        if(L != 0)
            pos /= L;
        mn[pos] = mx[pos] = x;
        max_gap_ = max(x + 1, N - x);
    }
}

int MaxGap::max_gap() {
    return max_gap_;
}

void MaxGap::join(MaxGap const& o) {
    int last = max_gap_ = -1;
    for(int i = 0; i < INV_EPS; ++i) {
        if(o.mn[i] != -1) {
            if(mn[i] == -1) {
                mn[i] = o.mn[i];
                mx[i] = o.mx[i];
            } else {
                mn[i] = min(mn[i], o.mn[i]);
                mx[i] = max(mx[i], o.mx[i]);
            }
        }

        if(mn[i] != -1) {
            max_gap_ = max(max_gap_, max(mn[i] - last, mx[i] - mn[i]));
            last = mx[i];
        }
    }
    max_gap_ = max(max_gap_, N - last);
}
