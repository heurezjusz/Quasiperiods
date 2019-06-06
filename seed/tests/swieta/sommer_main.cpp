/* Based on Marek Sommer's code */
#include "sommer.h"
#include <algorithm>
#include <cstdio>
using namespace std;


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

    printf("%d\n", mx);
}
