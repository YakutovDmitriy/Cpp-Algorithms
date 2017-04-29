#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
double const eps = 1e-8;
ll const INFL = 1e18 + 100;

bool eq(double a, double b) {
  return a < b + eps && b < a + eps;
}

struct Point {
  double x, y;
  Point() : x(0), y(0) {}
  Point(double x, double y) : x(x), y(y) {}
};

bool operator<(Point const &a, Point const &b) {
  return a.x < b.x || (eq(a.x, b.x) && a.y < b.y);
}

bool operator==(Point const &a, Point const &b) {
  return eq(a.x, b.x) && eq(a.y, b.y);
}

Point trans(Point const &a) {
  return Point(a.y, a.x);
}

double dist(Point const &a, Point const &b) {
  return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double cpp(vector<Point> a) {
  sort(a.begin(), a.end());
  int n = a.size();
  multiset<Point> s;
  double res = INFL;
  for (int j = 0, i = 0; i < n; ++i) {
    while (j < i && a[j].x + res < a[i].x)
      s.erase(s.find(trans(a[j++])));
    auto it = s.lower_bound(Point(a[i].y - res, -INFL));
    while (it != s.end() && it->x < a[i].y + res)
      res = min(res, dist(a[i], trans(*it++)));
    s.insert(trans(a[i]));
  }
  return res;
}

int rnd(int x, int y) {
  static mt19937 tw(960172);
  static uniform_int_distribution<int> di;
  return di(tw) % (y - x + 1) + x;
}

double stupid_cpp(vector<Point> const &p) {
  double res = INFL;
  for (int i = 0; i < (int)p.size(); ++i) {
    for (int j = 0; j < i; ++j) {
      res = min(res, dist(p[i], p[j]));
    }
  }
  return res;
}

int main() {
  {
    int its = 1000;
    for (int it = 1; it <= its; ++it) {
      int n = rnd(2, 300000);
      vector<Point> points(n);
      for (Point &p : points) {
        p.x = rnd(-300, 300);
        p.y = rnd(-300, 300);
      }
      double result = cpp(points);
      double actual = result;//stupid_cpp(points);
      if (abs(result - actual) > eps) {
        cerr << "ops " << it << '\n';
        cout << n << '\n';
        for (Point p : points)
          cout << p.x << ' ' << p.y << '\n';
        cout << setprecision((int)round(-log10(eps))) << fixed;
        cout << "result: " << result << '\n';
        cout << "actual: " << actual << '\n';
        break;
      }
      if (it % (its / 100) == 0)
        cerr << "ok " << it << " its\n";
    }
  }
}
