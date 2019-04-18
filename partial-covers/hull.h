#ifndef __HULL
#define __HULL

#include <vector>


struct Segment {
    int x1, x2, y1, dx;

    Segment(int x1 = 0, int x2 = 0, int y1 = 0, int dx = 0);

    int at(int x) const;
};


void get_hull(int N, std::vector<Segment> const& segments,
              std::vector<int>& result);

#endif