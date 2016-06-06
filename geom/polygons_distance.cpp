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

struct point_t {
	ll x, y;
	
	point_t() {}
	
	point_t(ll x, ll y)
		: x(x)
		, y(y)
	{}
	
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
	
	point_t& operator*=(ll coef) {
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

bool operator<(point_t const& a, point_t const& b) {
	return a.x < b.x || (a.x == b.x && a.y < b.y);
}

ll dot_prod(point_t const& a, point_t const& b) {
	return a.x * b.x + a.y * b.y;
}

ll cross_prod(point_t const& a, point_t const& b) {
	return a.x * b.y - a.y * b.x;
}

int turn(point_t const& a, point_t const& b, point_t const& c) {
	ll cross = (b.x - a.x) * (c.y - b.y) - (b.y - a.y) * (c.x - b.x);
	return cross > 0 ? 1 : cross < 0 ? -1 : 0;
}

ll dist2(point_t const& a, point_t const& b) {
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

ld dist(point_t const& p, point_t const& a, point_t const& b) {
	if (dot_prod(p - a, b - a) <= 0) {
		return sqrtl(dist2(p, a));
	}
	if (dot_prod(p - b, a - b) <= 0) {
		return sqrtl(dist2(p, b));
	}
	ll A = a.y - b.y;
	ll B = b.x - a.x;
	ll C = -A * b.x - B * b.y;
	return abs<ld>(A * p.x + B * p.y + C) / sqrtl(A * A + B * B);
}

typedef vector<point_t> polygon_t;

polygon_t minkowski_add(polygon_t a, polygon_t b) {
	static auto to_vectors = [](polygon_t const& p) {
		polygon_t ret(p.size());
		for (int i = 0; i < (int)p.size(); ++i) {
			int j = (i + 1) % p.size();
			ret[i] = p[j] - p[i];
		}
		return ret;
	};
	rotate(a.begin(), min_element(a.begin(), a.end()), a.end());
	rotate(b.begin(), min_element(b.begin(), b.end()), b.end());
	auto a_vectors = to_vectors(a);
	auto b_vectors = to_vectors(b);
	polygon_t sum_vectors(a_vectors.size() + b_vectors.size());
	merge(a_vectors.begin(), a_vectors.end(),
			b_vectors.begin(), b_vectors.end(), 
			sum_vectors.begin(), [](point_t const& a, point_t const& b) {
		return cross_prod(a, b) > 0;
	});
	polygon_t ret;
	ret.push_back(a[0] + b[0]);
	for (auto vec : sum_vectors) {
		ret.push_back(ret.back() + vec);
	}
	ret.pop_back();
	return ret;
}

ld dist(polygon_t a, polygon_t b) {
	for (auto& p : a) {
		p *= -1;
	}
	if (turn(a[0], a[1], a[2]) < 0) {
		reverse(a.begin(), a.end());
	}
	if (turn(b[0], b[1], b[2]) < 0) {
		reverse(b.begin(), b.end());
	}
	a = minkowski_add(a, b);
	ll sum_area = 0;
	ll real_area = 0;
	for (int i = 0; i < (int)a.size(); ++i) {
		int j = (i + 1) % a.size();
		ll triangle = cross_prod(a[i], a[j]);
		sum_area += abs<ll>(triangle);
		real_area += triangle;
	}
	real_area = abs<ll>(real_area);
	if (sum_area == real_area) {
		return 0;
	}
	ld ret = INFL;
	for (int i = 0; i < (int)a.size(); ++i) {
		int j = (i + 1) % a.size();
		ld to_segment = dist(ORIGIN, a[i], a[j]);
		ret = min<ld>(ret, to_segment);
	}
	return ret;
}

polygon_t read_polygon() {
	int vertices;
	scanf("%d", &vertices);
	polygon_t ret(vertices);
	for (int i = 0; i < vertices; ++i) {
		int x, y;
		scanf("%d%d", &x, &y);
		ret[i] = point_t(x, y);
	}
	return ret;
}

void solve() {
	auto a = read_polygon();
	auto b = read_polygon();
	printf("%.12f\n", (double) dist(a, b));
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