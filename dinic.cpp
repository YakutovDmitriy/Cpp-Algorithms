#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>

int const N = 100100;
int const INF = 1e9;

struct Edge {
	int to, cap, flow;
	
	Edge() {}
	
	Edge(int to, int cap) :
		to(to), cap(cap), flow(0) {}
};

std::vector<Edge> all;
std::vector<int> edges[N];

void addEdge(int from, int to, int cap) {
	edges[from].push_back(all.size());
	all.push_back(Edge(to, cap));
	edges[to].push_back(all.size());
	all.push_back(Edge(from, 0));
}

void clearGraph(int n) {
	all.clear();
	for (int i = 0; i < n; ++i) {
		edges[i].clear();
	}
}

void clearFlow() {
	for (auto& edge : all) {
		edge.flow = 0;
	}
}

int index[N];
int dist[N];

int dfs(int v, int target, int flow) {
	if (v == target || flow == 0) {
		return flow;
	}
	for (int& x = index[v]; x < (int)edges[v].size(); ++x) {
		int i = edges[v][x];
		Edge& e = all[i];
		if (e.flow < e.cap && dist[v] + 1 == dist[e.to]) {
			int now = dfs(e.to, target, std::min(flow, e.cap - e.flow));
			if (now > 0) {
				e.flow += now;
				all[i ^ 1].flow -= now;
				return now;
			}
		}
	}
	return 0;
}

long long getFlow(int source, int target, int n) {
	static int q[N];
	long long ret = 0;
	while (true) {
		std::fill(dist, dist + n, INF);
		dist[source] = 0;
		int tail = 0;
		q[tail++] = source;
		for (int i = 0; i < tail; ++i) {
			int v = q[i];
			for (int i : edges[v]) {
				Edge const& e = all[i];
				if (e.flow < e.cap && dist[e.to] == INF) {
					dist[e.to] = dist[v] + 1;
					q[tail++] = e.to;
				}
			}
		}
		if (dist[target] == INF) {
			break;
		}
		std::fill(index, index + n, 0);
		while (int flow = dfs(source, target, INF)) {
			ret += flow;
		}
	}
	return ret;
}

int main() {

}