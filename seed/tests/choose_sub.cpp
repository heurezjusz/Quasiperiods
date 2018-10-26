#include <iostream>
#include "../ukkonen.h"
using namespace std;

Tree st;
string w;
vector<int> word;
vector<int> I;
vector<int> chosen;
int len;

void dfs(int v) {
    Node& node = st.nodes[v];

    if (!node.is_leaf()) {
        I[v] = st.size();
        for (auto const& e : node.edges) {
            dfs(e.second.node);
            I[v] = min(I[v], I[e.second.node]);
        }
    }

    if (v != ROOT && node.depth >= len && st.nodes[node.parent].depth < len) {
        chosen[I[v]]++;
        chosen[I[v] + len]--;
    }
}


int main() {
    cin >> w >> len;
    for (char c : w)
        word.push_back(c - 97);
    word.push_back(-1);
    st.create(word);
    I.resize(st.size());
    int n = word.size() - 1;
    chosen.resize(n + 1);

    for (int i = 0; i < n; ++i)
        I[st.suf_map[i]] = i;

    dfs(ROOT);

    for (int sum = 0, i = 0; i < n; ++i) {
        sum += chosen[i];
        if (sum)
            printf("x");
        else
            printf(".");
    }
    puts("");
}
