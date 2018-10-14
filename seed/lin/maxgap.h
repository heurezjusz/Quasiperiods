#ifndef MAXGAP_H
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

#define MAXGAP_H
#endif
