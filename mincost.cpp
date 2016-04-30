#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>

int const N = 111;
int const M = 5555;
long long INFL = 9223372036854775807;

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
	for (int i = 0; i < m; ++i) {
		int from, to, capacity, cost;
		scanf("%d%d%d%d", &from, &to, &capacity, &cost);
		--from, --to;
		edges[2 * i] = {to, capacity, 0, cost};
		edges[2 * i + 1] = {from, 0, 0, -cost};
		e[from].push_back(2 * i);
		e[to].push_back(2 * i + 1);
	}
	int const source = 0;
	int const target = n - 1;
	long long cost = 0;
	std::fill(dist, dist + n, INFL);
	std::fill(edgeTo, edgeTo + n, -1);
	dist[source] = 0;
	for (int i = 0; i < n - 1; ++i) {
		for (int v = 0; v < n; ++v) {
			if (dist[v] == INFL) {
				continue;
			}
			for (int i : e[v]) {
				Edge const& edge = edges[i];
				long long now = dist[v] + edge.cost;
				if (edge.capacity > edge.flow && (edgeTo[edge.to] == -1 || now < dist[edge.to])) {
					dist[edge.to] = now;
					edgeTo[edge.to] = i;
				}
			}
		}
	}
	while (true) {
		std::copy(dist, dist + n, phi);
		std::fill(edgeTo, edgeTo + n, -1);
		dist[source] = 0;
		edgeTo[source] = source;
		std::set<std::pair<long long, int>> q;
		q.insert({dist[source], source});
		while (!q.empty()) {
			int v = q.begin()->second;
			if (v == target) {
				break;
			}
			q.erase(q.begin());
			for (int i : e[v]) {
				Edge const& edge = edges[i];
				long long now = phi[v] + dist[v] + edge.cost - phi[edge.to];
				if (edge.capacity > edge.flow && (edgeTo[edge.to] == -1 || now < dist[edge.to])) {
					q.erase({dist[edge.to], edge.to});
					dist[edge.to] = now;
					edgeTo[edge.to] = i;
					q.insert({dist[edge.to], edge.to});
				}
			}
		}
		if (edgeTo[target] == -1) {
			break;
		}
		long long add = INFL;
		for (int v = target; v != source; v = edges[edgeTo[v] ^ 1].to) {
			Edge& edge = edges[edgeTo[v]];
			add = std::min<long long>(add, edge.capacity - edge.flow);
		}
		for (int v = target; v != source; v = edges[edgeTo[v] ^ 1].to) {
			Edge& edge = edges[edgeTo[v]];
			edge.flow += add;
			edges[edgeTo[v] ^ 1].flow -= add;
			cost += add * edge.cost;
		}
	}
	printf("%I64d\n", cost);
}
