#include <algorithm>
#include <vector>

#include "util.hpp"
#define REP(i, a, b) for (int i = a; i <= b; i++)
#define rep(i, a, b) for (int i = a; i < b; i++)
#define PER(i, a, b) for (int i = a; i >= b; i--)
#define per(i, a, b) for (int i = a; i > b; i--)

using namespace std;

#pragma region ConvexHull
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


vector<Coord> MinEnclosingCircle(vector<Coord> points) {
    
}
int main() {
  vector<Coord> points = {{0, 0}, {3, 0}, {3, 3}, {0, 3}, {1, 1}, {2, 2},
                          {2, 0}, {0, 2}, {1, 0}, {0, 1}, {3, 1}, {3, 2},
                          {2, 3}, {1, 3}, {2, 1}, {1, 2}};
    auto convex_hull = ConvexHull_Grahams(points);
    for (auto c : convex_hull) 
        cout << c << "\n";

    
  return 0;
}
