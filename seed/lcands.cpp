#include "lcands.hpp"
#include <algorithm>
using namespace std;

#define val first
#define pos second

#define a first
#define b second

#include <iostream>
#include <cstdio>
#include <cassert>
namespace {
    vector<int> pref;
    vector<pair<int, int>> stack;
    vector<vector<pair<int, int>>> packs;
    int n;

    void compress(int i, vector<Pack>& res) {
        if(packs[i].empty())
            return;

        Pack p(i, packs[i].back().a, packs[i].back().b);
        for(int idx = packs[i].size() - 2; idx >= 0; --idx) {
            auto const& pck = packs[i][idx];
            if(pck.a <= p.j2 + 1)
                p.j2 = max(p.j2, pck.b);
            else {
                res.push_back(p);
                p.j1 = pck.a;
                p.j2 = pck.b;
            }
        }
        res.push_back(p);
    }
}


void lcands(vector<int> const& word, vector<Pack> &res) {
    n = word.size();
    pref.resize(n);
    packs.resize(n);

    for(int w = 0, i = 2; i <= n; ++i) {
        while(w > 0 && word[i - 1] != word[w])
            w = pref[w - 1];
        w += word[i - 1] == word[w];
        pref[i - 1] = w;
    }

    stack.emplace_back(-1, n - 1); // w = [..., -1]
    for(int i, cycle, j = n - 2; j >= 0; --j) {
        while(stack.back().val >= pref[j])
            stack.pop_back();

        i = pref[j];
        cycle = j - pref[j] + 1;

        if(i < cycle)
            packs[i].emplace_back(j, stack.back().pos - 1);
        stack.emplace_back(pref[j], j);
    }
    for(int i = 0; i < n - 1; ++i)
        compress(i, res);
    packs.clear();
}
