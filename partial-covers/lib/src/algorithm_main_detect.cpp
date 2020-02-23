#include <iostream>
#include "cst.h"
#include "ukkonen.h"
using namespace std;


namespace {
int N;
Tree st;
int limit;
vector<int> found;
vector<int> lens;
// vector<int> times;
vector<int> covered;
}  // namespace


void try_node(int v) {
    Node const& node = st.nodes[v];

    if (node.depth == st.nodes[node.parent].depth)
        return;
    if (node.cv < limit)
        return;
    // if (st.nodes[node.parent].cv >= limit)
    // return;

    if (node.depth >= limit)
        return;

    // separated occurences
    if (node.cv == node.depth * node.D)
        return;

    found.push_back(node.any_leaf_pos);
    lens.push_back(node.depth);
    covered.push_back(node.cv);
}


void algorithm(vector<int>& word, int min_positions, vector<int>& result) {
    N = word.size();
    limit = min_positions;
    word.push_back(-1);
    st.create(word);
    extend_to_cst(st);

    for (int i = 1; i < st.size(); ++i)
        try_node(i);

    result = found;
}


int main() {
    ios_base::sync_with_stdio(0);

    vector<int> word;
    vector<int> res;
    double percent;
    string sword;
    cin >> sword >> percent;
    int N = sword.size();
    double min_positions_ = N * percent / 100.;
    int min_positions = min_positions_;
    if (min_positions_ > min_positions)
        min_positions++;

    // cout << "limit: " << min_positions << "\n";

    for (char c : sword)
        word.push_back(c - 'a');
    algorithm(word, min_positions, res);

    cout << found.size() << "\n";
    for (int i = 0; i < (int)found.size(); ++i)
        cout << found[i] << " " << lens[i] << " " << covered[i] << "\n";
}