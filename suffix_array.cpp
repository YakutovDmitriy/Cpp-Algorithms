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
bool is_prime(ll x) { if (x <= 1) return 0; for (ll y = 2; y * y <= x; ++y) if (x % y == 0) return 0; return 1; }
ll sqr(int a) { return (ll) a * a; } ld sqr(ld a) { return a * a; } ll sqr(ll a) { return a * a; }
ll gcd(ll a, ll b) { while (b > 0) { ll t = a % b; a = b; b = t; } return a; }


int const A = 30;
int const N = 100100;

int sa_n;
int a[N];
int sa[N];
int where[N];

void build_sa(int n) {
    static int start[N], new_sa[N], cl[N], new_cl[N];
    sa_n = n;
    fill(start, start + A, 0);
    for (int i = 0; i < n; ++i) ++start[a[i] + 1];
    for (int i = 1; i < A; ++i) start[i] += start[i - 1];
    for (int i = 0; i < n; ++i) sa[start[a[i]]++] = i;
    for (int i = 0; i < n; ++i) --start[a[i]];
    copy(a, a + n, cl);
    for (int half = 1; half < n; half *= 2) {
        for (int i = 0; i < n; ++i) {
            int x = sa[i] - half;
            if (x < 0) x += n;
            new_sa[start[cl[x]]++] = x;
        }
        new_cl[new_sa[0]] = 0;
        start[0] = 0;
        int sz = 1;
        for (int i = 0; i + 1 < n; ++i) {
            int j = i + 1;
            int ni = new_sa[i] + half;
            if (ni >= n) ni -= n;
            int nj = new_sa[j] + half;
            if (nj >= n) nj -= n;
            if (cl[new_sa[i]] != cl[new_sa[j]] || cl[ni] != cl[nj]) {
                start[sz++] = j;
            }
            new_cl[new_sa[j]] = sz - 1;
        }
        copy(new_sa, new_sa + n, sa);
        copy(new_cl, new_cl + n, cl);
    }
    for (int i = 0; i < n; ++i) where[sa[i]] = i;
}

int lcp[20][N];
int deg[N];

void kasai() {
    int n = sa_n;
    for (int last = 0, i = 0; i < n; ++i) {
        if (last > 0) --last;
        if (where[i] == n - 1) {
            last = 0;
            continue;
        }
        int j = sa[where[i] + 1];
        while (i + last < n && j + last < n && a[i + last] == a[j + last]) ++last;
        lcp[0][where[i]] = last;
    }
    --n;
    for (int i = 1; (1 << i) <= n; ++i) {   
        int len = 1 << i;
        for (int j = 0; j + len <= n; ++j) {
            lcp[i][j] = min(lcp[i - 1][j], lcp[i - 1][j + len / 2]);
        }
    }
    for (int i = 2; i <= n; ++i) deg[i] = deg[i / 2] + 1;
}

int getLCP(int i, int j) {
    if (i == j) return sa_n - sa[i];
    if (i > j) swap(i, j);
    int lb = deg[j - i];
    return min(lcp[lb][i], lcp[lb][j - (1 << lb)]);
}


char ss[N];

void solve() {
    gets(ss);
    int n;
    for (n = 0; ss[n]; ++n) {
        a[n] = ss[n] - 'a' + 2;
    }
    a[n] = 0;
    build_sa(n + 1);
    kasai();
    for (int i = 0; i < n + 1; ++i) {
        printf("%d\n", sa[i]);
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
