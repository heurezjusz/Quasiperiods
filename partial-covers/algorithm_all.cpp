#include "algorithm_all.h"
#include "cst.h"
#include "hull.h"
#include "ukkonen.h"
using namespace std;


namespace {
int N;
Tree st;
vector<Segment> segments;
}


void get_segment_from_node(int v) {
    Node const& node = st.nodes[v];
    int pd = st.nodes[node.parent].depth;
    if (node.depth == pd)
        return;

    segments.emplace_back(pd + 1, node.depth,
                          node.cv + node.D * (pd + 1 - node.depth), node.D);
}


void algorithm(vector<int>& word, vector<int>& result) {
    N = word.size();
    word.push_back(-1);
    st.create(word);
    extend_to_cst(st);

    for (int i = 1; i < st.size(); i++)
        get_segment_from_node(i);

    vector<int> mid_results;
    get_hull(N, segments, mid_results);

    result.resize(N + 1, N);
    for (int i = N; i > 0; --i)
        result[mid_results[i]] = i;

    for (int i = N - 1; i > 0; --i)
        result[i] = min(result[i + 1], result[i]);
}
