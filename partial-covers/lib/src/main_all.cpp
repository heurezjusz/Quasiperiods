#include <iostream>
#include "algorithm_all.h"

using namespace std;


int main() {
    ios_base::sync_with_stdio(0);

    vector<int> word;
    vector<int> res;
    string sword;
    cin >> sword;
    int N = sword.size();

    for (char c : sword)
        word.push_back(c - 'a');
    algorithm(word, res);

    for (int i = 1; i <= N; ++i)
        cout << i << ": " << res[i] << "\n";
}
