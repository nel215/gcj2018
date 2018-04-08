#include <iostream>
#include <vector>
#include <cmath>
#include <complex>
#include <algorithm>
using namespace std;
const double pi = acos(-1.0);

typedef complex<double> P2;

namespace std {
  bool operator < (const P2& a, const P2& b) {
    return arg(a) < arg(b);
  }
}

struct P3 {
  P3(double _x, double _y, double _z) {
    x = _x;
    y = _y;
    z = _z;
  }
  double x, y, z;
  void print() {
    cerr << x << "," << y << "," << z << endl;
  }
};

void rotX(vector<P3> &points, double theta) {
  for (auto &p : points) {
    double y = p.y * cos(theta) - p.z * sin(theta);
    double z = p.y * sin(theta) + p.z * cos(theta);
    p.y = y;
    p.z = z;
  }
}

void rotZ(vector<P3> &points, double theta) {
  for (auto &p : points) {
    double x = p.x * cos(theta) - p.y * sin(theta);
    double y = p.x * sin(theta) + p.y * cos(theta);
    p.x = x;
    p.y = y;
  }
}

double cross(const P2& a, const P2& b) {
  return imag(conj(a)*b);
}

double dot(const P2& a, const P2& b) {
  return real(conj(a)*b);
}

int ccw(P2 a, P2 b, P2 c) {
  b -= a; c -= a;
  if (cross(b, c) > 0)   return +1;       // counter clockwise
  if (cross(b, c) < 0)   return -1;       // clockwise
  if (dot(b, c) < 0)     return +2;       // c--a--b on line
  if (norm(b) < norm(c)) return -2;       // a--b--c on line
  return 0;
}

vector<P2> convexHull(vector<P2> ps) {
  int n = ps.size(), k = 0;
  sort(ps.begin(), ps.end());
  vector<P2> ch(2*n);
  for (int i = 0; i < n; ch[k++] = ps[i++]) // lower-hull
    while (k >= 2 && ccw(ch[k-2], ch[k-1], ps[i]) <= 0) --k;
  for (int i = n-2, t = k+1; i >= 0; ch[k++] = ps[i--]) // upper-hull
    while (k >= t && ccw(ch[k-2], ch[k-1], ps[i]) <= 0) --k;
  ch.resize(k-1);
  return ch;
}

double getArea(const vector<P3> &in) {
  const int n = in.size();
  vector<P2> points(n);
  for (int i=0; i < n; i++) {
    points[i] = P2(in[i].x, in[i].z);
  }
  points = convexHull(points);
  double area = 0;
  for (int i=0; i < n; i++) {
    const auto &next = points[(i+1)%n];
    area += cross(points[i], next);
  }
  return area/2.0;
}

vector<P3> getInitialPoints() {
  vector<P3> points;
  points.push_back(P3(0.5, 0.5, 0.5));
  points.push_back(P3(-0.5, 0.5, 0.5));
  points.push_back(P3(0.5, 0.5, -0.5));
  points.push_back(P3(-0.5, 0.5, -0.5));
  points.push_back(P3(0.5, -0.5, 0.5));
  points.push_back(P3(-0.5, -0.5, 0.5));
  points.push_back(P3(0.5, -0.5, -0.5));
  points.push_back(P3(-0.5, -0.5, -0.5));
  return points;
}

vector<P3> solve() {
  double A;
  cin >> A;
  vector<P3> res;
  res.push_back(P3(0.5, 0, 0));
  res.push_back(P3(0, 0.5, 0));
  res.push_back(P3(0, 0, 0.5));
  if (A <= sqrt(2)) {
    double lb = 1e-12, ub = pi/4.0;
    for (int _=0; _ < 100; _++) {
      auto points = getInitialPoints();
      double m = (lb + ub) / 2.0;
      rotZ(points, m);
      if (getArea(points) < A) {
        lb = m;
      } else {
        ub = m;
      }
    }
    rotZ(res, lb);
    return res;
  } else {
    auto initial = getInitialPoints();
    rotZ(initial, pi/4.0);
    double lb = 1e-12, ub = 353.0/1800*pi;
    for (int _=0; _ < 100; _++) {
      auto points = initial;
      double m = (lb + ub) / 2.0;
      rotX(points, m);
      if (getArea(points) < A) {
        lb = m;
      } else {
        ub = m;
      }
    }
    rotZ(res, pi/4.0);
    rotX(res, lb);
    return res;
  }
}

int main() {
  int T;
  cin >> T;
  for (int tc=0; tc < T; tc++) {
    auto points = solve();
    printf("Case #%d:\n", tc+1);
    for (int i=0; i < 3; i++) {
      printf("%.9f %.9f %.9f\n", points[i].x, points[i].y, points[i].z);
    }
  }
}
