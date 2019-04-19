#include "segment.h"


Segment::Segment(int x1, int x2, int y1, int dx)
    : x1(x1), x2(x2), y1(y1), dx(dx) {}


int Segment::at(int x) const {
    return (x - x1) * dx + y1;
}
