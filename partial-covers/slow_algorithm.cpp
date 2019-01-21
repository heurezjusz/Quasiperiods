#include <algorithm>
#include <iostream>
#include <map>
using namespace std;
using ll = long long;


int n;
string s;

const ll p = 997;


void check_len(int len) {
    map<ll, int> last_pos;
    map<ll, int> pos_cnt;

    ll ppow = 1;
    ll hsh = 0;

    for (int i = 0; i < len; ++i) {
        ppow *= p;
        hsh = p * hsh + s[i];
    }

    ll best_cover = hsh;
    ll best_last_pos = len - 1;
    pos_cnt[hsh] = len;
    last_pos[hsh] = len - 1;

    for (int i = len; i <= n; ++i) {
        hsh = hsh * p - s[i - len] * ppow + s[i];

        pos_cnt[hsh] += min(len, i - last_pos[hsh]);
        last_pos[hsh] = i;

        if (pos_cnt[hsh] > pos_cnt[best_cover]) {
            best_cover = hsh;
            best_last_pos = i;
        }
    }

    cout << "best for len = " << len << "\n";
    cout << "covered " << pos_cnt[best_cover] << " / " << n << " = ";
    cout << pos_cnt[best_cover] * 100. / n << "%\n";

    string tmp;
    for (int i = 0; i < len; ++i)
        tmp += s[best_last_pos - len + i + 1];
    cout << tmp << "\n";
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    {
        string tmp;

        while (cin >> tmp)
            s += tmp;
    }

    n = s.size();
    for (int i = 1; i < n; ++i)
        check_len(i);
}
