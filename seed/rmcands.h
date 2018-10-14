#ifndef __RMCANDS
#define __RMCANDS

#include "ukkonen.h"
#include "pack.h"
#include "maxgap.h"

void right_and_mid_cands_and_word_lens(Tree& tree, std::vector<Pack>& cands, std::vector<int> &lens, int divisor);

#endif
