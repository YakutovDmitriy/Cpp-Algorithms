#include <cstdio>
#include <vector>
#include <algorithm>

struct Edge {
	int to, w;
	
	Edge() {}
	
	Edge(int to, int w) :
		to(to), w(w) {}
};

typedef std::vector<std::vector<Edge>> Graph;

void dfs(int v, Graph const& g, std::vector<char>& used, std::vector<int>& order) {
	used[v] = true;
	for (Edge const& e : g[v]) {
		if (!used[e.to]) {
			dfs(e.to, g, used, order);
		}
	}
	order.push_back(v);
}

std::vector<int> condence(Graph const& g) {
	int n = g.size();
	std::vector<char> used(n);
	std::vector<int> order;
	for (int v = 0; v < n; ++v) {
		if (!used[v]) {
			dfs(v, g, used, order);
		}
	}
	std::reverse(order.begin(), order.end());
	std::vector<std::vector<int>> r(n);
	for (int v = 0; v < n; ++v) {
		for (Edge const& e : g[v]) {
			r[e.to].push_back(v);
		}
	}
	std::vector<int> q(n);
	std::vector<int> ret(n);
	int last = 0;
	for (int i : order) {
		if (!ret[i]) {
			ret[i] = ++last;
			int tail = 0;
			q[tail++] = i;
			for (int head = 0; head < tail; ++head) {
				int v = q[head];
				for (int from : r[v]) {
					if (!ret[from]) {
						ret[from] = last;
						q[tail++] = from;
					}
				}
			}
		}
	}
	for (int v = 0; v < n; ++v) {
		--ret[v];
	}
	return ret;
}

bool isRoot(int start, Graph const& g) {
	int n = g.size();
	std::vector<int> q(n);
	std::vector<char> used(n);
	int tail = 0;
	q[tail++] = start;
	used[start] = true;
	for (int head = 0; head < tail; ++head) {
		int v = q[head];
		for (Edge const& e : g[v]) {
			if (!used[e.to]) {
				used[e.to] = true;
				q[tail++] = e.to;
			}
		}
	}
	return tail == n;
}

long long chinese(int root, Graph g) {
	static int const INF = (int)1e9;
	long long ret = 0;
	while (true) {
		int n = g.size();
		std::vector<int> minEdgeTo(n, INF);
		for (int v = 0; v < n; ++v) {
			for (Edge const& e : g[v]) {
				minEdgeTo[e.to] = std::min(minEdgeTo[e.to], e.w);
			}
		}
		for (int v = 0; v < n; ++v) {
			if (v != root) {
				ret += minEdgeTo[v];
			}
		}
		Graph zeros(n);
		for (int v = 0; v < n; ++v) {
			for (Edge const& e : g[v]) {
				if (e.w == minEdgeTo[e.to]) {
					zeros[v].push_back(Edge(e.to, 0));
				}
			}
		}
		if (isRoot(root, zeros)) {
			break;
		}
		std::vector<int> color = condence(zeros);
		int sz = *std::max_element(color.begin(), color.end()) + 1;
		Graph cond(sz);
		for (int v = 0; v < n; ++v) {
			for (Edge const& e : g[v]) {
				int x = color[v];
				int y = color[e.to];
				if (x != y) {
					cond[x].push_back(Edge(y, e.w - minEdgeTo[e.to]));
				}
			}
		}
		root = color[root];
		g = cond;
	}
	return ret;
}

int main() {
	freopen("chinese.in", "r", stdin);
	freopen("chinese.out", "w", stdout);
	int n, m;
	scanf("%d%d", &n, &m);
	Graph g(n);
	for (int i = 0; i < m; ++i) {
		int from, to, w;
		scanf("%d%d%d", &from, &to, &w);
		--from, --to;
		g[from].push_back(Edge(to, w));
	}
	if (isRoot(0, g)) {
		puts("YES");
		printf("%I64d\n", chinese(0, g));
	} else {
		puts("NO");
	}
}