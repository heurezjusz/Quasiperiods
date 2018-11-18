#ifndef MAXGAP_H
#include <algorithm>

// recognizes MaxGaps >= N / P
template <int P>
struct MaxGap {
    int mn[P];
    int mx[P];
    int max_gap_;

    void init(int n, int x = -1);
    int max_gap();
    void join(MaxGap const& o);
};


/* ========================= MaxGap implementation  ========================= */
template <int P>
void MaxGap<P>::init(int n, int x) {
    for (int i = 0; i < P; ++i)
        mn[i] = mx[i] = -1;
    max_gap_ = 0;

    if (x != -1) {
        int L = (n + P - 1) / P;
        int pos = x / L;
        mn[pos] = mx[pos] = x;
    }
}

template <int P>
int MaxGap<P>::max_gap() {
    return max_gap_;
}

template <int P>
void MaxGap<P>::join(MaxGap const& o) {
    int last = max_gap_ = -1;
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
            max_gap_ =
                std::max(max_gap_, std::max(mn[i] - last, mx[i] - mn[i]));
            last = mx[i];
        }
    }
}
#define MAXGAP_H
#endif
