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
struct coord {
    long double x, y, z; 
    static coord zero() {return {0,0,0};}
    friend coord operator /(const coord& rhs, long double n) {return {rhs.x / n, rhs.y / n, rhs.z / n};}
    friend void operator +=(coord& lhs, const coord &rhs) {lhs.x += rhs.x; lhs.y += rhs.y; lhs.z += rhs.z;}
    friend coord operator +(const coord& lhs, const coord& rhs) {return {rhs.x + lhs.x,rhs.y + lhs.y, rhs.z + lhs.z};}
    friend ostream& operator <<(ostream& o, const coord& c) {
        o << "(" << c.x << " " << c.y << " " << c.z << ")";
        return o;
    }
    coord mask(int axis) const noexcept{
        switch (axis) {
        case 0:
            return {0,y,z};
        case 1:
            return {x,0,z};
        case 2:
            return {x,y,0};
        default:
            break;
        }
        return {x,y,z};
    }
};

void solve() {
   int n;
   cin >> n;
   vector<coord> flecks(n);
   rep(i, 0, n) {
    cin >> flecks[i].x >> flecks[i].y >> flecks[i].z;
   }

   auto s_dist = [&](const coord& from, const coord& to) -> long double {long double dx = to.x-from.x, dy = to.y-from.y, dz = to.z-from.z; return dx*dx + dy*dy + dz*dz;};
   auto farthest = [&s_dist](const coord& to, const vector<coord>& flecks) -> coord {return *max_element(flecks.begin(), flecks.end(), [&](const coord& a, const coord& b){return s_dist(to, a) < s_dist(to, b);});};
   long double ans = numeric_limits<long double>::infinity();
   vector<coord> masked_flecks(n);
   rep(i, 0, 3) {
        transform(flecks.begin(), flecks.end(), masked_flecks.begin(), [&](const coord& x){return x.mask(i);});
        long double best = 0;
        for(auto &x : flecks) best = max(best, s_dist(x.mask(i),farthest(x.mask(i), masked_flecks)));
        ans = min(ans,best);
        cout << best << "\n";
        cout << ans << "\n";
   }
   cout << "==\n";
   cout << sqrt(ans) << "\n";
   // THIS DOESNT WORK! USE Minimum Enclosing Circle Instead.
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    // OPTIONAL FOR SOME CONTESTS
    //cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}