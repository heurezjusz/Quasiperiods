#ifndef TEST_CALL_PARTS
#ifndef TEST_CALL_SMALLER
#ifndef TEST_CHOOSE

#include "algorithm.h"
#include "combine.h"
#include "ukkonen.h"
using namespace std;

Tree* st;
vector<int> I;
vector<int> chosen;
int len;
#endif
#endif

void dfs_fill_chosen(int v, int len) {
    Node& node = st->nodes[v];

    if (!node.is_leaf()) {
        I[v] = st->size();
        for (auto const& e : node.edges) {
            dfs_fill_chosen(e.second.node, len);
            I[v] = min(I[v], I[e.second.node]);
        }
    }

    if (v != ROOT && node.depth >= len && st->nodes[node.parent].depth < len) {
        chosen[I[v]]++;
        chosen[I[v] + len]--;
    }
}
#endif


#ifndef TEST_CALL_SMALLER
#ifndef TEST_CHOOSE
void call_parts(vector<int>& word, vector<Pack>& result, int len) {}
#endif
#endif

#ifndef TEST_CHOOSE
#ifndef TEST_CALL_PARTS
void call_smaller(Tree& tree, vector<int>& word, vector<Pack>& result) {
    int sum = 0, n = word.size() - 1;
    vector<int> small_word;
    vector<vector<Pack>> small_results;
    int last = -1;
    vector<int> chosen_;
    chosen_.swap(chosen);

    for (int i = 0; i <= n; ++i) {
        sum += chosen_[i];
        if (sum == 0) {
            if (small_word.size() != 0) {
                algorithm(small_word, small_results.back());
                for (Pack& p : small_results.back())
                    p.move(last + 1);
                small_word.clear();
            }

            last = i;

        } else {
            small_word.emplace_back(word[i]);
        }
    }

    combine(tree, small_results, result);
}

#ifndef TEST_CALL_SMALLER

void algorithm(vector<int>& word, vector<Pack>& result) {
    word.push_back(-1);
    Tree tree;
    tree.create(word);
    st = &tree;
    I.resize(tree.size());
    int n = word.size() - 1;
    chosen.resize(n + 1);

    for (int i = 0; i < n; ++i)
        I[tree.suf_map[i]] = i;

    dfs_fill_chosen(ROOT, 5);

    call_smaller(tree, word, result);
}

#endif
#endif
#endif
