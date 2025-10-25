#pragma region 
#include <bits/stdc++.h>

using namespace std;
#define REP(i,a,b) for(int i = a; i <= b; i++)
#define rep(i,a,b) for(int i = a; i < b; i++)
#define PER(i,a,b) for(int i = a; i >= b; i--)
#define per(i,a,b) for(int i = a; i > b; i--)

#define pb push_back
#define mp make_pair
#define F first
#define S second
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef pair<int,int> pi;
typedef pair<ll,ll> pl;

const ll MOD = 1000000007;

ll mod_add(ll a, ll b, ll m) { return ((a % m) + (b % m)) % m; }
ll mod_sub(ll a, ll b, ll m) { return ((a % m) - (b % m) + m) % m; }
ll mod_mul(ll a, ll b, ll m) { return ((a % m) * (b % m)) % m; }
ll mod_exp(ll a, ll e, ll M) { ll res = 1; while (e) { if (e & 1) res = (res * a) % M; a = (a * a) % M; e >>= 1; } return res; }

template <typename T, typename Func>
T bin_apply_func(T obj, Func func, ll n) {
    T result = std::move(obj); // accumulator object
    Func f = func; // f will be "squared" (repeatedly composed)

    while (n > 0) {
        if (n & 1) {
            result = f(result); // appy the function
        }
        Func f_next = [f](T x) { // compose the function
            return f(f(x));
        };
        f = std::move(f_next); // avoid copying
        n >>= 1; // next bit
    }

    return result;
}
template<class T>
ostream& operator <<(ostream& o, const vector<T>& vec) {
    for(const auto& e : vec) {
        o << e << " ";
    }
    o << endl;
    return o;
}

#pragma endregion


#pragma region Answer
struct SegTree {
    vector<vector<ll>> tree;
    vector<uint8_t> lazy;
    int n, N = 1;
    string s;
    SegTree(const string& s) : n(s.size() + 1), s(s) {
        vector<uint8_t> prefix(n);
        prefix[0] = 0;
        rep(i, 0, n-1) {
            prefix[i+1] = prefix[i] ^ (1u << (s[i] - 'a'));
        }
        while (N < n) N <<= 1;
        tree.assign(2*N, vector<ll>(64,0));
        lazy.assign(2*N, 0);
        rep(i, 0, n) {
            tree[N + i][prefix[i]] = 1;
        }
        per(i, N-1, 0) {
            auto &l = tree[2*i], &r = tree[2*i +1], &p = tree[i];
            transform(l.begin(), l.end(), r.begin(), p.begin(), plus<ll>());
        }
    }

    ll query(int l, int r) {
        vector<ll> x(64, 0);
        l += N;
        r += N + 1; // inclusive
        while (l <= r) {
            if (l & 1) {
                transform(x.begin(), x.end(), tree[l].begin(), x.begin(), plus<ll>());
                ++l;
            }
            if (!(r & 1)) {
                transform(x.begin(), x.end(), tree[r].begin(), x.begin(), plus<ll>());
                --r;
            }
            l >>= 1;
            r >>= 1;
        }
        // n choose 2 = n(n-1)/2
        return accumulate(x.begin(), x.end(), 0ll, [](ll cur, ll r){ 
            return x < 2 ? cur : cur + (r *(r-1) / 2);
        });
    }
    void point_apply_update(int i){
        if (!lazy[i]) return;

        vector<ll> new_bin(64,0);
        rep(j, 0, 64) {
            new_bin[j ^ lazy[i]] = tree[i][j];
        }
        tree[i] = new_bin;
    }
    void update(int i, char new_c) {
        uint8_t tag = (1 << (s[i]-'a')) ^ (1 << (new_c - 'a'));
        i += N + 1;
        rep(j, i, 2*N) {
            lazy[j] ^= tag;

        }
    }


};

void answer() {
    string s;
    cin >> s;
    int q;
    cin >> q;
    rep(_, 0, q) {
        int type, l, r, i;
        char c;
        cin >> type;
        if (type == 1) {
            cin >> l >> r;
            --l; --r;
        }
        if (type == 2) {
            cin >> i >> c;
            --i;
        }

    }
}
#pragma endregion
void solve() {
   
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    // OPTIONAL FOR SOME CONTESTS
    //cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}