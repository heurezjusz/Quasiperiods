#include <algorithm>
#include <cassert>
#include <cstdio>
#include <vector>
using namespace std;

#define next next_

const int maxN = 1e5 + 10;

vector<int> lists[maxN];
int next[maxN];
int FU[maxN];
int N;

int find(int x) {
    return FU[x] == x ? x : FU[x] = find(FU[x]);
}

void ans() {
    int a, b;
    scanf("%d%d", &a, &b);
    printf("> %d %d <\n", a, b);
    a = find(a);
    b = find(b);
    assert(a != b);

    while (!lists[a].empty()) {
        lists[b].push_back(lists[a].back());
        lists[a].pop_back();
    }

    FU[a] = b;
    sort(lists[b].begin(), lists[b].end());

    puts("CHANGES");
    for (int i = 0; i < (int)lists[b].size() - 1; ++i) {
        int el = lists[b][i];
        if (next[el] != lists[b][i + 1]) {
            next[el] = lists[b][i + 1];
            printf("%d %d\n", el, next[el]);
        }
    }
    puts("NEXT");
    for (int i = 1; i <= N; ++i)
        printf("%d ", next[i]);

    puts("\nJOINED LIST");
    for (int el : lists[b])
        printf("%d ", el);

    puts("");
}


int main() {
    scanf("%d", &N);

    for (int i = 1; i <= N; ++i) {
        lists[i].push_back(i);
        FU[i] = i;
    }
    for (int i = 1; i < N; ++i)
        ans();
}
