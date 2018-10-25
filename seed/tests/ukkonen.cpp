#include "../ukkonen.h"
#include <iostream>
using namespace std;

Tree st;
string w;
vector<int> word;

int sum;
vector<int> dp;
void dfs_count(int v) {
    Node& node = st.nodes[v];

    for (auto& it : node.edges) {
        Edge& e = it.second;
        sum += e.len();
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
    for (auto& it : v.edges) {
        Edge& e = it.second;
        dfs_print(st.node(e.node), e.node);
    }
}


int main() {
    cin >> w;
    int N;
    N = w.size() + 1;
    for (char c : w)
        word.push_back(c - 97);
    word.push_back(-1);
    st.create(word);

    dp.resize(word.size() + 10);
    dfs_count(ROOT);
    printf("%d\n", sum);

    for (int i = N - 1; i >= 0; --i)
        dp[i] += dp[i + 1];
    printf("%d", dp[0]);
    for (int i = 1; i <= N; ++i)
        printf(" %d", dp[i]);
    puts("");

    printf("%d", st.sa[0]);
    for (int i = 1; i < N; ++i) {
        printf(" %d", st.sa[i]);
    }
    puts("");

    dfs_print(st.root(), 0);
    printf("%d", st.lcp[0]);
    for (int i = 1; i < N; ++i) {
        printf(" %d", st.lcp[i]);
    }
    puts("");
}
