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

void split_info(Node* v, int info, Node*& l, Node*& r) {
    if (!v) {
        l = r = NULL;
        return;
    }
    push(v);
    if (v->info >= info) {
        split_info(v->l, info, l, v->l);
        update(v);
        r = v;
    } else {
        split_info(v->r, info, v->r, r);
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

Node* leftmost(Node* v) {
    while (v && v->l) {
        v = v->l;
    }
    return v;
}

Node* rightmost(Node* v) {
    while (v && v->r) {
        v = v->r;
    }
    return v;
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
    
    solve();
    
#ifdef LOCAL
    cerr << "time: " << (ll) clock() * 1000 / CLOCKS_PER_SEC << " ms" << endl;
#endif
}