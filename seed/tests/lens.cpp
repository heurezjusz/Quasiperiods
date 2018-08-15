#include "../rmcands.hpp"
#include <iostream>
using namespace std;

Tree st;
string w;
vector<int> word;
bector<int> lens;

int main() {
    cin >> w;
    for(char c: w)
        word.push_back(c - 97);
    word.push_back(-1);
    st.create(word);
    n = word.size();
    lens.resize(n + 10);

    vector<Pack> res;
    right_and_mid_cands(st, res, 6);
    
    printf("%d\n", (int) res.size());
    for(Pack p: res) {
        cout << p.i << " " << p.j1 << " " << p.j2 << "\n";
    }
}