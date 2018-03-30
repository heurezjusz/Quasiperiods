#include <cstdio>
#include <vector>
using namespace std;

vector<int> p;
vector<int> dp;
vector<int> res;

vector<int> s;

char _s[1 << 19];
int n;

void get_input() {
    s.push_back(-1);
    scanf("%s", _s);
    for(; _s[n]; ++n)
        s.push_back(_s[n]);
    s.push_back(-2);
}

int main() {
    get_input();
    p.resize(n + 2);
    dp.resize(n + 2);
    res.resize(n + 2);

    dp[1] = res[1] = 1;

    for(int x, i = 2; i <= n; ++i) {
        x = p[i - 1];
        while(x && s[x + 1] != s[i])
            x = p[x];
        x += s[x + 1] == s[i];
        p[i] = x;

        dp[i] = res[i] = i;
        x = res[x];
        if(p[i] && dp[x] >= i - x) {
            dp[x] = i;
            res[i] = x;
        }
    }

    printf("%d\n", res[n]);
}