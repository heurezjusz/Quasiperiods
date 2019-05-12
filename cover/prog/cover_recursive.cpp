#include <cstdio>

const int maxN = 1 << 25;

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


bool KMP_check(int B, int _N) {
    int last_occ = 1;
    for (int psuf = 0, i = 2; i <= _N; ++i) {
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


int find_ans(int N) {
    int B = p[N];
    if (B == 0)
        return N;

    int candidate = N;
    if (B <= 2 * N / 3)
        candidate = find_ans(B);
    else {
        int period = N - B;
        candidate = find_ans(period + N % period);
    }

    if (candidate == N || KMP_check(candidate, N))
        return candidate;
    return N;
}


int main() {
    get_input();
    KMP();
    printf("%d\n", find_ans(N));
}