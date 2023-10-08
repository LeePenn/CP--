#include <stdio.h>
#include <iostream>
#include <stack>
#include <complex>
#include <vector>
#include <cstring>
#include <algorithm>

// #define mytest

using namespace std;
typedef long long LL;
const int N = 20000 + 5;
int kase, n, m;
struct ST {
    int l, r;
    int post, lazy;
}tr[N << 2];
int x[N], y[N];
int a[N], tot;
int ID[10000010];
bool vis[N];

void PushDown(int u) {
    if (tr[u].lazy) {
        tr[u << 1].post = tr[u].post;
        tr[u << 1 | 1].post = tr[u].post;
        tr[u << 1].lazy = tr[u << 1 | 1].lazy = tr[u].lazy;
        
        tr[u].lazy = 0;
    }
}

void PushUp(int u) {
    if (tr[u << 1].post == tr[u << 1 | 1].post) {
        tr[u].post = tr[u << 1].post;
    } else {
        tr[u].post = 0;
    }
}

void BuildTree(int u, int l, int r) {
    tr[u].l = l;
    tr[u].r = r;
    tr[u].post = 0;
    tr[u].lazy = 0;
    if (l == r) return;
    int mid = (l + r) >> 1;
    BuildTree(u << 1, l, mid);
    BuildTree(u << 1 | 1, mid + 1, r);
}

void Update(int u, int l, int r, int li, int ri, int color) {
    if (r < li || l > ri) return;
    if (l >= li && r <= ri) {
        tr[u].post = color;
        tr[u].lazy = color;
        return;
    }
    PushDown(u);
    int mid = (l + r) >> 1;
    if (mid >= li) Update(u << 1, l, mid, li, ri, color);
    if (mid < ri) Update(u << 1 | 1, mid + 1, r, li, ri, color);
    PushUp(u);
}

void Query(int u, int l, int r, int li, int ri) {
    if (r < li || l > ri) return;
    if (l >= li && r <= ri) {
        if (tr[u].post) {
            if (!vis[tr[u].post]) vis[tr[u].post] = true;
            return;
        }
    }
    PushDown(u);
    int mid = (l + r) >> 1;
    if (mid >= li) Query(u << 1, l, mid, li, ri);
    if (mid < ri) Query(u << 1 | 1, mid + 1, r, li, ri);
}

int main() {
    // 特别注意！！cin cout 加上取消同步后比 scanf 和 printf 要快
    ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    cin >> kase;
    while (cin >> n) {
        tot = 0;
        memset(a, 0, sizeof(a));
        // memset(a, 0, sizeof(a));
        for (int i = 1; i <= n; ++i) {
            cin >> x[i] >> y[i];
            a[++tot] = x[i]; a[++tot] = y[i];
        }
        sort(a + 1, a + n * 2 + 1);
        m = unique(a + 1, a + 2 * n + 1) - a - 1;
        for (int i = 1; i <= m; ++i) {
            vis[i] = false;
            ID[a[i]] = i;
        }
        BuildTree(1, 1, m);
        
        for (int i = 1; i <= n; ++i) {
            Update(1, 1, m, ID[x[i]], ID[y[i]], i);
        }
        
        Query(1, 1, m, 1, m);
        int ans = 0;
        for (int i = 1; i <= m; ++i) 
            if (vis[i]) ans++;
        
        cout << ans << endl;
    }
    

    return 0;
}
