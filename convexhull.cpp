#include <cstdio>
#include <algorithm>
#include <cstdlib>

typedef long long ll;

struct Point {
	int x, y;
};

bool operator<(Point const& a, Point const& b) {
	return a.x < b.x || (a.x == b.x && a.y < b.y);
}

int turn(Point const& a, Point const& b, Point const& c) {
	ll cross = (ll) (b.x - a.x) * (c.y - b.y) - (ll) (b.y - a.y) * (c.x - b.x);
	return cross > 0 ? 1 : cross < 0 ? -1 : 0;
}

int const N = 100100;

Point a[N], hull[N];

int main() {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%d%d", &a[i].x, &a[i].y);
	}
	std::iter_swap(a, std::min_element(a, a + n));
	std::sort(a + 1, a + n, [](Point const& p, Point const& q) {
		int cross = turn(a[0], p, q);
		if (cross != 0) {
			return cross > 0;
		}
		return p < q;
	});
	int size = 0;
	for (int i = 0; i < n; ++i) {
		while (size > 1 && turn(hull[size - 2], hull[size - 1], a[i]) <= 0) {
			--size;
		}
		hull[size++] = a[i];
	}
}