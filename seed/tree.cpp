#include "rmcands.hpp"
#include <iostream>
using namespace std;

Tree st;
string w;
vector<int> word;
vector<int> lens;


int main() {
    cin >> w;
    for(char c: w)
        word.push_back(c - 97);
    word.push_back(-1);
    int n = w.size(); // |w| = n
    lens.resize(n + 10);
    st.create(word);

    vector<Pack> res;
    right_and_mid_cands_and_word_lens(st, res, lens, 6);
    
    printf("%d\n", (int) res.size());
    for(Pack p: res) {
        cout << p.i << " " << p.j1 << " " << p.j2 << "\n";
    }
    
    for(int i = 0; i <= n; ++i) {
        printf("%d:%d ", i, lens[i]);
    }
    puts("");
    
}