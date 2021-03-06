#include <algorithm>
#include <cassert>
#include <cstdio>
#include <vector>
#include "../lib/src/partition.h"
#include "print_jst_node.h"
using namespace std;

const int maxN = 1e5 + 10;

Partition* P;
int N, new_label;


bool cmp(Change const& a, Change const& b) {
    return a.x < b.x;
}


void ans() {
    int a, b;
    scanf("%d%d", &a, &b);
    printf("> %d %d <\n", a, b);

    a = P->find(a);
    b = P->find(b);
    assert(a != b);

    vector<Change> change_list;
    P->union_({a, b}, new_label, change_list);

    sort(change_list.begin(), change_list.end(), cmp);

    puts("CHANGES");
    for (auto const& ch : change_list)
        printf("%d %d\n", ch.x, ch.next);

    // puts("NEXT");
    // for (int i = 1; i <= N; ++i)
    //     printf("%d ", nxt[i]);

    puts("\nJOINED LIST");
    print_node_elements(P->trees[new_label], P->BASE);
    puts("");
    // printf("[%d] ", P->BASE);
    // print_tree(P->trees[new_label], P->BASE);
    // puts("");
}


int main() {
    scanf("%d", &N);
    P = new Partition();
    P->init(N);
    new_label = N;

    for (int i = 1; i < N; ++i) {
        new_label++;
        ans();
    }
}
