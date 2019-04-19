#ifndef __HULL
#define __HULL

#include <vector>
#include "segment.h"

void get_hull(int N, std::vector<Segment> const& segments,
              std::vector<int>& result);

#endif