#define MXGAP_NLOGN
#include "maxgap_imp.h"
using namespace std;


Maxgap::Maxgap() {}


int Maxgap::size() {
    return positions.size();
}


list<int>::iterator Maxgap::append(int x) {
    positions.push_back(x);
    auto it = positions.end();
    it--;

    if (it != positions.begin()) {
        auto it_prv = it;
        it_prv--;

        gaps.insert(*it - *it_prv);
    }

    return it;
}


void Maxgap::erase(std::list<int>::iterator it) {
    auto it_nxt = it;
    it_nxt++;

    if (it_nxt != positions.end())
        gaps.erase(gaps.find(*it_nxt - *it));

    if (it != positions.begin()) {
        auto it_prv = it;
        it_prv--;
        gaps.erase(gaps.find(*it - *it_prv));

        if (it_nxt != positions.end())
            gaps.insert(*it_nxt - *it_prv);
    }

    positions.erase(it);
}


int Maxgap::maxgap() {
    if (gaps.empty())
        return 0;

    return *gaps.rbegin();
}
