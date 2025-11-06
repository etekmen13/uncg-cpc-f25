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
ll mod_exp(ll a, ll e, ll M) {
  ll res = 1;
  while (e) {
    if (e & 1) res = (res * a) % M;
    a = (a * a) % M;
    e >>= 1;
  }
  return res;
}

template <typename T, typename Func>
T bin_apply_func(T obj, Func func, ll n) {
  T result = std::move(obj);  // accumulator object
  Func f = func;              // f will be "squared" (repeatedly composed)

  while (n > 0) {
    if (n & 1) {
      result = f(result);  // appy the function
    }
    Func f_next = [f](T x) {  // compose the function
      return f(f(x));
    };
    f = std::move(f_next);  // avoid copying
    n >>= 1;                // next bit
  }

  return result;
}
template <class T>
ostream& operator<<(ostream& o, const vector<T>& vec) {
  for (const auto& e : vec) {
    o << e << " ";
  }
  o << endl;
  return o;
}

#pragma endregion
struct Edge {
  int to;
  float w;

  friend bool operator<(const Edge& a, const Edge& b) { return a.w > b.w; }
};
bool solve() {
  int N, M;
  cin >> N >> M;
  if (N == 0 && M == 0) return false;
  vector<vector<Edge>> adj(N);
  rep(i, 0, M) {
    int u, v;
    float w;
    cin >> u >> v >> w;
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
  }
  vector<double> best(N, 0.0);
  vector<int> parent(N, -1);
  best[0] = 1.0;
  using P = pair<double, int>;
  priority_queue<P> pq;
  pq.push({1.0, 0});

  while (!pq.empty()) {
    auto [val, u] = pq.top();
    pq.pop();

    for (const auto& [v, w] : adj[u]) {
      auto cand = val * w;
      if (cand > best[v]) {
        best[v] = cand;
        parent[v] = u;
        pq.push({cand, v});
      }
    }
  }
  cout << fixed << setprecision(4);
  cout << best[N-1] << "\n";
  return true;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int T = 1;
  // OPTIONAL FOR SOME CONTESTS
  // cin >> T;
  while (solve()) {
  }
  return 0;
}