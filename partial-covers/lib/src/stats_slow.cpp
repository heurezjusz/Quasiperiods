#include <algorithm>
#include <iostream>
#include <map>
using namespace std;
using ll = long long;


int n;
string s;

const ll p = 997;
const ll mod = 1100000017;

int prev_len, prev_last_pos, prev_pos_cnt = -1, printed;


void check_len(int len) {
    map<pair<ll, ll>, int> last_pos;
    map<pair<ll, ll>, int> pos_cnt;

    ll ppow = 1, ppow_ = 1;
    ll hsh = 0, hsh_ = 0;

    for (int i = 0; i < len; ++i) {
        ppow = (ppow * p) % mod;
        ppow_ *= p;
        hsh = (p * hsh + s[i]) % mod;
        hsh_ = p * hsh_ + s[i];
    }

    pair<ll, ll> best_cover = {hsh, hsh_};
    pos_cnt[{hsh, hsh_}] = len;
    last_pos[{hsh, hsh_}] = len - 1;

    for (int i = len; i < n; ++i) {
        hsh = ((hsh * p - s[i - len] * ppow + s[i]) % mod + mod) % mod;
        hsh_ = hsh_ * p - s[i - len] * ppow_ + s[i];

        pos_cnt[{hsh, hsh_}] += min(len, i - last_pos[{hsh, hsh_}]);
        last_pos[{hsh, hsh_}] = i;

        if (pos_cnt[{hsh, hsh_}] > pos_cnt[best_cover]) {
            best_cover = {hsh, hsh_};
        }
    }


    if (prev_pos_cnt > pos_cnt[best_cover]) {
        cout << "PEAK on len = " << prev_len << "\n";
        cout << "covered " << prev_pos_cnt << " / " << n << " = ";
        cout << prev_pos_cnt * 100. / n << "%\n";

        string tmp;
        for (int i = 0; i < prev_len; ++i)
            tmp += s[prev_last_pos - prev_len + i + 1];
        cout << tmp << "\n";
    }

    prev_len = len;
    prev_last_pos = last_pos[best_cover];
    prev_pos_cnt = pos_cnt[best_cover];
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
    for (int i = 1; i < n / 3; ++i)
        check_len(i);
}
