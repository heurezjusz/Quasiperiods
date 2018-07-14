#include "../ukkonen.hpp"
#include <iostream>
using namespace std;

Tree st;
string w;
vector<int> word;

int main() {
    cin >> w;
    for(char c: w)
        word.push_back(c - 97);
    word.push_back(-1);
    st.create(word);

    for(int a: st.sa) printf("%d ", a);
    puts("");
    for(int a: st.lcp) printf("%d ", a);
    puts("");
}