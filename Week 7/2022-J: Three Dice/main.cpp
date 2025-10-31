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

void solve()
{
    int n;
    cin >> n;
    vector<string> words(n);
    rep(i, 0, n)
    {
        cin >> words[i];
    }
    // Quick Feasability check: if any word has the same letter more than once, FAIL
    for (auto &w : words)
    {
        if (w[0] == w[1] || w[0] == w[2] || w[1] == w[2])
        {
            cout << 0 << "\n";
            return;
        }
    }
    bool letter_used[26] = {false};
    for (auto &w : words)
        for (char c : w)
            letter_used[c - 'a'] = true;

    vector<char> letters;
    for (int c = 0; c < 26; ++c)
        if (letter_used[c])
            letters.push_back(char('a' + c));

    int M = (int)letters.size();
    // If there are more than 18 unique letters, FAIL
    if (M > 18)
    {
        cout << 0 << "\n";
        return;
    }
    int id[26];
    fill(begin(id), end(id), -1);

    for (int i = 0; i < M; ++i)
        id[letters[i] - 'a'] = i;

    // Create the m-coloring graph
    vector<vector<int>> adj(M);
    auto add_edge = [&](int u, int v)
    {
        if (u == v)
            return;
        adj[u].push_back(v);
        adj[v].push_back(u);
    };

    // cat: (c,a), (c,t), (a,t)
    for (auto &w : words)
    {
        int a = id[w[0] - 'a'], b = id[w[1] - 'a'], c = id[w[2] - 'a'];
        add_edge(a, b);
        add_edge(a, c);
        add_edge(b, c);
    }
    // remove duplicate edges
    for (int i = 0; i < M; ++i)
    {
        auto &v = adj[i];
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
    }
    // sort by degree descending
    vector<int> order(M);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int a, int b)
         {
        if (adj[a].size() != adj[b].size()) return adj[a].size() > adj[b].size();
        return a < b; });

    // color[letter] = which dice we chose for the letter
    vector<int> color(M, -1);
    array<int, 3> cap = {6, 6, 6}; // remaining faces per die

    function<bool(int)> dfs = [&](int t) -> bool
    {
        if (t == M)
            return true;
        int u = order[t];

        for (int d = 0; d < 3; ++d)
        {
            if (cap[d] == 0)
                continue; // capacity check
            bool clash = false;
            for (int nb : adj[u])
                if (color[nb] == d)
                {
                    clash = true;
                    break;
                }
            if (clash)
                continue;

            color[u] = d;
            --cap[d];
            if (dfs(t + 1))
                return true;
            // backtrack
            ++cap[d];
            color[u] = -1;
        }
        return false;
    };

    if (!dfs(0))
    {
        cout << 0 << "\n";
        return;
    }
    // fill out the required letters on the dice
    array<string, 3> die = {"", "", ""};
    vector<bool> used(26, false);
    for (int i = 0; i < M; ++i)
    {
        int d = color[i];
        die[d].push_back(letters[i]);
        used[letters[i] - 'a'] = true;
    }
    // get the remaining unused letters
    vector<char> pool;
    for (int c = 0; c < 26; ++c)
        if (!used[c])
            pool.push_back(char('a' + c));
    
    // fill the rest of the dice with unused letters
    int ptr = 0;
    for (int d = 0; d < 3; ++d)
        while ((int)die[d].size() < 6)
            die[d].push_back(pool[ptr++]);

    cout << die[0] << "\n"
         << die[1] << "\n"
         << die[2] << "\n";
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