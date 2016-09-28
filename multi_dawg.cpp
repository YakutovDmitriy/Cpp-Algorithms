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

int const NONE = -1;
int const MANY = INF;

int const N = 200200;
int const A = 28;
int const maxCnt = 1010;
int const maxLen = 111;

int link[N], len[N], next[N][A];
int who[N], end[N], sz;

int get_node(int len, int link, int end) {
    ::len[sz] = len;
    ::link[sz] = link;
    ::end[sz] = end;
    who[sz] = NONE;
    fill(next[sz], next[sz] + A, -1);
    return sz++;
}

int copy_node(int v, int len) {
    ::len[sz] = len;
    link[sz] = link[v];
    end[sz] = end[v];
    who[sz] = who[v];
    copy(next[v], next[v] + A, next[sz]);
    return sz++;
}

int append(int v, int x, int i) {
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
    int now = get_node(len[v] + 1, 0, i);
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
    
    static char s[maxCnt][maxLen];

    int n;
    scanf("%d ", &n);
    
    get_node(0, -1, -1);
    
    auto add = [](int& who1, int who2) {
        if (who2 == NONE) {
            return;
        }
        if (who1 == NONE || who1 == who2) {
            who1 = who2;
        } else {
            who1 = MANY;
        }
    };

    for (int i = 0; i < n; ++i) {
        gets(s[i]);
        int v = 0;
        for (int j = 0; s[i][j]; ++j) {
            int x = s[i][j] - 'a';
            v = append(v, x, j);
            add(who[v], i);
        }
    }
    
    static int start[maxLen], ord[N];
    for (int i = 0; i < sz; ++i) {
        ++start[1 + len[i]];
    }
    for (int i = 1; i < maxLen; ++i) {
        start[i] += start[i - 1];
    }
    for (int i = 0; i < sz; ++i) {
        ord[start[len[i]]++] = i;
    }
    
    for (int i = sz - 1; i > 0; --i) {
        int x = ord[i];
        add(who[link[x]], who[x]);
    }
    
    static int from[maxCnt], to[maxCnt];
    for (int i = 0; i < n; ++i) {
        to[i] = strlen(s[i]);
    }
    
    for (int i = 1; i < sz; ++i) {
        int j = who[i];
        if (j != NONE && j != MANY) {
            int cur_len = len[link[i]] + 1;
            if (to[j] - from[j] > cur_len) {
                to[j] = end[i] + 1;
                from[j] = to[j] - cur_len;
            }
        }
    }
    
    for (int i = 0; i < n; ++i) {
        s[i][to[i]] = 0;
        puts(s[i] + from[i]);
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