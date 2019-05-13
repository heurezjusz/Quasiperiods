#include <cstdio>
#include <string>
using namespace std;


FILE *f;


void foo(int i) {
    if (i > 0)
        foo(i - 1);
    fprintf(f, "%c", 'a' + i);
    if (i > 0)
        foo(i - 1);
}


void gen_test(int i) {
    int N = (1 << (i + 1)) - 1;
    string fname = "recursive_" + to_string(N) + "_" + to_string(i + 1) + ".in";
    f = fopen(fname.c_str(), "w");
    foo(i);
    fprintf(f, "\n");
    fclose(f);
}


int main() {
    for (int i = 1; i < 25; ++i)
        gen_test(i);
}