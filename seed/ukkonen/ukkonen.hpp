#ifndef __UKKONEN
#define __UKKONEN
#include <vector>
#include <map>

struct Edge {
    int a, b, node;
};

struct Node {
    std::map<int, Edge> edges;
    int parent, depth;
    Node(int parent);
    bool is_leaf();
};

struct Tree {
    int root_;
    std::vector<Node> nodes;

    Tree();
    Node& root();
    void create(std::vector<int>& word);
};

#endif