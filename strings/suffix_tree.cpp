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

int const N = 300300;
int const A = 13;

int from[N], to[N], par[N], next[N][A], sz, root;

void build_tree(int *a, int n) {
    static int len[N], end[N];
    static auto const get_state = [&](int lnk, int ln, int lst) {
        par[sz] = lnk;
        len[sz] = ln;
        end[sz] = lst;
        fill(next[sz], next[sz] + A, -1);
        return sz++;
    };
    sz = 0;
    root = get_state(-1, 0, -1);
    int v = root;
    for (int i = n - 1; i >= 0; --i) {
        int cur = get_state(root, len[v] + 1, len[v] + 1);
        while (v != -1 && next[v][a[i]] < 0) {
            next[v][a[i]] = cur;
            v = par[v];
        }
        if (v >= 0) {
            int u = next[v][a[i]];
            if (len[v] + 1 == len[u]) {
                par[cur] = u;
            } else {
                int w = sz++;
                par[w] = par[u];
                len[w] = len[v] + 1;
                end[w] = end[u];
                copy(next[u], next[u] + A, next[w]);
                while (v != -1 && next[v][a[i]] == u) {
                    next[v][a[i]] = w;
                    v = par[v];
                }
                par[u] = w;
                par[cur] = w;
            }
        }
        v = cur;
    }
    for (int i = 0; i < sz; ++i) {
        fill(next[i], next[i] + A, -1);
    }
    from[root] = to[root] = 0;
    for (int v = 0; v < sz; ++v) {
        if (v != root) {
            from[v] = n - end[v] + len[par[v]];
            to[v] = n - end[v] + len[v];
            next[par[v]][a[from[v]]] = v;
        }
    }
}

struct Ans {
    long long ref;
    int l, r;
};

bool operator<(Ans const &a, Ans const &b) {
    return a.ref < b.ref;
}

pair<Ans, int> dfs(int v, int depth, int n) {
    Ans ans = {-1LL, -1, -1};
    int under = 0;
    for (int x = 0; x < A; ++x) {
        int u = next[v][x];
        if (u >= 0) {
            auto cur = dfs(u, depth + to[u] - from[u], n);
            ans = max(ans, cur.first);
            under += cur.second;
        }
    }
    if (under == 0)
        ++under;
    Ans cur = {(long long) under * depth, to[v] - depth, to[v]};
    if (cur.r > n) {
        cur.ref -= under * (cur.r - n);
        cur.r = n;
    }
    ans = max(ans, cur);
    return {ans, under};
}


void solve() {
    int n, m;
    scanf("%d%d", &n, &m);
    static int a[N];
    for (int i = 0; i < n; ++i)
        scanf("%d", a + i);
    a[n] = 0;
    build_tree(a, n + 1);
    Ans ans = dfs(root, 0, n).first;
    cout << ans.ref << '\n';
    cout << ans.r - ans.l << '\n';
    for (int i = ans.l; i < ans.r; ++i)
        cout << a[i] << ' ';
    cout << '\n';
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
