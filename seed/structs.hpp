#ifndef __HEADER

struct Pack {
    // represents a pack of words s[i..j1] to s[i..j2]
    int i, j1, j2;
    Pack(int i = 0, int j1 = -1, int j2 = -1)
    : i(i), j1(j1), j2(j2) {}
};


// minimum length of "long seed" is ceil(N / INV_EPS);
const int INV_EPS = 6;

struct MaxGap {
    int N, L;
    int mn[INV_EPS + 1];
    int mx[INV_EPS + 1];
    int max_gap_;

    void init(int n, int x = -1);
    int  max_gap();
    void join(MaxGap const& o);
};

#define __HEADER
#endif