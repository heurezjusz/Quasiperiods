#include <iostream>
#include "../lib/algorithm_single.h"

using namespace std;


int main() {
    ios_base::sync_with_stdio(0);

    vector<int> word;
    vector<int> res;
    double percent;
    string sword;
    cin >> sword >> percent;
    int N = sword.size();
    double min_positions_ = N * percent / 100.;
    int min_positions = min_positions_;
    if (min_positions_ > min_positions)
        min_positions++;

    for (char c : sword)
        word.push_back(c - 'a');
    cout << algorithm(word, min_positions, res) << "\n";

    for (int i : res)
        cout << i << " ";
    cout << "\n";
}
