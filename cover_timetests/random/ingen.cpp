#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace std;


char charset[] =
    "abcdefghijklmnopqrstuvwxyz"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "0123456789";
int MAX_CHAR = sizeof(charset) / sizeof(char) - 1;


int randint(int a, int b) {
    return a + rand() % (b - a + 1);
}


int gen_test(int seed, int N, int letters) {
    assert(letters <= MAX_CHAR);

    string fname = "rand_" + to_string(N) + "_" + to_string(letters) + ".in";
    FILE* f = fopen(fname.c_str(), "w");

    for (int i = 0; i < N; ++i)
        fprintf(f, "%c", charset[randint(0, letters - 1)]);

    fclose(f);
}


int main() {
    for (int n = 1; n <= 25; ++n) {
        int N = 1e6 * n;
        int seed0 = N;
        gen_test(seed0 + 1, N, 2);
        gen_test(seed0 + 2, N, 3);
        gen_test(seed0 + 3, N, 4);
        gen_test(seed0 + 4, N, 10);
        gen_test(seed0 + 5, N, 26);
        gen_test(seed0 + 6, N, 52);
        gen_test(seed0 + 7, N, 62);
    }
}