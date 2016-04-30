#include <cstdio>
#include <vector>

int const N = 1100100;

std::vector<int> e[N];
int cnt[N];
bool wasC[N];

void makeRoot(int v, int pr) {
	cnt[v] = 1;
	for (int to : e[v]) {
		if (to != pr && !wasC[to]) {
			makeRoot(to, v);
			cnt[v] += cnt[to];
		}
	}
}

int getCentroid(int v, int pr, int size) {
	for (int to : e[v]) {
		if (!wasC[to] && to != pr && cnt[to] * 2 > size) {
			return getCentroid(to, v, size);
		}
	}
	return v;
}

void solve(int v, int size) {
	v = getCentroid(v, -1, size);
	wasC[v] = true;
	makeRoot(v, -1);
	for (int to : e[v]) {
		if (!wasC[to]) {
			solve(to, cnt[to]);
		}
	}
}

int main() {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n - 1; ++i) {
		int a, b;
		scanf("%d%d", &a, &b);
		--a, --b;
		e[a].push_back(b);
		e[b].push_back(a);
	}
	makeRoot(0, -1);
	solve(0, n);
}