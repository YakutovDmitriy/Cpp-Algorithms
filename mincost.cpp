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

int const N = 3333;

struct edge_t {
    int to, cap, flow, cost;
    
    edge_t() {}
    
    edge_t(int to, int cap, int cost) :
        to(to), cap(cap), flow(0), cost(cost) {}
};

vector<edge_t> edges;
vector<int> g[N];

void clear_flow() {
    for (auto& e : edges) {
        e.flow = 0;
    }
}

void clear_graph() {
    edges.clear();
    for (int i = 0; i < N; ++i) {
        g[i].clear();
    }
}

void add_edge(int v, int to, int cap, int cost) {
    g[v].push_back(edges.size());
    edges.emplace_back(to, cap, cost);
    g[to].push_back(edges.size());
    edges.emplace_back(v, 0, -cost);
}

pair<ll, int> min_cost_max_flow(int source, int sink, int n) {
    ll cost = 0;
    int flow = 0;
    while (true) {
        static int q[N * N], in_q[N], dist[N], prev[N];
        int tail = 0;
        q[tail++] = source;
        fill(dist, dist + n, INF);
        dist[source] = 0;
        in_q[source] = true;
        for (int head = 0; head < tail; ++head) {
            int v = q[head];
            in_q[v] = false;
            for (int x : g[v]) {
                edge_t const& e = edges[x];
                int to = e.to;
                if (e.flow < e.cap && dist[to] > dist[v] + e.cost) {
                    dist[to] = dist[v] + e.cost;
                    prev[to] = x;
                    if (!in_q[to]) {
                        q[tail++] = to;
                        in_q[to] = true;
                    }
                }
            }
        }
        if (dist[sink] == INF) {
            break;
        }
        int cur_flow = INF;
        for (int v = sink; v != source;) {
            int x = prev[v];
            cur_flow = min(cur_flow, edges[x].cap - edges[x].flow);
            v = edges[x ^ 1].to;
        }
        flow += cur_flow;
        cost += (ll) cur_flow * dist[sink];
        for (int v = sink; v != source;) {
            int x = prev[v];
            edges[x].flow += cur_flow;
            edges[x ^ 1].flow -= cur_flow;
            v = edges[x ^ 1].to;
        }
    }
    return {cost, flow};
}


void solve() {
    static int a[N];
    
    int n;
    scanf("%d", &n);
    
    if (n == 1) {
        cout << 0 << endl;
        return;
    }
    
    for (int i = 0; i < n; ++i) {
        scanf("%d", a + i);
    }
    
    int sz = n + 1;
    int sink = sz++;
    int source = sz++;
    
    add_edge(source, 1, INF, 1);
    add_edge(source, n - 1, INF, 1);
    
    for (int i = 1; i < n; ++i) {
        int d = a[i] - a[i - 1];
        if (d > 1) {
            add_edge(source, i, d - 1, 0);
        } else if (d <= 0) {
            add_edge(i, sink, -d + 1, 0);
        }
    }
    
    for (int i = 1; i < n; ++i) {
        if (i > 1) {
            add_edge(i, i - 1, INF, 1);
        }
        if (i < n - 1) {
            add_edge(i, i + 1, INF, 1);
        }
    }
    
    auto res = min_cost_max_flow(source, sink, sz);
    
    //cerr << "flow = " << res.second << endl;
    
    printf("%I64d\n", res.first);
 
}



int main() {

    cout.precision(15);
    cout << fixed;
    cerr.precision(6);
    cerr << fixed;
    
    solve();

#ifdef LOCAL
    cerr << "time: " << (ll) clock() * 1000 / CLOCKS_PER_SEC << " ms" << endl;
#endif
}