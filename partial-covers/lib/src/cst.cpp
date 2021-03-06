#include "cst.h"
#include "partition.h"
using namespace std;
#include <cstdio>


namespace {
int N;
Tree* st;
Partition P;
int new_label, inf;

vector<vector<int>> list;
vector<int> dist;
vector<int> _D;
vector<int> _cv;
vector<int> label_to_node;
vector<int> node_to_label;
}


void local_correct(int p, int q, int v) {
    int d = q - p, _d = dist[p];

    if (_d < st->nodes[v].depth)
        _cv[v] -= _d;
    else
        _D[v]--;

    if (d < st->nodes[v].depth)
        _cv[v] += d;
    else
        _D[v]++;

    dist[p] = d;
    list[d].push_back(p);
    /* "removal" is made by if in chosing vertices */
}


void lift(int h) {
    for (int i : list[h]) {
        if (dist[i] != h)
            continue;  // "removed" element

        int label = P.find(i), v = label_to_node[label];

        _D[v]++;
        _cv[v] -= h;
        if (h < N + 1 && st->nodes[st->nodes[v].parent].depth < h)
            st->add_node_at_edge_to_parent(v, h);
    }
}


inline void set_values(int v) {
    st->nodes[v].cv = _cv[v] + _D[v] * st->nodes[v].depth;
    st->nodes[v].D = _D[v];
}


void cst_count(int v) {
    vector<int> old_labels;
    vector<Change> change_list;
    int label = new_label++;
    label_to_node[label] = v;
    node_to_label[v] = label;

    for (auto const& it : st->nodes[v].edges) {
        _cv[v] += _cv[it.second.node];
        _D[v] += _D[it.second.node];
        old_labels.push_back(node_to_label[it.second.node]);
    }

    P.union_(old_labels, label, change_list);
    for (Change const& ch : change_list)
        local_correct(ch.x, ch.next, v);

    set_values(v);
}


void create_cst() {
    P.init(N);

    for (int i = 0; i < N; ++i) {
        dist[i + 1] = inf;
        label_to_node[i + 1] = st->suf_map[i];
        node_to_label[st->suf_map[i]] = i + 1;

        _D[st->suf_map[i]] = 1;
        _cv[st->suf_map[i]] = 0;

        set_values(st->suf_map[i]);
    }
    new_label = N + 1;

    for (int h = N + 1; h > 0; --h) {
        lift(h);
        for (int v : st->nodes_on_depth[h])
            if (!st->nodes[v].is_leaf())
                cst_count(v);
    }
}


void init_arrays(int N) {
    list.resize(N + 10);
    dist.resize(N + 10);
    _D.resize(N + 10);
    _cv.resize(N + 10);
    label_to_node.resize(N + 10);
    node_to_label.resize(N + 10);
}


void extend_to_cst(Tree& _st) {
    st = &_st;
    N = st->N - 1;
    inf = N + 1;
    init_arrays(2 * _st.size());
    create_cst();
}
