#ifndef __PARTITION
#define __PARTITION
#include <set>
#include <vector>


struct Change {
    int x, next;

    Change(int x, int next) : x(x), next(next) {}
};


struct Partition {
    std::vector<int> label_to_set;
    std::vector<int> set_to_label;
    std::vector<int> element_to_set;
    std::vector<int> visited;
    std::vector<int> next;
    std::vector<std::set<int>> sets;
    int N;

    /* creates singletons {1},{2},...,{n} with labels 1,2,3,...,n */
    Partition(int n);

    /* returns label of set with element x */
    int find(int x);

    /* joins sets [old_labels] as new set [new_label] filling [change_list] */
/* assumption: all old_labels exists and are distinct */
    void union_(std::vector<int> const& old_labels, int new_label,
                std::vector<Change>& change_list);


    // === helpers
    int _union_id;

    int _union(int a, int b, std::vector<int>& change_list);
};

#endif
