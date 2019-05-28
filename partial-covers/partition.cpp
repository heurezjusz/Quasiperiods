#include "partition.h"
#include <algorithm>
using namespace std;


namespace JST {
vector<Change> global_changes;
int color;


void cp(Node* dst, Node* src) {
    dst->minval = src->minval;
    dst->maxval = src->maxval;
    dst->colormax = src->colormax;
    dst->colormin = src->colormin;
}


Node* join(Node* A, Node* B) {
    if (A == nullptr) {
        if (B != nullptr)
            B->_set_color(-color);
        return B;
    }
    if (B == nullptr) {
        A->_set_color(color);
        return A;
    }

    A->t0 = join(A->t0, B->t0);
    A->t1 = join(A->t1, B->t1);
    A->update();

    return A;
}


Node* create(int x, int BASE) {
    Node* root = new Node(x);
    x += BASE - 1;
    while (x != 1) {
        if (x & 1)
            root = new Node(nullptr, root);
        else
            root = new Node(root, nullptr);
        x >>= 1;
    }
    return root;
}


Node::Node(int x)
    : t0(nullptr),
      t1(nullptr),
      minval(x),
      maxval(x),
      colormin(0),
      colormax(0) {}


Node::Node(Node* t0, Node* t1) : t0(t0), t1(t1) {
    this->update();
}


void Node::update() {
    if (t0 == nullptr)
        cp(this, t1);
    else if (t1 == nullptr)
        cp(this, t0);
    else {
        minval = t0->minval;
        colormin = t0->colormin;
        maxval = t1->maxval;
        colormax = t1->colormax;

        if (t0->colormax != t1->colormin)
            global_changes.emplace_back(t0->maxval, t1->minval);
    }
}


void Node::_set_color(int color) {
    colormin = colormax = color;
}

};  // namespace JST


void Partition::init(int n, int max_label) {
    N = n;
    BASE = 1;
    while (BASE < N)
        BASE <<= 1;

    if (max_label == -1)
        max_label = N + 10;

    FU.reserve(max_label + 1);
    trees.reserve(max_label + 1);

    FU.push_back(-1);  // label 0 remains unused
    trees.push_back(nullptr);

    for (int i = 1; i <= N; ++i) {
        FU.push_back(i);
        trees.push_back(JST::create(i, BASE));
    }
}


int Partition::find(int x) {
    return FU[x] == x ? x : FU[x] = find(FU[x]);
}


void Partition::union_(vector<int> const& old_labels, int new_label,
                       vector<Change>& change_list) {
    JST::global_changes.clear();

    if ((int)trees.size() <= new_label) {
        FU.resize(2 * new_label);
        trees.resize(2 * new_label, nullptr);
    }

    trees[new_label] = trees[old_labels[0]];
    FU[old_labels[0]] = new_label;
    FU[new_label] = new_label;

    for (int i = 1; i < (int)old_labels.size(); ++i) {
        JST::color++;
        join(trees[new_label], trees[old_labels[i]]);
        FU[old_labels[i]] = new_label;
    }

    change_list.swap(JST::global_changes);
}
