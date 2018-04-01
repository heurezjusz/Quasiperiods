#include "combine.hpp"
#include <vector>
using namespace std;

const int conn = 0;
const int change = 1;

struct Event {
    int type, a, b;
};

vector<int> FU;
vector<vector<Event>> event;
vector<Pack> result;
int N;


struct Clear {
    ~Clear() {
        FU.clear();
        event.clear();
        result.clear();
    }
};


void put_tree_on_events() {
    
}

/* combine itself */

void combine(string& word, vector<vector<Pack>>& packs, vector<Pack>& res) {
    puts("NOT IMPLEMENTED");
}

void combine(int, vector<int>&depths, vector<vector<Pack>>& packs, vector<Pack>& res) {
    Clear clr;
    N = packs.size();

    put_tree_on_events();
    
    puts("NOT IMPLEMENTED");
}
