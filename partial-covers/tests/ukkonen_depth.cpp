#include "../lib/src/ukkonen.h"
#include <iostream>
#include <string>
#include "../lib/src/cst.h"
using namespace std;


Tree st;


int main() {
    vector<int> word;
    vector<int> res;
    string sword;
    cin >> sword;
    int N = sword.size();
    for (char c : sword)
        word.push_back(c - 'a');
    word.push_back(-1);

    st.create(word);

    for (int h = 1; h <= N; ++h) {
        cout << "== " << h << " ==\n";
        for (int v : st.nodes_on_depth[h])
            st.print_word_chr(v);
    }
    cout << "== END ==\n";
}
