#ifdef LOCAL
//#  define _GLIBCXX_DEBUG
#else
#  define cerr __get_ce
#endif
#include <bits/stdc++.h>

using namespace std;
#define next __next
#define prev __prev
#define right __right
#define left __left
#define index __index

typedef long long ll;
typedef long double ld;
typedef unsigned int uint;
typedef unsigned long long ull;

typedef pair<int, int> ipair;
#define szof(x) ((int)(x).size())
#define bend(x) (x).begin(), (x).end()
#define X first
#define Y second

int const INF = 100 + (int) 1e9;
ll const INFL = 100 + (ll) 1e18;
ld const PI = 3.141592653589793238462643L;
mt19937 tw(960172);

int millis() { static auto s = chrono::system_clock::now(); return 1e3 * chrono::duration<double>(chrono::system_clock::now() - s).count(); }
bool is_prime(ll x) { for (ll y = 2; y * y <= x; ++y) if (x % y == 0) return 0; return x > 1; }
ll rnd(ll x, ll y) { static uniform_int_distribution<ll> d; return d(tw) % (y - x + 1) + x; }
ll sqr(int a) { return (ll) a * a; } template<class T> T sqr(T const& a) { return a * a; }
ll gcd(ll a, ll b) { while (b > 0) { ll t = a % b; a = b; b = t; } return a; }


template<int M, int P>
struct mod_int {
    static int const mod = M;
    static mod_int<M, P> value_of(long long x) { return mod_int<M, P>((x % mod + mod) % mod); }
  
    int val;
    mod_int() : val(0) {}
    mod_int(int val) : val(val) {}
    mod_int<M, P> &operator+=(mod_int<M, P> const &a) { if ((val += a.val) >= mod) val -= mod; return *this; }
    mod_int<M, P> &operator-=(mod_int<M, P> const &a) { if ((val -= a.val) < 0) val += mod; return *this; }
    mod_int<M, P> &operator*=(mod_int<M, P> const &a) { val = (long long) val * a.val % mod; return *this; }
    mod_int<M, P> &operator/=(mod_int<M, P> const &a) { val = (long long) val * a.inv() % mod; return *this; }
    mod_int<M, P> inv() const { mod_int<M, P> r = value_of(1), a = *this; for (int b = P - 1; b; b /= 2) { if (b % 2) r *= a; a *= a; } return r; } 
};

template<int M, int P> bool operator==(mod_int<M, P> const &a, mod_int<M, P> const &b) { return a.val == b.val; }
template<int M, int P> bool operator!=(mod_int<M, P> const &a, mod_int<M, P> const &b) { return a.val != b.val; }
template<int M, int P> bool operator<(mod_int<M, P> const &a, mod_int<M, P> const &b) { return a.val < b.val; }
template<int M, int P> bool operator<=(mod_int<M, P> const &a, mod_int<M, P> const &b) { return a.val <= b.val; }
template<int M, int P> bool operator>(mod_int<M, P> const &a, mod_int<M, P> const &b) { return a.val > b.val; }
template<int M, int P> bool operator>=(mod_int<M, P> const &a, mod_int<M, P> const &b) { return a.val >= b.val; }
template<int M, int P> mod_int<M, P> operator+(mod_int<M, P> a, mod_int<M, P> const &b) { return a += b; }
template<int M, int P> mod_int<M, P> operator-(mod_int<M, P> a, mod_int<M, P> const &b) { return a -= b; }
template<int M, int P> mod_int<M, P> operator*(mod_int<M, P> a, mod_int<M, P> const &b) { return a *= b; }
template<int M, int P> mod_int<M, P> operator/(mod_int<M, P> a, mod_int<M, P> const &b) { return a /= b; }

template<typename... Args>
struct hash_t;

template<typename I, typename... Os>
struct hash_t<I, Os...> : hash_t<Os...> {
    typedef I value_type;
    typedef hash_t<Os...> base_type;
    
    base_type &base = static_cast<base_type&>(*this);
    value_type val;
    
