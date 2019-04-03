#include "maxgap_costas.h"
using namespace std;

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

        maxgap_ = max(*it - *it_prv, maxgap_);
    }

    return it;
}


void Maxgap::erase(std::list<int>::iterator it) {
    auto it_nxt = it;
    it_nxt++;

    if (it != positions.begin()) {
        auto it_prv = it;
        it_prv--;
        if (it_nxt != positions.end())
            maxgap_ = max(*it_nxt - *it_prv, maxgap_);
    }

    positions.erase(it);
}


int Maxgap::maxgap() {
    if (size() <= 1)
        return 0;
    return maxgap_;
}