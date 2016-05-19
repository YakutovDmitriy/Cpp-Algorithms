#include <bits/stdc++.h>

#if (_WIN32 || __WIN32__)
#  define LLD "%I64d"
#else
#  define LLD "%lld"
#endif

using std::istream; using std::ostream;using std::fixed; using std::greater;
using std::tuple; using std::tie; using std::make_pair; using std::multiset;
using std::vector; using std::set; using std::map; using std::string;
using std::fill; using std::copy; using std::sort; using std::unique;
using std::unordered_set; using std::unordered_map; using std::pair;
using std::next_permutation; using std::reverse; using std::rotate;
using std::cin; using std::cout; using std::cerr; using std::endl;
using std::lower_bound; using std::upper_bound; using std::deque;
using std::min; using std::max; using std::swap; using std::abs;
using std::priority_queue; using std::queue; using std::bitset;
using std::nth_element;

typedef long long ll;
typedef long double ld;

int const INF = (int) 1e9;
ll const INFL = (ll) 1e18;
ld const PI = 3.1415926535897932384626433832795028;



struct Point {
	ll x, y;
	int ind;

	Point() {}
	
	Point(ll x, ll y, int ind = -1) :
		x(x), y(y), ind(ind) {}
};

Point const NONE(INFL, INFL, INF);

bool compx(Point const& a, Point const& b) {
	return a.x < b.x || (a.x == b.x && a.y < b.y);
}

bool compy(Point const& a, Point const& b) {
	return a.y < b.y || (a.y == b.y && a.x < b.x);
}

ll dist2(Point const& a, Point const& b) {
	ll dx = a.x - b.x;
	ll dy = a.y - b.y;
	return dx * dx + dy * dy;
}



struct Node {
	int type; /// 0 -- x-sort, 1 -- y-sort, 2 -- leaf
	ll x1, y1;
	ll x2, y2;
	vector<Point> p;
	Node *L, *R;
};

int const MAX_IN_LEAF = 25;

bool inside(ll p, ll begin, ll end) {
	return begin <= p && p <= end;
}

ll dist2(ll p, ll begin, ll end) {
	if (inside(p, begin, end)) {
		return 0;
	}
	ll dist = min(abs(p - begin), abs(p - end));
	return dist * dist;
}

ll dist2(Point const& a, Node* v) {
	if (!v) {
		return INFL;
	}
	if (v->type == 2) {
		ll ret = INFL;
		for (auto p : v->p) {
			ll now = dist2(a, p);
			if (now > 0) {
				ret = min(ret, now);
			}
		}
		return ret;
	} else {
		if (inside(a.x, v->x1, v->x2)) {
			return dist2(a.y, v->y1, v->y2);
		} else if (inside(a.y, v->y1, v->y2)) {
			return dist2(a.x, v->x1, v->x2);
		} else {
			return min({
				dist2(a, Point(v->x1, v->y1)),
				dist2(a, Point(v->x1, v->y2)),
				dist2(a, Point(v->x2, v->y1)),
				dist2(a, Point(v->x2, v->y2))
			});
		}
	}
}

template<typename RAI>
Node* build(RAI a, RAI b, int type) {
	int n = b - a;
	Node* ret = new Node();
	ret->x1 = min_element(a, b, compx)->x;
	ret->y1 = min_element(a, b, compy)->y;
	ret->x2 = max_element(a, b, compx)->x;
	ret->y2 = max_element(a, b, compy)->y;
	if (n <= MAX_IN_LEAF) {
		ret->type = 2;
		ret->p = vector<Point>(a, b);
		ret->L = NULL;
		ret->R = NULL;
		return ret;
	}
	int ln = n / 2;
	nth_element(a, a + ln, a + n, type == 0 ? compx : compy);
	ret->type = type;
	ret->p = {a[ln]};
	ret->L = build(a, a + ln, !type);
	ret->R = build(a + ln, b, !type);
	return ret;
}

/**
 *
 * !!!!!!!!!!!!!!!!!!!!!!!!!!! ATTENTION !!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * !!!                                                            !!!
 * !!! THIS FUNCTION IGNORES POINTS IN TREE WHICH COINCIDE WITH P !!!
 * !!!                                                            !!!
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 */

Point closest(Node* tree, Point const& p) {
	ll res = INFL;
	Point ret = NONE;	
	priority_queue<pair<ll, Node*>> q;
	q.emplace(-dist2(p, tree), tree);
	while (!q.empty()) {
		ll cur = -q.top().first;
		if (cur >= res) {
			break;
		}
		Node* v = q.top().second;
		q.pop();
		if (v->type == 2) {
			res = cur;
			for (auto q : v->p) {
				if (cur == dist2(p, q)) {
					ret = q;
					break;
				}
			}
		} else {
			q.emplace(-dist2(p, v->L), v->L);
			q.emplace(-dist2(p, v->R), v->R);
		}
	}
	return ret;
}

void solve() {
	
	int n;
	scanf("%d", &n);

	vector<Point> a(n);

	ll sum = 0;
	
	for (int i = 0; i < n; ++i) {
		ll y;
		scanf(LLD, &y);
		sum += y;
		a[i] = Point(i, sum, i);
	}
	
	Node* tree = build(a.begin(), a.end(), 0);
	
	ll ans = INFL;
	
	for (auto p : a) {
		Point q = closest(tree, p);
		ans = min(ans, dist2(p, q));
	}
	
	cout << ans << endl;
	
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