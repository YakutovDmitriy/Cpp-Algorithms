#include <bits/stdc++.h>
//#include <fcntl.h>
#ifndef LOCAL
#  define cerr get_CE
#endif

using namespace std;
#define next Nachster
#define prev Zuruck
#define right Rechts
#define left Links
#define index Verzeichnis

typedef long long ll;
typedef long double ld;
typedef unsigned int uint;
typedef unsigned long long ull;

int const INF = 100 + (int) 1e9;
ll const INFL = 100 + (ll) 1e18;
ld const PI = 3.141592653589793238462643L;
mt19937 tw(960172);

ll sqr(int a) { return (ll) a * a; } ld sqr(ld a) { return a * a; } ll sqr(ll a) { return a * a; }
bool is_prime(ll x) { for (ll y = 2; y * y <= x; ++y) if (x % y == 0) return 0; return x > 1; }
ll rnd(ll x, ll y) { static uniform_int_distribution<ll> d; return d(tw) % (y - x + 1) + x; }
ll gcd(ll a, ll b) { while (b > 0) { ll t = a % b; a = b; b = t; } return a; }


struct comp_t {
    double x, y;
    
    comp_t()
        : x(0)
        , y(0)
    {}
    
    comp_t(double x) 
        : x(x)
        , y(0)
    {}
    
    comp_t(double x, double y)
        : x(x)
        , y(y)
    {}

    comp_t& operator+=(comp_t const& c) {
        x += c.x;
        y += c.y;
        return *this;
    }
    
    comp_t& operator-=(comp_t const& c) {
        x -= c.x;
        y -= c.y;
        return *this;
    }
    
    comp_t& operator*=(comp_t const& c) {
        double newx = x * c.x - y * c.y;
        y = x * c.y + y * c.x;
        x = newx;
        return *this;
    }
    
    comp_t& operator/=(comp_t const& c) {
        double cabs = c.x * c.x + c.y * c.y;
        double newx = (x * c.x + y * c.y) / cabs;
        y = (-x * c.y + y * c.x) / cabs;
        x = newx;
        return *this;
    }
};

bool operator==(comp_t const& a, comp_t const& b) {
    static double const eps_eq = 1e-8;
    return a.x < b.x + eps_eq && b.x < a.x + eps_eq &&
           a.y < b.y + eps_eq && b.y < a.y + eps_eq;
}

comp_t operator+(comp_t const& a) {
    return a;
}

comp_t operator+(comp_t a, comp_t const& b) {
    return a += b;
}

comp_t operator-(comp_t const& a) {
    return comp_t(-a.x, -a.y);
}

comp_t operator-(comp_t a, comp_t const& b) {
    return a -= b;
}

comp_t operator*(comp_t a, comp_t const& b) {
    return a *= b;
}

comp_t operator/(comp_t a, comp_t const& b) {
    return a /= b;
}

comp_t abs(comp_t const& c) {
    return sqrt(c.x * c.x + c.y * c.y);
}

comp_t abs2(comp_t const& c) {
    return c.x * c.x + c.y * c.y;
}

comp_t conj(comp_t const& c) {
    return comp_t(c.x, -c.y);
}

comp_t angle(comp_t const& c) {
    return atan2(c.y, c.x);
}

comp_t expt(comp_t const& a) {
    double len = exp(a.x);
    return comp_t(cos(a.y) * len, sin(a.y) * len);
}

comp_t ln(comp_t const& a) {
    return comp_t(log(a.x * a.x + a.y * a.y) / 2, atan2(a.y, a.x));
}

comp_t power(comp_t const& a, comp_t const& b) {
    return expt(ln(a) * b);
}

comp_t polar(double angle) {
    return comp_t(cos(angle), sin(angle));
}

ostream& operator<<(ostream& os, comp_t const& c) {
    return os << '(' << c.x << ", " << c.y << ')';
}

istream& operator>>(istream& is, comp_t& c) {
    return is >> c.x >> c.y;
}





void solve() {
    
    
    
    
}



int main() {

    //freopen("", "r", stdin);
    //freopen("", "w", stdout);

    cout.precision(15);
    cout << fixed;
#ifdef LOCAL
    cerr.precision(6);
    cerr << fixed;
#endif

    int tcn = 1;
    for (int tn = 1; tn <= tcn; ++tn)
        solve();

#ifdef LOCAL
    cerr << "time: " << (ll) clock() * 1000 / CLOCKS_PER_SEC << " ms" << endl;
#endif
}
