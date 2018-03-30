#include <sdsl/suffix_trees.hpp>
#include <iostream>
using namespace std;
using namespace sdsl;

int main() {
    cst_sada<> cst;
    string x;
    cin >> x;
    construct_im(cst, x, 1);
    cout << "inner nodes : " << cst.nodes() - cst.csa.size() << endl;
    for(auto v: cst) {
        auto d = cst.depth(v);
        if(d)
            cout << cst.id(cst.parent(v)) << " - " << cst.id(v) << "\n";
    }

    for(auto v: cst) {
//     auto v = cst.select_child(cst.child(cst.root(), 'o'), 1);
//     auto v = cst.root();
        auto d = cst.depth(v);
        cout << cst.id(v) << ": " << d << "-[" << cst.lb(v) << "," << cst.rb(v) << "]";
        if(d)
            cout << "  " << extract(cst, v);
        else cout << "--";
        cout << endl;
    }
}
