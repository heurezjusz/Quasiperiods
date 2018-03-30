#include <bits/stdc++.h>
#include "oi.h"
using namespace std;

string TASK_ID = "cover";

// HINT: Uzywamy liczb losowych wylacznie z pakietu oi.h
oi::Random RG(0xC0FFEE);

inline int rand_range(int a, int b) {
    return (RG.rand() % (b - a + 1)) + a;
}
inline long long rand_range(long long a, long long b) {
    return (RG.randULL() % (b - a + 1)) + a;
}
bool rand_bool(int pr = 50) {
    return rand_range(1, 100) <= pr;
}


/* ========================================================================== *
                                   structs
 * ========================================================================== */
struct TestCase
{
    vector<int> t;
    friend ostream& operator<<(ostream& out, TestCase const& tc) {
        out << tc.t.size() << "\n";
        for(int i: tc.t)
            out << i << " ";
        return out << "\n";
    }

    TestCase(int seed) {
        RG.setSeed(seed);
    }
};

/* ========================================================================== *
                                Writing to files
 * ========================================================================== */
void write(const char* filename, const TestCase& testCase)
{
    cout << "Writing " << filename << "..." << endl;
    ofstream file(filename);
    file << testCase;
    file.close();
}

void testGroup(const vector<TestCase>& cases)
{
    static int test_no = 0;
    ++test_no;
    for(int i = 0; i < (int) cases.size(); ++i)
    {
        stringstream ss;
        ss << TASK_ID;
        ss << test_no;
        if(cases.size() > 1U)
            ss << char('a' + i);
        ss << ".in";
        write(ss.str().c_str(), cases[i]);
    }
}

/* ========================================================================== *
                                     main
 * ========================================================================== */

int main()
{
    // 1
    {
        const TestCase t[] = {
        };
        testGroup(vector<TestCase>(t, t + sizeof(t) / sizeof(TestCase)));
    }
    return 0;
}
