#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>

int const N = 111;
int const M = 5555;
long long const INFL = 9223372036854775807LL;
int const INF = 1e9;

struct Edge {
	int to;
	int capacity;
	int flow;
	int cost;
};

Edge edges[M];
std::vector<int> e[N];
long long dist[N];
int edgeTo[N];
long long phi[N];

int main() {
	freopen("mincost.in", "r", stdin);
	freopen("mincost.out", "w", stdout);
	int n, m;
	scanf("%d%d", &n, &m);
	for (int sz = 0, i = 0; i < m; ++i) {
		int from, to, capacity, cost;
		scanf("%d%d%d%d", &from, &to, &capacity, &cost);
		--from, --to;
		e[from].push_back(sz);
		edges[sz++] = {to, capacity, 0, cost};
		e[to].push_back(sz);
		edges[sz++] = {from, 0, 0, -cost};
	}
	int const source = 0;
	int const target = n - 1;
	std::fill(phi, phi + n, INFL);
	phi[source] = 0;
	for (int i = 0; i < n - 1; ++i) {
		for (int v = 0; v < n; ++v) {
			if (phi[v] == INFL) {
				continue;
			}
			for (int i : e[v]) {
				Edge const& edge = edges[i];
				long long now = phi[v] + edge.cost;
				if (edge.capacity > edge.flow && now < phi[edge.to]) {
					phi[edge.to] = now;
				}
			}
		}
	}
	long long cost = 0;
	std::set<std::pair<long long, int>> q;
	while (true) {
		std::fill(edgeTo, edgeTo + n, -1);
		dist[source] = 0;
		edgeTo[source] = M;
		q.clear();
		q.insert({dist[source], source});
		while (!q.empty()) {
			int v = q.begin()->second;
			long long d = phi[v] + dist[v];
			q.erase(q.begin());
			for (int i : e[v]) {
				Edge const& edge = edges[i];
				int to = edge.to;
				long long now = d + edge.cost - phi[to];
				if (edge.capacity > edge.flow && (edgeTo[to] == -1 || now < dist[to])) {
					q.erase({dist[edge.to], edge.to});
					dist[to] = now;
					edgeTo[to] = i;
					q.insert({dist[edge.to], edge.to});
				}
			}
		}
		if (edgeTo[target] == -1) {
			break;
		}
		int add = INF;
		for (int v = target; v != source;) {
			int x = edgeTo[v];
			Edge const& edge = edges[x];
			add = std::min(add, edge.capacity - edge.flow);
			v = edges[x ^ 1].to;
		}
		for (int v = target; v != source;) {
			int x = edgeTo[v];
			Edge& edge = edges[x];
			edge.flow += add;
			edges[x ^ 1].flow -= add;
			cost += (long long) add * edge.cost;
			v = edges[x ^ 1].to;
		}
		for (int i = 0; i < n; ++i) {
			phi[i] += dist[i];
		}
	}
	printf("%I64d\n", cost);
}
