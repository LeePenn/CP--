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
const int N = 50000 + 5;
int T, n, m;
struct Edge {
    int v, nxt;
}edge[N << 1];
int hd[N], tot;
int in[N], rt, num, st[N], ed[N];
int task[N << 2], lazy[N << 2];

void add_edge(int u, int v) {
    edge[++tot] = (Edge){v, hd[u]};
    hd[u] = tot;
}

void Dfs(int u, int pa) {
    st[u] = ++num;
    for (int i = hd[u]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        if (v == pa) continue;
        Dfs(v, u);
    }
    ed[u] = num;
}

void Init() {
    tot = 0;
    memset(hd, 0, sizeof(hd));
    memset(in, 0, sizeof(in));
    memset(st, 0, sizeof(st));
    memset(ed, 0, sizeof(ed));
    memset(task, -1, sizeof(task));
    memset(lazy, -1, sizeof(lazy));
    num = 0;
}

void PushDown(int u, int l, int r) {
    if (lazy[u] != -1) {
        task[u << 1] = task[u << 1 | 1] = lazy[u];
        lazy[u << 1] = lazy[u << 1 | 1] = lazy[u];
        lazy[u] = -1;
    }
}

void Update(int u, int l, int r, int li, int ri, int v) {
    if (l >= li && r <= ri) {
        task[u] = v;
        lazy[u] = v;
        return;
    }
    PushDown(u, l, r);
    int mid = (l + r) >> 1;
    if (mid >= li) Update(u << 1, l, mid, li, ri, v);
    if (mid < ri) Update(u << 1 | 1, mid + 1, r, li, ri, v);
}

int Query(int u, int l, int r, int x) {
    if (l == r && l == x) {
        // printf("in\n");
        return task[u];
    }
    // printf("out %d %d %d\n", l, r, x);
    PushDown(u, l, r);
    int mid = (l + r) >> 1;
    if (mid >= x) return Query(u << 1, l, mid, x);
    if (mid < x) return Query(u << 1 | 1, mid + 1, r, x);
    return -1;
}

int main() {
    // POJ 上有时 scanf 比 cin 慢 = =！！
    ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    scanf("%d", &T);
    int kase;
    int u, v;
    char op;
    for (kase = 1; kase <= T; ++kase) {
        printf("Case #%d:\n", kase);
        scanf("%d", &n);
        Init();
        
        for (int i = 1; i < n; ++i) {
            scanf("%d%d", &u, &v);
            add_edge(v, u);
            in[u]++;
        }
        rt = -1;
        for (int i = 1; i <= n; ++i) {
            if (in[i] == 0) {
                rt = i; break;
            }
        }
        Dfs(rt, -1);
        // for (int i = 1; i <= n; ++i) {
        //     printf("! %d %d %d\n", i, st[i], ed[i]);
        // }
        // exit(0);
        
        
        scanf("%d", &m);
        getchar();
        for (int i = 1; i <= m; ++i) {
            op = getchar();
            if (op == 'T') {
                scanf("%d%d", &u, &v);
                Update(1, 1, n, st[u], ed[u], v);
                // for (int i = 1; i <= n; ++i) {
                //     printf("! %d %d\n", i, Query(1, 1, n, st[i]));
                // }
            } else if (op == 'C') {
                scanf("%d", &u);
                printf("%d\n", Query(1, 1, n, st[u]));
            }
            getchar();
        }
    }
    
    
    return 0;
}
