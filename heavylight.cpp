#include <bits/stdc++.h>

#if (_WIN32 || __WIN32__)
#  define LLD "%I64d"
#else
#  define LLD "%lld"
#endif

using std::istream; using std::ostream; using std::fixed; using std::greater;
using std::tuple; using std::tie; using std::make_pair; using std::multiset;
using std::nth_element; using std::min_element; using std::max_element;
using std::vector; using std::set; using std::map; using std::string;
using std::fill; using std::copy; using std::sort; using std::unique;
using std::unordered_set; using std::unordered_map; using std::pair;
using std::next_permutation; using std::reverse; using std::rotate;
using std::cin; using std::cout; using std::cerr; using std::endl;
using std::lower_bound; using std::upper_bound; using std::deque;
using std::min; using std::max; using std::swap; using std::abs;
using std::priority_queue; using std::queue; using std::bitset;
using std::make_tuple; using std::iota;

typedef long long ll;
typedef long double ld;

ll rnd(ll x, ll y) { static auto gen = std::bind(std::uniform_int_distribution<ll>(), std::mt19937(960172)); return gen() % (y - x + 1) + x; }
ll gcd(ll a, ll b) { while (b > 0) { ll t = a % b; a = b; b = t; } return a; }
template<typename T> T sqr(T const& a) { return a * a; }

int const INF = 100 + (int) 1e9;
ll const INFL = 100 + (ll) 1e18;
ld const PI = 3.1415926535897932384626433832795028;


namespace hld {

	int const N = 100100;
	int const LG = 18;
	
	vector<int> g[N];
	int root_of[N];
	vector<int> chain[N]; /// chain[v] -- chain with root v
	int iic[N]; /// index_in_chain[v] = 0 if v is root
	int under[N];
	int depth[N];
	int anc[LG][N];
	
	void precalc(int v, int prev) {
		anc[0][v] = prev;
		for (int i = 1; i < LG; ++i) {
			anc[i][v] = anc[i - 1][v] == -1 ? -1 : anc[i - 1][anc[i - 1][v]];
		}
		under[v] = 1;
		for (int to : g[v]) {
			if (to != prev) {
				depth[to] = depth[v] + 1;
				precalc(to, v);
				under[v] += under[to];
			}
		}
	}
	
	int go_up(int a, int del) {
		if (del <= 0) {
			return a;
		}
		for (int i = 0; i < LG; ++i) {
			if (del & 1) {
				a = anc[i][a];
			}
			del >>= 1;
		}
		return a;
	}
	
	int get_lca(int a, int b) {
		a = go_up(a, depth[a] - depth[b]);
		b = go_up(b, depth[b] - depth[a]);
		if (a == b) {
			return a;
		}
		for (int i = LG - 1; i >= 0; --i) {
			if (anc[i][a] != anc[i][b]) {
				a = anc[i][a];
				b = anc[i][b];
			}
		}
		return anc[0][a];
	}
	
	void dfs(int v) {
		int x = -1;
		for (int to : g[v]) {
			if (to != anc[0][v] && (x < 0 || under[x] < under[to])) {
				x = to;
			}
		}
		for (int to : g[v]) {
			if (to != anc[0][v]) {
				root_of[to] = to == x ? root_of[v] : to;
				iic[to] = chain[root_of[to]].size();
				chain[root_of[to]].push_back(to);
				dfs(to);
			}
		}
	}
	
	vector<int> sgt[N];
	
	void build(int root) {
		depth[root] = 0;
		precalc(root, -1);	
		root_of[root] = root;
		iic[root] = 0;
		chain[root].push_back(root);
		dfs(root);
		int n = under[root];
		for (int i = 0; i < n; ++i) {
			sgt[i] = vector<int>(4 * chain[i].size());
		}
	}
	
	void _add(int i, int v, int l, int r, int pos, int val) {
		if (r - l == 1) {
			sgt[i][v] += val;
		} else {
			int m = (l + r) / 2;
			if (pos < m) {
				_add(i, 2 * v + 1, l, m, pos, val);
			} else {
				_add(i, 2 * v + 2, m, r, pos, val);
			}
			sgt[i][v] = max(sgt[i][2 * v + 1], sgt[i][2 * v + 2]);
		}
	}
	
	void add(int v, int x) {
		int rt = root_of[v];
		_add(rt, 0, 0, chain[rt].size(), iic[v], x);
	}
	
	int _max(int i, int v, int l, int r, int from, int to) {
		if (r <= from || to <= l) {
			return -INF;
		}
		if (from <= l && r <= to) {
			return sgt[i][v];
		}
		int m = (l + r) / 2;
		return max(_max(i, 2 * v + 1, l, m, from, to),
				_max(i, 2 * v + 2, m, r, from, to));
	}
	
	int get_up_max(int v, int p) {
		int ret = 0;
		int prt = root_of[p];
		while (v >= 0 && depth[v] >= depth[p]) {
			int rt = root_of[v];
			int from = rt == prt ? iic[p] : 0;
			int to = iic[v] + 1;
			ret = max(ret, _max(rt, 0, 0, chain[rt].size(), from, to));
			v = anc[0][rt];
		}
		return ret;
	}
	
	int get_max(int a, int b) {
		int lca = get_lca(a, b);
		return max(get_up_max(a, lca), get_up_max(b, lca));
	}

};


void solve() {
	
	int n;
	scanf("%d", &n);
	
	for (int i = 0; i < n - 1; ++i) {
		int a, b;
		scanf("%d%d", &a, &b);
		--a, --b;
		hld::g[a].push_back(b);
		hld::g[b].push_back(a);
	}
	
	hld::build(0);

	int q;
	scanf("%d", &q);
	
	while (q--) {
		char type;
		int a, b;
		scanf(" %c%d%d", &type, &a, &b);
		--a;
		if (type == 'I') {
			hld::add(a, b);
		} else {
			--b;
			printf("%d\n", hld::get_max(a, b));
		}
	}
	
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