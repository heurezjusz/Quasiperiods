/* Based on Marek Sommer's code */
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

        FU(int N) {
            FUt.resize(N + 1);
            for (int i = 0; i <= N; ++i)
                FUt[i] = i;
        }

        int fuf(int x) {
            return x == FUt[x] ? x : FUt[x] = fuf(FUt[x]);
        }
        void fuu(int u, int v) {
            if (fuf(u) > fuf(v))
                swap(u, v);
            FUt[fuf(u)] = fuf(v);
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

    int main() {
        scanf("%d%d", &n, &m);

        inicjuj(n + 10);

        while (m--) {
            int a, b, l;
            scanf("%d%d%d", &a, &b, &l);
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
        int wynik = 0;
        for (int i = 1; i <= n; i++)
            if (rownosci[0].fuf(i) == i)
                wynik++;
        return wynik;
    }
};


int main() {
    Solution s;
    printf("%d\n", s.main());
}