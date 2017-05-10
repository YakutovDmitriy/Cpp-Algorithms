#include <bits/stdc++.h>
//#include <fcntl.h>

using std::max; using std::swap; using std::abs; using std::priority_queue; using std::queue; using std::bitset; using std::make_tuple; 
using std::istream; using std::ostream; using std::fixed; using std::greater; using std::tuple; using std::tie; using std::make_pair;
using std::cout; using std::cerr; using std::endl; using std::lower_bound; using std::upper_bound; using std::deque; using std::min; 
using std::map; using std::string; using std::fill; using std::copy; using std::sort; using std::unique; using std::unordered_set; 
using std::multiset; using std::nth_element; using std::min_element; using std::max_element; using std::vector; using std::set; 
using std::unordered_map; using std::pair; using std::next_permutation; using std::reverse; using std::rotate; using std::cin; 
using std::iota; using std::function; using std::shuffle; using std::iter_swap;

typedef long long ll;
typedef long double ld;
typedef unsigned int uint;
typedef unsigned long long ull;

int const INF = 100 + (int) 1e9;
ll const INFL = 100 + (ll) 1e18;
ld const PI = 3.141592653589793238462643L;
std::mt19937 mt19937(960172);

ll rnd(ll x, ll y) { static auto gen = std::bind(std::uniform_int_distribution<ll>(), mt19937); return gen() % (y - x + 1) + x; }
bool is_prime(ll x) { if (x <= 1) return 0; for (ll y = 2; y * y <= x; ++y) if (x % y == 0) return 0; return 1; }
ll sqr(int a) { return (ll) a * a; } ld sqr(ld a) { return a * a; } ll sqr(ll a) { return a * a; }
ll gcd(ll a, ll b) { while (b > 0) { ll t = a % b; a = b; b = t; } return a; }


int const N = 200200;

struct edge_t {
    int to, cap, flow;
    
    edge_t(int to, int cap)
        : to(to)
        , cap(cap)
        , flow(0)
    {}
};

vector<edge_t> all;
vector<int> g[N];
int index[N], dist[N];

void add_edge(int from, int to, int cap1, int cap2) {
    g[from].push_back(all.size());
    all.emplace_back(to, cap1);
    g[to].push_back(all.size());
    all.emplace_back(from, cap2);
}

void init_graph(int n) {
    all.clear();
    for (int i = 0; i < n; ++i) {
        g[i].clear();
    }
}

void clear_flow() {
    for (auto& edge : all) {
        edge.flow = 0;
    }
}

int dfs(int v, int sink, int flow) {
    if (v == sink || flow == 0) {
        return flow;
    }
    for (int& i = index[v]; i < (int)g[v].size(); ++i) {
        int x = g[v][i];
        auto& e = all[x];
        int to = e.to;
        int diff = e.cap - e.flow;
        if (diff > 0 && dist[v] - 1 == dist[to]) {
            int now = dfs(to, sink, min(flow, diff));
            if (now > 0) {
                e.flow += now;
                all[x ^ 1].flow -= now;
                return now;
            }
        }
    }
    return 0;
}

ll max_flow(int source, int sink, int n) {
    clear_flow();
    ll ret = 0;
    while (true) {
        static int q[N];
        memset(dist, 63, sizeof(int) * n);
        int tail = 0;
        dist[q[tail++] = sink] = 0;
        for (int i = 0; i < tail; ++i) {
            int v = q[i];
            for (int x : g[v]) {
                int to = all[x].to;
                if (all[x ^ 1].flow < all[x ^ 1].cap && dist[to] > INF) {
                    dist[q[tail++] = to] = dist[v] + 1;
                }
            }
        }
        if (dist[source] > INF) {
            break;
        }
        memset(index, 0, n * sizeof(int));
        while (int flow = dfs(source, sink, INF)) {
            ret += flow;
        }
    }
    return ret;
}



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