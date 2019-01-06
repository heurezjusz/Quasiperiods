#include "../partitions.h"
#include <cstdio>
#include <vector>
using namespace std;

const int maxN = 1e5 + 10;

Partitions *P;
int FU[maxN];
int fu_to_label[maxN];
int N;


int find(int x) {
    return FU[x] == x ? x : FU[x] = find(FU[x]);
}


int join(int a, int b) {


}


int main() {
    scanf("%d", &N);
    P = new Partitions(N);

    for (int i = 0; i <= N; ++i)
        FU[i] = fu_to_label[i] = i;

    for (int a, b, i = 1; i < N; ++i) {
        scanf("%d %d\n", &a, &b);
        a = find(a);
        b = find(b);
        join(fu_to_label[a], fu_to_label[b]);
    }
}
