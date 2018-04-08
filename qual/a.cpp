#include <iostream>
#include <string>
using namespace std;

int getDamage(const string &P) {
  int res = 0;
  int d = 1;
  for (size_t i=0; i < P.size(); i++) {
    if (P[i] == 'C') d *= 2;
    if (P[i] == 'S') res += d;
  }
  return res;
}

bool decrease(string &P) {
  for (size_t i=P.size()-1; i > 0 ; i--) {
    if (P[i-1] == 'C' && P[i] == 'S') {
      swap(P[i-1], P[i]);
      return true;
    }
  }
  return false;
}

int main() {
  int T;
  cin >> T;
  for (int tc=0; tc < T; tc++) {
    int D;
    string P;
    cin >> D >> P;
    int res = 0;
    while (res >= 0 && D < getDamage(P)) {
      if (!decrease(P)) {
        res = -1;
      } else {
        res++;
      }
    }
    cout << "Case #" << tc+1 << ": ";
    if (res == -1) {
      cout << "IMPOSSIBLE";
    } else {
      cout << res;
    }
    cout << endl;
  }
  return 0;
}
