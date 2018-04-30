#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

int solve() {
  int N, L;
  cin >> N >> L;
  int rem = N;
  int res = 0;
  vector<int> ok(N+1, 0);
  for (int c=1; c <= N; c++) {
    int a = 100*c/N;
    int b = 200*c-2*N*a;
    if (b == 0 || b >= N) ok[c] = 1;
  }
  vector<int> cost(N, 0);
  int prev = N;
  for (int c=N-1; c >= 0; c--) {
    if (ok[c]) {
      cost[c] = 0;
      prev = c;
    } else {
      cost[c] = prev - c;
    }
  }
  vector<pair<int, int> > need(N, make_pair(cost[0], 0));
  for (int i=0; i < L; i++) {
    int C;
    cin >> C;
    rem -= C;
    need[i] = make_pair(cost[C], C);
  }
  sort(need.begin(), need.end());
  for (int i=0; i < need.size(); i++) {
    if (rem >= need[i].first) {
      int c = need[i].second+need[i].first;
      int a = 100*c/N;
      int b = 200*c-2*N*a;
      res += a;
      if (b >= N) res++;
      rem -= need[i].first;
    } else if (rem > 0 || need[i].second > 0) {
      int c = need[i].second+rem;
      int a = 100*c/N;
      int b = 200*c-2*N*a;
      res += a;
      if (b >= N) res++;
      rem = 0;
    }
  }
  return res;
}

int main() {
  int T;
  cin >> T;
  for (int tc=0; tc < T; tc++) {
    int res = solve();
    printf("Case #%d: %d\n", tc+1, res);
  }
  return 0;
}
