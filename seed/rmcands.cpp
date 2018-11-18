#ifdef LENS
#include "rmcands_lens.h"
#else
#ifdef MX16
#include "rmcands16.h"
#else
#include "rmcands.h"
#endif
#endif
using namespace std;

namespace {

    vector<int> pref;

#ifdef MX16
    vector<MaxGap<16>> occ;
#else
    vector<MaxGap<6>> occ;
#endif

    vector<Pack>* res;
    vector<int> lens;
    Tree* tree;
    int n;

    int dfs(int v, int tree_dep) {
        int pos = -1;
        Node& node = tree->nodes[v];
        // where is v in the word
        if (node.is_leaf()) {
            pos = n - 1 - node.depth;
            occ[v].init(n, pos);
        } else {
            occ[v].init(n);
            for (auto i : node.edges) {
                pos = max(pos, dfs(i.second.node, tree_dep + i.second.len()));
                occ[v].join(occ[i.second.node]);
            }
        }
        if (v == ROOT)
            return -1;
#ifdef LENS
        else {
            lens[node.depth]++;
            lens[tree->nodes[node.parent].depth]--;
        }
#endif

        // cycle size
        int cycle = n - 1 - pos - pref[pos];
        int dep_from = max(tree->nodes[node.parent].depth + 1,
                           max(cycle, occ[v].max_gap()));
        int dep_to = node.depth;

        if (dep_from <= dep_to)
            res->emplace_back(pos, pos + dep_from - 1, pos + dep_to - 1);

        return pos;
    }
};

#ifdef LENS
void right_mid_cands_and_subwords_lens(Tree& st, vector<Pack>& cands,
                                       vector<int>& lens_res)
#else
#ifdef MX16
void right_mid_cands16(Tree& st, vector<Pack>& cands)
#else
void right_mid_cands(Tree& st, vector<Pack>& cands)
#endif
#endif
{
    // word has additional '-1' at the end
    res = &cands;
    tree = &st;

    vector<int>& word = st.word;
    n = word.size();
    pref.resize(n);
    occ.resize(st.size());
    pref[n - 2] = 0;

    // reversed kmp
    for (int w, i = n - 3; i >= 0; --i) {
        w = pref[i + 1];
        while (w > 0 && word[i] != word[n - 2 - w])
            w = pref[n - 1 - w];
        pref[i] = w + (word[i] == word[n - 2 - w]);
    }

#ifdef LENS
    lens.resize(n);
#endif

    dfs(ROOT, 0);

#ifdef LENS
    for (int i = n - 2; i >= 0; --i)
        lens[i] += lens[i + 1];
    lens_res.swap(lens);
#endif
}
