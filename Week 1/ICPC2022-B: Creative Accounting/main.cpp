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

#pragma region Answer
void answer() {}
#pragma endregion
void solve()
{
  /*
  Objective:
       Given l := min segment size, h := max segment size
       Return both the min and max number of profitable days (segments > 0)

   Naive: for each i in [l, h], and for each starting day j in [0, i], count
  profitable segments O(n) O(n * (h-l)^2) Worst Case: 3e4 * 1e6 = 3e10.
  Infeasible.

   With prefix sum, counting profitable segment is O(i), reducing worst case to
  1e12. Doable in 5 seconds.

   l = 3, h = 5
   3 2 -7 5 4 1 3 0 -3 5
   3 5 -2 3 7 8 11 11 8 13
   To get min profitable segments, make segments == 0 as much as possible.
   To get max profitable segments, make segments == 1 as much as possible.

  */

  int n, l, h;
  cin >> n >> l >> h;
  vector<int> daily;
  daily.reserve(n);
  vector<ll> prefix(n + 1);
  prefix[0] = 0;
  rep(i, 0, n)
  {
    int x;
    cin >> x;
    daily.push_back(x);
    prefix[i + 1] = prefix[i] + x;
  }
  // cout << daily << endl;
  // cout << prefix << endl;
  int min_profit = numeric_limits<int>::max();
  int max_profit = numeric_limits<int>::min();
  REP(i, l, h)
  { // segment length
    REP(j, 1, i)
    {            // starting day
      int k = j; // segment boundary
      int profit = 0;
      while (k < n)
      {
        int segment_profit = prefix[k] - prefix[max(0, k - i)];
        // cout << segment_profit << " "; // segment profit
        profit += (segment_profit > 0);
        k += i;
      }
      // cout << prefix[n] - prefix[k - i];
      profit += (prefix[n] - prefix[k - i] > 0);
      min_profit = min(min_profit, profit);
      max_profit = max(max_profit, profit);
      // cout << endl;
    }
    // cout << endl;
    // cout << "______" << endl;
  }
  cout << min_profit << " " << max_profit << "\n";
}

void solve2()
{
  ll n, h, l;
  cin >> n >> l >> h;
  vl profit;
  ll min_profit = numeric_limits<ll>::max(), max_profit = numeric_limits<ll>::min();
  profit.reserve(n);
  vl prefix(n + 1);
  prefix[0] = 0;
  rep(i, 0, n)
  {
    ll x;
    cin >> x;
    profit.push_back(x);
    prefix[i + 1] = prefix[i] + x;
  }
  REP(i, l, h) // segment size
  {
    rep(j, 0, i) // offset
    {
      ll profit = 0LL;
      ll k = j;
      while(k < n) { // sum over segments
        
        profit += (prefix[k] - prefix[max(0LL,k-i)] > 0);
        k += i;
      }
      profit += (prefix[n] - prefix[k-i] > 0);
      min_profit = min(min_profit, profit);
      max_profit = max(max_profit, profit);
    }
  }
  cout << min_profit << " " << max_profit << "\n";
}
int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int T = 1;
  // OPTIONAL FOR SOME CONTESTS
  // cin >> T;
  auto start = chrono::high_resolution_clock::now();

  while (T--)
  {
    solve2();
  }
  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
  // cout << duration.count() / 1e6 << endl;
  return 0;
}