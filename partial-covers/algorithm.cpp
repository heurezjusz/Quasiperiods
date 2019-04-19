#include "algorithm.h"
#include "hull.h"
#include "partition.h"
#include "ukkonen.h"
using namespace std;

namespace {
int N;
Tree st;
Partition P;
int new_label;

vector<vector<int>> list;
vector<int> dist;
vector<int> D;
vector<int> _D;
vector<int> cv;
vector<int> _cv;
vector<int> label_to_node;
vector<int> node_to_label;
vector<vector<int>> nodes_on_h;
}


void local_correct(int p, int q, int v) {
    // TODO
}


void lift(int h) {
    // TODO
}


void cst_count(int v) {
    vector<int> old_labels;
    vector<Change> change_list;
    int label = new_label++;
    label_to_node[label] = v;
    node_to_label[v] = label;

    for (auto const& it : st.nodes[v].edges) {
        _cv[v] += _cv[it.second.node];
        _D[v] += _D[it.second.node];
        old_labels.push_back(node_to_label[it.second.node]);
    }

    P.union_(old_labels, label, change_list);
    for (Change const& ch : change_list)
        local_correct(ch.x, ch.next, v);

    cv[v] = _cv[v] + _D[v] * st.nodes[v].depth;
    D[v] = _D[v];
}


void create_cst() {
    for (int i = 0; i < N; ++i) {
        // printf("wat\n");
        dist[i + 1] = N + 1;
        label_to_node[i + 1] = st.suf_map[i];
        node_to_label[st.suf_map[i]] = i + 1;
        list[N + 1].push_back(i + 1);

        _D[st.suf_map[i]] = 1;
        nodes_on_h[N - i].push_back(st.suf_map[i]);
        // printf("%d vs %d\n", N - i, st.nodes[st.suf_map[i]].depth);
    }
    new_label = N + 1;

    for (int h = N + 1; h > 0; --h) {
        lift(h);
        for (int v : nodes_on_h[h])
            if (!st.nodes[v].is_leaf())
                cst_count(v);
    }
}


void init_arrays(int N) {
    list.resize(N + 10);
    dist.resize(N + 10);
    D.resize(N + 10);
    _D.resize(N + 10);
    cv.resize(N + 10);
    _cv.resize(N + 10);
    label_to_node.resize(N + 10);
    node_to_label.resize(N + 10);
    nodes_on_h.resize(N + 10);
}


void algorithm(vector<int>& word, vector<int>& result) {
    N = word.size();
    word.push_back(-1);
    st.create(word);

    init_arrays(2 * st.size());
    create_cst();
}
