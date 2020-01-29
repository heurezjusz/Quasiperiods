#include <iostream>
#include "../lib/src/algorithm.h"
using namespace std;


vector<int> word;
vector<Pack> result;

int main() {
    string raw_word;
    cin >> raw_word;
    int n = raw_word.size();

    word.resize(n);

    for (int i = 0; i < n; ++i)
        word[i] = raw_word[i];

    algorithm(word, result);

    cout << result.size() << "\n";
    for (auto const& p : result)
        cout << p.i << " " << p.j1 << " " << p.j2 << "\n";
}
