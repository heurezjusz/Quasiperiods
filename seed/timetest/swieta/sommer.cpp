/* Based on Marek Sommer's code */
#ifndef Sommer
#include "sommer.h"
#else

struct Rownosc {
    int i, j, len;

    Rownosc(int i, int j, int len) : i(i), j(j), len(len) {}
};

#endif

#include <algorithm>
#include <cstdio>
#include <map>
#include <utility>
#include <vector>
using namespace std;


struct Solution {
    int limit;
    int logarytm;

    int podloga_z_logarytmu_dwojkowego(int n) {
        return (n <= 1) ? 0 : 1 + podloga_z_logarytmu_dwojkowego(n / 2);
    }

    struct FU {
        vector<int> FUt;
        vector<int> vals;
        int new_val;

        FU(int N) : new_val(1) {
            FUt.resize(N + 1);
            vals.resize(N + 1);
            for (int i = 0; i <= N; ++i)
                FUt[i] = i;
        }

        int fuf(int x) {
            return x == FUt[x] ? x : FUt[x] = fuf(FUt[x]);
        }

        void fuu(int u, int v) {
            FUt[fuf(u)] = fuf(v);
        }

        int get_val(int x) {
            if (vals[fuf(x)] == 0)
                vals[fuf(x)] = new_val++;
            return vals[fuf(x)];
        }
    };


    vector<FU> rownosci;

    int n, m;

    void inicjuj(int limit_) {
        limit = limit_;
        logarytm = podloga_z_logarytmu_dwojkowego(limit) + 2;
        rownosci.clear();
        for (int i = 0; i < logarytm + 5; ++i)
            rownosci.emplace_back(limit);
    }

    void main(int n, vector<Rownosc>& rown, vector<int>& result) {
        inicjuj(n + 10);

        for (auto const& r : rown) {
            int a = r.i, b = r.j, l = r.len;
            const int potega_dwojki = podloga_z_logarytmu_dwojkowego(l);
            rownosci[potega_dwojki].fuu(a, b);
            rownosci[potega_dwojki].fuu(a + l - (1 << potega_dwojki),
                                        b + l - (1 << potega_dwojki));
        }

        for (int i = logarytm; i > 0; i--) {
            for (int a = 1; a <= n; a++) {
                const int b = rownosci[i].fuf(a);
                rownosci[i - 1].fuu(a, b);
                if (max(a, b) + (1 << (i - 1)) <= n)
                    rownosci[i - 1].fuu(a + (1 << (i - 1)), b + (1 << (i - 1)));
            }
        }

        for (int i = 1; i <= n; i++)
            result.push_back(rownosci[0].get_val(i));
    }
};


int main() {
    int n, m;
    vector<Rownosc> R;
    vector<int> result;
    Solution s;

    scanf("%d%d", &n, &m);
    for (int a, b, c, i = 0; i < m; ++i) {
        scanf("%d%d%d", &a, &b, &c);
        R.emplace_back(a, b, c);
    }

    s.main(n, R, result);
    int mx = *max_element(result.begin(), result.end());

    /*    for (int a : result)
            printf("%d ", a);
        puts("");
    */
    printf("%d\n", mx);
}