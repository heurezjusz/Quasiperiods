#include "partition.h"
#include <algorithm>
using namespace std;


void Partition::init(int n) {
    N = n;
    _union_id = 0;
    element_to_set.resize(N + 1);
    visited.resize(N + 1);
    next.resize(N + 1);
    iota(element_to_set.begin(), element_to_set.end(), 0);
    label_to_set = set_to_label = element_to_set;

    sets.resize(N + 1);
    for (int i = 1; i <= N; ++i)
        sets[i].insert(i);
}


/* assumption: all old_labels exists and are distinct */
void Partition::union_(vector<int> const& old_labels, int new_label,
                       vector<Change>& change_list) {
    if ((int)label_to_set.size() <= new_label)
        label_to_set.resize(new_label + 1);

    int the_set = label_to_set[old_labels[0]];
    if (old_labels.size()) {
        ++_union_id;
        vector<int> raw_change_list;
        for (int i = 1; i < (int)old_labels.size(); ++i)
            the_set =
                _union(the_set, label_to_set[old_labels[i]], raw_change_list);

        for (int x : raw_change_list)
            change_list.emplace_back(x, next[x]);
    }

    label_to_set[new_label] = the_set;
    set_to_label[the_set] = new_label;
}


int Partition::find(int x) {
    return set_to_label[element_to_set[x]];
}


/* assuption: gets 2 non-empty, different sets */
int Partition::_union(int a, int b, vector<int>& change_list) {
    if (sets[a].size() > sets[b].size())
        swap(a, b);

    int prev = -1;
    for (int el : sets[a]) {
        auto it = sets[b].insert(el).first;
        element_to_set[el] = b;

        if (it != sets[b].begin()) {
            it--;

            if (*it != prev) {
                // updating prev data
                if (prev != -1) {
                    auto it_next = sets[b].upper_bound(prev);
                    if (it_next != sets[b].end()) {
                        next[prev] = *it_next;
                        if (visited[prev] != _union_id) {
                            change_list.push_back(prev);
                            visited[prev] = _union_id;
                        }
                    }
                }

                // updating element data
                next[*it] = el;
                if (visited[*it] != _union_id) {
                    change_list.push_back(*it);
                    visited[*it] = _union_id;
                }
            }
        }

        prev = el;
    }

    // updating prev last time
    auto it_next = sets[b].upper_bound(prev);
    if (it_next != sets[b].end()) {
        next[prev] = *it_next;
        if (visited[prev] != _union_id) {
            change_list.push_back(prev);
            visited[prev] = _union_id;
        }
    }

    sets[a].clear();

    return b;
}
