#include "ukkonen.hpp"
using namespace std;

Node::Node(int parent) : parent(parent) {}

Tree::Tree() {
    nodes.emplace_back(0);
    root_ = 0;
}

Node& Tree::root() {
   return nodes[root_];
}
