#include <algorithm>
#include <cassert>
#include <cstdio>
#include <string>
using namespace std;


char charset[] =
    "abcdefghijklmnopqrstuvwxyz"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "0123456789";
int MAX_CHAR = sizeof(charset) / sizeof(char) - 1;


int randint(int a, int b) {
    return a + rand() % (b - a + 1);
}


string rand_string(int seed, int N, int letters) {
    srand(seed);
    string res = "";
    for (int i = 0; i < N; ++i)
        res += charset[randint(0, letters - 1)];
    return res;
}


int gen_test(int seed, int N, int period, int letters) {
    assert(letters <= MAX_CHAR);

    string fname = "periodic_" + to_string(N) + "_" + to_string(letters) + "_" +
                   to_string(period) + ".in";
    printf("%s\n", fname.c_str());
    FILE* f = fopen(fname.c_str(), "w");

    string p = rand_string(seed, period, letters);
    for (int i = 0; i < N; ++i)
        fprintf(f, "%c", p[i % period]);

    fprintf(f, "\n");
    fclose(f);
}


int main() {
    for (int n = 1; n <= 20; ++n) {
        for (int letters : {2, 3, 4, 10, 26, 62}) {
            int N = 1e6 * n;
            for (int period : {1, 3, 10, 100, 1000, N / 100, N / 10}) {
                int seed0 = N + 100 * period + letters;
                gen_test(seed0 + 1, N, period, letters);
            }
        }
    }
}
