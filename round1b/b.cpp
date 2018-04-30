#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>
#include <set>
using namespace std;

pair<int, int> findWest(int lhs, int rhs, const vector<int> &M, const vector<int> &N) {
  int mid = (lhs+rhs)/2;
  int m = M[mid];
  for (int i=mid-1; i >= lhs; i--) {
    if (M[i] != m || i == lhs) {
      int n = N[i];
      while (i >= lhs && (N[i] == n || M[i] == m)) i--;
      for (int j=mid; j < rhs; j++) {
        if (m != M[j] && n != N[j]) return make_pair(i+1, j);
      }
      return make_pair(i+1, rhs);
    }
  }
  return make_pair(lhs, rhs);
}

pair<int, int> findEast(int lhs, int rhs, const vector<int> &M, const vector<int> &N) {
  int mid = (lhs+rhs)/2;
  int m = M[mid];
  for (int i=mid+1; i < rhs; i++) {
    if (M[i] != m || i == rhs-1) {
      int n = N[i];
      while (i < rhs && (N[i] == n || M[i] == m)) i++;
      for (int j=mid; j >= lhs; j--) {
        if (m != M[j] && n != N[j]) return make_pair(j+1, i);
      }
      return make_pair(lhs, i);
    }
  }
  return make_pair(lhs, rhs);
}

void maxPair(pair<int, int> cand, pair<int, set<int> > &res) {
  int len = cand.second-cand.first;
  if (res.first < len) res = make_pair(len, set<int>());
  if (res.first == len) res.second.insert(cand.first);
}

pair<int, set<int> > daq(int lhs, int rhs, const vector<int> &M, const vector<int> &N) {
  if (rhs-lhs <= 0) return make_pair(0, set<int>());
  int mid = (lhs+rhs)/2;
  auto res = daq(lhs, mid, M, N);
  auto rhsRes = daq(mid+1, rhs, M, N);
  if (rhsRes.first > res.first) res = rhsRes;
  else if (rhsRes.first == res.first) res.second.insert(rhsRes.second.begin(), rhsRes.second.end());
  auto tmp = make_pair(0, set<int>());
  maxPair(findWest(lhs, rhs, M, N), tmp);
  maxPair(findEast(lhs, rhs, M, N), tmp);
  maxPair(findWest(lhs, rhs, N, M), tmp);
  maxPair(findEast(lhs, rhs, N, M), tmp);
  if (tmp.first > res.first) res = make_pair(tmp.first, tmp.second);
  else if (tmp.first == res.first) res.second.insert(tmp.second.begin(), tmp.second.end());
  return res;
}

pair<int, set<int> > solve() {
  int S;
  cin >> S;
  vector<int> M(S);
  vector<int> N(S);
  for (int i=0; i < S; i++) {
    int D, A, B;
    cin >> D >> A >> B;
    M[i]= D+A;
    N[i]= D-B;
  }
  return daq(0, S, M, N);
}

int main() {
  int T;
  cin >> T;
  for (int tc=0; tc < T; tc++) {
    auto res = solve();
    printf("Case #%d: %d %d\n", tc+1, res.first, static_cast<int>(res.second.size()));
  }
  return 0;
}
