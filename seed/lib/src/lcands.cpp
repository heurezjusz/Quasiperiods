#include "lcands.h"
#include <algorithm>
using namespace std;

#define val first
#define pos second

#include <cassert>
#include <cstdio>
#include <iostream>

namespace {
vector<int> pref;
vector<pair<int, int>> stack;
int n;
}

void lcands(vector<int> const& word, vector<Pack>& res) {
    n = word.size();
    pref.resize(n);

    for (int w = 0, i = 2; i <= n; ++i) {
        while (w > 0 && word[i - 1] != word[w])
            w = pref[w - 1];
        w += word[i - 1] == word[w];
        pref[i - 1] = w;
    }

    stack.emplace_back(-1, n - 1);  // w = [..., -1]
    for (int i, cycle, j = n - 2; j > 0; --j) {
        while (stack.back().val >= pref[j])
            stack.pop_back();

        i = pref[j];
        cycle = j - pref[j] + 1;
        if (i < cycle && pref[j - 1] < pref[j])
            res.emplace_back(i, j, stack.back().pos - 1);

        stack.emplace_back(pref[j], j);
    }

    // 0...n-1 + word has '#' at the end
    res.emplace_back(0, 0, n - 2);
}
