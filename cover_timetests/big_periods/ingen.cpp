#include <algorithm>
#include <cassert>
#include <cstdio>
#include <map>
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


void gen_test(int seed, int N, int period, int letters) {
    assert(letters <= MAX_CHAR);

    string fname = "bigperiod_" + to_string(N) + "_" + to_string(letters) +
                   "_" + to_string(period) + ".in";
    printf("%s\n", fname.c_str());
    FILE* f = fopen(fname.c_str(), "w");

    string p = rand_string(seed, period, letters);
    for (int i = 0; i < N; ++i)
        fprintf(f, "%c", p[i % period]);

    fprintf(f, "\n");
    fclose(f);
}


int main() {
    const int P = 40;
    for (int p = 1; p <= P; p++) {
        int N = 2e7;
        for (int letters : {2, 4, 7, 10, 26, MAX_CHAR}) {
            int seed = 100 * p + letters;
            int period = p * N / P;
            gen_test(seed, N, period, letters);
            gen_test(seed, N, period * 2 / 3, letters);
        }
    }
}
