#include <iostream>
#include <vector>
using namespace std;

void solve() {
  int A;
  cin >> A;
  int w = 1;
  while (w*w < A) {
    w++;
  }
  vector<vector<int> > prepared(w, vector<int>(w, 0));
  while (true) {
    auto best_yx = make_pair(1, 1);
    int best_cnt = 9;
    for (int y=1; y < w-1; y++) {
      for (int x=1; x < w-1; x++) {
        int prepared_cnt = 0;
        for (int dy=-1; dy <= 1; dy++) {
          for (int dx=-1; dx <= 1; dx++) {
            prepared_cnt += prepared[y+dy][x+dx];
          }
        }
        if (prepared_cnt < best_cnt) {
          best_cnt = prepared_cnt;
          best_yx = make_pair(y, x);
        }
      }
    }
    cout << best_yx.first+1 << " " << best_yx.second+1 << endl;
    int res_y, res_x;
    cin >> res_y >> res_x;
    if (res_y == 0 && res_x == 0) {
      return;
    } else {
      prepared[res_y-1][res_x-1] = 1;
    }
  }
}

int main() {
  int T;
  cin >> T;
  for (int tc=0; tc < T; tc++) {
    solve();
  }
}

