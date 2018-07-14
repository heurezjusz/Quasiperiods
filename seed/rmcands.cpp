#include "rmcands.hpp"
using namespace std;


namespace {
    vector<int> pref;
};

void right_and_mid_cands(Tree& tree, std::vector<Pack>& cands) {
    // word has additional '-1' at the end
    vector<int>& word = tree.word;
    int n = word.size();
    pref.resize(n);
    pref[n - 2] = 0;

    // reversed kmp
    for(int w, i = n - 3; i >= 0; --i) {
        w = pref[i + 1];
        while(w > 0 && word[i] != word[n - 2 - w])
            w = pref[n - 1 - w];
        pref[i] = w + (word[i] == word[n - 2 - w]);
    }
    
    for(int i = 0; i < n - 1; ++i)
        printf("%d ", pref[i]);
    puts("");
    
}