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
    // Crucial Note about Modulo.
    // (a + b) % m = ((a % m) + (b % m)) % m
    // ab % m = ((a % m) (b % m)) % m



    // THE PROBLEM GIVES NODES IN 1-INDEX

    ll  n, // number of nodes
        m, // modulo
        q; // number of queries

    cin >> n >> m >> q;

    // size n+1 because we are 1 indexed!
    vector<vector<ll>> adj(n+1, vector<ll>()); // Tree

    // Build Tree
    rep(i,1,n) {
        ll x, y;
        cin >> x >> y;
        adj[x].push_back(y); 
        adj[y].push_back(x); // both directions
    }

    ll tree_depth = 1; // maximum tree depth = ceil[log(n)]
    while ((1 << tree_depth) <= n) ++tree_depth; 

    // size n+1 because we are 1 indexed!
    vector<ll>  tin(n+1, -1), // arrival time during DFS
                tout(n+1, -1), // exit time during DFS
                depth(n+1, 0), // depth of node
                pow10(n+1), // pre-compute powers of 10, its faster.
                fwd(n+1); // holds the digit string from root to node, mod m.
    
    // size n+1 because we are 1 indexed! HOWEVER... Tree depth is 0-indexed ! :)
    vector<vector<ll>>  jump(n+1, vector<ll>(tree_depth)), // for each node, holds the 2^jth parent, 0 < j < tree_depth.
    jump_digits(n+1, vector<ll>(tree_depth)); // for each node, holds the digit string from node to 2^jth parent, mod m.

    // size n+1 because we are 1 indexed!
    vector<int> digit(n+1); // holds the digit 0-9 assigned to node n.

    // assign digits to nodes
    // jump_digits[i][0] = the digit string of length 2^0 = length 1 = the digit itself.
    rep(i, 1, n+1) {
        int d;
        cin >> d;
        digit[i] = d;
        jump_digits[i][0] = d;
    }

    // precompute powers of 10 MOD M.
    pow10[0] = 1 % m;
    for (int i = 1; i <= n; ++i) {
        pow10[i] = (pow10[i-1] * 10) % m;
    }

    auto concat = 
    // Define how to concatenate the digit strings. 
    // e.g. a = 12, b = 13, len(b) = 2. 
    // 12 * 10^2 + 13 = 1213. Then mod m.
    [&](ll a, ll b, ll len_b) -> ll {
        return (a * pow10[len_b] + b) % m;
    };

    // Euler Tour Iterative DFS. 
    // We need to label tin[v] upon arrival of v, and tout[v] upon exiting of v.
    // tout[v] is determined after all of the subtrees of v have been visited.
    // So we need a way to recurse-and-return to our original node. 
    // Standard iterative DFS doesn't account for this.
    // With a recursive call stack we can pause in the middle of execution and recurse deeper.
    // To simulate this iteratively we add a flag "exiting" so we know when we are on the way out of a node.
    // Then for each node we enter, we push the "exiting" version of that node onto the stack before anything else,
    // which allows us to "resume execution" from that node again.

    // Simulated call stack frame.
    struct Frame {ll node; ll parent; bool exiting;};

    // Simulated call stack.
    stack<Frame> st;
    
    // Visited set. Standard DFS stuff.
    vector<bool> visited(n+1, 0);

    // 1-indexed, push root node with parent == -1, and exiting = false.
    st.push({1,-1, false});

    // root -> root digit string is just the digit (MOD M).
    fwd[1] = digit[1] % m;

    // Begin Euler Tour.
    ll timer = 0;
    while (!st.empty()) {
        // Pop from call stack.
        auto [v, p, exiting] = st.top(); st.pop();

        // we have "returned" to our dfs node, now we are exiting it, update tout.
        if (exiting) {
            tout[v] = timer++;
            continue;
        }

        if (visited[v]) continue;
        visited[v] = 1;
        
        // The trick: push the node AGAIN as "exiting", so we can return to it later.
        st.push({v, p , true});

        // We have arrived at the node for the first time. Update tin.
        tin[v] = timer++;

        // The 2^0th parent of a node is its direct parent, UNLESS its the root, in which case it is itself.
        jump[v][0] = (p == -1 ? v : p);

        
        // Binary Decomposition of Digit Strings.
        for(ll j = 1; j < tree_depth; ++j) { // 1-indexed!
            
            // 2^jth parent of v is just the 2^(j-1)th parent of the 2^(j-1)th parent.
            // e.g. if I have A - B - C -D - E:
            //      the 2^2 = 4th parent of E is A.
            //      the 2^1 = 2nd parent of E is C.
            //      the 2^1 = 2nd parent of C is A.
            //      So the 4th parent of E = the 2nd parent of C = the 2nd parent of the 2nd parent of E.
            jump[v][j] = jump[jump[v][j-1]][j-1];

            // the digit string from node -> 2^jth parent is the
            // the digit string from node ->2^(j-1)th parent concatenated with
            // the digit string from 2^(j-1)th parent -> 2^jth parent.
            jump_digits[v][j] = concat(
                                        jump_digits[v][j-1], 
                                        jump_digits[jump[v][j-1]][j-1],
                                        (1 << (j-1)) // length from 2^(j-1) -> 2^j = 2^(j-1).
                                    );
            // IMPORTANT NOTE:
            // Jump tables say "jump 2^n" i.e traverse 2^n edges. jump_digits says "digit string of *length* 2^n".
            // A path with 2^n edges will have 2^n+1 nodes. This means that our digit strings will be missing 1 digit.
            // Because we start at 2^0 = the digit itself, the missing digit is the end point.
            // This is actually perfect because then we don't have to worry about double counting the end point when we 
            // chain concatenations together.

        }
        // DFS:
        // push neighbors to stack, assign their depths.
        for(auto u : adj[v]) {
            if (u == p) continue;
            depth[u] = depth[v] + 1;
            st.push({u,v,false});

            // digit string from root -> node = digit string from root -> parent of node + digit of node.
            // e.g. A - B - C:
            // fwd[A] = A. (base case)
            // fwd[B] = fwd[A] + B = A + B = AB
            // fwd[C] = fwd[B] + C = AB + C = ABC.

            fwd[u] = concat(fwd[v], digit[u], 1);
        }
    }

    // Euler Tour allows for ancestor checks in O(1).
    // For a node a, all subnodes b of a will be entered AFTER entering a (tin[a] <= tin[b]) (we consider a to the 0th ancestor of itself.)
    // and all subnodes b of a well be exited BEFORE exiting a. (we consider a to be a subnode of itself).
    auto is_ancestor = [&tin, &tout](ll a, ll b){ return tin[a] <= tin[b] && tout[b] <= tout[a];};

    // LCA: Lowest Common Ancestor.

    auto lca = [&](ll a, ll b){ 
        if (is_ancestor(a,b)) return a;
        if (is_ancestor(b,a)) return b;

        // At this point, there must be some common ancestor above both a and b.
        for (int j = tree_depth-1; j >= 0; --j) 
        // If the farthest power of 2 ancestor is NOT an ancestor of b,
        // then we can safely jump up to that ancestor
        // otherwise, try a smaller jump
        // repeat this until the direct parent of a is also an ancestor of b.
            if (!is_ancestor(jump[a][j], b)) 
                a = jump[a][j];
        
        return jump[a][0];
    };

    // Get the digit string from node a -> LCA, excluding the LCA digit.
    auto get_up_value = [&](int a, int len_to_lca) -> int {
        ll val = 0;
        // Binary decomposition: 
        // The digit string is the concatenation of the digit strings for each 2^jth parent 
        // e.g. A - B - C - D - E - F - G - H
        // digit string A -> H has length 7 = 0b111. = 2^0 + 2^1 + 2^2
        // digit string A -> H consists of  H -> G +  G -> E +  E -> A.
        //                                  2^0,        2^1,    2^2 parent.

        // ***MAIN IDEA***
        // Any digit string can be formed in log(N) time using precomputed digit strings of powers of 2.
        for (int j = 0; j < tree_depth; ++j) {

            // check if bit j is set => 2^jth parent is included
            if (len_to_lca & (1 << j)) {
                val = concat(val, jump_digits[a][j], (1 << j)); // append this segment
                a   = jump[a][j];                                // move up by 2^j
            }
        }
        return val;
    };

    // FINALLY! 

    // Process for each query.
    rep(_, 0, q) {
        ll x, y; // path from node x -> y.
        cin >> x >> y;
        ll w = lca(x,y); // find least common ancestor LCA(x,y)

        // get the length to the LCA.
        int lenUp   = depth[x] - depth[w];
        // get the digit string x -> LCA.
        auto up_walk = get_up_value(x, lenUp);

        // length from LCA -> y. LCA digit is excluded.
        int lenDown = depth[y] - depth[w];

        // Digit string from LCA->y = digit string from root->y - digit string from root->LCA.
        // This ends up removing the LCA digit...
        ll no_lca = (fwd[y] - (fwd[w] * pow10[lenDown]) % m + m) % m;  // add m so we dont go negative. (C++ keeps the sign of negative residues.)

        //... so we must add it back.
        ll down_walk = concat(digit[w], no_lca, lenDown);

        int down_len = 1 + lenDown; // modified length after adding LCA digit

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