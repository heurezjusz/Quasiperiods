#ifndef __COMBINE
#define __COMBINE

#include <string>
#include <vector>
#include "pack.h"
#include "ukkonen.h"

void combine(Tree& st, std::vector<std::vector<Pack>>& packs,
             std::vector<Pack>& res, int minlen = 0, int maxlen = -1);

#endif
