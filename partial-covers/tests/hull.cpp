#include "../hull.h"
#include <cstdio>
using namespace std;

int main() {
    vector<Segment> segments;
    vector<int> res;

    int N, M;
    scanf("%d%d", &N, &M);
    for (int x1, x2, a0, dx, i = 0; i < M; ++i) {
        scanf("%d%d%d%d", &x1, &x2, &a0, &dx);
        segments.emplace_back(x1, x2, a0, dx);
    }

    get_hull(N, segments, res);

    for (int i = 1; i <= N; ++i)
        printf("%d ", res[i]);
    puts("");
}