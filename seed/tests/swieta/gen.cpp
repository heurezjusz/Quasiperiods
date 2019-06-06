#include <algorithm>
#include <cstdio>
#include "genword.h"
using namespace std;

int main() {
    srand(1);

    vector<int> w = gen_word(20, 7, {2, 4});
    printf("20\n");
    for (int i : w)
        printf("%d ", i);
    puts("");
}
