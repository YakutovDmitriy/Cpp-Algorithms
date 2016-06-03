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

ll rnd(ll x, ll y) { static auto gen = std::bind(std::uniform_int_distribution<ll>(), std::mt19937(1510)); return gen() % (y - x + 1) + x; }
ll gcd(ll a, ll b) { while (b > 0) { int t = a % b; a = b; b = t; } return a; }

int const INF = (int) 1e9;
ll const INFL = (ll) 1e18;
ld const PI = 3.1415926535897932384626433832795028;


struct Point {
	ll x, y;
	int ind;
	
	Point() {}
	
	Point(ll x, ll y, int ind) :
		x(x), y(y), ind(ind) {}
};

int turn(Point const& a, Point const& b, Point const& c) {
	ll cross = (b.x - a.x) * (c.y - b.y) - (b.y - a.y) * (c.x - b.x);
	return cross > 0 ? 1 : cross < 0 ? -1 : 0;
}

bool inAngle(Point const& a, Point const& b, Point const& c, Point const& x) {
	return turn(b, c, x) >= 0 && turn(b, x, a) >= 0;
}

bool inTriangle(Point const& a, Point const& b, Point const& c, Point const& x) {
	return inAngle(a, b, c, x) && inAngle(b, c, a, x) && inAngle(c, a, b, x);
}

void solve() {
	
	int n;
	scanf("%d", &n);

	std::list<Point> a;
	for (int i = 0; i < n; ++i) {
		int x, y;
		scanf("%d%d", &x, &y);
		a.emplace_back(x, y, i + 1);
	}
	
	vector<tuple<int, int, int>> ans;
	
	typedef std::list<Point>::iterator it;
	auto next = [&a](it& i) {
		++i;
		if (i == a.end()) i = a.begin();
	};
	auto prev = [&a](it& i) {
		if (i == a.begin()) i = a.end();
		--i;
	};
	
	it A = a.begin();
	it B = A; next(B);
	it C = B; next(C);
	
	while (a.size() >= 3) {
		if (turn(*A, *B, *C) > 0) {
			bool good = true;
			for (it x = a.begin(); good && x != a.end(); ++x) {
				if (x != A && x != B && x != C) {
					good &= !inTriangle(*A, *B, *C, *x);
				}
			}
			if (good) {
				ans.emplace_back(A->ind, B->ind, C->ind);
				a.erase(B);
				prev(A);
				B = A; next(B);
				C = B; next(C);
				continue;
			}
		}
		next(A);
		next(B);
		next(C);
	}
	
	for (auto t : ans) {
		printf("%d %d %d\n", std::get<0>(t), std::get<1>(t), std::get<2>(t));
	}
	
}



int main() {

	cout.precision(15);
	cout << fixed;
	cerr.precision(6);
	cerr << fixed;
	
	solve();

#ifdef LOCAL
	cerr << "time: " << clock() << " ms" << endl;
#endif
}