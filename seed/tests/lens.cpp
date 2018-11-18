#include <iostream>
#include "../rmcands_lens.h"
using namespace std;

Tree st;
string w;
vector<int> word;
vector<int> lens;

int main() {
    cin >> w;
    for (char c : w)
        word.push_back(c - 97);
    word.push_back(-1);
    st.create(word);

    vector<Pack> _ign;
    right_mid_cands_and_subwords_lens(st, _ign, lens);

    for (int i = 1; i < (int)word.size(); ++i)
        printf("%d:%d\n", i, lens[i]);
}
