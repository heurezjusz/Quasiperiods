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

int get_distinct(set<string>& s, string& word, const char* fname,
                 int req_n = -32) {
    ifstream fin;
    fin.open(fname);
    int N;
    fin >> N;

    if (req_n != -32 && N != req_n) {
        cout << "WRONG\n";
        cout << "represantations of different size " << N << " vs " << req_n
             << "\n";
        exit(1);
    }

    for (int I, j1, j2, i = 0; i < N; ++i) {
        fin >> I >> j1 >> j2;
        if (!(I <= j1 && j1 <= j2)) {
            cout << "WRONG\n";
            cout << "File " << fname << ": Incorrect representation [" << I
                 << ", " << j1 << ", " << j1 << "]\n";
            exit(1);
        }
        for (int j = j1; j <= j2; ++j) {
            string str = cut(word, I, j);
            if (s.find(str) != s.end()) {
                cout << "WRONG\n";
                cout << "File " << fname << ": Word \"" << str
                     << "\" represented more than once\n";
                exit(1);
            }
            s.insert(str);
        }
    }
    fin.close();
    return N;
}


void print_diff(set<string> s1, set<string> s2, string name1, string name2) {
    cout << "+++" << name1 << "\n";
    cout << "---" << name2 << "\n";
    for (string const& s : s1)
        if (s2.find(s) == s2.end())
            cout << "+ " << s << "\n";
    for (string const& s : s2)
        if (s1.find(s) == s1.end())
            cout << "- " << s << "\n";
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
    get_distinct(s1, word, argv[2]);
    get_distinct(s2, word, argv[3]);
    if (s1 != s2) {
        cout << "WRONG\n";
        cout << "sets of represented words are different\n";
        print_diff(s1, s2, argv[2], argv[3]);
        return 1;
    }

    cout << "OK\n";
    return 0;
}
