#include <algorithm>
#include <cstdio>
#include <map>
#include "../swieta/genword.h"
using namespace std;


char charset[] =
    "abcdefghijklmnopqrstuvwxyz"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "0123456789"
    "%!@#$^&*()_+-=[]{}|:;\"'<>,.?/\\";
int MAX_CHAR = sizeof(charset) / sizeof(char) - 1;

map<int, char> charmap;
char int_to_char(int x) {
    if (x < MAX_CHAR)
        return charset[x];
    if (charmap.find(x) == charmap.end())
        charmap[x] = charset[rand() % MAX_CHAR];
    return charmap[x];
}


void write_to_file(string fname, vector<int> word) {
    printf("writing %s\n", fname.c_str());
    charmap.clear();

    FILE* f = fopen(fname.c_str(), "w");
    for (int l : word)
        fprintf(f, "%c", int_to_char(l - 1));
    fprintf(f, "\n");
    fclose(f);
}


bool is_only_ones(vector<int>& word, int cover) {
    for (int i = 0; i < cover - 1; ++i) {
        if (word[i] != word[i + 1])
            return false;
    }
    return true;
}


void gen_test(int seed, int N, int cover, vector<int> presufs,
              string msg = "") {
    srand(seed);
    string fname = "smallcovers_" + to_string(N) + "_" + to_string(cover) +
                   "_" + msg + ".in";

    printf("generating %s...\n", fname.c_str());
    vector<int> word = gen_word(N, cover, presufs);
    while (is_only_ones(word, cover)) {
        printf("FAIL\n");
        word = gen_word(N, cover, presufs);
    }
    printf("OK\n");

    write_to_file(fname, word);
}


void many_presufs(int seed, int N, int cover) {
    vector<int> presufs;
    for (int i = 2; i < cover / 2 - 3; ++i)
        presufs.push_back(i);
    gen_test(seed, N, cover, presufs, "manyperfs");
}


int main() {
    for (int n = 1; n <= 20; ++n) {
        int N = 1e6 * n;
        int seed0 = N;

        many_presufs(seed0 + 0, N, 100);
        // return 0;
        many_presufs(seed0 + 1, N, 200);
        many_presufs(seed0 + 2, N, 1000);
        gen_test(seed0 + 3, N, 100, {10, 25});
        gen_test(seed0 + 4, N, 200, {23, 75});
        gen_test(seed0 + 5, N, 500, {3, 9, 27, 81, 243});
    }
}