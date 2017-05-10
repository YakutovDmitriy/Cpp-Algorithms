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

int const N = 100100;
int const A = 130;

int go[N][A], link[N];
bool leaf[N];

void solve() {
    static char str[N];
    int n;
    scanf("%d", &n);
    gets(str);
    memset(go, -1, sizeof go);
    int sz = 1;
    for (int i = 0; i < n; ++i) {
        gets(str);
        int v = 0;
        for (int j = 0; str[j]; ++j) {
            int x = str[j];
            if (go[v][x] < 0)
                go[v][x] = sz++;
            v = go[v][x];
        }
        leaf[v] = true;
    }
    static int q[N];
    int tail = 0;
    link[0] = 0;
    for (int x = 0; x < A; ++x) {
        if (go[0][x] >= 0) {
            link[go[0][x]] = 0;
            q[tail++] = go[0][x];
        } else {
            go[0][x] = 0;
        }
    }
    for (int head = 0; head < tail; ++head) {
        int v = q[head];
        leaf[v] |= leaf[link[v]];
        for (int x = 0; x < A; ++x) {
            if (go[v][x] >= 0) {
                link[go[v][x]] = go[link[v]][x];
                q[tail++] = go[v][x];
            } else {
                go[v][x] = go[link[v]][x];
            }
        }
    }
    while (fgets(str, N, stdin)) {
        int v = 0;
        bool ans = false;
        for (int i = 0; str[i] > 31; ++i) {
            int x = str[i];
            v = go[v][x];
            ans |= leaf[v];
        }
        if (ans)
            cout << str;
    }
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
