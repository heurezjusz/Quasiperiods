#include "../lib/src/cst.h"
#include <iostream>
#include <string>
#include "../lib/src/ukkonen.h"
using namespace std;


Tree st;

#define node st.nodes[v]


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
    extend_to_cst(st);

    for (int h = 1; h <= N; ++h) {
        cout << "== " << h << " ==\n";
        for (int v : st.nodes_on_depth[h]) {
            cout << node.cv << " " << node.D << " ";
            st.print_word_chr(v);
        }
    }
    puts("== END ==");
}
