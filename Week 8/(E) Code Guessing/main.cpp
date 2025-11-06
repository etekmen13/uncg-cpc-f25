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
    // 1-9
    // a < a < b < b -> biggest a must be 7 -> 8,9
    // b < b < a < a -> smallest a must be 3 -> 1, 2
    // a < b < a < b -> small a = 6, big a = 8 -> 7, 9
    // b < a < b < a -> small a = 2, big a = 4 -> 1, 3
    // a < b < b < a -> small a must be 2 less than big a -> b's can be from 2-8
    // b < a < a < b -> small a = 2, big a = 8 -> 1, 9

    int a1, a2;
    cin >> a1 >> a2;
    if (a2 < a1)
        swap(a2, a1);

    cin.ignore();
    string s;
    getline(cin, s);
    if (s[0] == 'A' && s[1] == 'A')
        cout << (a2 == 7 ? "8 9" : "-1") << "\n";
    else if (s[0] == 'A' && s[2] == 'A')
        cout << (a1 == 6 && a2 == 8 ? "7 9" : "-1") << "\n";
    else if (s[0] == 'A' && s[3] == 'A')
        cout << (a2 - a1 == 3 ? format("{} {}", a1 + 1, a2 - 1) : "-1") << "\n";
    else if (s[1] == 'A' && s[2] == 'A')
        cout << (a1 == 2 && a2 == 8 ? "1 9" : "-1") << "\n";
    else if (s[1] == 'A' && s[3] == 'A')
        cout << (a1 == 2 && a2 == 4 ? "1 3" : "-1") << "\n";
    else if (s[2] == 'A' && s[3] == 'A')
        cout << (a1 == 3 ? "1 2" : "-1") << "\n";
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