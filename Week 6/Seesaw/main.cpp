#include <bits/stdc++.h>
using namespace std;

struct Item {
  long double avg;
  int id, ver;
};
struct Cmp {
  bool operator()(const Item &a, const Item &b) const { return a.avg < b.avg; }
};

void solve() {
  int n;
  cin >> n;
  vector<long double> p(n), w(n);
  vector<int> C(n, 1), L(n), R(n), ver(n, 0);
  priority_queue<Item, vector<Item>, Cmp> pq;
  for (int i = 0; i < n; ++i) {
    cin >> p[i] >> w[i];
    pq.push({w[i], i, 0});
    L[i] = i - 1;
    R[i] = i + 1;
  }
  R[n - 1] = -1;

  long double eps = 1e-12L;
  long double T = 0.0L, ans = 0.0L;
  for (int i = 0; i < n; ++i)
    T += p[i] * w[i];

  auto push_id = [&](int i) { pq.push({w[i] / C[i], i, ++ver[i]}); };

  auto merge = [&](int i, int j) {
    w[i] += w[j];
    C[i] += C[j];
    ++ver[i];
    ++ver[j];
    int Lj = L[j], Rj = R[j];
    if (Lj == i) {
      R[i] = Rj;
      if (Rj != -1)
        L[Rj] = i;
    } else if (Rj == i) {
      L[i] = Lj;
      if (Lj != -1)
        R[Lj] = i;
    }
    push_id(i);
  };

  while (fabsl(T) > eps) {
    int dir = (T > 0 ? -1 : 1);
    int i = -1;
    while (!pq.empty()) {
      auto x = pq.top();
      pq.pop();
      if (x.ver != ver[x.id])
        continue;
      i = x.id;
      break;
    }
    if (i == -1)
      break;
    int j = (dir == -1 ? L[i] : R[i]);
    long double cap = (j == -1 ? numeric_limits<long double>::infinity()
                               : fabsl(p[j] - p[i]));
    long double need = fabsl(T) / w[i];
    long double d = min(need, cap);

    p[i] += dir * d;
    T += dir * w[i] * d;
    ans += (long double)C[i] * d;

    if (d + 1e-18L >= cap && j != -1) {
      p[i] = p[j];
      merge(i, j);
    } else
      push_id(i);
  }

  cout << fixed << setprecision(10) << ans << "\n";
}
