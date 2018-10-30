#ifndef TEST_QUASISEED_PARTS
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
#endif  // QUASISEED_PARTS

#ifndef TEST_CHOOSE
#ifndef TEST_QUASISEED_PARTS
#ifndef TEST_CALL_SMALLER
void candidates_from_word(vector<int>& word, int offset,
                          vector<vector<Pack>> results) {
    word.push_back(-1);
}
#endif
#endif
#endif

#ifndef TEST_CALL_SMALLER
#ifndef TEST_CHOOSE
void quasiseed_parts(Tree& tree, int len, vector<Pack>& result) {
    vector<int>& word = tree.word;
    int n = word.size() - 1;

    vector<vector<Pack>> part_results;
    if (len >= n) {
        word.pop_back();
        candidates_from_word(word, 0, part_results);

    } else {
        vector<int> part_word;
        for (int i = 0; i < n - len; i += len / 2) {
            for (int j = 0; j < len; ++j)
                part_word.push_back(word[i + j]);
            candidates_from_word(part_word, i, part_results);
            part_word.clear();
        }

        for (int i = n - len; i < n; ++i)
            part_word.push_back(word[i]);
        candidates_from_word(part_word, n - len, part_results);
    }

    combine(tree, part_results, result);
}
#endif
#endif

#ifndef TEST_CHOOSE
#ifndef TEST_QUASISEED_PARTS
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
    // quasiseed_parts();
}

#endif
#endif
#endif
