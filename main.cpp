#include <stdio.h>
#include <iostream>
#include <stack>
#include <complex>
#include <vector>
#include <cstring>
#include <map>
#include <algorithm>
#include <queue>
#include <set>

// #define mytest

using namespace std;
typedef long long LL;
const int N = 30000 + 5, M = 1e6 + 5, INF = 1000000000;
int n;
struct Edge {
    int v, nxt;
}edge[M];
int hd[N], tot;
int father[N], son[N], dep[N], sz[N], top[N], seg[N], rev[N];
int val[N];
int sum[M], Max[M], Sum, Maxx, m;

void add_edge(int u, int v) {
    edge[++tot] = {v, hd[u]};
    hd[u] = tot;
}

void Dfs1(int u, int fa) {
    father[u] = fa;
    dep[u] = dep[fa] + 1;
    sz[u] = 1;
    for (int i = hd[u]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        if (v == fa) continue;
        Dfs1(v, u);
        if (sz[v] > sz[son[u]]) son[u] = v;
        sz[u] += sz[v];
    }
}

void Dfs2(int u, int fa) {
    if (son[u]) {
        seg[son[u]] = ++seg[0];
        rev[seg[0]] = son[u];
        top[son[u]] = top[u];
        Dfs2(son[u], u);
    }
    
    for (int i = hd[u]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        if (v == fa) continue;
        if (!top[v]) {
            seg[v] = ++seg[0];
            rev[seg[0]] = v;
            top[v] = v;
            Dfs2(v, u);
        }
    }
}

void PushUp(int u) {
    sum[u] = sum[u << 1] + sum[u << 1 | 1];
    Max[u] = max(Max[u << 1], Max[u << 1 | 1]);
}

void Build(int u, int l, int r) {
    if (l == r) {
        sum[u] = Max[u] = val[rev[l]];
        return;
    }
    int mid = (l + r) >> 1;
    Build(u << 1, l, mid);
    Build(u << 1 | 1, mid + 1, r);
    PushUp(u);
}

void Update(int u, int l, int r, int pos, int v) {
    if ()
}

void Solve() {
    scanf("%d", &m);
    char op[10];
    int u, v;
    for (int i = 1; i <= m; ++i) {
        scanf("%s", op + 1);
        scanf("%d%d", &u, &v);
        if (op[1] == 'C') {
            Update(1, 1, seg[0], seg[u], v);
        } else {
        
        }
    }
}

int main() {
    // POJ 上有时 scanf 比 cin 慢 = =！！
    ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    scanf("%d", &n);
    int u, v;
    for (int i = 1; i < n; ++i) {
        scanf("%d%d", &u, &v);
        add_edge(u, v); add_edge(v, u);
    }
    
    for (int i = 1; i <= n; ++i) scanf("%d", &val[i]);
    Dfs1(1, 0);
    seg[0] = seg[1] = top[1] = rev[1] = 1;
    Dfs2(1, 0);
    Build(1, 1, seg[0]);
    
    Solve();
    
    return 0;
}
