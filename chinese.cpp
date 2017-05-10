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

struct Edge {
    int from, to, w, ind;
    
    Edge() {}
    
    Edge(int from, int to, int w, int ind)
        : from(from), to(to), w(w), ind(ind) {}
};

typedef vector<vector<Edge>> Graph;

vector<int> is_root(Graph const& g, int root) {
    int n = g.size();
    vector<int> x(n, -1), q = {root}; 
    x[q[0]] = INF;
    for (int i = 0; i < (int)q.size(); ++i) {
        int v = q[i];
        for (Edge e : g[v]) {
            if (x[e.to] < 0) {
                x[e.to] = e.ind;
                q.push_back(e.to);
            }
        }
    }
    if ((int)q.size() != n) {
        return {};
    }
    x.erase(x.begin() + q[0]);
    return x;
}

void dfs(int v, Graph const& g, vector<int>& order, vector<int>& used) {
    used[v] = 1;
    for (Edge e : g[v]) {
        if (used[e.to] < 0) {
            dfs(e.to, g, order, used);
        }
    }
    order.push_back(v);
}

vector<int> make_colors(Graph const& g) {
    int n = g.size();
    vector<int> order, used(n, -1);
    for (int i = 0; i < n; ++i) {
        if (used[i] < 0) {
            dfs(i, g, order, used);
        }
    }
    reverse(bend(order));
    Graph gt(n);
    for (int i = 0; i < n; ++i) {
        for (Edge e : g[i]) {
            gt[e.to].emplace_back(e.to, i, e.w, e.ind);
        }
    }
    int colors = 0;
    vector<int> color(n, -1);
    fill(bend(used), -1);
    for (int v : order) {
        if (color[v] < 0) {
            vector<int> cur;
            dfs(v, gt, cur, used);
            for (int u : cur) {
                color[u] = colors;
            }
            ++colors;
        }
    }
    return color;
}

vector<int> chinese(Graph const& g, int root) {
    int n = g.size();
    if (n == 1) {
        return {};
    }
    vector<int> mine(n, INF);
    for (int i = 0; i < n; ++i) {
        for (Edge e : g[i]) {
            mine[e.to] = min(mine[e.to], e.w);
        }
    }
    Graph zeros(n);
    for (int i = 0; i < n; ++i) {
        for (Edge e : g[i]) {
            if (e.w == mine[e.to]) {
                zeros[i].push_back(e);
            }
        }
    }

    auto res = is_root(zeros, root);
    if (!res.empty()) {
        return res;
    }
    
    auto color = make_colors(zeros);
    int cnt = *max_element(bend(color)) + 1;
    
    Graph newg(cnt);
    vector<Edge> edges;
    for (int i = 0; i < n; ++i) {
        for (Edge e : g[i]) {
            while ((int)edges.size() <= e.ind)
                edges.emplace_back();
            edges[e.ind] = e;
            if (color[i] != color[e.to])
                newg[color[i]].emplace_back(color[i], color[e.to], e.w - mine[e.to], e.ind);
        }
    }
    
    res = chinese(newg, color[root]);
    
    vector<int> x(n, -1);
    vector<int> q = {root};
    x[q[0]] = INF;
    
    for (int i : res) {
        int v = edges[i].to;
        q.push_back(v);
        x[v] = edges[i].ind;
    }
    
    for (int i = 0; i < (int)q.size(); ++i) {
        int v = q[i];
        int col = color[v];
        for (Edge e : zeros[v]) {
            if (x[e.to] < 0 && color[e.to] == col) {
                x[e.to] = e.ind;
                q.push_back(e.to);
            }
        }
    }
    
    x.erase(x.begin() + q[0]);
    return x;
}

void solve() {
    int n, m;
    scanf("%d%d", &n, &m);
    Graph g(n);
    for (int i = 0; i < m; ++i) {
        int a, b, w;
        scanf("%d%d%d", &a, &b, &w);
        --a, --b;
        g[a].emplace_back(a, b, w, i);
    }
    /// assume that is_root(g, 0) == true
    auto ans = chinese(g, 0);
    cout << ans.size() << '\n';
    for (int x : ans) {
        cout << x + 1 << ' ';
    }
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
