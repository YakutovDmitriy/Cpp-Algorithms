#include <cstdio>

struct Point {
	int x, y;
};

bool operator<=(Point const& a, Point const& b) {
	return a.x < b.x || (a.x == b.x && a.y <= b.y);
}

int turn(Point const& a, Point const& b, Point const& c) {
	int cross = (b.x - a.x) * (c.y - b.y) - (b.y - a.y) * (c.x - b.x);
	return cross > 0 ? 1 : cross < 0 ? -1 : 0;
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

int main() {
	Point a, b, c, d;
	scanf("%d%d%d%d%d%d%d%d", &a.x, &a.y, &b.x, &b.y, &c.x, &c.y, &d.x, &d.y);
	puts(intersect(a, b, c, d) ? "Yes" : "No");
}