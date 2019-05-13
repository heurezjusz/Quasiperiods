#include <cstdio>
#include "maxN.h"

int p[maxN];
int dp[maxN];
int res[maxN];


char s[maxN];
int N;

void get_input() {
    scanf("%s", s + 1);
    while (s[N + 1])
        N++;
}

int main() {
    get_input();

    dp[1] = res[1] = 1;

    for (int x, i = 2; i <= N; ++i) {
        x = p[i - 1];
        while (x && s[x + 1] != s[i])
            x = p[x];
        x += s[x + 1] == s[i];
        p[i] = x;

        dp[i] = res[i] = i;
        x = res[x];
        if (p[i] && dp[x] >= i - x) {
            dp[x] = i;
            res[i] = x;
        }
    }

    printf("%d\n", res[N]);
}