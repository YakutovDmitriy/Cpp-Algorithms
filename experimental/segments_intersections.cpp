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

ll const SHIFT = 10000;	
ll LEN;

struct Point {
	ll x, y;
	
	Point() {}
	
	Point(ll x, ll y) :
		x(x), y(y) {}
		
	ll toLL() const {
		return (x + SHIFT) * INF + y + SHIFT;
	}
};

bool operator<=(Point const& a, Point const& b) {
	return a.x < b.x || (a.x == b.x && a.y <= b.y);
}

bool operator<(Point const& a, Point const& b) {
	return a.x < b.x || (a.x == b.x && a.y < b.y);
}

bool operator==(Point const& a, Point const& b) {
	return a.x == b.x && a.y == b.y;
}

bool operator!=(Point const& a, Point const& b) {
	return a.x != b.x || a.y != b.y;
}

int turn(Point const& a, Point const& b, Point const& c) {
	ll cross = (b.x - a.x) * (c.y - b.y) - (b.y - a.y) * (c.x - b.x);
	return cross > 0 ? 1 : cross < 0 ? -1 : 0;
}

ld dist(Point const& a, Point const& b) {
	ll dx = a.x - b.x;
	ll dy = a.y - b.y;
	return sqrtl(dx * dx + dy * dy);
}

bool between(Point const& p, Point const& a, Point const& b) {
	return (a <= p && p <= b) || (b <= p && p <= a);
}

bool intersect(Point const& a, Point const& b, Point const& c, Point const& d) {
	if (turn(a, b, c) == 0 && turn(a, b, d) == 0) {
		return between(a, c, d) || between(b, c, d) || between(c, a, b) || between(d, a, b);
	}
	return turn(a, c, b) * turn(a, b, d) >= 0 && turn(c, a, d) * turn(c, d, b) >= 0;
}

Point getCell(Point const& a) {
	return Point(
		(a.x + SHIFT) / LEN * LEN - SHIFT, 
		(a.y + SHIFT) / LEN * LEN - SHIFT
	);
}

unordered_map<ll, unordered_set<int>> t;

void add(Point const& from, Point const& to, int index) {
	Point st = getCell(from);
	Point fn = getCell(to);

	t[st.toLL()].insert(index);
	
	while (st != fn) {
	
		int turnUp = turn(from, to, Point(st.x + LEN, st.y + LEN));
		
		if (turnUp < 0) {
			st.y += LEN;
		} else if (turnUp == 0) {
			st.x += LEN;
			st.y += LEN;
		} else {
			
			int turnDown = turn(from, to, Point(st.x + LEN, st.y));
			
			if (turnDown <= 0) {
				st.x += LEN;
			} else {
				st.y -= LEN;
			}		
		}

		t[st.toLL()].insert(index);
	
	}
}

void solve() {
	
	int n;
	scanf("%d", &n);
	
	ld sum = 0;
	
	vector<Point> from(n), to(n);
	
	for (int i = 0; i < n; ++i) {
		int x, y;
		scanf("%d%d", &x, &y);
		from[i] = Point(x, y);

		scanf("%d%d", &x, &y);
		to[i] = Point(x, y);
	
		sum += dist(from[i], to[i]);
		
		if (to[i] < from[i]) {
			swap(from[i], to[i]);
		}
	}
	
	LEN = (ll) (sum / n / 9) + 1;
	
	for (int i = 0; i < n; ++i) {
		add(from[i], to[i], i);
	}
	
	for (auto& cell : t) {
		vector<int> points(cell.second.begin(), cell.second.end());

		for (int i = 0; i < (int)points.size(); ++i) {
			for (int j = i + 1; j < (int)points.size(); ++j) {
				int id1 = points[i], id2 = points[j];
				if (intersect(from[id1], to[id1], from[id2], to[id2])) {
					cout << "YES" << endl;
					cout << id1 + 1 << " " << id2 + 1 << endl;
					return;
				}
			}
		}
	
	}
	
	cout << "NO" << endl;
	
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