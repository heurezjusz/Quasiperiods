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


void rename() {
    int label = P->find(randint(1, N));
    vector<Change> _ignore;
    P->union_({label}, new_label, _ignore);
    assert(_ignore.empty());
}

int main() {
    scanf("%d", &N);
    P = new Partition();
    P->init(N);
    new_label = N + 1;

    srand(42 + N);

    for (int i = 1; i < N; ++i) {
        new_label++;
        rename();
        new_label++;
        ans();
    }
}
