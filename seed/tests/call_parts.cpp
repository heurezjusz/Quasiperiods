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


void algorithm(vector<int>& word, vector<Pack>&) {
    for (int c : word)
        cout << (char)(c + 'a');
    cout << "\n";
}
#define TEST_CALL_PARTS
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
    len = min(4 * len, n - 2);
    chosen.resize(n + 1);

    for (int i = 0; i < n; ++i)
        I[tree.suf_map[i]] = i;

    vector<Pack> _ign;
    call_parts(word, _ign, len);
}
