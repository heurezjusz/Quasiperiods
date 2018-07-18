#ifndef __UKKONEN
#define __UKKONEN
#include <vector>
#include <map>

const int NONE = -1;
const int ROOT = 0;

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
    int N; // word size
    std::vector<int> word;
    std::vector<Node> nodes;
    std::vector<int> sa;
    std::vector<int> lcp;
    std::vector<int> suf_map;

    Tree();
    Node& root();
    Node& node(int id);
    int size();
    void create(std::vector<int>& word);
    void get_word(int node, std::vector<int>& res);
    void print();
    void print_word_chr(int v);

    // helpers
    void _add_node(int i);
    void _split_edge(int i);
    void _align(int i);
    void _step_back(int i);
    void _dfs(int v);
    void _connect_sl(int id);
    void _print_node(int v);
};


#endif
