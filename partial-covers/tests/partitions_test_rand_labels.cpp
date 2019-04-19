#include "../partition.h"
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <vector>
using namespace std;

const int maxN = 1e5 + 10;

Partition* P;
int N, new_label;


void ans() {
    int a, b;
    scanf("%d%d", &a, &b);
    printf("> %d %d <\n", a, b);

    a = P->find(a);
    b = P->find(b);
    assert(a != b);

    vector<Change> change_list;
    P->union_({a, b}, new_label, change_list);

    puts("CHANGES");
    for (auto const& ch : change_list)
        printf("%d %d\n", ch.x, ch.next);

    puts("NEXT");
    for (int i = 1; i <= N; ++i)
        printf("%d ", P->next[i]);

    puts("\nJOINED LIST");
    for (int a : P->sets[P->label_to_set[new_label]])
        printf("%d ", a);
    puts("");
}


int randint(int a, int b) {
    return a + rand() % (b - a + 1);
}


vector<int> labels;
void gen_labels() {
    set<int> s;
    while (N > (int)s.size())
        s.insert(randint(2 * N, 1e5));
    for (int i : s)
        labels.push_back(i);
    random_shuffle(labels.begin(), labels.end());
}


int main() {
    scanf("%d", &N);
    P = new Partition();
    P->init(N);

    srand(42 + N);

    gen_labels();
    for (int i = 1; i < N; ++i) {
        new_label = labels[i];
        ans();
    }
}
