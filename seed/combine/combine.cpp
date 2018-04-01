#include "combine.hpp"
#include <vector>
using namespace std;
using namespace sdsl;

const int conn = 0;
const int change = 1;

struct Event {
    int type, a, b;
};

vector<int> FU;
vector<vector<Event>> event;
vector<Pack> result;
int N;
cst_sada<>* cst;

struct Clear {
    ~Clear() {
        FU.Clear();
        event.clear();
        res.clear();
        cst = nullptr;
    }
};


void put_tree_on_events() {
    for(auto it = cst->begin_bottom_up(); it != cst->end_bottom_up(); it++)
        ;
}

/* combine itself */

void combine(string& word, vector<vector<Pack>>& packs, vector<Pack>& res) {
    cst_sada<> cst;
    construct_im(cst, word, 1);
    vector<int> dep;
    count_depths(word, cst, dep);
    combine(cst, dep, packs, res);
}

void combine(cst_sada<>& cst_, vector<int>&depths, vector<vector<Pack>>& packs, vector<Pack>& res) {
    Clear clr;
    N = packs.size();
    cst = &cst_;

    put_tree_on_events();
    
    puts("NOT IMPLEMENTED");
}
