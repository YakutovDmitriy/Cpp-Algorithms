#ifdef LOCAL
//#  define _GLIBCXX_DEBUG
#else
#  define cerr __get_ce
#endif
#include <bits/stdc++.h>

namespace {
    int const input_size = 10100100;
    char input[input_size];
    int inptr = 0;
    
    int next_int() {
        while (input[inptr] < 33)
            ++inptr;
        bool sign = input[inptr] == '-';
        inptr += sign;
        int ret = 0;
        while (input[inptr] > 32)
            ret = 10 * ret + input[inptr++] - '0';
        return sign ? -ret : ret;
    }
}

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

void solve() {
    
}

int main() {
    //freopen("", "r", stdin);
    //freopen("", "w", stdout);
    cout << setprecision(15) << fixed;
#ifdef LOCAL
    cerr << setprecision(6) << fixed;
#endif
    fread(input, 1, input_size, stdin);
    int tcnt = 1;
    //tcnt = next_int();
    for (int test = 1; test <= tcnt; ++test)
        solve();
#ifdef LOCAL
    cerr << "time: " << (ll) clock() * 1000 / CLOCKS_PER_SEC << " ms" << endl;
#endif
}
