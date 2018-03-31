#include <string>
#include <set>
#include <iostream>
#include <fstream>
using namespace std;

string cut(string &word, int a, int b) {
    string res = "";
    for(int i = a; i <= b; ++i)
        res += word[i];
    return res;
}

void get_distinct(set<string>& s, string &word, const char* fname) {
    ifstream fin;
    fin.open(fname);
    int N;
    fin >> N;

    for(int I, j1, j2, i = 0; i < N; ++i) {
        fin >> I >> j1 >> j2;
        for(int j = j1; j <= j2; ++j) {
            string str = cut(word, I, j);
            if(s.find(str) != s.end()) {
                cout << "WRONG\n";
                cout << "File " << fname << ": Word \"" << str << "\" represented more than once\n";
                exit(1);
            }
            s.insert(str);
        }
    }
    fin.close();
}

int main(int argc, char* argv[]) {
    if(argc != 4) {
        cout << "Usage: " << argv[0] << " input_str packages_1 packages_2\n";
        return 1;
    }

    string word;
    ifstream fin;
    fin.open(argv[1]);
    fin >> word;
    fin.close();

    set<string> s1, s2;
    get_distinct(s1, word, argv[2]);
    get_distinct(s2, word, argv[3]);
    if(s1 != s2) {
        cout << "WRONG\n";
        cout << "sets of represented words are different\n";
        return 1;
    }

    cout << "OK\n";
    return 0;
}