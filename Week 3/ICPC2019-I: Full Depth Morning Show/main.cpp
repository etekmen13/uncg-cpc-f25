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
void answer() {
    int n;
    cin >> n;
    vector<int> t(n);
    
    ll total_tax = 0;
    rep(i, 0, n) {cin >> t[i]; total_tax += t[i];}

    struct Edge {int v; int w;};

    vector<vector<Edge>> tree(n, vector<Edge>());

    rep(i, 0, n-1) {
        int u,v,w; 
        cin >> u>> v >>w; --u; --v;

        tree[u].push_back({v, w});
        tree[v].push_back({u, w});
    }

    vector<ll> _size(n, 0), _tax(n, 0), sum_dist(n, 0), weighted_sum_dist(n, 0);

    function<void(int, int, ll)> dfs = [&](int node, int parent, ll dist) -> void {
        _size[node] = 1;
        _tax[node] = t[node];
        sum_dist[0] += dist;
        weighted_sum_dist[0] += t[node] * dist;
        for(auto& [neighbor, cost] : tree[node]) {
            if (neighbor == parent) continue;
            dfs(neighbor,node,dist + cost);
            _size[node] += _size[neighbor];
            _tax[node] += _tax[neighbor];
        }
    };

    function<void(int, int)> reroot = [&](int node, int parent) -> void {
        for (auto& [neighbor, cost] : tree[node]) {
            if (neighbor == parent) continue;
            sum_dist[neighbor] = sum_dist[node] + cost * ((ll)n - 2LL * _size[neighbor]);
            weighted_sum_dist[neighbor] = weighted_sum_dist[node] + cost * (total_tax - 2LL * _tax[neighbor]);
            reroot(neighbor, node);
        }
    };

    dfs(0, -1, 0);
    reroot(0, -1);

    rep(i, 0, n) cout << t[i] * sum_dist[i] + weighted_sum_dist[i] << "\n";
    
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
        answer();
    }
    return 0;
}