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
using std::make_tuple; using std::iota;

typedef long long ll;
typedef long double ld;

ll rnd(ll x, ll y) { static auto gen = std::bind(std::uniform_int_distribution<ll>(), std::mt19937(1510)); return gen() % (y - x + 1) + x; }
ll gcd(ll a, ll b) { while (b > 0) { ll t = a % b; a = b; b = t; } return a; }

int const INF = 100 + (int) 1e9;
ll const INFL = 100 + (ll) 1e18;
ld const PI = 3.1415926535897932384626433832795028;
ld const EPS = 1e-6;

struct point_t {
	ld x, y;
	
	point_t() {}
	
	point_t(ld x, ld y)
		: x(x), y(y) {}
	
	point_t& operator-=(point_t const& a) {
		x -= a.x;
		y -= a.y;
		return *this;
	}
	
	point_t& operator+=(point_t const& a) {
		x += a.x;
		y += a.y;
		return *this;
	}
	
	point_t& operator*=(ld coef) {
		x *= coef;
		y *= coef;
		return *this;
	}
};

point_t const ORIGIN(0, 0);

point_t operator-(point_t a, point_t const& b) {
	return a -= b;
}

point_t operator+(point_t a, point_t const& b) {
	return a += b;
}

point_t operator*(point_t a, ld coef) {
	return a *= coef;
}

bool equals(ld a, ld b) {
	return a < b + EPS && b < a + EPS;
}

bool operator<(point_t const& a, point_t const& b) {
	return a.x + EPS < b.x || (equals(a.x, b.x) && a.y + EPS < b.y);
}

int turn(point_t const& a, point_t const& b, point_t const& c) {
	ll cross = (b.x - a.x) * (c.y - b.y) - (b.y - a.y) * (c.x - b.x);
	return cross > EPS ? 1 : cross + EPS < 0 ? -1 : 0;
}

ld dist2(point_t const& a, point_t const& b) {
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

ld dist(point_t const& a, point_t const& b) {
	return sqrtl((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

ld dot_prod(point_t const& a, point_t const& b) {
	return a.x * b.x + a.y  * b.y;
}

struct line_t {
	ld A, B, C;
	
	line_t() {}
	
	line_t(point_t const& a, point_t const& b) {
		A = a.y - b.y;
		B = b.x - a.x;
		C = -A * a.x - B * a.y;
	}
};

point_t intersect(line_t const& l1, line_t const& l2) {
	/// l1.A * x + l1.B * y = -l1.C
	/// l2.A * x + l2.B * y = -l2.C
	ld x = (-l1.C * l2.B + l2.C * l1.B) / (l1.A * l2.B - l2.A * l1.B);
	ld y = (-l1.C * l2.A + l2.C * l1.A) / (l1.B * l2.A - l2.B * l1.A);
	return point_t(x, y);
}

line_t mid_perp(point_t const& a, point_t const& b) {
	point_t mid = (a + b) * 0.5;
	point_t ab = a - b;
	point_t perp(ab.y, -ab.x);
	return line_t(mid, mid + perp);
}

struct circle_t {
	point_t c;
	ld rad;
	
	circle_t() {}

	circle_t(point_t const& a) {
		c = a;
		rad = 0;
	}
	
	circle_t(point_t const& a, point_t const& b) {
		c = (a + b) * 0.5;
		rad = dist(a, c);
	} 
	
	circle_t(point_t const& p, point_t const& q, point_t const& r) {
		if (dot_prod(p - q, r - q) < EPS) {
			c = (p + r) * 0.5;
			rad = dist(c, p);
		} else if (dot_prod(p - r, q - r) < EPS) {
			c = (p + q) * 0.5;
			rad = dist(c, p);
		} else if (dot_prod(q - p, r - p) < EPS) {
			c = (q + r) * 0.5;
			rad = dist(c, q);
		} else {
			c = intersect(mid_perp(p, q), mid_perp(q, r));
			rad = dist(c, p);
		}
	}
};

bool inside(point_t const& a, circle_t const& cir) {
	return dist2(a, cir.c) < cir.rad * cir.rad + EPS;
}

circle_t min_disk(vector<point_t> points) {
	if (points.size() == 1U) {
		return circle_t(points[0]);
	}
	if (points.size() == 2U) {
		return circle_t(points[0], points[1]);
	}
	static std::mt19937 gen(960172);
	std::shuffle(points.begin(), points.end(), gen);
	std::list<point_t> a(points.begin(), points.end());
	circle_t ans(points[0], points[1], points[2]);
	vector<point_t> b(4);
	for (auto i = std::next(a.begin(), 3); i != a.end();) {
		if (!inside(*i, ans)) {
			a.splice(a.end(), a, std::next(a.begin(), 3), i);
			copy(a.begin(), std::next(a.begin(), 4), b.begin());
			do {
				rotate(b.begin(), b.begin() + 1, b.end());
				ans = circle_t(b[0], b[1], b[2]);
			} while (!inside(b[3], ans));
			copy(b.begin(), b.end(), a.begin());
			i = std::next(a.begin(), 4);
		} else {
			++i;
		}
	}	
	return ans;
}

void solve() {
	int n;
	scanf("%d", &n);
	vector<point_t> points(n);
	for (int i = 0; i < n; ++i) {
		int x, y;
		scanf("%d%d", &x, &y);
		points[i] = point_t(x, y);
	}
	auto ans = min_disk(points);
	printf("%.12f\n", (double) ans.rad);
	printf("%.12f %.12f\n", (double) ans.c.x, (double) ans.c.y);
}



int main() {

	cout.precision(15);
	cout << fixed;
	cerr.precision(6);
	cerr << fixed;
	
	solve();

#ifdef LOCAL
	cerr << "time: " << (ll) clock() * 1000 / CLOCKS_PER_SEC << " ms" << endl;
#endif
}