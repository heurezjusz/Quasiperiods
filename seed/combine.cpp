#include "combine.h"
#include <vector>
using namespace std;

namespace {

const int CONNECT_FU = 0;
const int CHANGE = 1;

struct Event {
    int type, node, depth, diff;
    Event(int type, int node, int depth = 0, int diff = 0)
        : type(type), node(node), depth(depth), diff(diff) {}
};

struct Diff {
    int depth, diff;
    Diff(int depth, int diff) : depth(depth), diff(diff) {}
};

vector<int> FU;
vector<int> I;       // I + 1
vector<int> opened;  // j2 + 1
vector<int> sum;
vector<vector<Event>> event;
vector<vector<Diff>> diffs;
vector<Pack> result;
int tree_N, word_N, M;
Tree* st;


struct Clear {
    ~Clear() {
        FU.clear();
        event.clear();
        diffs.clear();
        result.clear();
        opened.clear();
        I.clear();
        sum.clear();
        st = nullptr;
    }
};


int find(int x) {
    return FU[x] == x ? x : FU[x] = find(FU[x]);
}


void dfs_add_FU_events(int id) {
    Node& node = st->nodes[id];
    if (id != ROOT)
        event[st->nodes[node.parent].depth].emplace_back(CONNECT_FU, id);
    FU[id] = id;
    for (auto const& it : node.edges)
        dfs_add_FU_events(it.second.node);
}


void connect_(int i) {
    FU[i] = st->nodes[i].parent;
}


void add_diff(Event const& e) {
    int v = find(e.node);
    diffs[v].emplace_back(e.depth, e.diff);
}


void open(int v, int depth) {
    opened[v] = depth;
}


void close(int v, int depth) {
    result.emplace_back(I[v] - 1, I[v] - 1 + depth, I[v] + opened[v] - 2);
    opened[v] = 0;
}


void dfs_exec_events(int v) {
    Node& node = st->nodes[v];

    // go for kids, sum results
    for (auto const& it : node.edges) {
        dfs_exec_events(it.second.node);
        sum[v] += sum[it.second.node];
    }

    // get only events on your depth
    int current_event;
    for (current_event = 0; current_event < (int)diffs[v].size() &&
                            diffs[v][current_event].depth == node.depth;
         current_event++) {
        sum[v] += diffs[v][current_event].diff;
    }

    // get_some_I, see whether you are opened & some of them too
    for (auto const& it : node.edges) {
        int a = it.second.node;
        if (!I[v])
            I[v] = I[a];
        if (opened[a]) {
            if (opened[v])
                close(a, node.depth);  // as if -1 were here (it actually was)
            else if (sum[v] == M) {
                opened[v] = opened[a];
                I[v] = I[a];
            } else  // v should be closed, so kid too
                close(a, node.depth);
        }
    }
    // the case when v should be opened, but no kid was
    if (sum[v] == M && !opened[v])
        open(v, node.depth);

    for (; current_event < (int)diffs[v].size(); current_event++) {
        Diff& diff = diffs[v][current_event];
        // printf("[%d] %d at %d\n", v, diff.diff, diff.depth);
        sum[v] += diff.diff;
        if (sum[v] == M && !opened[v])
            open(v, diff.depth);
        if (sum[v] != M && opened[v])
            close(v, diff.depth);
    }
}


//  end namespace
}


void combine(Tree& _st, vector<vector<Pack>>& packs, vector<Pack>& res) {
    Clear clr;

    tree_N = _st.nodes.size();
    FU.resize(tree_N);
    diffs.resize(tree_N);
    I.resize(tree_N);
    opened.resize(tree_N);
    sum.resize(tree_N);

    M = packs.size();
    word_N = _st.word.size();
    event.resize(word_N + 10);

    st = &_st;

    for (int i = 0; i < M; ++i) {
        for (Pack const& p : packs[i]) {
            event[p.j2 - p.i + 1].emplace_back(CHANGE, _st.suf_map[p.i],
                                               p.j2 - p.i + 1, 1);
            event[p.j1 - p.i].emplace_back(CHANGE, _st.suf_map[p.i], p.j1 - p.i,
                                           -1);
        }
    }
    dfs_add_FU_events(ROOT);

    for (int i = word_N; i >= 0; --i) {
        while (!event[i].empty()) {
            if (event[i].back().type == CONNECT_FU)
                connect_(event[i].back().node);
            else
                add_diff(event[i].back());
            event[i].pop_back();
        }
        if (i < word_N)
            I[_st.suf_map[i]] = i + 1;
    }

    dfs_exec_events(ROOT);
    res.swap(result);
}
