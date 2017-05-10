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

typedef pair<int, int> pii;
typedef pair<int, int> ipair;
#define szof(x) ((int)(x).size())
#define bend(x) (x).begin(), (x).end()

int const INF = 100 + (int) 1e9;
ll const INFL = 100 + (ll) 1e18;
ld const PI = 3.141592653589793238462643L;
mt19937 tw(960172);

bool is_prime(ll x) { for (ll y = 2; y * y <= x; ++y) if (x % y == 0) return 0; return x > 1; }
ll rnd(ll x, ll y) { static uniform_int_distribution<ll> d; return d(tw) % (y - x + 1) + x; }
ll sqr(int a) { return (ll) a * a; } template<class T> T sqr(T const& a) { return a * a; }
ll gcd(ll a, ll b) { while (b > 0) { ll t = a % b; a = b; b = t; } return a; }

typedef double ffld;
int const N = 1100100;
int const LOG = 22;

ffld wre[LOG][N], wim[LOG][N];
int bitr[N];

inline void cmul(ffld& x, ffld& y, ffld xx, ffld yy) {
    ffld newx = x * xx - y * yy;
    y = y * xx + yy * x;
    x = newx;
}

void init_fft() {
    for (int logl = 1, len = 2; len < N; ++logl, len *= 2) {
        for (int j = 0; j < len / 2; ++j) {
            ffld ang = 2 * PI * j / len;
            wre[logl][j] = cos(ang);
            wim[logl][j] = sin(ang);
        }
    }
}

void fft(ffld* re, ffld* im, int n, bool inv) {
    for (int i = 0; i < n; ++i) {
        if (i < bitr[i]) {
            swap(re[i], re[bitr[i]]);
            swap(im[i], im[bitr[i]]);
        }
    }
    for (int logl = 1, len = 2; len <= n; ++logl, len *= 2) {
        for (int i = 0; i < n; i += len) {
            for (int j = 0; j < len / 2; ++j) {
                ffld re2 = re[i + j + len / 2], im2 = im[i + j + len / 2];
                cmul(re2, im2, wre[logl][j], (inv ? -wim[logl][j] : wim[logl][j]));
                re[i + j + len / 2] = re[i + j] - re2;
                im[i + j + len / 2] = im[i + j] - im2;
                re[i + j] += re2;
                im[i + j] += im2;
            }
        }
    }
    if (inv) {
        for (int i = 0; i < n; ++i) {
            re[i] /= n;
            im[i] /= n;
        }
    }
}

int mul(int* a, int sa, int* b, int sb, ll* c) {
    int deg = sa + sb - 1;
    int n = 2, logn = 1;
    while (n < deg) {
        n *= 2;
        ++logn;
    }
    bitr[0] = 0;
    for (int i = 1; i < n; ++i) {
        bitr[i] = bitr[i >> 1] >> 1 | ((i & 1) << (logn - 1));
    }
    static ffld are[N], aim[N], bre[N], bim[N];
    copy(a, a + sa, are);
    fill(are + sa, are + n, 0);
    fill(aim, aim + n, 0);
    copy(b, b + sb, bre);
    fill(bre + sb, bre + n, 0);
    fill(bim, bim + n, 0);
    fft(are, aim, n, false);
    fft(bre, bim, n, false);
    for (int i = 0; i < n; ++i) {
        cmul(are[i], aim[i], bre[i], bim[i]);
    }
    fft(are, aim, n, true);
    for (int i = 0; i < deg; ++i) {
        c[i] = (ll)(are[i] + 0.5);
    }
    return deg;
}


void solve() {
    init_fft();

}

int main() {
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
    cerr << "time: " << (ll) clock() * 1000 / CLOCKS_PER_SEC << " ms" << endl;
#endif
}
