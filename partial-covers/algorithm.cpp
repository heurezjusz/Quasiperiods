#include "algorithm.h"
#include "cst.h"
#include "hull.h"
#include "ukkonen.h"
using namespace std;


namespace {
int N;
Tree st;
}


void algorithm(vector<int>& word, vector<int>& result) {
    N = word.size();
    word.push_back(-1);
    st.create(word);
    extend_to_cst(st);
}
