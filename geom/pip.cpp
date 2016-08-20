#include <cstdio>
#include <algorithm>

typedef long long ll;

struct point_t {
	ll x, y;

	point_t() {}

	point_t(ll x, ll y) :
		x(x), y(y) {}

	point_t& operator-=(point_t const& a) {
		x -= a.x;
		y -= a.y;
		return *this;
	}
};

bool operator==(point_t const& a, point_t const& b) {
	return a.x == b.x && a.y == b.y;
}

point_t operator-(point_t a, point_t const& b) {
	return a -= b;
}

bool operator<=(point_t const& a, point_t const& b) {
	return a.x < b.x || (a.x == b.x && a.y <= b.y);
}

int turn(point_t const& a, point_t const& b, point_t const& c) {
	ll cross = (b.x - a.x) * (c.y - b.y) - (b.y - a.y) * (c.x - b.x);
	return cross > 0 ? 1 : cross < 0 ? -1 : 0;
}

bool on_segment(point_t const& p, point_t const& a, point_t const& b) {
	return turn(a, b, p) == 0 && ((a <= p && p <= b) || (b <= p && p <= a));
}

bool on_ray(point_t const& p, point_t const& a, point_t const& b) {
	return turn(a, b, p) == 0 && (a == p || ((a <= p) == (a <= b)));
}

int for_angle(point_t const& p, point_t const& a, point_t const& b, point_t const& c) {
	if (on_ray(p, b, a) || on_ray(p, b, c)) return 0;
	return turn(b, a, p) > 0 && turn(b, p, c) > 0 ? 1 : -1;
}

int const N = 100100;

point_t a[N];

/// >0 -- inside, 0 -- border, <0 -- outside
int get_pip(point_t p, int n) {
	int st = for_angle(p, a[1], a[0], a[n - 1]);
	if (st < 0) return st;
	if (st == 0) {
		return on_segment(p, a[n - 1], a[0]) || on_segment(p, a[0], a[1]) ? 0 : -1;
	}
	int l = 1;
	int r = n - 1;
	while (r - l > 1) {
		int m = (l + r) / 2;
		int left = for_angle(p, a[l], a[0], a[m]);
		int right = for_angle(p, a[m], a[0], a[r]);
		if (left < 0) {
			l = m;
		} else if (right < 0) {
			r = m;
		} else {
			return p == a[m] ? 0 : on_segment(p, a[0], a[m]) ? 1 : -1;
		}
	}
	return for_angle(p, a[0], a[r], a[l]);
}

int main() {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		int x, y;
    	scanf("%d%d", &x, &y);
		a[i] = point_t(x, y);
    }
    if (turn(a[0], a[1], a[2]) < 0) {
    	std::reverse(a + 1, a + n);
    }
	int m;
	scanf("%d", &m);
	for (int i = 0; i < m; ++i) {
		int x, y;
		scanf("%d%d", &x, &y);
		int ans = get_pip(point_t(x, y), n);
		puts(ans > 0 ? "INSIDE" : ans < 0 ? "OUTSIDE" : "BORDER");
	}
}