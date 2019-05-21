
/* Based on Marek Sommer's code */
#include "sommer.h"
#include <algorithm>
#include <map>
#include <utility>
using namespace std;


int podloga_z_logarytmu_dwojkowego(int n) {
    return (n <= 1) ? 0 : 1 + podloga_z_logarytmu_dwojkowego(n / 2);
}


Solution::FU::FU(int N) : new_val(1) {
    FUt.resize(N + 1);
    vals.resize(N + 1);
    for (int i = 0; i <= N; ++i)
        FUt[i] = i;
}


int Solution::FU::fuf(int x) {
    return x == FUt[x] ? x : FUt[x] = fuf(FUt[x]);
}


void Solution::FU::fuu(int u, int v) {
    FUt[fuf(u)] = fuf(v);
}


int Solution::FU::get_val(int x) {
    if (vals[fuf(x)] == 0)
        vals[fuf(x)] = new_val++;
    return vals[fuf(x)];
}


void Solution::inicjuj(int limit_) {
    limit = limit_;
    logarytm = podloga_z_logarytmu_dwojkowego(limit) + 2;
    rownosci.clear();
    for (int i = 0; i < logarytm + 5; ++i)
        rownosci.emplace_back(limit);
}


void Solution::main(int n, vector<Rownosc>& rown, vector<int>& result) {
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