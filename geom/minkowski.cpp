#include <bits/stdc++.h>

#if (_WIN32 || __WIN32__)
#  define LLD "%I64d"
#else
#  define LLD "%lld"
#endif

using std::istream; using std::ostream; using std::fixed; using std::greater;
using std::tuple; using std::tie; using std::make_pair; using std::multiset;
using std::nth_element; using std::min_element; using std::max_element;
using std::vector; using std::set; using std::map; using std::string;
using std::fill; using std::copy; using std::sort; using std::unique;
using std::unordered_set; using std::unordered_map; using std::pair;
using std::next_permutation; using std::reverse; using std::rotate;
using std::cin; using std::cout; using std::cerr; using std::endl;
using std::lower_bound; using std::upper_bound; using std::deque;
using std::min; using std::max; using std::swap; using std::abs;
using std::priority_queue; using std::queue; using std::bitset;
using std::make_tuple;

typedef long long ll;
typedef long double ld;

int const INF = (int) 1e9;
ll const INFL = (ll) 1e18;
ld const PI = 3.1415926535897932384626433832795028;

struct Point {
	ll x, y;
	
	Point() {}
	
	Point(ll x, ll y) :
		x(x), y(y) {}
		
	Point& operator*=(ll coef) {
		x *= coef;
		y *= coef;
		return *this;
	}
	
	Point& operator+=(Point const& a) {
		x += a.x;
		y += a.y;
		return *this;
	}
	
	Point& operator-=(Point const& a) {
		x -= a.x;
		y -= a.y;
		return *this;
	}
};

Point const ORIGIN = Point(0, 0);

Point operator+(Point a, Point const& b) {
	return a += b;
}

Point operator-(Point a, Point const& b) {
	return a -= b;
}

bool operator<(Point const& a, Point const& b) {
	return a.x < b.x || (a.x == b.x && a.y < b.y);
}

bool operator==(Point const& a, Point const& b) {
	return a.x == b.x && a.y == b.y;
}

int turn(Point const& a, Point const& b, Point const& c) {
	ll cross = (b.x - a.x) * (c.y - b.y) - (b.y - a.y) * (c.x - b.x);
	return cross > 0 ? 1 : cross < 0 ? -1 : 0;
}

ll dist2(Point const& a, Point const& b) {
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

ld dist(Point const& a, Point const& b) {
	return sqrtl((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

typedef vector<Point> polygon;

polygon readPolygon() {
	int n;
	scanf("%d", &n);
	polygon ret(n);
	for (int i = 0; i < n; ++i) {
		int x, y;
		scanf("%d%d", &x, &y);
		ret[i] = Point(x, y);
	}
	return ret;
}

polygon negate(polygon p) {
	for (auto& pt : p) {
		pt *= -1;
	}
	return p;
}

vector<Point> vectors(polygon const& a) {
	vector<Point> ret(a.size());
	for (int i = 0; i < (int)a.size(); ++i) {
		int j = (i + 1) % a.size();
		ret[i] = a[j] - a[i];
	}
	return ret;
}

bool compVectors(Point const& a, Point const& b) {
	int t = turn(ORIGIN, a, b);
	if (t != 0) {
		return t > 0;
	}
	return a < b;
}

polygon minkowski(polygon a, polygon b) {

	rotate(a.begin(), min_element(a.begin(), a.end()), a.end());
	rotate(b.begin(), min_element(b.begin(), b.end()), b.end());

	auto avs = vectors(a);
	auto bvs = vectors(b);
	
	vector<Point> vs(avs.size() + bvs.size());
	
	merge(avs.begin(), avs.end(), bvs.begin(), bvs.end(), vs.begin(), compVectors);
	
	polygon ret;
	ret.push_back(a[0] + b[0]);
	for (auto v : vs) {
		ret.push_back(ret.back() + v);
	}
	ret.pop_back();
	
	return ret;
}

ld distToLine(Point const& p, Point const& a, Point const& b) {
	ll A = a.y - b.y;
	ll B = b.x - a.x;
	ll C = -A * a.x - B * a.y;
	return (ld) abs(A * p.x + B * p.y + C) / sqrtl(A * A + B * B);
}

ll scalar(Point const& a, Point const& b) {
	return a.x * b.x + a.y * b.y;
}

ld distToSegment(Point const& p, Point const& a, Point const& b) {
	if (scalar(p - a, b - a) <= 0) {
		return dist(a, p);
	} else if (scalar(p - b, a - b) <= 0) {
		return dist(b, p);
	}
	return distToLine(p, a, b);
}

void solve() {
	
	auto p1 = readPolygon();
	auto p2 = negate(readPolygon());
	
	if (p1.size() >= 3U && turn(p1[0], p1[1], p1[2]) < 0) {
		reverse(p1.begin() + 1, p1.end());
	}
	
	if (p2.size() >= 3U && turn(p2[0], p2[1], p2[2]) < 0) {
		reverse(p2.begin() + 1, p2.end());
	}
	
	auto p3 = minkowski(p1, p2);
	
	ld ans = INFL;
	
	int n = p3.size();
	for (int i = 0; i < n; ++i) {
		int j = (i + 1) % n;
		ans = min(ans, distToSegment(ORIGIN, p3[i], p3[j]));
	}
	
	cout << (double) ans << endl;
	
}



int main() {

	cout.precision(15);
	cout << fixed;
	cerr.precision(6);
	cerr << fixed;
	
	srand(1510);

	solve();

#ifdef LOCAL
	cerr << "time: " << clock() << " ms" << endl;
#endif
}