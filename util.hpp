#pragma once
#include <bits/stdc++.h>
using namespace std;
template <class T> ostream &operator<<(ostream &o, const vector<T> &vec) {
  for (const auto &e : vec) {
    o << e << " ";
  }
  o << endl;
  return o;
}
template <class T, class K>
ostream &operator<<(ostream &o, const pair<T, K> &vec) {
  o << vec.first << " " << vec.second << " ";
  o << endl;
  return o;
}
