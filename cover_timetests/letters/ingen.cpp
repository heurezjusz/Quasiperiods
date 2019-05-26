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


void gen_test(int seed, int N, int period, int letters, string type) {
    assert(letters <= MAX_CHAR);

    string fname = "letters_" + to_string(N) + "_" + to_string(letters) + "_" +
                   type + ".in";
    printf("%s\n", fname.c_str());
    FILE* f = fopen(fname.c_str(), "w");

    string p = rand_string(seed, period, letters);
    for (int i = 0; i < N; ++i)
        fprintf(f, "%c", p[i % period]);

    fprintf(f, "\n");
    fclose(f);
}


int main() {
    for (int letters = 1; letters <= MAX_CHAR; letters++) {
        int N = 3e7;
        int seed0 = letters;
        gen_test(seed0 + 0, N, N, letters, "random");
        gen_test(seed0 + 1, N, 2 * MAX_CHAR, letters, "small_period");
        gen_test(seed0 + 2, N, N / 10, letters, "big_period");
        gen_test(seed0 + 0, N, N, letters, "random2");
        gen_test(seed0 + 1, N, 2 * MAX_CHAR, letters, "small_period2");
        gen_test(seed0 + 2, N, N / 10, letters, "big_period2");
    }
}
