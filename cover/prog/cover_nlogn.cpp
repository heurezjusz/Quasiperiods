#include <cstdio>
#include "maxN.h"

int p[maxN];
int s[maxN];
int borders[maxN];
char _s[maxN];
int N;


void get_input() {
    scanf("%s", _s);
    while (_s[N]) {
        s[N + 1] = _s[N];
        N++;
    }
}


void KMP() {
    for (int psuf = 0, i = 2; i <= N; ++i) {
        while (psuf > 0 && s[psuf + 1] != s[i])
            psuf = p[psuf];
        if (s[psuf + 1] == s[i])
            psuf++;
        p[i] = psuf;
    }
}


bool KMP_check(int B) {
    int last_occ = 1;
    for (int psuf = 0, i = 2; i <= N; ++i) {
        while (psuf > 0 && s[psuf + 1] != s[i])
            psuf = p[psuf];
        if (s[psuf + 1] == s[i])
            psuf++;

        if (psuf == B) {
            int occ = i - B + 1;
            if (occ - last_occ > B)
                return false;

            last_occ = occ;
            psuf = p[B];
        }
    }

    return true;
}


int main() {
    get_input();
    KMP();
    int bn = 0, psuf = N;
    while (psuf > 0) {
        borders[bn++] = psuf;
        psuf = p[psuf];
    }

    int res = bn - 1;
    while (res >= 0 &&
           (borders[res] <= 2 * borders[res + 1] || !KMP_check(borders[res])))
        res--;

    printf("%d\n", res == -1 ? N : borders[res]);
}