#include <iostream>
#include <set>
#include "../combine/combine.hpp"
using namespace std;
using namespace sdsl;

int main() {
    string w; int n;
    cin >> w;
    cin >> n;
    vector<vector<Pack>> inp;

    for(int ni, i = 0; i < n; ++i) {
        vector<Pack> v;
        cin >> ni;
        for(int I, j1, j2, j = 0; j < ni; ++j) {
            cin >> I >> j1 >> j2;
            v.emplace_back(I, j1, j2);
        }
        inp.push_back(v);
    }

    vector<Pack> res;

    cst_sada<> cst;
    construct_im(cst, w, 1);

    combine(cst, inp, res);
    cout << res.size() << "\n";
    for(auto p: res)
        cout << p.i << " " << p.j1 << " " << p.j2 << "\n";
}

