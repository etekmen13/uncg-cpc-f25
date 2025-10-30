#include <algorithm>
#include <vector>

#include "util.hpp"
#define REP(i, a, b) for (int i = a; i <= b; i++)
#define rep(i, a, b) for (int i = a; i < b; i++)
#define PER(i, a, b) for (int i = a; i >= b; i--)
#define per(i, a, b) for (int i = a; i > b; i--)

using namespace std;

#pragma region Geometry
struct Coord {
  int x, y;
  friend Coord operator-(const Coord& a, const Coord& b) {
    return {a.x - b.x, a.y - b.y};
  }
};

ostream& operator<<(ostream& o, const Coord& a) {
  o << "[" << a.x << " " << a.y << "]";
  return o;
}

vector<Coord> ConvexHull_Grahams(vector<Coord> points) {
  auto s_dist = [](const Coord& a) { return a.x * a.x + a.y * a.y; };
  auto cross = [](const Coord& p, const Coord& q) {
    return p.x * q.y - p.y * q.x;
  };
  auto orientation = [&cross](const Coord& a, const Coord& b, const Coord& c) {
    int v = cross(b - a, c - b);
    if (v > 0) return 1;   // ccw
    if (v < 0) return -1;  // cw
    return 0;              // collinear
  };
  Coord p0 = *min_element(points.begin(), points.end(),
                          [](const Coord& a, const Coord& b) {
                            return a.y == b.y ? a.x < b.x : a.y < b.y;
                          });
  sort(points.begin(), points.end(),
       [&p0, &orientation, &s_dist](const Coord& a, const Coord& b) {
         int o = orientation(p0, a, b);
         return o == 0 ? s_dist(a - p0) < s_dist(b - p0) : o < 0;
       });
  vector<Coord> convex_hull;

  rep(i, 0, points.size()) {
    auto curr = points[i];
    while (convex_hull.size() > 1 &&
           orientation(convex_hull[convex_hull.size() - 2], convex_hull.back(),
                       curr) >= 0) {
      convex_hull.pop_back();
    }
    convex_hull.push_back(curr);
  }
  return convex_hull;
}

vector<Coord> MinEnclosingCircle(vector<Coord> points) { return {}; }
#pragma endregion

#pragma region Backtracking

void m_color(const vector<vector<int>>& adj, int m, bool heuristic,
             bool debug) {
  int n = adj.size();
  vector<int> color(n, 0);
  // Heuristic: color higher-degree vertices first
  vector<int> order(n);
  iota(order.begin(), order.end(), 0);
  sort(order.begin(), order.end(),
       [&](int a, int b) { return adj[a].size() > adj[b].size(); });
  auto safe = [&](int u, int c) {
    for (auto v : adj[u])
      if (color[v] == c) return false;
    return true;
  };

  function<bool(int)> paint = [&](int idx) -> bool {
    if (idx == n) return true;
    int u = heuristic ? order[idx] : idx;
    REP(c, 1, m) {
      if (!safe(u, c)) continue;
      color[u] = c;
      if (paint(idx + 1)) return true;
      color[u] = 0;
    }
    return false;
  };
  if (!paint(0)) {
    cout << "failed to " << m << "-color the graph\n";
    return;
  }
  if (!debug) return;
  rep(i, 0, n) {
    cout << i << ": " << color[i] << "\n";
    for (auto j : adj[i]) {
      cout << "\t" << j << " : " << color[j] << "\n";
    }
  }
}

#pragma endregion.
int main() {
  //   vector<Coord> points = {{0, 0}, {3, 0}, {3, 3}, {0, 3}, {1, 1}, {2, 2},
  //                           {2, 0}, {0, 2}, {1, 0}, {0, 1}, {3, 1}, {3, 2},
  //                           {2, 3}, {1, 3}, {2, 1}, {1, 2}};
  //     auto convex_hull = ConvexHull_Grahams(points);
  //     for (auto c : convex_hull)
  //         cout << c << "\n";
  vector<vector<int>> graph1 = {
      {1, 4},  // 0
      {0, 2},  // 1
      {1, 3},  // 2
      {2, 4},  // 3
      {3, 0}   // 4
  };
//   m_color(graph1, 3, false, true);
//   return 0;  // remove
  vector<vector<int>> graph2 = {
      /*  0 */ {1, 2, 36},
      /*  1 */ {0, 2, 37},
      /*  2 */ {0, 1, 5, 35},

      /*  3 */ {4, 5, 36},
      /*  4 */ {3, 5, 37},
      /*  5 */ {3, 4, 2, 8},

      /*  6 */ {7, 8, 36},
      /*  7 */ {6, 8, 37},
      /*  8 */ {6, 7, 5, 11},

      /*  9 */ {10, 11, 36},
      /* 10 */ {9, 11, 37},
      /* 11 */ {9, 10, 8, 14},

      /* 12 */ {13, 14, 36},
      /* 13 */ {12, 14, 37},
      /* 14 */ {12, 13, 11, 17},

      /* 15 */ {16, 17, 36},
      /* 16 */ {15, 17, 37},
      /* 17 */ {15, 16, 14, 20},

      /* 18 */ {19, 20, 36},
      /* 19 */ {18, 20, 37},
      /* 20 */ {18, 19, 17, 23},

      /* 21 */ {22, 23, 36},
      /* 22 */ {21, 23, 37},
      /* 23 */ {21, 22, 20, 26},

      /* 24 */ {25, 26, 36},
      /* 25 */ {24, 26, 37},
      /* 26 */ {24, 25, 23, 29},

      /* 27 */ {28, 29, 36},
      /* 28 */ {27, 29, 37},
      /* 29 */ {27, 28, 26, 32},

      /* 30 */ {31, 32, 36},
      /* 31 */ {30, 32, 37},
      /* 32 */ {30, 31, 29, 35},

      /* 33 */ {34, 35, 36},
      /* 34 */ {33, 35, 37},
      /* 35 */ {33, 34, 32, 2},

      /* 36 */ {0, 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 37},
      /* 37 */ {1, 4, 7, 10, 13, 16, 19, 22, 25, 28, 31, 34, 36}};

  auto start = chrono::high_resolution_clock::now();
  m_color(graph2, 3, false, false);
  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
  cout << "Without Heuristic: " << duration.count() / 1e6 << "s\n";
  start = chrono::high_resolution_clock::now();
  m_color(graph2, 3, true, false);
  end = chrono::high_resolution_clock::now();
  duration = chrono::duration_cast<chrono::microseconds>(end - start);
  cout << "With Heuristic: " << duration.count() / 1e6 << "s\n";
  return 0;
}
