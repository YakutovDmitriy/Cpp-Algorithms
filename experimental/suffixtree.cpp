#include <cstdio>
#include <algorithm>
#include <cstring>

int const N = 200200;
int const A = 26;

int next[N][A], link[N], len[N], pos[N], sz;

int getNode(int len_, int link_, int pos_) {
    std::fill(next[sz], next[sz] + A, -1);
    len[sz] = len_;
    link[sz] = link_;
    pos[sz] = pos_;
    return sz++;
}

char s[N];
int l[N], r[N];

int main() {
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    gets(s);
    int n = strlen(s);
    int last = getNode(0, -1, -1);
    for (int i = n - 1; i >= 0; --i) {
        int x = s[i] - 'a';
        int now = getNode(len[last] + 1, 0, len[last] + 1);
        while (last >= 0 && next[last][x] < 0) {
            next[last][x] = now;
            last = link[last];
        }
        if (last >= 0) {
            int u = next[last][x];
            if (len[u] == len[last] + 1) {
                link[now] = u;
            } else {
                int s = getNode(len[last] + 1, link[u], pos[u]);
                std::copy(next[u], next[u] + A, next[s]);
                while (last >= 0 && next[last][x] == u) {
                    next[last][x] = s;
                    last = link[last];
                }
                link[u] = s;
                link[now] = s;
            }
        }
        last = now;
    }
    for (int v = 1; v < sz; ++v) {
        int p = link[v];
        l[v] = n - pos[v] + len[p];
        r[v] = n - pos[v] + len[v];
    }
    printf("%d %d\n", sz, sz - 1);
    for (int v = 1; v < sz; ++v) {
        printf("%d %d %d %d\n", link[v] + 1, v + 1, l[v] + 1, r[v]);
    }
}
