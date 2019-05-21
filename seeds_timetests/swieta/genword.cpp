#include "genword.h"
#include "sommer.h"

#include <algorithm>
#include <cstdio>
using namespace std;


inline int randint(int a, int b) {
    return a + rand() % (b - a + 1);
}


inline int choice(vector<int>& v) {
    return v[randint(0, v.size() - 1)];
}


vector<int> gen_word(int N, int cover_len, vector<int> possible_presuf) {
    vector<int> occurences;
    vector<int> result;
    // case: do not overlap
    possible_presuf.push_back(0);
    // first occurence
    occurences.push_back(0);

    while (occurences.back() + cover_len < N) {
        int presuf = choice(possible_presuf);
        int next_occ = occurences.back() + cover_len - presuf;
        occurences.push_back(next_occ);
    }

    // printf("occurences\n");
    // for (int o : occurences)
    //     printf("%d ", o);
    // puts("");

    vector<Rownosc> R;
    for (int i = 0; i < (int)occurences.size() - 1; i++)
        R.emplace_back(occurences[i] + 1, occurences[i + 1] + 1, cover_len);

    N = occurences.back() + cover_len;

    // for (auto r : R)
    //     printf("[%d %d] == [%d %d]\n", r.i - 1, r.i + r.len - 2, r.j - 1,
    //            r.j + r.len - 2);
    // puts("");

    Solution s;
    s.main(N, R, result);

    return result;
}