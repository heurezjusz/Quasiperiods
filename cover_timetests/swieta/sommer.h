#ifndef Sommer
#define Sommer

#include <vector>


struct Rownosc {
    int i, j, len;

    Rownosc(int i, int j, int len) : i(i), j(j), len(len) {}
};


struct Solution {
    int limit;
    int logarytm;

    struct FU {
        std::vector<int> FUt;
        std::vector<int> vals;
        int new_val;

        FU(int N);
        int fuf(int x);
        void fuu(int u, int v);
        int get_val(int x);
    };

    std::vector<FU> rownosci;
    int n, m;

    void inicjuj(int limit_);

    void main(int n, std::vector<Rownosc>& rown, std::vector<int>& result);
};


#endif