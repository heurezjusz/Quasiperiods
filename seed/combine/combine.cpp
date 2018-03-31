#include "combine.hpp"
using namespace std;
using namespace sdsl;

void combine(string& word, vector<vector<Pack>>& packs, vector<Pack>& res) {
    cst_sada<> cst;
    construct_im(cst, word, 1);
    combine(cst, packs, res);
}

void combine(cst_sada<>& cst, vector<vector<Pack>>& packs, vector<Pack>& res) {
    puts("NOT IMPLEMENTED");
}
