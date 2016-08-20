#include <algorithm>
#include <cstdio>

int const N = 100500;
int const A = 50;

int saN;
int s[N];
int sa[N];
int start[N];
int newSa[N];
int cl[N];
int newCl[N];
int where[N];
int lcp[20][N];
int deg[N];

void buildSA(int n) {
	saN = n;
	std::fill(start, start + A, 0);
	for (int i = 0; i < n; ++i) ++start[s[i] + 1];
	for (int i = 1; i < A; ++i) start[i] += start[i - 1];
	for (int i = 0; i < n; ++i) sa[start[s[i]]++] = i;
	for (int i = 0; i < n; ++i) --start[s[i]];
	std::copy(s, s + n, cl);
	for (int half = 1; half < n; half *= 2) {
		for (int i = 0; i < n; ++i) {
			int x = sa[i] - half;
			if (x < 0) x += n;
			newSa[start[cl[x]]++] = x;
		}
		newCl[newSa[0]] = 0;
		start[0] = 0;
		int sz = 1;
		for (int i = 0; i + 1 < n; ++i) {
			int j = i + 1;
			int ni = newSa[i] + half;
			if (ni >= n) ni -= n;
			int nj = newSa[j] + half;
			if (nj >= n) nj -= n;
			if (cl[newSa[i]] != cl[newSa[j]] || cl[ni] != cl[nj]) {
				start[sz] = j;
				newCl[newSa[j]] = sz++;
			} else {
				newCl[newSa[j]] = newCl[newSa[i]];
			}
		}
		std::copy(newSa, newSa + n, sa);
		std::copy(newCl, newCl + n, cl);
	}
	for (int i = 0; i < n; ++i) where[sa[i]] = i;
	for (int last = 0, i = 0; i < n; ++i) {
		if (last > 0) --last;
		if (where[i] == n - 1) {
			last = 0;
			continue;
		}
		int j = sa[where[i] + 1];
		while (i + last < n && j + last < n && s[i + last] == s[j + last]) ++last;
		lcp[0][where[i]] = last;
	}
	--n;
	for (int i = 1; (1 << i) <= n; ++i) {	
		int len = 1 << i;
		for (int j = 0; j + len <= n; ++j) {
			lcp[i][j] = std::min(lcp[i - 1][j], lcp[i - 1][j + len / 2]);
		}
	}
	for (int i = 2; i <= n; ++i) deg[i] = deg[i / 2] + 1;
}

int getLCP(int i, int j) {
	if (i == j) return saN - sa[i];
	if (i > j) std::swap(i, j);
	int lb = deg[j - i];
	return std::min(lcp[lb][i], lcp[lb][j - (1 << lb)]);
}

char ss[N];

int main() {
	gets(ss);
	int n;
	for (n = 0; ss[n]; ++n) {
		s[n] = ss[n] - 'a' + 10;
	}
	s[n] = 1;
	buildSA(n + 1);
	for (int i = 0; i < n + 1; ++i) {
		printf("%d\n", sa[i]);
	}
}