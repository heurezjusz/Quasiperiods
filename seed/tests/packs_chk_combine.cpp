#include "../lib/src/combine.h"
#include "../lib/src/pack.h"
#include "../lib/src/ukkonen.h"

#include <fstream>
#include <iostream>
#include <set>
#include <string>
using namespace std;


void get_packs(const char* fname, vector<Pack>& res) {
    ifstream fin;
    fin.open(fname);

    int n;
    fin >> n;
    for (int i = 0; i < n; ++i) {
        int a, b, c;
        fin >> a >> b >> c;
        res.emplace_back(a, b, c);
    }
}


int main(int argc, char* argv[]) {
    if (argc != 4) {
        cout << "Usage: " << argv[0] << " input_str packages_1 packages_2\n";
        return 1;
    }

    string sword;
    ifstream fin;
    fin.open(argv[1]);
    fin >> sword;
    fin.close();
    vector<int> word;
    for (char c : sword)
        word.push_back(c);
    word.push_back(-1);

    vector<vector<Pack>> packs;
    for (int i = 0; i < 2; ++i) {
        packs.emplace_back();
        get_packs(argv[2 + i], packs.back());
    }


    Tree tree;
    tree.create(word);
    vector<int> buff;
    buff.resize(tree.size());

    vector<Pack> res;
    combine(tree, packs, buff, res);

    long long sum0, sum1, sum2;
    sum0 = sum1 = sum2 = 0;

    for (Pack const& p : packs[0])
        sum0 += p.j2 - p.j1 + 1;
    for (Pack const& p : packs[1])
        sum1 += p.j2 - p.j1 + 1;
    for (Pack const& p : res)
        sum2 += p.j2 - p.j1 + 1;

    if (sum0 == sum1 && sum1 == sum2)
        cout << "OK\n";
    else {
        cout << "WRONG\n"
             << "p1: " << sum0 << " p2: " << sum1 << " res: " << sum2 << "\n";
        exit(1);
    }
    return 0;
}
