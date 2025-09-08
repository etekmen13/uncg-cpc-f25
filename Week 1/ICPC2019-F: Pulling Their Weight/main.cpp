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
    Objective: Find smallest t that splits the set equally by sum.

    Note: Some weights W will be == t. If |W| is even, split W evenly.
    else, remove one and then split W evenly.
    
    Note: There will *always* exist a t that works.
    Example:
    1 2 3 6. t = 4 -> {1,2,3} = {6}
    3 8 10 11. t = 10 -> {3, 8} = {11} (10 is discarded)

    Idea: Compute prefix sum forwards and compare to suffix sum.

    3  8  9 11
    Total: 31
    3 11 |20 31
    29 20 11 0
    
    0  3  11 20
    29 20 11  0

    Case 1: t is not in the set (prefix == suffix). return t + 1
    Case 2: t is in the set even # times (prefix == suffix). return t.
        - Check input bounds. smallest case is {1,1}. We can safely check if v[i] == v[i+1] to determine if we are in this case.
    Case 3: t is in the set odd # times (prefix < suffix). return t.
    */
   int m;
   cin >> m;
   vector<int> vec(m);
   rep(i, 0, m) {
    cin >> vec[i];
   }
   sort(vec.begin(), vec.end());
   ll total = accumulate(vec.begin(), vec.end(), 0LL);
   ll sum = 0;
   rep(i, 0, m) {
    if (sum + vec[i] == total - sum - vec[i]) {

        cout << vec[i] + (vec[i] != vec[i+1]) << "\n";
        return;
    }
    if (sum + vec[i] > total - sum - vec[i]) {
        cout << vec[i] << "\n";
        return;
    }
    sum += vec[i];
   }
}
#pragma endregion
void solve() {
   
}

// Problem Link:
// https://open.kattis.com/problems/pullingtheirweight

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