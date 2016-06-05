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

ll rnd(ll x, ll y) { static auto gen = std::bind(std::uniform_int_distribution<ll>(), std::mt19937(1510)); return gen() % (y - x + 1) + x; }
ll gcd(ll a, ll b) { while (b > 0) { ll t = a % b; a = b; b = t; } return a; }

int const INF = 100 + (int) 1e9;
ll const INFL = 100 + (ll) 1e18;
ld const PI = 3.1415926535897932384626433832795028;



struct Node {
	int info, sz;
	int prior;
	Node *l, *r, *p;
	
	Node() {}
	
	Node(int info) 
		: info(info), sz(1), prior(rnd(0, INF)), 
		l(NULL), r(NULL), p(NULL) {}
};

int size(Node* v) {
	return v ? v->sz : 0;
}

void update(Node* v) {
	if (v) {
		v->sz = 1 + size(v->l) + size(v->r);
		v->p = NULL;
		if (v->l) v->l->p = v;
		if (v->r) v->r->p = v;
	}
}

void push(Node* v) {

}

Node* merge(Node* a, Node* b) {
	if (!a) return b;
	if (!b) return a;
	if (a->prior > b->prior) {
		push(a);
		a->r = merge(a->r, b);
		update(a);
		return a;
	} else {
		push(b);
		b->l = merge(a, b->l);
		update(b);
		return b;
	}
}

void split_cnt(Node* v, int cnt, Node*& l, Node*& r) {
	if (!v) {
		l = r = NULL;
		return;
	}
	push(v);
	if (size(v->l) >= cnt) {
		split_cnt(v->l, cnt, l, v->l);
		update(v);
		r = v;
	} else {
		split_cnt(v->r, cnt - size(v->l) - 1, v->r, r);
		update(v);
		l = v;
	}
}

Node* root_of(Node* v) {
	while (v && v->p) {
		v = v->p;
	}
	return v;
}




void solve() {
	
	
	
	
	
	
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