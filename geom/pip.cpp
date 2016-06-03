#include <cstdio>
#include <algorithm>

typedef long long ll;

struct Point {
	ll x, y;

	Point() {}

	Point(ll x, ll y) :
		x(x), y(y) {}

	Point& operator-=(Point const& a) {
		x -= a.x;
		y -= a.y;
		return *this;
	}
};

ll operator%(Point const& a, Point const& b) {
	return a.x * b.x + a.y * b.y;
}

bool operator==(Point const& a, Point const& b) {
	return a.x == b.x && a.y == b.y;
}

Point operator-(Point a, Point const& b) {
	return a -= b;
}

bool operator<=(Point const& a, Point const& b) {
	return a.x < b.x || (a.x == b.x && a.y <= b.y);
}

int turn(Point const& a, Point const& b, Point const& c) {
	ll cross = (b.x - a.x) * (c.y - b.y) - (b.y - a.y) * (c.x - b.x);
	return cross > 0 ? 1 : cross < 0 ? -1 : 0;
}

bool isOnSegment(Point const& p, Point const& a, Point const& b) {
	return turn(a, b, p) == 0 && ((a <= p && p <= b) || (b <= p && p <= a));
}

bool isOnRay(Point const& p, Point const& a, Point const& b) {
	return turn(a, b, p) == 0 && (a == p || ((a <= p) == (a <= b)));
}

int forAngle(Point const& p, Point const& a, Point const& b, Point const& c) {
	if (isOnRay(p, b, a) || isOnRay(p, b, c)) return 0;
	return turn(b, a, p) > 0 && turn(b, p, c) > 0 ? 1 : -1;
}

int const N = 100100;

Point a[N];

/// >0 -- inside, 0 -- border, <0 -- outside
int getPIP(Point p, int n) {
	int st = forAngle(p, a[1], a[0], a[n - 1]);
	if (st < 0) return st;
	if (st == 0) {
		return isOnSegment(p, a[n - 1], a[0]) || isOnSegment(p, a[0], a[1]) ? 0 : -1;
	}
	int l = 1;
	int r = n - 1;
	while (r - l > 1) {
		int m = (l + r) / 2;
		int left = forAngle(p, a[l], a[0], a[m]);
		int right = forAngle(p, a[m], a[0], a[r]);
		if (left < 0) {
			l = m;
		} else if (right < 0) {
			r = m;
		} else {
			return p == a[m] ? 0 : isOnSegment(p, a[0], a[m]) ? 1 : -1;
		}
	}
	return forAngle(p, a[0], a[r], a[l]);
}

int main() {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		int x, y;
    	scanf("%d%d", &x, &y);
		a[i] = Point(x, y);
    }
    if (turn(a[0], a[1], a[2]) < 0) {
    	std::reverse(a + 1, a + n);
    }
	int m;
	scanf("%d", &m);
	for (int i = 0; i < m; ++i) {
		int x, y;
		scanf("%d%d", &x, &y);
		int ans = getPIP(Point(x, y), n);
		puts(ans > 0 ? "INSIDE" : ans < 0 ? "OUTSIDE" : "BORDER");
	}
}