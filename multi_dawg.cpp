#include <bits/stdc++.h>
//#include <fcntl.h>

using std::max; using std::swap; using std::abs; using std::priority_queue; using std::queue; using std::bitset; using std::make_tuple; 
using std::istream; using std::ostream; using std::fixed; using std::greater; using std::tuple; using std::tie; using std::make_pair;
using std::cout; using std::cerr; using std::endl; using std::lower_bound; using std::upper_bound; using std::deque; using std::min; 
using std::map; using std::string; using std::fill; using std::copy; using std::sort; using std::unique; using std::unordered_set; 
using std::multiset; using std::nth_element; using std::min_element; using std::max_element; using std::vector; using std::set; 
using std::unordered_map; using std::pair; using std::next_permutation; using std::reverse; using std::rotate; using std::cin; 
using std::iota; using std::function; using std::shuffle;

typedef long long ll;
typedef long double ld;
typedef unsigned int uint;
typedef unsigned long long ull;

int const INF = 100 + (int) 1e9;
ll const INFL = 100 + (ll) 1e18;
ld const PI = 3.141592653589793238462643L;
std::mt19937 mt19937(960172);

ll rnd(ll x, ll y) { static auto gen = std::bind(std::uniform_int_distribution<ll>(), mt19937); return gen() % (y - x + 1) + x; }
ll gcd(ll a, ll b) { while (b > 0) { ll t = a % b; a = b; b = t; } return a; }
ll sqr(int a) { return (ll) a * a; } ld sqr(ld a) { return a * a; } ll sqr(ll a) { return a * a; }

int const N = 200200;
int const A = 28;

int link[N], len[N], next[N][A], sz;

int get_node(int len, int link) {
    ::len[sz] = len;
    ::link[sz] = link;
    fill(next[sz], next[sz] + A, -1);
    return sz++;
}

int copy_node(int v, int len) {
    ::len[sz] = len;
    link[sz] = link[v];
    copy(next[v], next[v] + A, next[sz]);
    return sz++;
}

int append(int v, int x) {
    if (next[v][x] >= 0) {
        int u = next[v][x];
        if (len[v] + 1 != len[u]) {
            int w = copy_node(u, len[v] + 1);
            while (v >= 0 && next[v][x] == u) {
                next[v][x] = w;
                v = link[v];
            }
            link[u] = w;
            return w;
        }
        return u;
    }
    int now = get_node(len[v] + 1, 0);
    while (v >= 0 && next[v][x] < 0) {
        next[v][x] = now;
        v = link[v];
    }
    if (v >= 0) {
        int u = next[v][x];
        if (len[v] + 1 == len[u]) {
            link[now] = u;
        } else {
            int w = copy_node(u, len[v] + 1);
            while (v >= 0 && next[v][x] == u) {
                next[v][x] = w;
                v = link[v];
            }
            link[u] = w;
            link[now] = w;            
        }
    }
    return now;
}

void solve() {
    int n;
    scanf("%d ", &n);
    
    get_node(0, -1);

    for (int i = 0; i < n; ++i) {
        static char s[N];
        gets(s);
        int v = 0;
        for (int j = 0; s[j]; ++j) {
            int x = s[j] - 'a';
            v = append(v, x);
        }
    }
}



int main() {
    
    //freopen("", "r", stdin);
    //freopen("", "w", stdout);
    
    cout.precision(15);
    cout << fixed;
    cerr.precision(6);
    cerr << fixed;
    
    solve();
    
#ifdef LOCAL
    cerr << "time: " << (ll) clock() * 1000 / CLOCKS_PER_SEC << " ms" << endl;
#endif
}