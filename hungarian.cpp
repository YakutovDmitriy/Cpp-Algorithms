#include <cstdio>
#include <algorithm>

int const N = 333;
int const INF = 1e9;

int a[N][N];
int from[N];
int mi[N], pos[N];
int dx[N], dy[N];
int px[N], py[N];
bool ux[N], uy[N];

int main() {
    freopen("assignment.in", "r", stdin);
    freopen("assignment.out", "w", stdout);
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) scanf("%d", a[i] + j);
    std::fill(px, px + n, -1);
    std::fill(py, py + n, -1);
    for (int row = 0; row < n; ++row) {
        int x1 = row;
        int x0 = -1, y0 = -1;
        std::fill(mi, mi + n, INF);
        std::fill(ux, ux + n, false);
        std::fill(uy, uy + n, false);
        while (x1 >= 0) {
            ux[x1] = true;
            int delta = INF;
            for (int y = 0; y < n; ++y) {
                int val = a[x1][y] + dx[x1] + dy[y];
                if (val < mi[y]) {
                    mi[y] = val;
                    pos[y] = x1;
                }
                if (!uy[y] && mi[y] < delta) {
                    delta = mi[y];
                    x0 = pos[y];
                    y0 = y;
                }
            }
            for (int t = 0; t < n; ++t) {
                if (ux[t]) dx[t] -= delta;
                if (uy[t]) dy[t] += delta;
                if (!uy[t]) mi[t] -= delta;
            }
            from[y0] = x0;
            uy[y0] = true;
            x1 = py[y0];
        }
        while (y0 >= 0) {
            x0 = from[y0];
            int newy0 = px[x0];
            px[x0] = y0;
            py[y0] = x0;
            y0 = newy0;
        }
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) ans += a[i][px[i]];
    printf("%d\n", ans);
    for (int i = 0; i < n; ++i) printf("%d %d\n", i + 1, px[i] + 1);
}