#include <iostream>
#include "../combine.h"
#include "../pack.h"
#include "../ukkonen.h"
using namespace std;

Tree* st;
string w;
vector<int> word;
vector<int> I;
vector<int> chosen;
int len;


void candidates_from_word(vector<int>& word, int offset,
                          vector<vector<Pack>>&) {
    cout << offset << " ";
    for (int c : word)
        cout << (char)(c + 'a');
    cout << "\n";
}
#define TEST_QUASISEED_PARTS
#include "../algorithm.cpp"

int main() {
    cin >> w >> len;
    for (char c : w)
        word.push_back(c - 97);
    word.push_back(-1);
    Tree tree;
    st = &tree;
    tree.create(word);
    I.resize(tree.size());
    int n = word.size() - 1;
    chosen.resize(n + 1);

    for (int i = 0; i < n; ++i)
        I[tree.suf_map[i]] = i;

    vector<Pack> _ign;
    quasiseed_parts(tree, 4 * len, _ign, 0, n + 10);
}
