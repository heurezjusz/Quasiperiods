#include "algorithm_single.h"
#include "cst_leafs.h"
#include "ukkonen_leafs.h"
using namespace std;


namespace {
int N;
Tree st;
int limit;
int min_len_found;
vector<int> found;
}  // namespace


void try_node(int v) {
    Node const& node = st.nodes[v];

    if (node.depth == st.nodes[node.parent].depth)
        return;
    if (node.cv < limit)
        return;
    if (st.nodes[node.parent].cv >= limit)
        return;

    int dx = (node.cv - limit) / node.D;
    int depth = node.depth - dx;

    if (min_len_found > depth) {
        min_len_found = depth;
        found.clear();
    }
    if (min_len_found == depth)
        found.push_back(node.any_leaf_pos);
}


int algorithm(vector<int>& word, int min_positions, vector<int>& result) {
    N = word.size();
    min_len_found = N;
    limit = min_positions;
    word.push_back(-1);
    st.create(word);
    extend_to_cst(st);

    for (int i = 1; i < st.size(); ++i)
        try_node(i);

    result = found;
    return min_len_found;
}
