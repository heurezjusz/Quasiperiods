#ifndef __SEGMENT
#define __SEGMENT

struct Segment {
    int x1, x2, y1, dx;

    Segment(int x1 = 0, int x2 = 0, int y1 = 0, int dx = 0);

    int at(int x) const;
};

#endif