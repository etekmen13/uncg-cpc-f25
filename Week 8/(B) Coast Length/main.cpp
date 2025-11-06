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
    int N, M;
    cin >> N >> M;
    vector<string> g(N);
    vector<vector<bool>> vis(N, vector<bool>(M, 0));
    ll coast = 0LL;
    vector<pair<int, int>> look = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    cin.ignore();
    rep(i, 0, N)
    {
        getline(cin, g[i]);
    }
    auto in_b = [&](int r, int c) -> bool
    {
        return r >= 0 && r < N && c >= 0 && c < M;
    };

    auto get_coast = [&](int r, int c) -> int
    {
        int count = 0;
        int i = 0;
        vi found(4, 0);
        for (const auto &[dr, dc] : look)
        {
            int nr = r + dr, nc = c + dc;
            if (in_b(nr, nc) && g[nr][nc] == '1')
            {
                ++count;
                found[i] = 1;
            }
            ++i;
        }
        // cout << "  " << found[3] << "  \n";
        // cout << found[1] << "(" << r << "," << c << ")" << found[0] << "\n";
        // cout << "  " << found[2] << "  \n";
        // cout << "\n";
        return count;
    };
    auto search = [&](int r, int c)
    {
        if (!in_b(r, c) || vis[r][c] || g[r][c] == '1')
            return;
        queue<pair<int, int>> q;
        q.push({r, c});
        while (!q.empty())
        {
            auto [_r, _c] = q.front();
            q.pop();

            if (vis[_r][_c])
                continue;
            vis[_r][_c] = 1;
            coast += get_coast(_r, _c);
            // cout << coast << "\n";
            for (const auto &[dr, dc] : look)
            {
                int nr = _r + dr, nc = _c + dc;
                if (in_b(nr, nc) && !vis[nr][nc] && g[nr][nc] == '0')
                    q.push({nr, nc});
            }
        }
    };
    auto count_edge = [&](int r, int c)
    {
        if (in_b(r, c))
            coast += g[r][c] == '1';
    };
    rep(i, 0, max(N, M))
    {
        search(0, i);
        search(i, 0);
        search(N - 1, i);
        search(i, M - 1);
        count_edge(0, i);
        count_edge(N - 1, i);
        count_edge(i, 0);
        count_edge(i, M - 1);
    }
    cout << coast << "\n";
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