#ifndef __PARTITION
#define __PARTITION
#include <vector>


struct Change {
    int x, next;

    Change(int x, int next) : x(x), next(next) {}
};

namespace JST {
struct Node {
    Node *t0, *t1;
    int minval, maxval, colormin, colormax;

    Node(int x);
    Node(Node* t0, Node* t1);

    void update();

    void _set_color(int color);
};
}  // namespace JST

struct Partition {
    std::vector<JST::Node*> trees;
    std::vector<int> FU;
    int N, BASE;

    /* creates singletons {1},{2},...,{n} with labels 1,2,3,...,n */
    void init(int n, int max_label = -1);

    /* returns label of set with element x */
    int find(int x);

    /* joins sets [old_labels] as new set [new_label] filling [change_list] */
    /* assumption: all old_labels exists and are distinct */
    void union_(std::vector<int> const& old_labels, int new_label,
                std::vector<Change>& change_list);
};

#endif
