#include "ukkonen.hpp"
using namespace std;

Edge::Edge(int target, int a, int b)
: a(a), b(b), node(target) {}

int Edge::len() const {
    return b - a + 1;
}

Node::Node(int parent) : parent(parent) {}

bool Node::is_leaf() {
    return edges.empty();
}

Tree::Tree() {
    nodes.emplace_back(NONE);
    root_ = 0;
}

Node& Tree::root() {
   return nodes[root_];
}



// ==== create ====
namespace {

    int active_node, active_len, last_creted;
    map<int, Edge>::iterator active_edge;

    int remainder;

    vector<int> word;
}

void Tree::split_edge(int i) {
    int id_mid = nodes.size();
    nodes.emplace_back(active_node);
    int id_leaf = nodes.size();
    nodes.emplace_back(id_mid);

    Node& mid = nodes[id_mid];
    Edge& e = active_edge->second;
    
    mid.edges[word[i]] = Edge{id_leaf, i};
    mid.edges[word[e.a + active_len]] = Edge{e.node, e.a + active_len};

    e.b = e.a + active_len - 1;
    e.node = id_mid;

    if(last_creted != NONE)
        nodes[last_creted].sl = id_mid;
    last_creted = id_mid;
}

void Tree::add_node(int i) {
    last_creted = NONE;
}

void Tree::create(vector<int>& word_) {
    active_node = root_;
    active_len = 0;
    word.swap(word_);
    
    for(int i = 0; i < (int)word.size(); ++i)
        add_node(i);

    word.swap(word_);
}
