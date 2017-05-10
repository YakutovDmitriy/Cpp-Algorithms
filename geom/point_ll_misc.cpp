#include <bits/stdc++.h>
//#include <fcntl.h>

using std::max; using std::swap; using std::abs; using std::priority_queue; using std::queue; using std::bitset; using std::make_tuple; 
using std::istream; using std::ostream; using std::fixed; using std::greater; using std::tuple; using std::tie; using std::make_pair;
using std::cout; using std::cerr; using std::endl; using std::lower_bound; using std::upper_bound; using std::deque; using std::min; 
using std::map; using std::string; using std::fill; using std::copy; using std::sort; using std::unique; using std::unordered_set; 
using std::multiset; using std::nth_element; using std::min_element; using std::max_element; using std::vector; using std::set; 
using std::unordered_map; using std::pair; using std::next_permutation; using std::reverse; using std::rotate; using std::cin; 
using std::iota; using std::function; using std::shuffle; using std::iter_swap;

typedef long long ll;
typedef long double ld;
typedef unsigned int uint;
typedef unsigned long long ull;

int const INF = 100 + (int) 1e9;
ll const INFL = 100 + (ll) 1e18;
ld const PI = 3.141592653589793238462643L;
std::mt19937 mt19937(960172);

ll rnd(ll x, ll y) { static auto gen = std::bind(std::uniform_int_distribution<ll>(), mt19937); return gen() % (y - x + 1) + x; }
bool is_prime(ll x) { if (x <= 1) return 0; for (ll y = 2; y * y <= x; ++y) if (x % y == 0) return 0; return 1; }
ll sqr(int a) { return (ll) a * a; } ld sqr(ld a) { return a * a; } ll sqr(ll a) { return a * a; }
ll gcd(ll a, ll b) { while (b > 0) { ll t = a % b; a = b; b = t; } return a; }

struct point_t {
    ll x, y;

    point_t() {}

    point_t(ll x, ll y) 
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
    
    point_t& operator*=(ll coef) {
        x *= coef;
        y *= coef;
        return *this;
    }
};

point_t operator-(point_t a, point_t const& b) {
    return a -= b;
}

point_t operator+(point_t a, point_t const& b) {
    return a += b;
}

point_t operator*(point_t a, ll coef) {
    return a *= coef;
}

int turn(point_t const& a, point_t const& b, point_t const& c) {
    ll cross = (b.x - a.x) * (c.y - b.y) - (b.y - a.y) * (c.x - b.x);
    return cross > 0 ? 1 : cross < 0 ? -1 : 0;
}

