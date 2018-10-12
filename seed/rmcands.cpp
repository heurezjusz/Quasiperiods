#include "rmcands.hpp"
using namespace std;
// TODO: separate rmcands & lens

namespace {
    vector<int> pref;
    vector<MaxGap> occ;
    vector<Pack>* res;
    Tree* tree;
    int n, divisor;
    vector<int> lens;
};


int dfs(int v, int tree_dep) {
    int pos = -1;
    Node& node = tree->nodes[v];
    // where is v in the word
    if(node.is_leaf()) {
        node.depth -= 1;
        pos = n - 1 - node.depth;
        occ[v].init(n, divisor, pos);
        lens[tree_dep]--;
        lens[tree_dep + 1] ++;
    }
    else {
        occ[v].init(n, divisor);
        for(auto i: node.edges) {
            lens[tree_dep + 1]++;
            lens[tree_dep + i.second.len() + 1]--;
            pos = max(pos, dfs(i.second.node, tree_dep + i.second.len()));
            occ[v].join(occ[i.second.node]);
        }
    }

    if(v == ROOT)
        return -1;

    // cycle size
    int cycle = n - 1 - pos - pref[pos];
    int dep_from = max(tree->nodes[node.parent].depth + 1,
                       max(cycle, occ[v].max_gap()));
    int dep_to = node.depth;

    if(dep_from <= dep_to)
        res->emplace_back(pos, pos + dep_from - 1, pos + dep_to - 1);

    
    return pos;
}

// lens expect to be zeroed
void right_and_mid_cands_and_word_lens(Tree& st, vector<Pack>& cands, vector<int>& lens_, int _divisor) {
    // word has additional '-1' at the end
    res = &cands;
    tree = &st;
    divisor = _divisor;
    lens.swap(lens_);

    vector<int>& word = st.word;
    n = word.size();
    pref.resize(n);
    occ.resize(st.size());
    pref[n - 2] = 0;

    // reversed kmp
    for(int w, i = n - 3; i >= 0; --i) {
        w = pref[i + 1];
        while(w > 0 && word[i] != word[n - 2 - w])
            w = pref[n - 1 - w];
        pref[i] = w + (word[i] == word[n - 2 - w]);
    }
 
    dfs(ROOT, 0);
    for(int i = 1; i < n; ++i)
        lens[i] += lens[i - 1];
    lens.swap(lens_);
}