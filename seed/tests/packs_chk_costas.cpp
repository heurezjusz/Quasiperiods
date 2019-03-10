#include <fstream>
#include <iostream>
#include <set>
#include <string>
using namespace std;

string cut(string& word, int a, int b) {
    string res = "";
    for (int i = a; i <= b; ++i)
        res += word[i];
    return res;
}

int get_all(set<string>& s, string& word, const char* fname) {
    ifstream fin;
    fin.open(fname);
    int N;
    fin >> N;

    for (int I, J, K, i = 0; i < N; ++i) {
        fin >> I >> J >> K;

        if (I <= J && J <= K)
            // i, j1, j2 pack
            for (int j = J; j <= K; ++j) {
                string str = cut(word, I, j);
                s.insert(str);
            }
        else
            // j, i2, i1 pack
            for (int _i = K; _i <= J; ++_i) {
                string str = cut(word, _i, I);
                s.insert(str);
            }
    }
    fin.close();
    return N;
}

void print_set_diff(set<string>& s1, set<string>& s2) {
    cout << "diffs:\n";

    for (auto const& s : s1) {
        if (s2.find(s) == s2.end())
            cout << "- only in 1: " << s << "\n";
    }
    for (auto const& s : s2) {
        if (s1.find(s) == s1.end())
            cout << "+ only in 2: " << s << "\n";
    }
}


int main(int argc, char* argv[]) {
    if (argc != 4) {
        cout << "Usage: " << argv[0] << " input_str packages_1 packages_2\n";
        return 1;
    }

    string word;
    ifstream fin;
    fin.open(argv[1]);
    fin >> word;
    fin.close();

    set<string> s1, s2;
    get_all(s1, word, argv[2]);
    get_all(s2, word, argv[3]);
    if (s1 != s2) {
        cout << "WRONG\n";
        cout << "sets of represented words are different\n";
        print_set_diff(s1, s2);
        return 1;
    }

    cout << "OK\n";
    return 0;
}