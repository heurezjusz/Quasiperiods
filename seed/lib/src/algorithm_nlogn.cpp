#include "algorithm.h"
#include "combine.h"
#include "lcands.h"
#include "pack.h"
#include "rmcands_nlogn.h"
#include "ukkonen.h"
using namespace std;


void algorithm(vector<int>& word, vector<Pack>& result) {
    vector<vector<Pack>> candidates;
    candidates.resize(2);
    word.push_back(-1);

    Tree tree;
    tree.create(word);
    lcands(word, candidates[0]);
    right_and_mid_cands(tree, candidates[1]);

    vector<int> buff;
    buff.resize(tree.size());

    combine(tree, candidates, buff, result);
}
