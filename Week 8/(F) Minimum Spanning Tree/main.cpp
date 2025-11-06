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
struct edge
{
    int to, w;
};
struct Edge
{
    int u, id;
    edge e;
};
struct DSU
{
    vector<int> repr, rank;
    DSU(int _n) : repr(_n), rank(_n, 0) { iota(repr.begin(), repr.end(), 0); };
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
                ++rank[a];
        }
    }
    int find(int v)
    {
        if (v == repr[v])
            return v;

        return repr[v] = find(repr[v]);
    }
};
void solve(bool &go)
{
    int N, M;
    cin >> N >> M;
    if (N == 0 && M == 0)
    {
        go = false;
        return;
    }
    if (M == 0)
    {
        cout << "Impossible\n";
        return;
    }
    vector<vector<edge>> adj(N);
    vector<Edge> edges;
    edges.reserve(N);
    DSU dsu(N);
    rep(i, 0, M)
    {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
        edges.push_back({u, i, {v, w}});
    }

    sort(edges.begin(), edges.end(), [](Edge a, Edge b)
         { return a.e.w < b.e.w; });

    vector<Edge> MST;
    MST.reserve(M);
    for (const auto &x : edges)
    {
        if (MST.size() == 0 || dsu.find(x.u) != dsu.find(x.e.to))
        {
            MST.push_back(x);
            dsu.unite(x.u, x.e.to);
        }
    }
    cout << accumulate(MST.begin(), MST.end(), 0LL, [](ll curr, Edge x)
                       { return curr + x.e.w; })
         << "\n";
    sort(MST.begin(), MST.end(), [](Edge a, Edge b) {if (a.u == b.u) return a.e.to < b.e.to; return a.u < b.u;});
    for (const auto &x : MST)
    {
        int a = x.u, b = x.e.to;
        if (b < a) {
            swap(a, b);
        }
        cout << a << " " << b << "\n";
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    // OPTIONAL FOR SOME CONTESTS
    // cin >> T;
    bool go = true;
    while (go)
    {
        solve(go);
    }
    return 0;
}