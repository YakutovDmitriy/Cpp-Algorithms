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


int const N = 200100;

struct comp {
    double re, im;
    
    comp() : 
        re(0), im(0) {}
    
    comp(int x) : 
        re(x), im(0) {}
    
    comp(double a, double b) : 
        re(a), im(b) {}
    
    comp operator+(comp const& a) const {
        return comp(re + a.re, im + a.im);
    }

    comp operator-(comp const& a) const {
        return comp(re - a.re, im - a.im);
    }

    comp& operator*=(comp const& a) {
        double newRe = re * a.re - im * a.im;
        im = re * a.im + im * a.re;
        re = newRe;
        return *this;
    }

    comp& operator/=(double a) {
        re /= a;
        im /= a;
        return *this;
    }
};

comp operator*(comp const& a, comp const& b) {
    return a *= b;
}

void FFT(comp* a, int n, bool const inv) {                                           
    for (int i = 1, j = 0; i < n; ++i) {                                                                                    
        int bit = n >> 1;                                                                                         
        while (j >= bit) {
            j -= bit;
            bit >>= 1;
        }
        j += bit;
        if (i < j) {                                                                            
            std::swap(a[i], a[j]);                                                                                 
        }                                                                                                         
    }
    for (int len = 2; len <= n; len <<= 1) {                            
        double angle = 2 * PI / len;                                
        if (inv) {                                                  
            angle = -angle;                                     
        }                                                           
        comp const g(cos(angle), sin(angle));                
        for (int i = 0; i < n; i += len) {                          
            comp r = comp(1);                                   
            for (int j = 0; j < len / 2; ++j) {                 
                comp x = a[i + j];                          
                comp y = r * a[i + j + len / 2];            
                a[i + j] = x + y;                           
                a[i + j + len / 2] = x - y;                 
                r *= g;                                  
            }                                                                                                  
        }                                                                                                              
    }                                                                                                                                                         
    if (inv) {
        for (int i = 0; i < n; ++i) {
            a[i] /= n;
        }
    }
}

int p1[N], p2[N], p3[N];

comp ta[N], tb[N];

void mul(int sz) {
    int n = 1;
    while (n < sz) {
        n <<= 1;
    }
    n <<= 1;
    for (int i = 0; i < sz; ++i) {
        ta[i] = comp(p1[i]);
    }
    for (int i = 0; i < sz; ++i) {
        tb[i] = comp(p2[i]);
    }
    for (int i = sz; i < n; ++i) {
        ta[i] = 0;
        tb[i] = 0;
    }
    FFT(ta, n, false);
    FFT(tb, n, false);
    for (int i = 0; i < n; ++i) {
        ta[i] *= tb[i];
    }
    FFT(ta, n, true);
    for (int i = 0; i < n; ++i) {
        p3[i] = (int) (ta[i].re + 0.5);
    }
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
    
    solve();
    
#ifdef LOCAL
    cerr << "time: " << (ll) clock() * 1000 / CLOCKS_PER_SEC << " ms" << endl;
#endif
}