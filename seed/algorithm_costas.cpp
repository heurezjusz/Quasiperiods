#include <iostream>
#include <vector>

#include "algorithm.h"
#include "pack.h"
using namespace std;

int N;
vector<int> p;

void kmp(vector<int> const& word) {
    p.resize(N);
    for (int len = 0, i = 1; i <= N; ++i) {
        while (len > 0 && word[i] != word[len])
            len = p[len - 1];
        if (word[i] == word[len])
            len++;
        p[i] = len;
    }
}


void algorithm(vector<int>& word, vector<Pack>& result) {
    N = word.size();
    kmp(word);
    for (int i : p)
        cout << i << " ";
    cout << "\n";

    /* easy seeds */
    int period = N - p[N - 1];
    for (int i = 0; i < period; i++) {
        if (i + period > N)
            break;
        result.emplace_back(i, i + period - 1, N - 1);
    }
}
