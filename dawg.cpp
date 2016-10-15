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
int const A = 26;
int const SZ = 2 * N + 55;

int link[SZ];
int len[SZ];
int next[SZ][A];
int sz;

int getNode(int le, int li) {
    link[sz] = li;
    len[sz] = le;
    std::fill(next[sz], next[sz] + A, -1);
    return sz++;
}

int append(int last, int x) {
    int now = getNode(len[last] + 1, 0);
    while (last != -1 && next[last][x] == -1) {
        next[last][x] = now;
        last = link[last];
    }
    if (last != -1) {
        int q = next[last][x];
        if (len[last] + 1 == len[q]) {
            link[now] = q;
        } else {
            int clone = getNode(len[last] + 1, link[q]);
            std::copy(next[q], next[q] + A, next[clone]);
            while (last != -1 && next[last][x] == q) {
                next[last][x] = clone;
                last = link[last];
            }
            link[q] = clone;
            link[now] = clone;
        }
    }
    return now;
}

void longestPrefixOfEverySuffixOfSWhichContainedInT() {
    static char s[N];
    static char t[N];
    static int lpt[N];
    gets(s);
    gets(t);
    int last = getNode(0, -1);
    for (int i = 0; t[i]; ++i) {
        int x = t[i] - 'a';
        last = append(last, x);
    }
    int v = 0;
    int end = 0;
    for (int i = 0; s[i]; ++i) {
        end = max(end, i);
        if (v > 0 && len[link[v]] == end - i) {
            v = link[v];
        }
        while (s[end] && next[v][s[end] - 'a'] >= 0) {
            v = next[v][s[end] - 'a'];
            ++end;
        }
        lpt[i] = end - i;
    }
}

void solve() {
    static std::string pats[N];
    static char buf[N];
    int n;
    scanf("%d", &n);
    gets(buf);
    for (int i = 0; i < n; ++i) {
        gets(buf);
        pats[i] = buf;
    }
    gets(buf);
    int last = getNode(0, -1);
    for (int i = 0; buf[i]; ++i) {
        int x = buf[i] - 'a';
        last = append(last, x);
    }
    for (int it = 0; it < n; ++it) {
        bool ans = true;
        int v = 0;
        for (int i = 0; i < (int)pats[it].length(); ++i) {
            int x = pats[it][i] - 'a';
            if (next[v][x] == -1) {
                ans = false;
                break;
            } else {
                v = next[v][x];
            }
        }
        puts(ans ? "YES" : "NO");
    }
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