#ifndef STRUCTS_H

struct Pack {
    // represents a pack of words s[i..j1] to s[i..j2]
    int i, j1, j2;
    Pack(int i = 0, int j1 = -1, int j2 = -1)
    : i(i), j1(j1), j2(j2) {}
};


#include <vector>

// recognizes MaxGaps >= N / parts
struct MaxGap {
    int N, L, parts;
    std::vector<int> mn;
    std::vector<int> mx;
    int max_gap_;

    void init(int n, int parts, int x = -1);
    int  max_gap();
    void join(MaxGap const& o);
};

#define STRUCTS_H
#endif
