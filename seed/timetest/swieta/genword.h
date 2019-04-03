#ifndef GENWORD
#define GENWORD

#include <vector>

std::vector<int> gen_word(int n, int seed_len,
                          std::vector<int> possible_presuf);

#endif