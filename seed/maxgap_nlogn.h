#ifndef MAXGAP_H
#define MAXGAP_H

namespace maxgap {
    struct node {
        int no, maxgap, mn, mx;
        node *left, *right;

        node(int no, int x = -1);

        void update();
    };
}

struct MaxGap {
    int base;
    maxgap::node* root;

    void init(int n, int x = -1);
    int max_gap();
    void join(MaxGap const& o);
};

#endif
