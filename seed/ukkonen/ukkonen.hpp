#ifndef __UKKONEN
#define __UKKONEN
#include <vector>
#include <map>

struct Edge {
    int a, b, node;
};

struct Node {
    std::map<int, Edge> edges;
    int parent;
    Node(int parent);
};

struct Tree {
    int root_;
    std::vector<Node> nodes;

    Tree();
    Node& root();
};

#endif