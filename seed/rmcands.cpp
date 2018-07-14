#include "rmcands.hpp"
using namespace std;


namespace {
    vector<int> pref;
    vector<Pack>* res;
    Tree* tree;
    int n;
};


int dfs(int v) {
    int pos = -1;
    Node& node = tree->nodes[v];
    // where is v in the word
    if(node.edges.empty()) {
        node.depth -= 1;
        pos = n - 1 - node.depth;
    }
    else {
        for(auto i: node.edges)
            pos = max(pos, dfs(i.second.node));
    }

    if(v == ROOT)
        return -1;
    
//     tree->print_word_chr(v);
//     printf("pos = %d\n", pos);

    // cycle size
    int cycle = n - 1 - pos - pref[pos];
    int dep_from = max(tree->nodes[node.parent].depth + 1, cycle);
    int dep_to = node.depth;

//     printf("cycle = %d\n", cycle);
//     printf("dep = |%d %d|\n", dep_from, dep_to);
    
    if(dep_from <= dep_to) {
        res->emplace_back(pos, pos + dep_from - 1, pos + dep_to - 1);
//         printf("+(%d %d %d)\n", pos, pos + dep_from - 1, pos + dep_to - 1);
    }
    
    return pos;
}

void right_and_mid_cands(Tree& st, std::vector<Pack>& cands) {
    // word has additional '-1' at the end
    res = &cands;
    tree = &st;

    vector<int>& word = st.word;
    n = word.size();
    pref.resize(n);
    pref[n - 2] = 0;

    // reversed kmp
    for(int w, i = n - 3; i >= 0; --i) {
        w = pref[i + 1];
        while(w > 0 && word[i] != word[n - 2 - w])
            w = pref[n - 1 - w];
        pref[i] = w + (word[i] == word[n - 2 - w]);
    }
    
//     for(int i = 0; i < n - 1; ++i)
//         printf("%d ", pref[i]);
//     puts("");
 
    dfs(ROOT);
}