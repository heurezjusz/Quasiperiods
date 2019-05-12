#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

const int maxN = 1 << 22;
char t[maxN];
int pref[maxN];
int order[maxN];

int n;

int nxt[maxN];
int prv[maxN];
int mxgap = 1;

void init() {
    for (int i = 0; i < n + 2; i++) {
        nxt[i] = i + 1;
        prv[i] = i - 1;
    }
}

int get_max_gap() {
    return mxgap;
}

void remove(int i) {
    i++;
    nxt[prv[i]] = nxt[i];
    prv[nxt[i]] = prv[i];
    mxgap = max(mxgap, nxt[i] - prv[i]);
}


bool cmp(int a, int b) {
    return pref[a] < pref[b];
}

int main() {
    scanf("%s", t);
    while (t[n])
        n++;
    init();

    int best = 0;
    for (int i = 1; i < n; ++i) {
        pref[i] = max(0, min(pref[i - best], best - i + pref[best]));
        while (t[i + pref[i]] == t[pref[i]])
            pref[i]++;
        if (i + pref[i] > best + pref[best])
            best = i;
    }

    for (int i = 0; i < n; ++i)
        order[i] = i + 1;
    sort(order, order + n - 1, cmp);

    for (int i = 0; i < n; ++i) {
        if (pref[order[i]] >= mxgap) {
            printf("%d\n", mxgap);
            return 0;
        }
        remove(order[i]);
    }
    printf("%d\n", n);
}
