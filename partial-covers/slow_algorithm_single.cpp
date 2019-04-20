#include <algorithm>
#include <iostream>
#include <map>
using namespace std;
using ll = long long;


int N;
string S;

const ll p = 997;
const ll mod = 1100000017;
vector<int> found;
int limit;


int check_len(int len) {
    map<pair<ll, ll>, int> last_pos;
    map<pair<ll, ll>, int> pos_cnt;

    ll ppow = 1, ppow_ = 1;
    ll hsh = 0, hsh_ = 0;

    for (int i = 0; i < len; ++i) {
        ppow = (ppow * p) % mod;
        ppow_ *= p;
        hsh = (p * hsh + S[i]) % mod;
        hsh_ = p * hsh_ + S[i];
    }

    pos_cnt[{hsh, hsh_}] = len;
    last_pos[{hsh, hsh_}] = len - 1;

    for (int i = len; i < N; ++i) {
        hsh = ((hsh * p - S[i - len] * ppow + S[i]) % mod + mod) % mod;
        hsh_ = hsh_ * p - S[i - len] * ppow_ + S[i];

        pos_cnt[{hsh, hsh_}] += min(len, i - last_pos[{hsh, hsh_}]);
        last_pos[{hsh, hsh_}] = i;
    }

    found.clear();
    for (auto const& it : pos_cnt) {
        if (it.second >= limit)
            found.push_back(last_pos[it.first] - len + 1);
    }

    return !found.empty();
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int percent;
    cin >> S >> percent;

    N = S.size();
    limit = N * percent / 100;

    if (limit == 0) {
        cout << "0\n";
        return 0;
    }

    int len = 1;
    while (!check_len(len))
        len++;
    cout << len << "\n";

    for (int a : found)
        cout << a + 1 << " ";
    cout << "\n";
}
