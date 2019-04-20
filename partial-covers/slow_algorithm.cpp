#include <algorithm>
#include <iostream>
#include <map>
using namespace std;
using ll = long long;


int N;
string S;

const ll p = 997;
const ll mod = 1100000017;


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

    pair<ll, ll> best_cover = {hsh, hsh_};
    pos_cnt[{hsh, hsh_}] = len;
    last_pos[{hsh, hsh_}] = len - 1;

    for (int i = len; i < N; ++i) {
        hsh = ((hsh * p - S[i - len] * ppow + S[i]) % mod + mod) % mod;
        hsh_ = hsh_ * p - S[i - len] * ppow_ + S[i];

        pos_cnt[{hsh, hsh_}] += min(len, i - last_pos[{hsh, hsh_}]);
        last_pos[{hsh, hsh_}] = i;

        if (pos_cnt[{hsh, hsh_}] > pos_cnt[best_cover]) {
            best_cover = {hsh, hsh_};
        }
    }

    return pos_cnt[best_cover];
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> S;

    N = S.size();
    vector<int> pos_to_len;
    pos_to_len.resize(N + 1, N + 100);

    for (int i = 1; i <= N; ++i) {
        int covered = check_len(i);
        pos_to_len[covered] = min(pos_to_len[covered], i);
    }

    for (int i = N - 1; i >= 1; --i)
        pos_to_len[i] = min(pos_to_len[i], pos_to_len[i + 1]);

    for (int i = 1; i <= N; ++i)
        cout << i << ": " << pos_to_len[i] << "\n";
}
