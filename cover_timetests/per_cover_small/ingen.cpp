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


bool has_short_period(vector<int>& word) {
    int N = word.size();
    vector<int> p;
    p.resize(N);
    for (int w = 0, i = 1; i < N; ++i) {
        while (w > 0 && word[i] != word[w])
            w = p[w - 1];
        if (word[i] == word[w])
            w++;
        p[i] = w;
    }

    return p.back() >= N / 2;
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

    string fname = "percoversml_" + to_string(N) + "_" + to_string(cover) +
                   "_" + msg + ".in";

    printf("generating %s...\n", fname.c_str());
    vector<int> word = gen_word(N, cover, presufs);
    while (has_short_period(word)) {
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


int rand_range(int a, int b) {
    return rand() % (b - a + 1) + a;
}

void rand_presufs(int seed, int N, int cover, int num_of_presufs) {
    vector<int> presufs;
    srand(seed);
    for (int i = 2; i < num_of_presufs; ++i)
        presufs.push_back(rand_range(1, cover / 2 - 3));
    gen_test(seed + 1, N, cover, presufs, "randperfs");
}


int main() {
    for (int p = 100; p <= 1000; p += 20) {
        int N = 2e7;
        int seed0 = p * 100;
        int clen = p;

        many_presufs(seed0 + 0, N, clen);
        many_presufs(seed0 + 1, N, clen);

        rand_presufs(seed0 + 3, N, clen, 3);
        rand_presufs(seed0 + 4, N, clen, 5);

        // return 0;
    }
}
