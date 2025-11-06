#pragma region
#include <bits/stdc++.h>

using namespace std;
#define REP(i, a, b) for (int i = a; i <= b; i++)
#define rep(i, a, b) for (int i = a; i < b; i++)
#define PER(i, a, b) for (int i = a; i >= b; i--)
#define per(i, a, b) for (int i = a; i > b; i--)

#define pb push_back
#define mp make_pair
#define F first
#define S second
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef pair<int, int> pi;
typedef pair<ll, ll> pl;

const ll MOD = 1000000007;

ll mod_add(ll a, ll b, ll m) { return ((a % m) + (b % m)) % m; }
ll mod_sub(ll a, ll b, ll m) { return ((a % m) - (b % m) + m) % m; }
ll mod_mul(ll a, ll b, ll m) { return ((a % m) * (b % m)) % m; }
ll mod_exp(ll a, ll e, ll M)
{
    ll res = 1;
    while (e)
    {
        if (e & 1)
            res = (res * a) % M;
        a = (a * a) % M;
        e >>= 1;
    }
    return res;
}

template <typename T, typename Func>
T bin_apply_func(T obj, Func func, ll n)
{
    T result = std::move(obj); // accumulator object
    Func f = func;             // f will be "squared" (repeatedly composed)

    while (n > 0)
    {
        if (n & 1)
        {
            result = f(result); // appy the function
        }
        Func f_next = [f](T x) { // compose the function
            return f(f(x));
        };
        f = std::move(f_next); // avoid copying
        n >>= 1;               // next bit
    }

    return result;
}
template <class T>
ostream &operator<<(ostream &o, const vector<T> &vec)
{
    for (const auto &e : vec)
    {
        o << e << " ";
    }
    o << endl;
    return o;
}

#pragma endregion
struct DSU
{
    vector<int> repr, rank;
    DSU(int RC) : repr(RC), rank(RC, 0) { iota(repr.begin(), repr.end(), 0); }

    void unite(int a, int b)
    {
        a = find(a);
        b = find(b);
        if (a != b)
        {
            if (rank[a] < rank[b])
                swap(a, b);
            repr[b] = a;
            if (rank[a] == rank[b])
                rank[a]++;
        }
    }

    int find(int v)
    {
        if (v == repr[v])
            return v;
        return repr[v] = find(repr[v]);
    }
};
void solve()
{
    int R, C;
    cin >> R >> C;
    cin.ignore();
    vector<string> g(R);
    rep(i, 0, R)
    {
        getline(cin, g[i]);
    }
    DSU dsu(R * C);
    rep(r, 0, R)
    {
        rep(c, 0, C)
        {
            int i = r * C + c;
            if (c + 1 < C && g[r][c] == g[r][c + 1])
                dsu.unite(i, i + 1);
            if (r + 1 < R && g[r][c] == g[r + 1][c])
                dsu.unite(i, i + C);
        }
    }
    int N;
    cin >> N;
    rep(i, 0, N) {
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;
        --r1; --c1; --r2; --c2;

        int idx1 = r1 * C + c1, idx2 = r2 * C + c2;

        if(dsu.find(idx1) == dsu.find(idx2)) {
            cout << (g[r1][c1] == '0' ? "binary" : "decimal") << "\n";
        }
        else {
            cout << "neither\n";
        }
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    // OPTIONAL FOR SOME CONTESTS
    // cin >> T;
    while (T--)
    {
        solve();
    }
    return 0;
}