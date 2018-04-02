#ifndef __UKKONEN
#define __UKKONEN
#include <vector>
#include <map>

const int NONE = -1;

struct Edge {
    int a, b, node;
    Edge(int target = NONE, int a = NONE, int b = NONE);
    int len() const;
};

struct Node {
    std::map<int, Edge> edges;
    int parent, depth, sl;
    Node(int parent);
    bool is_leaf();
};

struct Tree {
    int root_;
    std::vector<int> word;
    std::vector<Node> nodes;
    std::vector<int> sa;
    std::vector<int> lcp;

    Tree();
    Node& root();
    void create(std::vector<int>& word);

    // helpers
    void add_node(int i);
    void split_edge(int i);
};

#endif
