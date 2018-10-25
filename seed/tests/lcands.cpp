#include "../lcands.h"
#include <iostream>
#include <string>
using namespace std;

string s;
vector<int> w;
vector<Pack> res;

int main() {
    cin >> s;
    for (char c : s)
        w.push_back(c);
    w.push_back(-1);
    lcands(w, res);
    printf("%d\n", (int)res.size());
    for (Pack const& p : res)
        cout << p.i << " " << p.j1 << " " << p.j2 << "\n";
}
