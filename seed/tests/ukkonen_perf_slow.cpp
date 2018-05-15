#include <cstdio>
#include <algorithm>
using namespace std;

const int maxN = 3e5 + 10;
const int mod = 1100000017;
const int p = 313;
using ll = long long;

ll hsh[maxN];
ll ppow[maxN];
char s[maxN];
int n;

int sa[maxN];
int _sa[maxN];
int lcp[maxN];

ll get_hsh(int a, int b) {
    if(!a)
        return hsh[b];
    return (hsh[b] - hsh[a - 1] * ppow[b - a + 1] % mod + mod) % mod;
}


bool cmp(int a0, int b0) {
    int a = -1, b = n - max(a0, b0) + 1, avg;
    while(b - a > 1) {
        avg = (a + b) / 2;
        if(get_hsh(a0, a0 + avg) == get_hsh(b0, b0 + avg))
            a = avg;
        else
            b = avg;
    }
    return s[a0 + b] < s[b0 + b];
}

int main() {
    scanf("%s", s);
    while(s[n]) n++;
    n++;
    hsh[0] = s[0];
    ppow[0] = 1;
    for(int i = 1; i < n; ++i) {
        hsh[i] = (hsh[i - 1] * p + s[i]) % mod;
        ppow[i] = ppow[i - 1] * p % mod;
        sa[i] = i;
    }

    sort(sa, sa + n, cmp);
    for(int i = 0; i < n; ++i) {
        printf("%d ", sa[i]);
        _sa[sa[i]] = i;
    }
    puts("");

    for(int x = 0, i = 0; i < n; ++i) {
        if(_sa[i] == n - 1) {
            x = 0;
            continue;
        }
//         printf("suffix %d vs %d", i, sa[_sa[i] + 1]);
        while(s[i + x] == s[sa[_sa[i] + 1] + x])
            x++;
//         printf("->%d\n", x);

        lcp[_sa[i]] = x;
        x = max(x - 1, 0);
    }
    for(int i = 0; i < n; ++i) {
        printf("%d ", lcp[i]);
    }
    puts("");
}