    hash_t() : hash_t<Os...>(), val() {}
    hash_t(hash_t const &other) : hash_t<Os...>(other.base), val(other.val) {}
    hash_t &operator=(hash_t const &other) { val = other.val; base = other.base; return *this; }
    hash_t(I val, Os... os) : hash_t<Os...>(os...), val(val) {}
    template<class J> hash_t(J j) : hash_t<Os...>(j), val(j) {}
    hash_t<I, Os...> &operator+=(hash_t<I, Os...> const &h) { val += h.val; base += h.base; return *this; }
    hash_t<I, Os...> &operator-=(hash_t<I, Os...> const &h) { val -= h.val; base -= h.base; return *this; }
    hash_t<I, Os...> &operator*=(hash_t<I, Os...> const &h) { val *= h.val; base *= h.base; return *this; }
    hash_t<I, Os...> &operator/=(hash_t<I, Os...> const &h) { val /= h.val; base /= h.base; return *this; }
    friend bool operator==(hash_t<I, Os...> const &a, hash_t<I, Os...> const &b) { return a.val == b.val && a.base == b.base; }
    friend bool operator!=(hash_t<I, Os...> const &a, hash_t<I, Os...> const &b) { return a.val != b.val || a.base != b.base; }
    friend bool operator<(hash_t<I, Os...> const &a, hash_t<I, Os...> const &b) { return a.val < b.val || (a.val == b.val && a.base < b.base); }
    friend bool operator<=(hash_t<I, Os...> const &a, hash_t<I, Os...> const &b) { return a.val < b.val || (a.val == b.val && a.base <= b.base); }
    friend bool operator>(hash_t<I, Os...> const &a, hash_t<I, Os...> const &b) { return a.val > b.val || (a.val == b.val && a.base > b.base); }
    friend bool operator>=(hash_t<I, Os...> const &a, hash_t<I, Os...> const &b) { return a.val > b.val || (a.val == b.val && a.base >= b.base); }
};

template<>
struct hash_t<> {
    hash_t<>() {}
    template<class J> hash_t(J) {}
    hash_t<> &operator+=(hash_t<> const&) { return *this; }
    hash_t<> &operator-=(hash_t<> const&) { return *this; }
    hash_t<> &operator*=(hash_t<> const&) { return *this; }
    hash_t<> &operator/=(hash_t<> const&) { return *this; }
    friend bool operator==(hash_t<> const&, hash_t<> const&) { return true; }
    friend bool operator!=(hash_t<> const&, hash_t<> const&) { return false; }
    friend bool operator<(hash_t<> const&, hash_t<> const&) { return false; }
    friend bool operator<=(hash_t<> const&, hash_t<> const&) { return true; }
    friend bool operator>(hash_t<> const&, hash_t<> const&) { return false; }
    friend bool operator>=(hash_t<> const&, hash_t<> const&) { return true; }
};

template<class... Os> hash_t<Os...> operator+(hash_t<Os...> a, hash_t<Os...> const &b) { return a += b; }
template<class... Os> hash_t<Os...> operator-(hash_t<Os...> a, hash_t<Os...> const &b) { return a -= b; }
template<class... Os> hash_t<Os...> operator*(hash_t<Os...> a, hash_t<Os...> const &b) { return a *= b; }
template<class... Os> hash_t<Os...> operator/(hash_t<Os...> a, hash_t<Os...> const &b) { return a /= b; }

int const P = 997;
typedef mod_int<1000000007, 1000000006> mint1;
typedef mod_int<1000000009, 1000000008> mint2;
typedef hash_t<mint1, mint2> Hash;



void solve() {
    
}

int main() {
    millis();
    //freopen("", "r", stdin);
    //freopen("", "w", stdout);
    cout << setprecision(15) << fixed;
#ifdef LOCAL
    cerr << setprecision(6) << fixed;
#endif
    int tcnt = 1;
    //scanf("%d", &tcnt);
    for (int test = 1; test <= tcnt; ++test)
        solve();
#ifdef LOCAL
    cerr << "time: " << millis() << " ms" << endl;
#endif
}
