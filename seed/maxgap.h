#ifndef MAXGAP_H
#include <algorithm>

// recognizes MaxGaps >= N / P
template <int P>
struct MaxGap {
    int mn[P];
    int mx[P];
    int max_gap;

    void init(int n, int x = -1);
    void join(MaxGap const& o);
};


/* ========================= MaxGap implementation  ========================= */
template <int P>
void MaxGap<P>::init(int n, int x) {
    if (x != -1) {
        for (int i = 0; i < P; ++i)
            mn[i] = mx[i] = -1;
        max_gap = 0;

        int L = (n + P - 1) / P;
        int pos = x / L;
        mn[pos] = mx[pos] = x;
    } else
        max_gap = -1;
}


template <int P>
void MaxGap<P>::join(MaxGap const& o) {
    if (max_gap != -1) {
        int last = max_gap = -1;
        for (int i = 0; i < P; ++i) {
            if (o.mn[i] != -1) {
                if (mn[i] == -1) {
                    mn[i] = o.mn[i];
                    mx[i] = o.mx[i];
                } else {
                    mn[i] = std::min(mn[i], o.mn[i]);
                    mx[i] = std::max(mx[i], o.mx[i]);
                }
            }

            if (mn[i] != -1) {
                if (last == -1)
                    last = mn[i];
                max_gap =
                    std::max(max_gap, std::max(mn[i] - last, mx[i] - mn[i]));
                last = mx[i];
            }
        }
    }

    else {
        for (int i = 0; i < P; ++i) {
            mn[i] = o.mn[i];
            mx[i] = o.mx[i];
        }
        max_gap = o.max_gap;
    }
}
#define MAXGAP_H
#endif
