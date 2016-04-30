#include <cstdio>
#include <algorithm>

int const N = 1001001;
int const A = 26;

std::string pats[N];
char buf[N];
int link[2 * N];
int len[2 * N];
int next[2 * N][A];
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
		end = std::max(end, i);
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

int main() {
	freopen("search4.in", "r", stdin);
	freopen("search4.out", "w", stdout);
	int n;
	scanf("%d", &n);
	gets(buf);
	for (int i = 0; i < n; ++i) {
		gets(buf);
		pats[i] = std::string(buf);
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