bool operator<(point_t const& a, point_t const& b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

bool operator<=(point_t const& a, point_t const& b) {
    return a.x < b.x || (a.x == b.x && a.y <= b.y);
}

bool operator==(point_t const& a, point_t const& b) {
    return a.x == b.x && a.y == b.y;
}

bool operator!=(point_t const& a, point_t const& b) {
    return a.x != b.x || a.y != b.y;
}

bool operator>(point_t const& a, point_t const& b) {
    return a.x > b.x || (a.x == b.x && a.y > b.y);
}

bool operator>=(point_t const& a, point_t const& b) {
    return a.x > b.x || (a.x == b.x && a.y >= b.y);
}

istream& operator>>(istream& is, point_t& a) {
    return is >> a.x >> a.y;
}

ostream& operator<<(ostream& os, point_t const& a) {
    return os << '(' << a.x << ", " << a.y << ')';
}

bool on_segment(point_t const& p, point_t const& a, point_t const& b) {
    return turn(a, b, p) == 0 && ((a <= p && p <= b) || (b <= p && p <= a));
}

bool on_ray(point_t const& p, point_t const& a, point_t const& b) {
    return turn(a, b, p) == 0 && (a == p || ((a <= p) == (a <= b)));
}

/// check if $p$ lies inside of angle $abc$ where $abc$ has ccw orientation
int in_angle(point_t const& p, point_t const& a, point_t const& b, point_t const& c) {
    if (on_ray(p, b, a) || on_ray(p, b, c)) 
        return 0;
    return turn(b, a, p) > 0 && turn(b, p, c) > 0 ? 1 : -1;
}

/// проверяет, что $p$ лежит под полуинтервалом $[a; b)$ или $[b; a)$
///    в зависимости от того, какой из них идет "направо"
bool check_under(point_t const& p, point_t a, point_t b) {
    if (b < a)
        swap(a, b);
    if (p < a)
        return 0;
    if (!(p < b))
        return 0;
    return turn(a, b, p) <= 0;
}

/// o = origin
ll dot_prod(point_t const& o, point_t const& a, point_t const& b) {
    return (a.x - o.x) * (b.x - o.x) + (a.y - o.y) * (b.y - o.y);
}

ll dot_prod(point_t const& a, point_t const& b) {
    return a.x * b.x + a.y * b.y;
}

/// o = origin
ll cross_prod(point_t const& o, point_t const& a, point_t const& b) {
    return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

ll cross_prod(point_t const& a, point_t const& b) {
    return a.x * b.y - a.y * b.x;
}

ll dist2(point_t const& a, point_t const& b) {
    return sqr(a.x - b.x) + sqr(a.y - b.y);
}

double dist(point_t const& a, point_t const& b) {
    return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}

/// distance between point_t $p$ and segment $[a; b]$
double dist(point_t const& p, point_t const& a, point_t const& b) {
    if (dot_prod(a, b, p) <= 0)
        return dist(p, a);
    if (dot_prod(b, a, p) <= 0)
        return dist(p, b);
    ll A = a.y - b.y;
    ll B = b.x - a.x;
    ll C = -A * a.x - B * a.y;
    return abs(A * p.x + B * p.y + C) / sqrt(sqr(A) + sqr(B)); 
}

/// check if segment $[a; b]$ intersects with segment $[c; d]$
bool intersect(point_t const& a, point_t const& b, point_t const& c, point_t const& d) {
    static auto const between = [](point_t const& p, point_t const& a, point_t const& b) -> bool {
        return (a <= p && p <= b) || (b <= p && p <= a);
    };
    if (turn(a, b, c) == 0 && turn(a, b, d) == 0)
        return between(a, c, d) || between(b, c, d) || between(c, a, b) || between(d, a, b);
    return turn(a, c, b) * turn(a, b, d) >= 0 && turn(c, a, d) * turn(c, d, b) >= 0;
}

/// build convex hull using Graham algorithm
void graham(vector<point_t>& a) {
    if (a.size() == 1u)
        return;
    iter_swap(a.begin(), min_element(a.begin(), a.end()));
    sort(a.begin() + 1, a.end(), [&](point_t const& p, point_t const& q) {
        int t = turn(a[0], p, q);
        if (t != 0)
            return t > 0;
        return p < q;
    });
    int c = 0;
    for (point_t const& p : a) {
        while (c > 1 && turn(a[c - 2], a[c - 1], p) <= 0)
            --c;
        a[c++] = p;
    }
    if (c < (int)a.size())
        a.erase(a.begin() + c, a.end());
}

/// build convex hull using Andrew algorithm
void andrew(vector<point_t>& a) {    if (a.size() == 1u)
        return;
    sort(a.begin(), a.end());
    vector<point_t> d, u;
    for (point_t const& p : a) {
        while (d.size() > 1u && turn(d[d.size() - 2u], d[d.size() - 1u], p) <= 0)
            d.pop_back();
        d.push_back(p);
        while (u.size() > 1u && turn(u[u.size() - 2u], u[u.size() - 1u], p) >= 0)
            u.pop_back();
        u.push_back(p);
    }
    u.pop_back();
    reverse(u.begin(), u.end());
    u.pop_back();
    d.insert(d.end(), u.begin(), u.end());
    a = d;
}


void solve() {
    
    
    
    
}



int main() {
    
    //freopen("", "r", stdin);
    //freopen("", "w", stdout);
    
    cout.precision(15);
    cout << fixed;
    cerr.precision(6);
    cerr << fixed;
    
    int tests_count = 1;
    for (int test_number = 1; test_number <= tests_count; ++test_number)
        solve();
    
#ifdef LOCAL
    cerr << "time: " << (ll) clock() * 1000 / CLOCKS_PER_SEC << " ms" << endl;
#endif
}