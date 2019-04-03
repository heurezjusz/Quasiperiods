#include <algorithm>
#include <cstdio>
#include "swieta/genword.h"
using namespace std;


void write_to_file(string fname, vector<int> word) {
    printf("writing %s\n", fname.c_str());

    FILE* f = fopen(fname.c_str(), "w");
    fprintf(f, "%d\n", (int)word.size());
    for (int l : word)
        fprintf(f, "%d ", l);
    fprintf(f, "\n");
    fclose(f);
}


int main() {
    srand(1);

    write_to_file("simple1.in", gen_word(20, 7, {2, 4}));
    write_to_file("simple2.in", gen_word(30, 13, {4, 1}));
    write_to_file("simple3.in", gen_word(30, 8, {2, 3}));
    write_to_file("simple4.in", gen_word(30, 13, {1, 3, 5}));
    write_to_file("simple5.in", gen_word(50, 20, {7, 9, 1}));
}