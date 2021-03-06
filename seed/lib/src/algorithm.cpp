#ifndef TEST_QUASISEED_PARTS
#ifndef TEST_CALL_SMALLER
#ifndef TEST_CHOOSE

#include "algorithm.h"
#include "combine.h"
#include "lcands.h"
#include "rmcands.h"
#include "rmcands_16.h"
#include "rmcands_lens.h"
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

#ifndef TEST_CHOOSE
void call_smaller(Tree& tree, vector<int>& word, vector<Pack>& result,
                  int maxlen) {
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
                small_results.emplace_back();
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

    combine(tree, small_results, I, result, 0, maxlen);
}
#endif
#endif  // QUASISEED_PARTS

#ifndef TEST_CHOOSE
#ifndef TEST_QUASISEED_PARTS
#ifndef TEST_CALL_SMALLER
void candidates_from_word(vector<int>& word, int offset,
                          vector<vector<Pack>>& results) {
    word.push_back(-1);

    Tree st;
    st.create(word);
    results.emplace_back();
    right_mid_cands16(st, results.back());
    for (Pack& p : results.back())
        p.move(offset);

    results.emplace_back();
    lcands(word, results.back());
    for (Pack& p : results.back())
        p.move(offset);
}
#endif
#endif
#endif

#ifndef TEST_CALL_SMALLER
#ifndef TEST_CHOOSE
void quasiseed_parts(Tree& tree, int len, vector<Pack>& result, int minlen,
                     int maxlen) {
    if (minlen > maxlen)
        return;

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

    combine(tree, part_results, I, result, minlen, maxlen);
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
    if ((int)I.size() < tree.size())
        I.resize(tree.size());
    int n = word.size() - 1;
    chosen.resize(n + 1);

    for (int i = 0; i < n; ++i)
        I[tree.suf_map[i]] = i;

    vector<vector<Pack>> big_seeds;
    big_seeds.emplace_back();
    lcands(word, big_seeds.back());
    big_seeds.emplace_back();
    if (n > 6) {
        vector<int> lens;
        right_mid_cands_and_subwords_lens(tree, big_seeds.back(), lens);

        int chosen_len = 1;
        while (chosen_len <= (n + 3) / 4) {
            if (lens[4 * chosen_len - 3] + 4 * chosen_len - 4 >= 2 * n / 3)
                break;
            chosen_len++;
        }
        chosen_len--;

        if (chosen_len) {
            dfs_fill_chosen(ROOT, 2 * chosen_len - 1);
            call_smaller(tree, word, result, chosen_len);

            quasiseed_parts(tree, chosen_len * 16, result, chosen_len + 1,
                            n / 4);
            combine(tree, big_seeds, I, result, n / 4 + 1);

        } else
            combine(tree, big_seeds, I, result);

    } else {
        vector<int> _ign;
        right_mid_cands(tree, big_seeds.back());
        combine(tree, big_seeds, I, result);
    }
}

#endif
#endif
#endif
