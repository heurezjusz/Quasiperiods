#include <algorithm>
#include <cstdio>
using namespace std;


int N, M;
const int maxN = 1e5 + 10;

int t[maxN];


void add(int a, int b, int a0, int dx) {
    for (int i = a; i <= b; ++i) {
        t[i] = max(t[i], a0);
        a0 += dx;
    }
}


int main() {
    scanf("%d%d", &N, &M);
    for (int a, b, a0, dx, i = 0; i < M; ++i) {
        scanf("%d%d%d%d", &a, &b, &a0, &dx);
        add(a, b, a0, dx);
    }

    for (int i = 1; i <= N; ++i)
        t[i] = max(t[i], t[i - 1]);

    for (int i = 1; i <= N; ++i)
        printf("%d ", t[i]);
    puts("");
}
