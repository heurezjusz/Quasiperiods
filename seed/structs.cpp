#include "structs.hpp"
#include <algorithm>
#include <cstdio>
using namespace std;

/* ========================= MaxGap ========================= */
void MaxGap::init(int n, int _parts, int x)
{
    N = n;
    if(n >= _parts) {
        L = N / _parts; // minimum detected len
        parts = (N + L - 1) / L;
    } else {
        parts = N;
        L = 1;
    }
    mn.resize(parts);
    mx.resize(parts);

    for(int i = 0; i < parts; ++i)
        mn[i] = mx[i] = -1;
    max_gap_ = N + 1;

    if(x != -1) {
        int pos = x;
        if(L != 0)
            pos /= L;
        mn[pos] = mx[pos] = x;
    }
}

int MaxGap::max_gap() {
    return max_gap_;
}

void MaxGap::join(MaxGap const& o) {
    int last = max_gap_ = -1;
    for(int i = 0; i < parts; ++i) {
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
            if(last == -1)
                last = mn[i];
            max_gap_ = max(max_gap_, max(mn[i] - last, mx[i] - mn[i]));
            last = mx[i];
        }
    }
    if(max_gap_ == -1)
        max_gap_ = N + 1;
}
