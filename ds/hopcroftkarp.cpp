#include <bits/stdc++.h>
//#include <fcntl.h>
#ifndef LOCAL
#  define cerr __get_ce
#endif

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

int const INF = 100 + (int) 1e9;
ll const INFL = 100 + (ll) 1e18;
ld const PI = 3.141592653589793238462643L;
mt19937 tw(960172);

ll sqr(int a) { return (ll) a * a; } ld sqr(ld a) { return a * a; } ll sqr(ll a) { return a * a; }
bool is_prime(ll x) { for (ll y = 2; y * y <= x; ++y) if (x % y == 0) return 0; return x > 1; }
ll rnd(ll x, ll y) { static uniform_int_distribution<ll> d; return d(tw) % (y - x + 1) + x; }
ll gcd(ll a, ll b) { while (b > 0) { ll t = a % b; a = b; b = t; } return a; }



int const N = 200200;

vector<int> g[N];
int py[N], px[N], dist[N], used[N], ver, ind[N];

int dfs(int v) {
    used[v] = ver;
    for (int& i = ind[v]; i < (int)g[v].size(); ++i) {
        int to = g[v][i];
        int u = px[to];
        if (u < 0 || (used[u] != ver && dist[u] == dist[v] + 1 && dfs(u))) {
            px[to] = v;
            py[v] = to;
            return 1;
        }
    }
    return 0;
}

int matching(int L, int R) {
    fill(py, py + L, -1);
    fill(px, px + R, -1);
    int ret = 0;
    while (true) {
        static int q[N];
        int tail = 0;
        for (int i = 0; i < L; ++i) {
            if (py[i] < 0) {
                dist[q[tail++] = i] = 0;
            } else {
                dist[i] = INF;
            }
        }
        bool was = false;
        for (int head = 0; head < tail; ++head) {
            int v = q[head];
            for (int to : g[v]) {
                int u = px[to];
                if (u < 0) {
                    was = true;
                } else if (dist[u] == INF) {
                    dist[q[tail++] = u] = dist[v] + 1;
                }
            }
        }
        if (!was) {
            break;
        }
        fill(ind, ind + L, 0);
        ++ver;
        for (int i = 0; i < L; ++i) {
            if (py[i] < 0 && used[i] != ver) {
                ret += dfs(i);
            }
        }
    }
    return ret;
}

void solve() {
    int L, R;
    scanf("%d%d", &L, &R);
    for (int i = 0; i < L; ++i) {
        g[i].clear();
    }
    int m;
    scanf("%d", &m);
    for (int i = 0; i < m; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        --a, --b;
        g[b].push_back(a);
    }
    if (matching(R, L) == R) {
        cout << "0\n\n";
        return;
    }
    vector<int> ans;
    for (int i = 1; i <= R; ++i) {
        if (R > L || dist[i - 1] < INF) {
            ans.push_back(i);
        }
    }
    cout << ans.size() << '\n';
    for (int x : ans) {
        cout << x << ' ';
    }
    cout << "\n\n";
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
