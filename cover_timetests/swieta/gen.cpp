#include <algorithm>
#include <cstdio>
#include "genword.h"
using namespace std;

int main() {
    srand(1);

    vector<int> w = gen_word(20, 5, {2});
    printf("%d\n", (int)w.size());
    for (int i : w)
        printf("%d ", i);
    puts("");
}