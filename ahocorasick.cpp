#include <cstdio>
#include <algorithm>

int const N = 100100;
int const A = 26;

int next[N][A];
int link[N];
int go[N][A];
int prev[N];
int back[N];
int leaf[N];
int sz;

int getNode(int pr, int edge) {
	std::fill(next[sz], next[sz] + A, -1);
	link[sz] = -1;
	std::fill(go[sz], go[sz] + A, -1);
	prev[sz] = pr;
	back[sz] = edge;
	leaf[sz] = -1;
	return sz++;
}

int getGo(int, int);

int getLink(int v) {
	if (link[v] == -1) {
		if (v == 0 || prev[v] == 0) {
			link[v] = 0;
		} else {
			link[v] = getGo(getLink(prev[v]), back[v]);
		}
	}
	return link[v];
}

int getGo(int v, int x) {
	if (go[v][x] == -1) {
		if (next[v][x] != -1) {
			go[v][x] = next[v][x];
		} else if (v == 0) {
			go[v][x] = v;
		} else{
			go[v][x] = getGo(getLink(v), x);
		}
	}
	return go[v][x];
}	

char buf[N];
bool ans[N];
bool used[N];
int q[N];

int main() {
	freopen("search4.in", "r", stdin);
	freopen("search4.out", "w", stdout);
	int n;
	scanf("%d", &n);
	gets(buf);
	getNode(0, 0);
	for (int i = 0; i < n; ++i) {
		gets(buf);
		int v = 0;
		for (int j = 0; buf[j]; ++j) {
			int x = buf[j] - 'a';
			if (next[v][x] == -1) {
				next[v][x] = getNode(v, x);
			}
			v = next[v][x];
		}
		leaf[v] = i;
	}
	gets(buf);
	int v = 0;
	used[v] = true;
	int tail = 0;
	q[tail++] = v;
	for (int i = 0; buf[i]; ++i) {
		int x = buf[i] - 'a';
		v = getGo(v, x);
		used[v] = true;
		q[tail++] = v;
	}
	for (int head = 0; head < tail; ++head) {
		v = q[head];
		int to = getLink(v);
		if (!used[to]) {
			used[to] = true;
			q[tail++] = to;
		}
	}
	for (int i = 0; i < tail; ++i) {
		int ind = leaf[q[i]];
		if (ind >= 0) {
			ans[ind] = true;
		}
	}
	for (int i = 0; i < n; ++i) {
		puts(ans[i] ? "YES" : "NO");
	}
}