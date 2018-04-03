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
    int N;
    std::vector<int> word;
    std::vector<Node> nodes;
    std::vector<int> sa;
    std::vector<int> lcp;

    Tree();
    Node& root();
    Node& node(int id);
    void create(std::vector<int>& word);
    void get_word(int node, std::vector<int>& res);
    void print();

    // helpers
    void _add_node(int i);
    void _split_edge(int i);
    void _align();
    void _step_back();
    void _dfs(int v);
    void _connect_sl(int id);
};

#endif
