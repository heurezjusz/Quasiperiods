#include "ukkonen.hpp"
using namespace std;

Node::Node(int parent) : parent(parent) {}

bool Node::is_leaf() {
    return edges.empty();
}

Tree::Tree() {
    nodes.emplace_back(0);
    root_ = 0;
}

Node& Tree::root() {
   return nodes[root_];
}


void Tree::create(vector<int>& word) {
    
}