#include <sdsl/suffix_trees.hpp>
#include <iostream>
using namespace std;
using namespace sdsl;

const int maxN = 1e6 + 10;
int dep[maxN];

int main() {
    cst_sada<> cst;
    string x;
    cin >> x;

    construct_im(cst, x, 1);
    for(auto v: cst) {
        auto d = cst.depth(v);
        dep[cst.id(v)] = d;
    }
    for(int i = 0; i < cst.nodes(); ++i) {
        cout << i << ": " << dep[i] << "\n";
    }
}
