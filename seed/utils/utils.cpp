#include "utils.hpp"
#include <iostream>
using namespace std;
using namespace sdsl;

void get_sa(std::string& word, sdsl::cst_sada<>& cst, std::vector<int>& res) {
    int i = 0;
    for(auto v: cst)
        if(cst.is_leaf(v)) {
            res[i++] = cst.sn(v);
//             cout << extract(cst, v) << "\n";
        }
//     for(int i = 0; i < res.size(); ++i) cout << res[i] << " ";
//     cout << "\n";
}

void get_lcp(std::string& word, std::vector<int>& sa, std::vector<int>& lcp) {
    int n = word.size();
    vector<int> _sa;
    _sa.resize(n + 1);
    for(int i = 0; i < n; ++i)
        _sa[sa[i]] = i;
    for(int pos, sn = 0; sn < n; ++sn) { // suffix number
        pos = _sa[sn]; // pos in suffix array

//         cout << sn << " at pos " << pos << "\n";
        while(max(sn, sa[pos + 1]) + lcp[pos] < n &&  word[lcp[pos] + sn] == word[lcp[pos] + sa[pos + 1]])
            lcp[pos]++;
//         cout << "result for " << sn << " = " << lcp[pos] << "\n";
        lcp[sa[sn + 1]] = max(lcp[pos] - 1, lcp[sa[sn + 1]]);
    }
//     for(int i = 0; i <= n; ++i) {
//         cout << "lcp["<< i <<"]=" << lcp[i] << "\n";
//     }
}

void get_depths(std::string& word, sdsl::cst_sada<>& cst, std::vector<int>& depth) {
    int n = word.size();
    vector<int> sa, lcp;
    sa.resize(n + 1);
    lcp.resize(n + 1);
    get_sa(word, cst, sa);
    get_lcp(word, sa, lcp);

    vector<int> dlcp;
    int N = cst.nodes();
    dlcp.resize(N);
    int i = 0;
    for(auto it = cst.begin_bottom_up(); it != cst.end_bottom_up(); it++) {
        auto v = *it;
        int vid = cst.id(v);
        if(cst.is_leaf(v)) {
            int sn = cst.sn(v);
            depth[vid] = n - sn;
            dlcp[vid] = lcp[i];
            i++;
        }
        if(v != cst.root()) {
            int pid = cst.id(cst.parent(v));
            if(!depth[pid])
                depth[pid] = dlcp[vid];
            dlcp[pid] = dlcp[vid];
        }
    }
}