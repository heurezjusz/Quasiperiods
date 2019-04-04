#ifndef MXGAP_COSTAS
#define MXGAP_COSTAS

#include <cstdio>
#include <list>
#include <set>

struct Maxgap {
    std::list<int> positions;

    Maxgap();

    int size();

    std::list<int>::iterator append(int x);

    void erase(std::list<int>::iterator it);

    int maxgap();


#ifdef MXGAP_NLOGN
    std::multiset<int> gaps;
#else
    int maxgap_;
#endif
};


#endif