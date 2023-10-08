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
const int N = 20000 + 5, M = 60000 + 5, INF = 1000000000;
int n, m;
struct Edge {
    int u, v;
}edge[M];
bool del[M];
int rt[N], tot;
int ch[N][2], sz[N], cnt[N], pr[N];
int val[N];
struct Op {
    char c;
    int u, k;
}op[M];
int fa[N];
int opcnt;

void PushUp(int u) {
    sz[u] = sz[ch[u][0]] + sz[ch[u][1]] + cnt[u];
}

void Zig(int &u) {
    int k = ch[u][0];
    ch[u][0] = ch[k][1];
    ch[k][1] = u;
    PushUp(u);
    PushUp(k);
    u = k;
}

void Zag(int &u) {
    int k = ch[u][1];
    ch[u][1] = ch[k][0];
    ch[k][0] = u;
    PushUp(u);
    PushUp(k);
    u = k;
}

void Insert(int &u, int v) {
    if (!u) {
        u = ++tot;
        ch[u][0] = ch[u][1] = 0;
        sz[u] = cnt[u] = 1;
        val[u] = v;
        pr[u] = rand();
        return;
    }
    if (v == val[u]) {
        sz[u]++, cnt[u]++;
        return;
    }
    
    if (v <= val[u]) {
        Insert(ch[u][0], v);
        if (pr[ch[u][0]] > pr[u]) Zig(u);
    } else if (v > val[u]) {
        Insert(ch[u][1], v);
        if (pr[ch[u][1] > pr[u]]) Zag(u);
    }
    PushUp(u);
}

void Init() {
    memset(del, 0, sizeof(del));
    memset(rt, 0, sizeof(rt));
    memset(ch, 0, sizeof(ch));
    memset(sz, 0, sizeof(sz));
    memset(cnt, 0, sizeof(cnt));
    for (int i = 1; i <= n; ++i) {
        fa[i] = i;
    }
}

int FindKthMax(int u, int k) {
    if (!u) return -INF;
    
    if (sz[ch[u][1]] >= k) return FindKthMax(ch[u][1], k);
    if (sz[ch[u][1]] + cnt[u] >= k) return val[u];
    return FindKthMax(ch[u][0], k - cnt[u] - sz[ch[u][1]]);
}

void Del(int &u, int v) {
    if (!u) return;
    
    if (val[u] == v) {
        if (cnt[u] > 1) {
            sz[u]--, cnt[u]--;
            return;
        }
        
        if (!ch[u][0] || !ch[u][1]) {
            u = ch[u][0] + ch[u][1];
        } else if (pr[ch[u][0]] > pr[ch[u][1]]) {
            Zig(u);
            Del(ch[u][1], v);
        } else {
            Zag(u);
            Del(ch[u][0], v);
        }
        PushUp(u);
        return;
    }
    
    if (v <= val[u]) Del(ch[u][0], v);
    else Del(ch[u][1], v);
    if (u) PushUp(u);
}

int Find(int u) {
    if (fa[u] != u) fa[u] = Find(fa[u]);
    return fa[u];
}

void Uni(int u, int v) {
    u = Find(u), v = Find(v);
    if (sz[rt[u]] > sz[rt[v]]) swap(u, v);
    if (u != v) {
        while (1) {
            int cur = FindKthMax(rt[u], 1);
            if (cur == -INF) break;
            Del(rt[u], cur);
            Insert(rt[v], cur);
        }
    }
    fa[u] = v;
    rt[u] = 0;
}

int main() {
    // POJ 上有时 scanf 比 cin 慢 = =！！
    ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    char c;
    int kase = 0;
    while (scanf("%d%d", &n, &m) == 2 && (n + m)) {
        kase++;
        Init();
        for (int i = 1; i <= n; ++i) scanf("%d", &val[i]);
        for (int i = 1; i <= m; ++i) {
            scanf("%d%d", &edge[i].u, &edge[i].v);
        }
        getchar();
        
        opcnt = 0;
        while ((c = getchar()) && isalpha(c)) {
            if (c == 'E') break;
            opcnt++;
            op[opcnt].c = c;
            if (c == 'D') {
                scanf("%d", &op[opcnt].u);
                del[op[opcnt].u] = 1;
            }
            
            if (c == 'Q') {
                scanf("%d%d", &op[opcnt].u, &op[opcnt].k);
            }
            
            if (c == 'C') {
                scanf("%d", &op[opcnt].u);
                int tmp = val[op[opcnt].u];
                op[opcnt].k = tmp;
                scanf("%d", &val[op[opcnt].u]);
            }
            
            getchar();
        }
        
        tot = 0;
        for (int i = 1; i <= n; ++i) {
            Insert(rt[i], val[i]);
        }
        
        // printf("! %d\n", tot);
        // exit(0);
        
        for (int i = 1; i <= m; ++i) {
            if (!del[i]) {
                int u = edge[i].u, v = edge[i].v;
                if (Find(u) != Find(v)) {
                    Uni(u, v);
                }
            }
        }
        
        int t = 0;
        LL ans = 0;
        for (int i = opcnt; i >= 1; --i) {
            if (op[i].c == 'C') {
                int u = op[i].u, k = op[i].k;
                u = Find(op[i].u);
                int cur = val[op[i].u];
                // printf("!! %d\n", cur);
                // exit(0);
                Del(rt[u], cur);
                Insert(rt[u], k);
                val[op[i].u] = k;
            } else if (op[i].c == 'D') {
                int cur = op[i].u;
                int u = edge[cur].u, v = edge[cur].v;
                if (Find(u) != Find(v)) {
                    Uni(u, v);
                }
            } else if (op[i].c == 'Q') {
                t++;
                int u = op[i].u;
                u = Find(u);
                int cur = FindKthMax(rt[u], op[i].k);
                
                if (cur != -INF) ans += cur;
            }
        }
        
        printf("Case %d: %.6f\n", kase, 1.0 * ans / t);
    }
    
    return 0;
}
