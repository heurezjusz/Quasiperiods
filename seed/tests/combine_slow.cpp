#include <algorithm>
#include <cassert>
#include <iostream>
#include <set>
#include "../pack.h"
using namespace std;

void combine(string& word, vector<vector<Pack>>& packs, vector<Pack>& res);


int main() {
    string w;
    int n;
    cin >> w;
    cin >> n;
    vector<vector<Pack>> inp;

    for (int ni, i = 0; i < n; ++i) {
        vector<Pack> v;
        cin >> ni;
        for (int I, j1, j2, j = 0; j < ni; ++j) {
            cin >> I >> j1 >> j2;
            v.emplace_back(I, j1, j2);
        }
        inp.push_back(v);
    }

    vector<Pack> res;

    combine(w, inp, res);
    cout << res.size() << "\n";
    for (auto p : res)
        cout << p.i << " " << p.j1 << " " << p.j2 << "\n";
}


string cut(string word, int a, int b) {
    string res = "";
    for (int i = a; i <= b; ++i)
        res += word[i];
    return res;
}

void addif(set<string>& s0, set<string>& s1, string s) {
    if (s0.find(s) != s0.end())
        s1.insert(s);
}

Pack get_idx(string& word, string s) {
    auto pos = word.find(s, 0);
    assert(pos != string::npos);
    int i = pos;
    int j = pos + s.size() - 1;
    return Pack{i, j, j};
}

bool cmp(Pack const& a, Pack const& b) {
    if (a.i == b.i) {
        return a.j1 < b.j1;
    }
    return a.i < b.i;
}


void compress(vector<Pack>& v, vector<Pack>& res) {
    sort(v.begin(), v.end(), cmp);

    for (Pack const& p : v) {
        // get_idx returns only i,j,j
        if (res.empty() || res.back().i != p.i || res.back().j2 != p.j1 - 1) {
            res.push_back(p);
        } else
            res.back().j2++;
    }
}

void combine(string& word, vector<vector<Pack>>& packs, vector<Pack>& res) {
    set<string> s;
    int N = packs.size();
    for (Pack const& p : packs[0])
        for (int j = p.j1; j <= p.j2; j++)
            s.insert(cut(word, p.i, j));

    for (int i = 1; i < N; ++i) {
        set<string> tmp;
        for (Pack const& p : packs[i])
            for (int j = p.j1; j <= p.j2; j++)
                addif(s, tmp, cut(word, p.i, j));
        s.swap(tmp);
    }

    vector<Pack> v;
    for (auto str : s)
        v.push_back(get_idx(word, str));

    compress(v, res);
}
