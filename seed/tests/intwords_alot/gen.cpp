#include <algorithm>
#include <cstdio>
#include <string>
#include "../swieta/genword.h"
using namespace std;


/* seed of length 6, all possibilities of 1 and 2 prefix-sufixes
    tested on 5 words of length 15 and 20
*/


/*
    aaand 100 tests with N=200, seed=32, 2 or 3 random prfix-sufix
*/
void write_to_file(string fname, vector<int> word) {
    printf("writing %s\n", fname.c_str());

    FILE* f = fopen(fname.c_str(), "w");
    fprintf(f, "%d\n", (int)word.size());
    for (int l : word)
        fprintf(f, "%d ", l);
    fprintf(f, "\n");
    fclose(f);
}


int randint(int a, int b) {
    return a + rand() % (b - a + 1);
}


vector<int> random_test() {
    vector<int> presuf;
    int PS = randint(2, 3);
    for (int _ = 0; _ < PS; ++_)
        presuf.push_back(randint(1, 16));
    return gen_word(200, 32, presuf);
}

int main() {
    srand(1);

    for (int v = 1; v <= 5; ++v) {
        for (int i = 1; i < 6; ++i) {
            write_to_file(
                "one_" + to_string(i) + "_15_v" + to_string(v) + ".in",
                gen_word(15, 6, {i}));
            write_to_file(
                "one_" + to_string(i) + "_20_v" + to_string(v) + ".in",
                gen_word(20, 6, {i}));

            for (int j = i + 1; j < 6; ++j) {
                write_to_file("two_" + to_string(i) + "," + to_string(j) +
                                  "_15_v" + to_string(v) + ".in",
                              gen_word(15, 6, {i, j}));
                write_to_file("two_" + to_string(i) + "," + to_string(j) +
                                  "_20_v" + to_string(v) + ".in",
                              gen_word(20, 6, {i, j}));
            }
        }
    }

    for (int id = 0; id < 100; ++id) {
        write_to_file("spam" + to_string(id) + ".in", random_test());
    }
}
