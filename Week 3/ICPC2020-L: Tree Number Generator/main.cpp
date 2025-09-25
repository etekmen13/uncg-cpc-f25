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
    WTS: Walk path a -> b. 

    Let node v hold the digit concatenation from the root to v, as well as the reverse concatenation.
        - During Euler Tour/jump table, assign digit string for node v like:
            Define concat(u, v, len_to_v) = (u * pow10[len_to_v] + digit[v]) mod m
            Let jump_digits[v][j] be the digit string from 2^jth parent down to v (e.g. the ancestor 1, 2, 4, 8 away, etc.)
            Let target_ancestor := jump_digits[v][j]
            Let first_half_to_target_ancestor := jump_digits[v][j-1]  ----> 2^(j-1) == 2^j ÷ 2
            Let second_half_to_target_ancestor := jump_digits[first_half_to_target_ancestor][j-1]
            Finally, Let target_ancestor := concat(first_half, second_half)
            Makes sense? If i want the digits from nodes a --> e, I can do so with `concat(a --> c, c --> e)`
        -
        

    
    Define get_digits(node, walk_len, down):
        result = 0
        walk_len += 1 if down else 0 // we must include c on the way down, but NOT on the way up

        for set_bit in walk_len:
            if down:
                result = concat(jump_digits[node][set_bit], result)
            else:
                result = concat(result, jump_digits[node][set_bit])
            node = jump[node][set_bit]
        return result
    
    Then the final algorithm is:
    Let c := LCA(a,b)
    Let a_to_c = get_digits(a, depth[a]-depth[c], False)
    Let c_to_b = get_digits(b, depth[b]-depth[c], True)
    Let final_answer = concat(a_to_c, c_to_b, depth[b]-depth[c]) 
    */


    // ***1-INDEXED***
    ll n, m, q;
    cin >> n >> m >> q;
    vector<vector<ll>> adj(n+1, vector<ll>());
    rep(i,1,n) {
        ll x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    // data structures
    ll LOG = 1;
    while ((1 << LOG) <= n) ++LOG;
    vector<ll> tin(n+1, -1), tout(n+1, -1), depth(n+1, 0), pow10(n+1), fwd(n+1);
    vector<vector<ll>> jump(n+1, vector<ll>(LOG)), jump_digits(n+1, vector<ll>(LOG));

    vector<int> digit(n+1);
    // init jump_digits and digits
    rep(i, 1, n+1) {
        int d;
        cin >> d;
        digit[i] = d;
        jump_digits[i][0] = d;
    }
    // init pow10 cache
    pow10[0] = 1 % m;
    for (int i = 1; i <= n; ++i) pow10[i] = (pow10[i-1] * 10) % m;
    auto concat = [&](ll a, ll b, ll len_to_b) -> ll {return (a * pow10[len_to_b] + b) % m;};
    struct Frame {ll node; ll parent; bool exiting;};
    stack<Frame> st;
    vector<bool> visited(n+1, 0);
    st.push({1,-1, false});
    fwd[1] = digit[1] % m;
    ll timer = 0;
    // Euler tour / jump table
    while (!st.empty()) {
        auto [v, p, exiting] = st.top(); st.pop();
        if (exiting) {
            tout[v] = timer - 1;
            continue;
        }
        if (visited[v]) continue;
        visited[v] = 1;
        st.push({v, p , true});
        tin[v] = timer++;
        jump[v][0] = (p == -1 ? v : p);
        for(ll j = 1; j < LOG; ++j) {
            jump[v][j] = jump[jump[v][j-1]][j-1];
            jump_digits[v][j] = concat(jump_digits[v][j-1], jump_digits[jump[v][j-1]][j-1], (1 << (j-1)));
        }

        for(auto u : adj[v]) {
            if (u == p) continue;
            depth[u] = depth[v] + 1;
            st.push({u,v,false});
            fwd[u] = (fwd[v] * 10 + digit[u]) % m;
        }
    }
    auto is_ancestor = [&tin, &tout](ll a, ll b){ return tin[a] <= tin[b] && tin[b] <= tout[a];};

    auto lca = [&](ll a, ll b){ 
        if (is_ancestor(a,b)) return a;
        if (is_ancestor(b,a)) return b;
        for (int j = LOG-1; j >= 0; --j) 
            if (!is_ancestor(jump[a][j], b)) a = jump[a][j];
        return jump[a][0];
    };

    auto get_up_value = [&](int a, int need)-> pair<ll,int> {
        ll val = 0;
        int len = 0;
        for (int j = 0; j < LOG; ++j) {
            if (need & (1 << j)) {
                val = concat(val, jump_digits[a][j], (1 << j)); // append this segment
                a   = jump[a][j];                                // move up by 2^j
                len += 1 << j;
            }
        }
        return {val, len}; // (value, length)
    };
    rep(oops, 0, q) {
        ll x, y;
        cin >> x >> y;
        ll w = lca(x,y);
        int lenUp   = depth[x] - depth[w];
        auto [up_walk, up_len] = get_up_value(x, lenUp);

        int lenDown = depth[y] - depth[w];
        ll no_c = (fwd[y] - (fwd[w] * pow10[lenDown]) % m + m) % m;   // exclude C
        ll down_walk = ( (1LL * digit[w] * pow10[lenDown]) + no_c ) % m;
        int down_len = 1 + lenDown;

        cout << concat(up_walk, down_walk, down_len) << "\n";
    }
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