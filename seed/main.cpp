#include <iostream>
#include "combine.h"
#include "lcands.h"
#include "pack.h"
#include "rmcands.h"
#include "ukkonen.h"
using namespace std;


int n;
vector<int> word;
vector<vector<Pack>> candidates;
vector<Pack> result;

int main() {
    string raw_word;
    cin >> raw_word;
    n = raw_word.size();

    word.resize(n + 10);
    candidates.resize(2);

    for (int i = 0; i < n; ++i)
        word[i] = raw_word[i];
    word[n] = -1;

    Tree tree;
    tree.create(word);
    lcands(word, candidates[0]);
    right_and_mid_cands(tree, candidates[1], -1);

    combine(tree, candidates, result);

    printf("%d\n", (int)result.size());
    for (auto const& p : result)
        cout << p.i << p.j1 << p.j2 << "\n";
}
