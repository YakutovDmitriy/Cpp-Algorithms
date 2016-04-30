#include <cstdio>

int const N = 100100;
int const A = 30;

int next[N][A], link[N], len[N], a[N];
int sz;

int node(int _link, int _len) {
	link[sz] = _link;
	len[sz] = _len;
	return sz++;
}

int go(int v, int ind) {
	while (a[ind] != a[ind - len[v] - 1]) {
		v = link[v];
	}
	return v;
}

char s[N];

int main() {
	s[0] = 'a' + A - 1;
	gets(s + 1);
	for (int i = 0; s[i]; ++i) {
		a[i] = s[i] - 'a';
	}
	node(1, 0); /// even empty
	node(0, -1); /// odd empty
	int last = 0;
	for (int i = 1; s[i]; ++i) {
		int x = a[i];
		last = go(last, i);
		if (!next[last][x]) {
			int _link = go(link[last], i);
			next[last][x] = node(next[_link][x], len[last] + 2);
		}
		last = next[last][x];
		printf("%d ", sz - 2);
	}
}