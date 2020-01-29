#include <algorithm>
#include <cassert>
#include <iostream>
#include <list>
#include <vector>

#include "algorithm.h"
#include "maxgap_imp.h"
#include "pack.h"
using namespace std;

// #define DEB

int N;
vector<int> B;
vector<int> F;
vector<int> MF;
vector<int> p;
vector<Pack> global_res;
int global_period_size;


void kmp(vector<int> const &word) {
    p.resize(N);
    for (int w = 0, i = 1; i < N; ++i) {
        while (w > 0 && word[i] != word[w])
            w = p[w - 1];
        if (word[i] == word[w])
            w++;
        p[i] = w;
    }
}


void kmp_B(vector<int> const &word) {
    B.resize(N);
    for (int w = 0, i = N - 2; i >= 0; --i) {
        while (w > 0 && word[i] != word[N - 1 - w])
            w = B[N - 1 - w + 1];
        if (word[i] == word[N - 1 - w])
            w++;
        B[i] = w;
    }

    // for (int i = 0; i < N; ++i)
    //     printf("%d ", B[i]);
    // puts("");
}


void kmp_F(vector<int> const &word) {
    F.resize(N);
    MF.resize(N + 1);

    for (int i = 1; i <= N; ++i)
        MF[i] = 0;
    for (int w = 0, i = 1; i < N; ++i) {
        while (w > 0 && word[i] != word[w])
            w = F[w - 1];
        if (word[i] == word[w])
            w++;
        F[i] = w;
        MF[i + 1 - F[i]] = i;
    }
    for (int i = 1; i <= N; ++i)
        MF[i] = max(MF[i - 1], MF[i]);
}


struct Class : Maxgap {
    int id, k0;
    bool decomposed, printed;

    Class(int id, int k0) : id(id), k0(k0), decomposed(false), printed(false) {}

    void register_decomposition(int k_last) {
        if (decomposed)
            return;
        decomposed = true;

        // imp stuff
        int e1 = positions.front() + 1, et = positions.back() + 1;
        int k = (N - et + 1) - B[et - 1];  // length
        int s = (MF[k] + 1) + 1 - e1;      // length

#ifdef DEB
        printf("%d: MIN len: %d\n", id, k);
        printf("%d: MAX len: %d\n", id, s);
#endif
        k = max(maxgap(), max(k, k0));
        s = min(min(k_last, s), global_period_size - 1);
        if (k <= s) {
            e1 -= 1;
            global_res.emplace_back(e1, e1 + k - 1, e1 + s - 1);
#ifdef DEB
            printf("<%d:%d>, (%d %d %d)\n", k, s, e1, e1 + k - 1, e1 + s - 1);
#endif
        }
    }

    void reopen(int _k0) {
        k0 = _k0;
        decomposed = false;
    }


    void print() {
        printf("%d: {", id);
        for (int p : positions)
            printf(" %d", p);
        printf(" }%s maxgap: %d\n", decomposed ? "*" : "", maxgap());
        printed = true;
    }
};


struct SmallClass {
    /* represents "small class" from crochmere partitioning. Its a list with ID
     */
    list<int> positions;
    int id;

    SmallClass(Class const &c) : positions(list<int>{c.positions}), id(c.id) {}
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
        : new_class_id(0), max_alph_size(max_alph_size), k(1) {}


    int _create_new_class(int k0) {
        int id = new_class_id;
        classes.emplace_back(new_class_id++, k0);
        subclasses.emplace_back();
        last_subclass_from.push_back(-1);
        last_subclass_k.push_back(-1);
        return id;
    }

    void _create(vector<int> const &word) {
        N = word.size();

        // create empty classes
        for (int i = 0; i < max_alph_size; ++i)
            _create_new_class(1);

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


    int _get_subclass_id(int cid, int pid) {
        if (last_subclass_from.at(cid) == pid)
            return subclasses.at(cid).back();

        // we need to _create subclass
        if (last_subclass_k[cid] != k)
            has_subclasses.push_back(cid);

        last_subclass_k.at(cid) = k;
        last_subclass_from.at(cid) = pid;
        int sid = _create_new_class(k + 1);
        subclasses.at(cid).push_back(sid);

        return sid;
    }

    void _move_element(int x, int from, int to) {
        auto it = position_iterator[x];
        classes[from].register_decomposition(k);
        classes[from].erase(it);
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
                int sid = _get_subclass_id(cid, P.id);
                _move_element(i - 1, cid, sid);
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


    void kill(int k_last) {
#ifdef DEB
        printf("KILL %d\n", k_last);
#endif
        for (int i = 0; i < N; ++i) {
            if (!classes[position_to_class[i]].decomposed)
                classes[position_to_class[i]].register_decomposition(k_last);
        }
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


void easy_seeds(vector<int> &word, vector<Pack> &result) {
    kmp(word);

    /* easy seeds */
    int period = N - p[N - 1];
    for (int i = 0; i < period; i++) {
        if (i + period > N)
            break;
        result.emplace_back(i, i + period - 1, N - 1);
    }

#ifdef DEB
    printf("perdiod = %d\n", period);
#endif
}


void hard_seeds(vector<int> &word, vector<Pack> &result) {
    kmp_B(word);
    kmp_F(word);
    result.swap(global_res);

    global_period_size = N - B[0];
    assert(global_period_size == N - F[N - 1]);

    int max_letter = 0, min_letter = word[0];
    for (int a : word) {
        max_letter = max(a, max_letter);
        min_letter = min(a, min_letter);
    }
    for (int &a : word)
        a -= min_letter;
    max_letter -= min_letter;

#ifdef DEB
    for (int a : word)
        printf("%c", 'a' + a);
    puts("");

    for (int i = 0; i < N; ++i)
        printf("%d", i % 10);
    puts("");

    for (int i = 0; i < N; ++i)
        printf("%d", F[i]);
    puts("");

    for (int i = 0; i < N; ++i)
        printf("%d", i + 1 - F[i]);
    puts("");

    for (int i = 0; i <= N; ++i)
        printf("%d", MF[i]);
    puts("");

    for (int i = 0; i < N; ++i)
        printf("%d", B[i]);
    puts("");

#endif

    Partitioning partitioning(max_letter + 1);
    partitioning._create(word);
#ifdef DEB
    partitioning.print();
#endif

    for (int i = 0; i < global_period_size && !partitioning.end(); i++) {
        partitioning.do_a_step();
#ifdef DEB
        partitioning.print();
#endif
    }
    // if (!partitioning.end())
    partitioning.kill(global_period_size - 1);

    result.swap(global_res);
}


void reverse_packs(vector<Pack> &packs) {
    for (auto &p : packs) {
        p.i = N - 1 - p.i;
        p.j1 = N - 1 - p.j1;
        p.j2 = N - 1 - p.j2;
    }
}


void algorithm(vector<int> &word, vector<Pack> &result) {
    N = word.size();
    easy_seeds(word, result);
    hard_seeds(word, result);

    reverse(word.begin(), word.end());
    vector<Pack> reversed_packs;
    hard_seeds(word, reversed_packs);
    for (auto const &p : reversed_packs)
        // i, j1, j2 -> j, i2, i1
        result.emplace_back(N - 1 - p.i, N - 1 - p.j1, N - 1 - p.j2);
}
