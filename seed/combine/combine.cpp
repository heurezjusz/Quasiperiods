#include "combine.hpp"
#include "../ukkonen/ukkonen.hpp"
#include <vector>
using namespace std;

namespace {

const int conn = 0;
const int change = 1;

struct Event {
    int type, i, j, diff;
    Event(int type, int i, int j = 0, int diff = 0)
    : type(type), i(i), j(j), diff(diff) {}
};

struct Diff {
    int j, diff;
    Diff(int j, int diff)
    : j(j), diff(diff) {}
};

vector<int> FU;
vector<vector<Event>> event;
vector<vector<Diff>> diffs;
vector<Pack> result;
int N, wn, M;
Tree *st;


struct Clear {
    ~Clear() {
        FU.clear();
        event.clear();
        diffs.clear();
        result.clear();
        st = nullptr;
    }
};


void dfs_events(int id) {
    Node& node = st->nodes[id];
    event[node.depth].emplace_back(conn, id);
    FU[id] = id;
    for(auto const& it: node.edges)
        dfs_events(it.second.node);
}
//  end namespace
}


void combine(Tree& _st, vector<vector<Pack>>& packs, vector<Pack>& res) {
    Clear clr;
    N = _st.nodes.size();
    FU.resize(N);
    diffs.resize(N);
    M = packs.size();
    wn = _st.word.size();
    event.resize(wn + 10);

    _st.print();
    st = &_st;
    dfs_events(ROOT);
    
    for(int i = 0; i < M; ++i) {
        for(Pack const& p: packs[i]) {
            event[p.j2].emplace_back(change, _st.suf_map[p.i], p.j2, 1);
            if(p.j1)
                event[p.j1 - 1].emplace_back(change, _st.suf_map[p.i], p.j1 - 1, -1);
        }
    }

    for(int i = 0; i <= wn; ++i) {
        if(event[i].size()) {
            printf("events %d:\n", i);
            for(Event const& e: event[i]) {
                if(e.type == conn)
                    printf("- connect %d\n", e.i);
                else {
                    printf("- change suff: %d, j: %d, diff: %d\n", e.i, e.j, e.diff);
                }
            }
        }
    }

    puts("NOT IMPLEMENTED");
}
