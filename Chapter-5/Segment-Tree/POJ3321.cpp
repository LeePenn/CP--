#include <stdio.h>
#include <iostream>
#include <stack>
#include <complex>
#include <vector>
#include <cstring>
#include <map>
#include <algorithm>
// #include <queue>

// #define mytest

using namespace std;
typedef long long LL;
const int N = 100000 + 5;
struct Edge {
    int v, nxt;
}edge[N << 1];
int hd[N], tot;
int n, m;
int a[N], tr[N];
int st[N], ed[N], num;

void add_edge(int u, int v) {
    edge[++tot] = {v, hd[u]};
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

int lowbit(int i) {
    return i & (-i);
}

void Update(int u, int v) {
    int idx = n - st[u] + 1;
    while (idx <= n) {
        tr[idx] += v;
        idx += lowbit(idx);
    } 
}

int Query(int u) {
    int ret = 0;
    while (u) {
        ret += tr[u];
        u -= lowbit(u);
    }
    return ret;
}

int getSum(int u) {
    int e = n - st[u] + 1, s = n - ed[u] + 1;
    return Query(e) - Query(s - 1);
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
    Dfs(1, -1);
    for (int i = 1; i <= n; ++i) {
        a[st[i]] ^= 1;
        Update(i, a[st[i]]);
    }
    // for (int i = 1; i <= n; ++i) {
    //     printf("!! %d %d %d\n", st[i], ed[i], getSum(i));
    // }
    // exit(0);
    
    scanf("%d", &m);
    char ch;
    getchar();
    for (int i = 1; i <= m; ++i) {
        ch = getchar();
        scanf("%d", &u);
        if (ch == 'Q') {
            v = getSum(u);
            printf("%d\n", v);
        } else if (ch == 'C') {
            v = a[st[u]] == 1 ? -1 : 1;
            a[st[u]] ^= 1;
            Update(u, v);
        }
        getchar();
    }
    

    return 0;
}
