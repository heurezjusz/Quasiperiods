#include "combine.h"
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
    Diff(int j, int diff) : j(j), diff(diff) {}
};

vector<int> FU;
vector<int> I;       // I + 1
vector<int> opened;  // j2 + 1
vector<int> sum;
vector<vector<Event>> event;
vector<vector<Diff>> diffs;
vector<Pack> result;
int N, wn, M;
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

void dfs_events(int id) {
    Node& node = st->nodes[id];
    if (id != ROOT)
        event[st->nodes[node.parent].depth].emplace_back(conn, id);
    FU[id] = id;
    for (auto const& it : node.edges)
        dfs_events(it.second.node);
}

void connect_(int i) {
    FU[i] = st->nodes[i].parent;
}

void add_diff(Event const& e) {
    int v = find(e.i);
    diffs[v].emplace_back(e.j, e.diff);
}

void open(int v, int j) {
    opened[v] = j + I[v];
}

void close(int v, int j) {
    // j = j1 - 1
    result.emplace_back(I[v] - 1, I[v] + j, opened[v] - 1);
    opened[v] = 0;
}

void dfs_exec(int v) {
    Node& node = st->nodes[v];
    for (auto const& it : node.edges) {
        int child = it.second.node;
        dfs_exec(child);
        sum[v] += sum[child];
        if (opened[child]) {
            if (opened[v])
                close(child, node.depth - 1);
            else {
                I[v] = I[child];
                opened[v] = opened[child];
            }
        }
        if (!opened[v] && !I[v])
            I[v] = I[child];
    }

    if (sum[v] == M && !opened[v] &&
        (diffs[v].empty() || diffs[v][0].j != node.depth - 1))
        open(v, node.depth - 1);

    for (int i = 0; i < (int)diffs[v].size(); ++i) {
        sum[v] += diffs[v][i].diff;
        if (i + 1 < (int)diffs[v].size() && diffs[v][i].j == diffs[v][i + 1].j)
            continue;
        if (sum[v] == M && !opened[v])
            open(v, diffs[v][i].j);
        if (sum[v] < M && opened[v])
            close(v, diffs[v][i].j);
    }
}

//  end namespace
}


void combine(Tree& _st, vector<vector<Pack>>& packs, vector<Pack>& res) {
    Clear clr;

    N = _st.nodes.size();
    FU.resize(N);
    diffs.resize(N);
    I.resize(N);
    opened.resize(N);
    sum.resize(N);

    M = packs.size();
    wn = _st.word.size();
    event.resize(wn + 10);

    st = &_st;

    dfs_events(ROOT);
    for (int i = 0; i < M; ++i) {
        for (Pack const& p : packs[i]) {
            event[p.j2 - p.i].emplace_back(change, _st.suf_map[p.i], p.j2 - p.i,
                                           1);
            if (p.j1 - p.i)
                event[p.j1 - p.i - 1].emplace_back(change, _st.suf_map[p.i],
                                                   p.j1 - p.i - 1, -1);
        }
    }

    for (int i = wn; i >= 0; --i) {
        while (!event[i].empty()) {
            if (event[i].back().type == conn)
                connect_(event[i].back().i);
            else
                add_diff(event[i].back());
            event[i].pop_back();
        }
        if (i < wn)
            I[_st.suf_map[i]] = i + 1;
    }

    dfs_exec(ROOT);
    if (opened[ROOT])
        close(ROOT, -1);
    res.swap(result);
}
