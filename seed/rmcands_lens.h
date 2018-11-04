#ifndef __RMCANDS_LENS
#define __RMCANDS_LENS

#include "maxgap.h"
#include "pack.h"
#include "ukkonen.h"

/* vector "lens" is expected to be empty */
void right_mid_cands_and_subwords_lens(Tree& tree, int divisor,
                                       std::vector<Pack>& cands,
                                       std::vector<int>& lens);

#endif
