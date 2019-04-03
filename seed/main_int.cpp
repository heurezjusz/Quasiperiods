#include <iostream>
#include "algorithm.h"
using namespace std;


vector<int> word;
vector<Pack> result;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    word.resize(n);

    for (int i = 0; i < n; ++i)
        cin >> word[i];

    algorithm(word, result);

    cout << result.size() << "\n";
    for (auto const& p : result)
        cout << p.i << " " << p.j1 << " " << p.j2 << "\n";
}
