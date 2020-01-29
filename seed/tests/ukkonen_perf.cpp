#include <iostream>
#include <map>
#include "../lib/src/ukkonen.h"
using namespace std;

Tree st;
string w;
vector<int> word;

int _lcp, N;
vector<int> lcp;
vector<int> suf_arr;


void dfs_count(int v) {
    Node& node = st.nodes[v];

    if (node.is_leaf()) {
        if (_lcp != NONE)
            lcp.push_back(_lcp);
        _lcp = node.depth;
        suf_arr.push_back(N - node.depth - 1);
    }

    map<int, Edge> edges(node.edges.begin(), node.edges.end());
    for (auto& it : edges) {
        Edge& e = it.second;
        _lcp = min(_lcp, node.depth);
        dfs_count(e.node);
    }
}


int main() {
    cin >> w;
    N = w.size() + 1;
    for (char c : w)
        word.push_back(c - 97);
    word.push_back(-1);
    st.create(word);

    _lcp = NONE;
    dfs_count(ROOT);
    lcp.push_back(0);

    for (int a : suf_arr)
        printf("%d ", a);
    puts("");
    for (int a : lcp)
        printf("%d ", a);
    puts("");
}
