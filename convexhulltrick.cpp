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

int const N = 200200;

struct CHT {
    ll bs[N], ks[N], from[N];
    int size;
    
    CHT() : size(0) {}
    
    ll int_back(ll k, ll b) const {
        if (size == 0)
            return -INFL;
        return (bs[size - 1] - b + k - ks[size - 1] - 1) / (k - ks[size - 1]);
    }
    
    /// add lines with increasing K 
    void add_line(ll k, ll b) {
        while (size > 0 && int_back(k, b) <= from[size - 1])
            --size;
        ks[size] = k;
        bs[size] = b;
        from[size] = int_back(k, b);
        ++size;
    }

    /// find max[line : lines][line(x)]
    ll eval(ll x) const {
        int pos = upper_bound(from, from + size, x) - from - 1;
        return ks[pos] * x + bs[pos];
    }
    
    void clear() {
        size = 0;
    }
};

void solve() {
    int n, k;
    scanf("%d%d", &n, &k);
     
    static int a[N];
    for (int i = 0; i < n; ++i)
        scanf("%d", a + i);
         
    a[n++] = 0;
    sort(a, a + n);
  
    static ll dp[N], newdp[N];
    fill(dp, dp + n, INFL);
    dp[0] = 0;
  
    ll ans = INFL;
    CHT cht;
  
    for (int x = 1; x <= min(n, 2030); ++x) {
        fill(newdp, newdp + n, INFL);
        cht.clear();
        for (int i = 1; i < n; ++i) {
            if (dp[i - 1] < INFL)
                cht.add_line(i - 1, -dp[i - 1]);
            if (i >= x) {
                newdp[i] = -cht.eval(a[i] + (ll)k * x) + (a[i] + (ll)k * x) * i;
                newdp[i] = min(newdp[i], INFL);
            }
        }
        copy(newdp, newdp + n, dp);
        ans = min(ans, dp[n - 1]);
    }
  
    cout << ans << '\n';
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
