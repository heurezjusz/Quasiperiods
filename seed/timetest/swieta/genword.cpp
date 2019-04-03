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


vector<int> gen_word(int N, int seed_len, vector<int> possible_presuf) {
    vector<int> occurences;
    vector<int> result;
    // case: do not overlap
    possible_presuf.push_back(0);
    // first (left-cutted) occurence
    occurences.push_back(randint(-seed_len + 1, 0));

    while (occurences.back() + seed_len < N) {
        int presuf = choice(possible_presuf);
        int next_occ = occurences.back() + seed_len - presuf;
        occurences.push_back(next_occ);
    }

    reverse(occurences.begin(), occurences.end());
    while (occurences[occurences.size() - 2] < 0)
        occurences.pop_back();
    reverse(occurences.begin(), occurences.end());

    // printf("occurences\n");
    // for (int o : occurences)
    //     printf("%d ", o);
    // puts("");

    vector<Rownosc> R;
    for (int i = 1; i < (int)occurences.size() - 2; i++)
        R.emplace_back(occurences[i] + 1, occurences[i + 1] + 1, seed_len);

    int first_part_len = seed_len + occurences[0];
    R.emplace_back(1, occurences[1] + 1 + seed_len - first_part_len,
                   first_part_len);

    int last_part_len = N - occurences.back();
    R.emplace_back(occurences[1] + 1, occurences.back() + 1, last_part_len);

    // for (auto r : R)
    //     printf("[%d %d] == [%d %d]\n", r.i - 1, r.i + r.len - 2, r.j - 1,
    //            r.j + r.len - 2);
    // puts("");

    Solution s;
    s.main(N, R, result);

    return result;
}