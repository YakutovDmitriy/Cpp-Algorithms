#ifdef LOCAL
#  define _GLIBCXX_DEBUG
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

typedef pair<int, int> pii;
typedef pair<int, int> ipair;
#define szof(x) ((int)(x).size())
#define ff first
#define ss second
#define puba push_back
#define bend(x) (x).begin(), (x).end()

int const INF = 100 + (int) 1e9;
ll const INFL = 100 + (ll) 1e18;
ld const PI = 3.141592653589793238462643L;
mt19937 tw(960172);

bool is_prime(ll x) { for (ll y = 2; y * y <= x; ++y) if (x % y == 0) return 0; return x > 1; }
ll rnd(ll x, ll y) { static uniform_int_distribution<ll> d; return d(tw) % (y - x + 1) + x; }
ll sqr(int a) { return (ll) a * a; } template<class T> T sqr(T const& a) { return a * a; }
ll gcd(ll a, ll b) { while (b > 0) { ll t = a % b; a = b; b = t; } return a; }


int const mod = 1000000007;

void add(int& a, int b) {
    if ((a += b) >= mod)
        a -= mod;
}

int sum(int a, int b) {
    if ((a += b) >= mod)
        a -= mod;
    return a;
}

int prod(int a, int b) {
    ull x = (ull) a * b;
    uint xh = x >> 32, xl = x, q, r;
#ifdef __GNUC__
    asm(
        "divl %4; \n\t"
        : "=a" (q), "=d" (r)
        : "d" (xh), "a" (xl), "r" (mod)
    );
#else
    __asm {
        mov edx, dword ptr[xh];
        mov eax, dword ptr[xl];
        div dword ptr[mod];
        mov dword ptr[q], eax;
        mov dword ptr[r], edx;
    };
#endif
    return r;
}

void mul(int& a, int b) {
    a = prod(a, b);
}

int modpow(int a, ll b) {
    int ret = 1;
    for (; b > 0; b /= 2) {
        if (b % 2 == 1)
            mul(ret, a);
        mul(a, a);
    }
    return ret;
}



void solve() {
    
}

int main() {
//    freopen("", "r", stdin);
//    freopen("", "w", stdout);
    cout << setprecision(15) << fixed;
#ifdef LOCAL
    cerr << setprecision(6) << fixed;
#endif
    int tcnt = 1;
    for (int test = 1; test <= tcnt; ++test)
        solve();
#ifdef LOCAL
    cerr << "time: " << (ll) clock() * 1000 / CLOCKS_PER_SEC << " ms" << endl;
#endif
}
