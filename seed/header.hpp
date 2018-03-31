#ifndef __HEADER

struct Pack {
    // represents a pack of words s[i..j1] to s[i..j2]
    int i, j1, j2;
    Pack(int i = 0, int j1 = -1, int j2 = -1)
    : i(i), j1(j1), j2(j2) {}
};

#define __HEADER
#endif