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
    int r, c;
    cin >> r >> c;
    cin.ignore();
    vector<vector<ll>> attacked(r, vector<ll>(c, 0));
    vector<vector<bool>> reachable(r, vector<bool>(c, 0));
    vector<vector<bool>> knights(r, vector<bool>(c, 0));
    vector<vector<bool>> seen(r, vector<bool>(c, 0));
    queue<pair<int,int>> q;

    
    auto unlock_squares = [&](int _r, int _c) {
        auto apply = [&](int y, int x) {
            if (!attacked[y][x] && !reachable[y][x]) {
                reachable[y][x] = true;
                q.push({y,x});
            }
            if (knights[y][x]) return true;
            return false;
        };
        for (int i=_r-1; i>=0; --i) if (apply(i,_c)) break;
        for (int i=_r+1; i<r; ++i)  if (apply(i,_c)) break;
        for (int j=_c-1; j>=0; --j) if (apply(_r,j)) break;
        for (int j=_c+1; j<c; ++j)  if (apply(_r,j)) break;

    };

    auto try_attach_if_connected = [&](int y, int x) {
        if (reachable[y][x]) return; 
    
        auto sees_reachable_in_dir = [&](int dy, int dx) {
            int ny=y+dy, nx=x+dx;
            while (0<=ny && ny<r && 0<=nx && nx<c) {
                if (knights[ny][nx]) return false;      
                if (reachable[ny][nx]) return true;     
                ny += dy; nx += dx;
            }
            return false;
        };
    
        if (sees_reachable_in_dir(-1,0) || sees_reachable_in_dir(1,0) ||
            sees_reachable_in_dir(0,-1) || sees_reachable_in_dir(0,1)) {
            unlock_squares(y, x);  
        }
    };
    auto attack_squares = [&](int i, int j, int increment) {
        vector<pair<int,int>> d = {{1,2}, {-1,2}, {2,1}, {-2,1}, {2,-1}, {-2,-1}, {1,-2}, {-1, -2}};

        for(auto& [x,y] : d) {
            if (i + y >= 0 && i + y < r && j + x >= 0 && j + x < c) {
                attacked[i + y][j + x] += increment;
                if (attacked[i + y][j + x] == 0) {
                    try_attach_if_connected(i + y, j + x);
                }
            }
        }
    };
   
    pair<int, int> start, target;
    rep(i, 0, r) {
        string s;
        getline(cin, s, '\n');
        rep(j, 0, c) {
            if (s[j] == '.') continue;
            if (s[j] == 'T') target = {i, j};
            if (s[j] == 'K') {
                attack_squares(i, j, 1);
                knights[i][j] = 1;
            }
            if (s[j] == 'R') {
                start = {i, j};
                reachable[i][j] = 1;
            }
        }
    }
    q.push(start);
    while (!q.empty()) {
        auto [r,c] = q.front(); q.pop();
        if (seen[r][c]) continue;
        seen[r][c] = 1;
        if (knights[r][c]) {
            attack_squares(r, c, -1);
            knights[r][c] = false;
        }
        unlock_squares(r, c);
    }
    auto [y, x] = target;
    bool target_reached = reachable[y][x];
    cout << (target_reached ? "yes" : "no") << "\n";
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