#include "ukkonen.h"
using namespace std;


Edge::Edge(int target, int a, int b) : a(a), b(b), node(target) {}

int Edge::len() const {
    return b - a + 1;
}

// ==== Node ====
Node::Node(int parent)
    : parent(parent), sl(NONE), letter(NONE), D(NONE), cv(NONE) {
#ifdef ADD_LEAF
// any_leaf_pos = NONE;
#endif
}

bool Node::is_leaf() {
    return edges.empty();
}


// ==== Tree ====
Tree::Tree() {
    nodes.emplace_back(NONE);
}


Node& Tree::root() {
    return nodes[ROOT];
}


Node& Tree::node(int id) {
    return nodes[id];
};


void Tree::get_word(int id, vector<int>& res) {
    if (id == ROOT)
        return;

    Node& node = nodes[id];
    get_word(node.parent, res);
    auto it = nodes[node.parent].edges.begin();
    while (it->second.node != id)
        it++;
    int a = it->second.a, b = it->second.b;
    if (b == -1)
        b = N - 1;
    for (int i = a; i <= b; i++)
        res.push_back(word[i]);
}


namespace {
void spaces(int n) {
    for (int i = 0; i < n; ++i)
        printf(" ");
}
}


void Tree::_print_node(int v) {
    printf("-%d:\n", v);
    for (auto const& it : nodes[v].edges) {
        Edge const& e = it.second;
        spaces(nodes[v].depth + 1);
        int b = e.b == -1 ? N - 1 : e.b;
        for (int i = e.a; i <= b; ++i)
            printf("%c", word[i] == -1 ? '$' : 'a' + word[i]);
        _print_node(e.node);
    }
}


void Tree::print() {
    _print_node(ROOT);
}


int Tree::size() {
    return nodes.size();
}


void Tree::print_word_chr(int v) {
    vector<int> w;
    get_word(v, w);
    for (int i : w)
        printf("%c", i == -1 ? '$' : i + 'a');
    puts("");
}

// ==== create ====
namespace {

int active_node, active_len, last_creted;
map<int, Edge>::iterator active_edge;

int remainder;
}

void Tree::_connect_sl(int id) {
    if (last_creted != NONE)
        nodes[last_creted].sl = id;
    last_creted = id;
}

void Tree::_split_edge(int i) {
    int id_mid = nodes.size();
    nodes.emplace_back(active_node);
    int id_leaf = nodes.size();
    nodes.emplace_back(id_mid);

    Node& mid = nodes[id_mid];
    Edge& e = active_edge->second;

    nodes[e.node].parent = id_mid;
    mid.edges[word[i]] = Edge{id_leaf, i};
    mid.edges[word[e.a + active_len]] = Edge{e.node, e.a + active_len, e.b};

    e.b = e.a + active_len - 1;
    e.node = id_mid;

    _connect_sl(id_mid);
}


void Tree::_align(int i) {
    // move active node if active_len > active_edge.len()

    while (active_len && active_edge->second.b != NONE &&
           active_edge->second.len() <= active_len) {
        active_node = active_edge->second.node;
        active_len -= active_edge->second.len();
        if (active_len)
            active_edge = nodes[active_node].edges.find(word[i - active_len]);
    }
}

void Tree::_step_back(int i) {
    if (active_node == ROOT) {
        if (!active_len)
            return;
        active_len--;
        if (active_len) {
            active_edge =
                nodes[ROOT].edges.find(word[active_edge->second.a + 1]);
            _align(i);
        }
        return;
    }

    if (nodes[active_node].sl == NONE)
        active_node = ROOT;
    else
        active_node = nodes[active_node].sl;
    if (active_len) {
        active_edge =
            nodes[active_node].edges.find(word[active_edge->second.a]);
    }
    _align(i);
}

void Tree::_add_node(int i) {
    last_creted = NONE;
    remainder++;

    while (remainder > 0) {
        if (!active_len) {
            active_edge = nodes[active_node].edges.find(word[i]);
            if (active_edge != nodes[active_node].edges.end()) {
                active_len++;
                _align(i);
                break;
            } else {
                int id_leaf = nodes.size();
                nodes.emplace_back(active_node);
                nodes[active_node].edges[word[i]] = Edge{id_leaf, i};
                remainder--;
                _step_back(i);
            }
        } else {
            if (word[i] == word[active_edge->second.a + active_len]) {
                active_len++;
                _align(i);
                break;
            } else {
                _split_edge(i);
                _step_back(i);
                if (!active_len)
                    _connect_sl(active_node);
                remainder--;
            }
        }
    }
}


void Tree::_dfs(int v) {
    Node& node = nodes[v];
    if (node.is_leaf()) {
        suf_map[N - node.depth] = v;
        node.depth -= 1;
#ifdef ADD_LEAF
        node.any_leaf_pos = N - node.depth;
#endif
    }

    for (auto& it : node.edges) {
        Edge& e = it.second;
        if (e.b == NONE)
            e.b = N - 1;
        nodes[e.node].letter = it.first;
        nodes[e.node].depth = node.depth + e.len();
        _dfs(e.node);

#ifdef ADD_LEAF
        node.any_leaf_pos = nodes[e.node].any_leaf_pos;
#endif
    }

    nodes_on_depth[node.depth].push_back(v);
}


void Tree::create(vector<int>& word_) {
    active_node = ROOT;
    active_len = 0;
    word = word_;
    N = word.size();

    nodes.reserve(4 * N);

    for (int i = 0; i < (int)word.size(); ++i)
        _add_node(i);

    nodes[ROOT].depth = 0;
    suf_map.resize(N);
    nodes_on_depth.resize(N + 10);
    _dfs(ROOT);
}


void Tree::add_node_at_edge_to_parent(int v, int depth) {
    Node& node = nodes[v];
    int new_v = nodes.size();
    nodes.emplace_back(node.parent);
    Node& new_node = nodes.back();

    new_node.depth = depth;
    nodes_on_depth[depth].push_back(new_v);
    new_node.letter = node.letter;
#ifdef ADD_LEAF
    new_node.any_leaf_pos = node.any_leaf_pos;
#endif

    Edge& edge = nodes[node.parent].edges[node.letter];
    int new_a = depth - nodes[node.parent].depth + edge.a;
    new_node.edges[word[new_a]] = Edge(v, new_a, edge.b);
    edge.b = new_a - 1;
    edge.node = new_v;

    node.letter = word[new_a];
    node.parent = new_v;
}