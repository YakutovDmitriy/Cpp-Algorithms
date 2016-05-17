#include <cstdio>
#include <cstdlib>

struct Node {
	int info, sz;
	int prior;
	Node *l, *r;
	
	Node() {}
	
	Node(int info) 
		: info(info), sz(1), prior(rand() | (rand() << 16)), 
		l(NULL), r(NULL) {}
};

int size(Node* v) {
	return v ? v->sz : 0;
}

void upd(Node* v) {
	if (v) v->sz = 1 + size(v->l) + size(v->r);
}

Node* merge(Node* a, Node* b) {
	if (!a) return b;
	if (!b) return a;
	if (a->prior > b->prior) {
		a->r = merge(a->r, b);
		upd(a);
		return a;
	} else {
		b->l = merge(a, b->l);
		upd(b);
		return b;
	}
}

void split(Node* v, int cnt, Node*& l, Node*& r) {
	if (!v) {
		l = r = NULL;
		return;
	}
	if (size(v->l) >= cnt) {
		split(v->l, cnt, l, v->l);
		upd(v);
		r = v;
	} else {
		split(v->r, cnt - 1 - size(v->l), v->r, r);
		upd(v);
		l = v;
	}
}

int main() {
	freopen("movetofront.in", "r", stdin);
	freopen("movetofront.out", "w", stdout);
	srand(1510);
	Node* v = NULL;
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++i) {
		v = merge(v, new Node(i + 1));
	}
	for (int it = 0; it < m; ++it) {
		int l, r;
		scanf("%d%d", &l, &r);
		--l;
		Node *a, *b, *c;
		split(v, r, b, c);
		split(b, l, a, b);
		v = merge(b, merge(a, c));
	}
	for (int i = 0; i < n; ++i) {
		Node* r;
		split(v, 1, r, v);
		printf("%d ", r->info);
	}
	puts("");
}