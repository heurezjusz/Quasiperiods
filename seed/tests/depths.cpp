#include <sdsl/suffix_trees.hpp>
#include <iostream>
#include "../utils/utils.hpp"
using namespace std;
using namespace sdsl;

int main() {
    cst_sada<> cst;
    string x;
    cin >> x;
    construct_im(cst, x, 1);
    
    int N = cst.nodes();
    vector<int> depth;
    depth.resize(N);

    get_depths(x, cst, depth);

    for(int i = 0; i < cst.nodes(); ++i) {
        cout << i << ": " << depth[i] << "\n";
    }
}
