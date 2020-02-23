#include "../lib/src/ukkonen.h"
#include <iostream>
#include <map>
using namespace std;

Tree st;
string w;
int N;
vector<int> word;
int _lcp;

int sum;
vector<int> dp;
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
        sum += e.len();
        _lcp = min(_lcp, node.depth);
        dfs_count(e.node);
    }

    if (v != ROOT) {
        dp[node.depth]++;
        dp[st.nodes[node.parent].depth]--;
    }
    sum -= node.is_leaf();  // erasing subwords containing '$'
}

void print_word(int id) {
    vector<int> w;
    st.get_word(id, w);
    for (int a : w) {
        printf("%c", a == -1 ? '$' : 'a' + a);
    }
    puts("");
}

void dfs_print(Node& v, int id) {
    if (v.is_leaf()) {
        print_word(id);
        return;
    }

    map<int, Edge> edges(v.edges.begin(), v.edges.end());
    for (auto& it : edges) {
        Edge& e = it.second;
        dfs_print(st.node(e.node), e.node);
    }
}


int main() {
    cin >> w;
    N = w.size() + 1;
    for (char c : w)
        word.push_back(c - 97);
    word.push_back(-1);
    st.create(word);

    dp.resize(word.size() + 10);
    _lcp = NONE;
    dfs_count(ROOT);
    lcp.push_back(0);
    printf("%d\n", sum);

    for (int i = N - 1; i >= 0; --i)
        dp[i] += dp[i + 1];
    printf("%d", dp[0]);
    for (int i = 1; i <= N; ++i)
        printf(" %d", dp[i]);
    puts("");

    printf("%d", suf_arr[0]);
    for (int i = 1; i < N; ++i) {
        printf(" %d", suf_arr[i]);
    }
    puts("");

    dfs_print(st.root(), 0);
    printf("%d", lcp[0]);
    for (int i = 1; i < N; ++i) {
        printf(" %d", lcp[i]);
    }
    puts("");
}
