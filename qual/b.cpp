#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int solve() {
  int N;
  cin >> N;

  vector<int> V[2];
  for (int i=0; i < N; i++) {
    int v;
    cin >> v;
    V[i%2].push_back(v);
  }
  sort(V[0].begin(), V[0].end());
  sort(V[1].begin(), V[1].end());
  vector<int> U(N);
  for (size_t i=0; i < V[0].size(); i++) {
    U[2*i+0] = V[0][i];
  }
  for (size_t i=0; i < V[1].size(); i++) {
    U[2*i+1] = V[1][i];
  }
  for (int i=0; i < N-1; i++) {
    if (U[i] > U[i+1]) {
      return i;
    }
  }
  return -1;
}

int main() {
  int T;
  cin >> T;
  for (int tc=0; tc < T; tc++) {
    int res = solve();
    cout << "Case #" << tc+1 << ": ";
    if (res == -1) {
      cout << "OK";
    } else {
      cout << res;
    }
    cout << endl;
  }
}
