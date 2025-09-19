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
    /*
    Power: Too low = miss a pillar. Too high = cause damage to pillar.
    Find smallest jump distance to guarantee that your robot can reach any pillar and return back to the start, without landing on a pillar twice.

    Monotone Predicate: At power P, can I reach any pillar and make it back without revisiting?
    Binary search on P, DFS and if start node is ever re-encountered, add visited set to "reachable".
    If all reachable, then bisect_left.
    */


    
    int n;
    cin >> n;
    vector<pair<int,int>> g(n+1);
    g[0] = {0,0};
    rep(i, 0, n) {
        int x, y;
        cin >> x >> y;
        g[i+1] = {x,y};
    }

    auto dist2 = [](pair<int,int> a, pair<int,int> b)->long long {
        long long dx = (long long)a.first - b.first;
        long long dy = (long long)a.second - b.second;
        return dx*dx + dy*dy;
    };
    
    auto connected = [&](long long D2)->bool {
        int N = (int)g.size(); // nodes 0..n
        vector<char> vis(N, 0);
        stack<int> st; st.push(0); vis[0]=1;
        while(!st.empty()){
            int u = st.top(); st.pop();
            for(int v=0; v<N; ++v){
                if(!vis[v] && dist2(g[u], g[v]) <= D2){
                    vis[v]=1; st.push(v);
                }
            }
        }
        return all_of(vis.begin(), vis.end(), [](char x){return x;});
    };
    
    auto ok = [&](long double P)->bool {
        long double Pd = P;                    
        long double P2d = Pd*Pd;
    
        if(!connected(P2d)) return false;
    
        int N = (int)g.size();
        vector<int> disc(N,-1), low(N,0), parent(N,-1);
        vector<char> arti(N,0);
        int timer = 0;
    
        struct Frame { int u, it; };
        vector<Frame> st;
        st.push_back({0, 0});
    
        while(!st.empty()){
            auto &fr = st.back();
            int u = fr.u;
    
            if(disc[u] == -1){
                disc[u] = low[u] = ++timer;
            }
    
            if(fr.it < N){
                int v = fr.it++;
                if(u == v) continue;
                if(dist2(g[u], g[v]) > P2d) continue;
    
                if(disc[v] == -1){
                    parent[v] = u;
                    st.push_back({v, 0});          
                } else if(v != parent[u]){
                    low[u] = min(low[u], disc[v]); // back edge
                }
                continue; 
            }
    
            st.pop_back();
            int p = parent[u];
            if(p != -1){
                low[p] = min(low[p], low[u]);
                if(low[u] >= disc[p]) arti[p] = 1; 
            }
        }
        // Only node 0 may be an articulation
        for(int i=1;i<N;i++) if(arti[i]) return false;
        return true;
    };

    long double hi = sqrt(8) * 1e9, lo = 0.0, eps = 1e-9;

    while((hi - lo) > eps) {
        long double mid = midpoint(lo, hi);
        if (ok(mid)) hi = mid; // Try lower power.
        else lo = mid;
    }
    cout << fixed << setprecision(15);
    cout << lo + (hi- lo) / 2 << "\n";
    

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