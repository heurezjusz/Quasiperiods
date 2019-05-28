#include <iostream>
#include "algorithm_single.h"

using namespace std;


int main() {
    ios_base::sync_with_stdio(0);

    vector<int> word;
    vector<int> res;
    int percent;
    string sword;
    cin >> sword >> percent;
    int N = sword.size();
    int min_positions = N * percent / 100;

    for (char c : sword)
        word.push_back(c - 'a');
    cout << algorithm(word, min_positions, res) << "\n";

    for (int i : res)
        cout << i << " ";
    cout << "\n";
}
