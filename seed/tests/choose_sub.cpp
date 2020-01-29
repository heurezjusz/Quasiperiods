#include <iostream>
#include "../lib/src/ukkonen.h"
using namespace std;

Tree *st;
string w;
vector<int> word;
vector<int> I;
vector<int> chosen;
int len;


#define TEST_CHOOSE
#include "../lib/src/algorithm.cpp"

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

    dfs_fill_chosen(ROOT, len);

    for (int sum = 0, i = 0; i < n; ++i) {
        sum += chosen[i];
        if (sum)
            printf("x");
        else
            printf(".");
    }
    puts("");
}
