#include <cstdio>
#include <algorithm>

int const N = 100100;
int const A = 30;

int a[N];
int sa[N];

void buildSA(int n) {
	static int start[N];
	static int color[N], newcolor[N];
	static int newsa[N];
	std::fill(start, start + A, 0);
	for (int i = 0; i < n; ++i) ++start[1 + a[i]];
	for (int i = 1; i < A; ++i) start[i] += start[i - 1];
	for (int i = 0; i < n; ++i) sa[start[a[i]]++] = i;
	std::fill(start, start + A, 0);
	for (int i = 0; i < n; ++i) ++start[1 + a[i]];
	for (int i = 1; i < A; ++i) start[i] += start[i - 1];
	std::copy(a, a + n, color);
	for (int half = 1; half < n; half *= 2) {
		for (int i = 0; i < n; ++i) {
			sa[i] -= half;
			if (sa[i] < 0) sa[i] += n;
		}
		for (int i = 0; i < n; ++i) {
			newsa[start[color[sa[i]]]++] = sa[i];
		}
		int last = 0;
		newcolor[newsa[0]] = 0;
		start[0] = 0;
		for (int i = 0; i < n - 1; ++i) {
			int j = i + 1;
			int x = newsa[i] + half;
			if (x >= n) x -= n;
			int y = newsa[j] + half;
			if (y >= n) y -= n;
			if (color[newsa[i]] != color[newsa[j]] || color[x] != color[y]) {
				start[++last] = j;
			}
			newcolor[newsa[j]] = last;
		}
		std::copy(newsa, newsa + n, sa);
		std::copy(newcolor, newcolor + n, color);
	}
}

int lcp[N];

void buildLCP(int n) {
	static int where[N];
	for (int i = 0; i < n; ++i) {
		where[sa[i]] = i;
	}
	int last = 0;
	for (int i = 0; i < n; ++i) {
		int x = where[i];
		if (x == n - 1) {
			last = 0;
			continue;
		}
		if (last > 0) {
			--last;
		}
		int j = sa[x + 1];
		while (a[i + last] == a[j + last]) {
			++last;
		}
		lcp[x] = last;
	}
}

int pr[N], l[N], r[N], next[N][A];
int sz;

int getNode(int pr1, int l1, int r1) {
	pr[sz] = pr1;
	l[sz] = l1;
	r[sz] = r1;
	std::fill(next[sz], next[sz] + A, -1);
	return sz++;
}

int split(int v, int x, int len) {
	int u = next[v][x];
	int mid = getNode(v, l[u], l[u] + len);
	next[v][x] = mid;
	l[u] += len;
	pr[u] = mid;
	next[mid][a[l[u]]] = u;
	return mid;
}

void addPrefix(int n, int start, int len) {
	printf("add prefix %d, lcp = %d\n", start, len);
	static int v = 0, depth = 0;
	while (depth > len) {
		printf("  up %d -> %d, depth = %d, len = %d\n", v, pr[v], depth, len);
		depth -= r[v] - l[v];
		v = pr[v];
	}
	if (len > depth) {
		int spl = split(v, a[start + depth], len - depth);
		printf("  split down %d -> %d, string %d %d\n", v, spl, l[spl], r[spl]);
		v = spl;
		depth += r[v] - l[v];
	}
	if (start + len < n) {
		int to = getNode(v, start + len, n);
		next[v][a[start + len]] = to;
		printf("  new down %d -> %d string %d %d\n", v, to, l[to], r[to]);
		v = to;
		depth += r[v] - l[v];
	}
	printf("end adding: v = %d, depth = %d\n", v, depth);
}

#include <string>

char s[N];

void dfs(int v) {
	for (int c = 0; c < A; ++c) {
		if (next[v][c] >= 0) {
			int to = next[v][c];
			printf("edge from %d to %d by %d, string = %s\n", v, to, c, std::string(s + l[to], s + r[to]).data());
			dfs(to);
		}
	}
}

int main() {
	gets(s);
	int n;
	for (n = 0; s[n]; ++n) {
		a[n] = s[n] - 'a' + 1;
	}
	a[n] = 0;
	buildSA(n + 1);
	buildLCP(n + 1);
	sz = 0;
	int root = getNode(-1, 0, 0);
	for (int i = 0; i < n; ++i) {
		addPrefix(n, sa[i + 1], lcp[i]);
	}
	dfs(root);
}