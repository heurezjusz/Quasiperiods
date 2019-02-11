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
    for (int w = 0, i = 1; i < N; ++i) {
        while (w > 0 && word[i] != word[w])
            w = p[w - 1];
        if (word[i] == word[w])
            w++;
        p[i] = w;
    }
}


struct Class {
    list<int> positions;
    int id, k0;
    bool decomposed, printed;

    Class(int id, int k0) : id(id), k0(k0), decomposed(false), printed(false) {}

    int size() {
        return positions.size();
    }


    void register_decomposition(int /*k_last*/) {
        if (decomposed)
            return;
        decomposed = true;

        // TODO: costas stuff
    }


    void reopen(int _k0) {
        k0 = _k0;
        decomposed = false;
    }


    list<int>::iterator append(int x) {
        assert(!decomposed);
        positions.push_back(x);
        auto it = positions.end();
        it--;
        return it;
    }


    void print() {
        printf("%d:", id);
        for (int p : positions)
            printf(" %d", p);
        puts("");
        printed = true;
    }
};


struct SmallClass {
    list<int> positions;
    int id;

    SmallClass(Class const& c) : positions(list<int>{c.positions}), id(c.id) {}
};


struct Partitioning {
    vector<Class> classes;
    vector<int> position_to_class;
    vector<list<int>::iterator> position_iterator;

    vector<SmallClass> small_classes;
    vector<int> last_subclass_from;
    vector<int> last_subclass_k;
    vector<int> has_subclasses;
    vector<vector<int>> subclasses;

    int new_class_id, max_alph_size, k, N;


    Partitioning(int max_alph_size)  // assumes letters 0...max_alph_size-1
        : new_class_id(0),
          max_alph_size(max_alph_size),
          k(1) {}


    int create_new_class(int k0) {
        int id = new_class_id;
        classes.emplace_back(new_class_id++, k0);
        subclasses.emplace_back();
        last_subclass_from.push_back(-1);
        last_subclass_k.push_back(-1);
        return id;
    }


    void create(vector<int> const& word) {
        N = word.size();

        // create empty classes
        for (int i = 0; i < max_alph_size; ++i)
            int cid = create_new_class(1);

        // put positions to classes
        for (int i = 0; i < (int)word.size(); ++i) {
            auto it = classes[word[i]].append(i);
            position_to_class.push_back(word[i]);
            position_iterator.push_back(it);
        }

        // initialize small classes
        for (int i = 0; i < max_alph_size; ++i)
            small_classes.emplace_back(classes[i]);
    }


    bool end() {
        return small_classes.empty();
    }


    int get_subclass_id(int cid, int pid) {
        if (last_subclass_from.at(cid) == pid)
            return subclasses.at(cid).back();

        // we need to create subclass
        if (last_subclass_k[cid] != k)
            has_subclasses.push_back(cid);

        last_subclass_k.at(cid) = k;
        last_subclass_from.at(cid) = pid;
        int sid = create_new_class(k + 1);
        subclasses.at(cid).push_back(sid);

        return sid;
    }


    void move_element(int x, int from, int to) {
        auto it = position_iterator[x];
        classes[from].register_decomposition(k);
        classes[from].positions.erase(it);
        position_iterator[x] = classes[to].append(x);
        position_to_class[x] = to;
    }


    void do_a_step() {
        // paritioning
        for (auto P : small_classes) {
            for (auto i : P.positions) {
                if (i == 0)
                    continue;

                int cid = position_to_class[i - 1];
                int sid = get_subclass_id(cid, P.id);
                move_element(i - 1, cid, sid);
            }
        }

        small_classes.clear();
        // choice of new small classes
        for (int cid : has_subclasses) {
            if (classes[cid].size() != 0) {
                subclasses[cid].push_back(cid);
                classes[cid].reopen(k + 1);
            }

            int bestsize = -1;
            for (int sid : subclasses[cid])
                bestsize = max(bestsize, classes[sid].size());
            // add all to small classes except for the first one of size
            // [bestsize]
            for (int sid : subclasses[cid])
                if (classes[sid].size() == bestsize)
                    bestsize = -1;
                else
                    small_classes.emplace_back(classes[sid]);

            subclasses[cid].clear();
        }

        has_subclasses.clear();

        k += 1;
    }


    void print() {
        printf("-- %d --\n", k);
        for (int i = 0; i < N; ++i)
            if (!classes[position_to_class[i]].printed)
                classes[position_to_class[i]].print();
        for (int i = 0; i < N; ++i)
            classes[position_to_class[i]].printed = false;
    }
};


void algorithm(vector<int>& word, vector<Pack>& result) {
    N = word.size();
    for (int& a : word) {
        a -= 'a';
        printf("%d ", a);
    }
    puts("");

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

    int max_letter = 0;
    for (int a : word)
        max_letter = max(a, max_letter);

    Partitioning partitioning(max_letter + 1);
    partitioning.create(word);
    partitioning.print();
    while (!partitioning.end()) {
        partitioning.do_a_step();
        partitioning.print();
    }
}
