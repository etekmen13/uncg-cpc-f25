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
struct BIT
{
  ll n;
  vl arr;
  BIT(ll _n) : n(_n + 1), arr(_n + 1) {}
  void update(ll i, ll diff)
  {
    while (i < n)
    {
      // cout << i << "\n";
      arr[i] += diff;
      i += (i & -i);
    }
  }
  ll query(ll i)
  {
    ll result = 0LL;
    while (i > 0)
    {
      // cout << i << "\n";
      result += arr[i];
      i -= (i & -i);
    }
    return result;
  }
};
struct Point
{
  ll id, x, y, v;
  friend Point operator-(const Point &a, const Point &b)
  {
    return {0LL, a.x - b.x, a.y - b.y, 0LL};
  }
  friend ostream &operator<<(ostream &o, const Point &a)
  {
    o << (char)('A' + a.id) << ": " << a.x << ", " << a.y << ", " << a.v << " ";
    return o;
  }
};
void solve()
{
  auto cross = [](const Point &a, const Point &b) -> ll
  {
    return a.x * b.y - a.y * b.x;
  };
  auto orientation = [&cross](const Point &p0, const Point &a, const Point &b)
  {
    ll v = cross(a - p0, b - a);
    if (v < 0)
      return -1; // cw
    if (v > 0)
      return 1; // ccw
    return 0;
  };
  ll n, x;
  cin >> n >> x;
  Point barnleft = {-1, 0, 0, 0}, barnright = {-2, x, 0, 0};
  vector<Point> points;
  points.reserve(n);
  rep(i, 0, n)
  {
    ll x, y, v;
    cin >> x >> y >> v;
    points.push_back({i, x, y, v});
  }
  vector<Point> ranks(n);
  sort(points.begin(), points.end(),
       [&orientation, &barnright](const Point &a, const Point &b)
       {
         return orientation(barnright, a, b) < 0;
       });
  rep(i, 0, n) { ranks[points[i].id].y = i; }
  sort(points.begin(), points.end(),
       [&orientation, &barnleft](const Point &a, const Point &b)
       {
         return orientation(barnleft, a, b) > 0;
       });

  rep(i, 0, n)
  {
    ranks[points[i].id].id = points[i].id;
    ranks[points[i].id].x = i;
    ranks[points[i].id].v = points[i].v;
  }

  BIT tree(n);
  vl ans(n);
  // rep(i, 0, n) { cout << ranks[i] << "\n"; }
  // cout << endl;
  for (ll i = 0LL; i < n; ++i) {
    auto rank = ranks[points[i].id];
    // cout << "querying point " << (char)('A' + rank.id) << " with right-rank: " << rank.y << endl;
    ans[rank.id] = tree.query(rank.y+1);
    // cout << "Value: " << ans[rank.id] << endl;
    tree.update(rank.y+1, rank.v);
  }
  for(auto& x : ans) {
    cout << x << "\n";
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