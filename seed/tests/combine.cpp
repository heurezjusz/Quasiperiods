#include "../combine.h"
#include <iostream>
#include <vector>
using namespace std;


int main() {
    Tree st;
    string w;
    int n;
    cin >> w;
    vector<int> word;
    for (char c : w)
        word.push_back(c - 'a');
    word.push_back(-1);
    st.create(word);

    cin >> n;
    vector<vector<Pack>> inp;

    for (int ni, i = 0; i < n; ++i) {
        vector<Pack> v;
        cin >> ni;
        for (int I, j1, j2, j = 0; j < ni; ++j) {
            cin >> I >> j1 >> j2;
            v.emplace_back(I, j1, j2);
        }
        inp.push_back(v);
    }

    vector<Pack> res;
    vector<int> buff;
    buff.resize(st.size());

    combine(st, inp, buff, res);
    cout << res.size() << "\n";
    for (auto p : res)
        cout << p.i << " " << p.j1 << " " << p.j2 << "\n";
}
