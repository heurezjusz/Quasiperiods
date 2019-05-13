#include <cstdio>
#include <vector>
using namespace std;


vector<int> t;
vector<int> pref;
vector<vector<int>> buck;
vector<int> order;
int n;

struct MaxGap {
    vector<int> nxt;
    vector<int> prev;
    int mxgap;

    MaxGap(int n) : nxt(n + 2), prev(n + 2), mxgap(0) {
        for (int i = 0; i < n + 2; i++) {
            nxt[i] = i + 1;
            prev[i] = i - 1;
        }
    }

    int get_max_gap() {
        return mxgap;
    }

    void remove(int i) {
        i++;
        nxt[prev[i]] = nxt[i];
        prev[nxt[i]] = prev[i];
        mxgap = max(mxgap, nxt[i] - prev[i] - 1);
    }
};


char txt[1 << 25];
void get_input() {
    scanf("%s", txt);
    for (n = 0; txt[n]; n++)
        t.push_back(txt[n]);
    t.push_back(0);
}

int main() {
    get_input();
    pref.resize(n);
    buck.resize(n);
    order.reserve(n);

    t[n] = -1;

    int best = 0;
    for (int i = 1; i < n; ++i) {
        pref[i] = max(0, min(pref[i - best], best - i + pref[best]));
        while (t[i + pref[i]] == t[pref[i]])
            pref[i]++;
        if (i + pref[i] > best + pref[best])
            best = i;
        buck[pref[i]].push_back(i);
    }

    for (int i = 0; i < n; ++i)
        for (int idx : buck[i])
            order.push_back(idx);

    MaxGap mg(n);
    for (int i = 0; i < n; ++i) {
        if (pref[order[i]] >= mg.get_max_gap() + 1) {
            printf("%d\n", mg.get_max_gap() + 1);
            return 0;
        }
        mg.remove(order[i]);
    }
    printf("%d\n", n);
}