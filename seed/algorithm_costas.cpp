#include <cassert>
#include <iostream>
#include <list>
#include <vector>

#include "algorithm.h"
#include "pack.h"
using namespace std;

int N;
vector<int> p;

void kmp(vector<int> const& word) {
    p.resize(N);
    for (int len = 0, i = 1; i <= N; ++i) {
        while (len > 0 && word[i] != word[len])
            len = p[len - 1];
        if (word[i] == word[len])
            len++;
        p[i] = len;
    }
}


struct Class {
    list<int> positions;
    int id, k0;
    bool decomposed;

    Class(int id, int k0) : id(id), k0(k0), decomposed(false) {}


    int size() {
        return positions.size();
    }


    void register_decomposition(int /*k_last*/) {
        if (decomposed)
            return;
        decomposed = true;

        // TODO: costas stuff
    }


    list<int>::iterator append(int x) {
        assert(!decomposed);
        positions.push_back(x);
        auto it = positions.end();
        it--;
        return it;
    }
};


struct Partitioning {
    vector<Class> classes;
    vector<int> position_to_class;
    vector<list<int>::iterator> position_iterator;
    vector<int> small_classes;
    int new_class_id, max_alph_size, k;

    Partitioning(int max_alph_size)  // assumes letters 0...max_alph_size-1
        : new_class_id(0),
          max_alph_size(max_alph_size),
          k(1) {}


    void create(vector<int> const& word) {
        // create empty classes
        for (int i = 0; i < max_alph_size; ++i) {
            classes.emplace_back(new_class_id++, 1);
            small_classes.push_back(i);
        }

        // put positions to classes
        for (int i = 0; i < (int)word.size(); ++i) {
            auto it = classes[word[i]].append(i);
            position_to_class.push_back(word[i]);
            position_iterator.push_back(it);
        }
    }
};


void algorithm(vector<int>& word, vector<Pack>& result) {
    N = word.size();
    kmp(word);
    for (int i : p)
        cout << i << " ";
    cout << "\n";

    /* easy seeds */
    int period = N - p[N - 1];
    for (int i = 0; i < period; i++) {
        if (i + period > N)
            break;
        result.emplace_back(i, i + period - 1, N - 1);
    }
}
