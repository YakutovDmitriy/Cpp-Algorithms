#include <bits/stdc++.h>
//#include <fcntl.h>

using namespace std;
#define next nachster
#define prev zuruck

typedef long long ll;
typedef long double ld;
typedef unsigned int uint;
typedef unsigned long long ull;

int const INF = 100 + (int) 1e9;
ll const INFL = 100 + (ll) 1e18;
ld const PI = 3.141592653589793238462643L;
mt19937 tw(960172);

bool is_prime(ll x) { if (x <= 1) return 0; for (ll y = 2; y * y <= x; ++y) if (x % y == 0) return 0; return 1; }
ll rnd(ll x, ll y) { static auto d = uniform_int_distribution<ll>(); return d(tw) % (y - x + 1) + x; }
ll sqr(int a) { return (ll) a * a; } ld sqr(ld a) { return a * a; } ll sqr(ll a) { return a * a; }
ll gcd(ll a, ll b) { while (b > 0) { ll t = a % b; a = b; b = t; } return a; }




void solve() {
    
    
    
    
}



int main() {

    //freopen("", "r", stdin);
    //freopen("", "w", stdout);

    cout.precision(15);
    cout << fixed;
    cerr.precision(6);
    cerr << fixed;

    int tcn = 1;
    for (int tn = 1; tn <= tcn; ++tn)
        solve();

#ifdef LOCAL
    cerr << "time: " << (ll) clock() * 1000 / CLOCKS_PER_SEC << " ms" << endl;
#endif
}
