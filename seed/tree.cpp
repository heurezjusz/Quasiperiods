#include "rmcands.hpp"
#include <iostream>
using namespace std;

Tree st;
string w;
vector<int> word;

int main() {
    cin >> w;
    for(char c: w)
        word.push_back(c - 97);
    word.push_back(-1);
    st.create(word);

    vector<Pack> res;
    right_and_mid_cands(st, res);
    for(Pack p: res) {
        cout << p.i << " " << p.j2 << " " << p.j2 << "\n";
    }
}