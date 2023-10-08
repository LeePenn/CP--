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
struct ST {
    int l, r;
    int sum, lazy;
}tr[N << 2];

void PushUp(int u) {
    tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
}

void PushDown(int u) {
    int ls = u << 1, rs = u << 1 | 1;
    if (tr[u].lazy != -1) {
        tr[ls].sum = (tr[ls].r - tr[ls].l + 1) * tr[u].lazy;
        tr[rs].sum = (tr[rs].r - tr[rs].l + 1) * tr[u].lazy;
        tr[ls].lazy = tr[rs].lazy = tr[u].lazy;
        tr[u].lazy = -1;
    }
}

void BuildTree(int u, int l, int r) {
    tr[u].l = l;
    tr[u].r = r;
    tr[u].sum = r - l + 1;
    tr[u].lazy = -1;
    if (l == r) return;
    int mid = (l + r) >> 1;
    BuildTree(u << 1, l, mid);
    BuildTree(u << 1 | 1, mid + 1, r);
}

void Update(int u, int l, int r, int li, int ri, int v) {
    if (l >= li && r <= ri) {
        tr[u].lazy = v;
        tr[u].sum = (r - l + 1) * v;
        return;
    }
    PushDown(u);
    int mid = (l + r) >> 1;
    if (mid >= li) Update(u << 1, l, mid, li, ri, v);
    if (mid < ri) Update(u << 1 | 1, mid + 1, r, li, ri, v);
    PushUp(u);
}

int Query(int u, int l, int r, int li, int ri) {
    if (l >= li && r <= ri) {
        return tr[u].sum;
    }
    
    PushDown(u);
    int res = 0;
    int mid = (l + r) >> 1;
    if (mid >= li) res += Query(u << 1, l, mid, li, ri);
    if (mid < ri) res += Query(u << 1 | 1, mid + 1, r, li, ri);
    return res;
}

int Search(int l, int k) {
    int r = n;
    int ans = -1;
    int cur = l;
    while (cur <= r) {
        int mid = (cur + r) >> 1;
        if (Query(1, 1, n, l, mid) >= k) {
            ans = mid;
            r = mid - 1;
        } else cur = mid + 1;
    }
    return ans;
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
    while (T--) {
        scanf("%d%d", &n, &m);
        BuildTree(1, 1, n);
        
        int t, x, y;
        for (int i = 1; i <= m; ++i) {
            scanf("%d%d%d", &t, &x, &y);
            // printf("! %d\n", Search(x + 1, 1));
            // exit(0);
            if (t == 1) {
                if (Query(1, 1, n, x, n) == 0) {
                    printf("Can not put any one.\n");
                } else {
                    int st = Search(x + 1, 1), ed = Search(x + 1, min(y, Query(1, 1, n, x + 1, n)));
                    // printf("! %d @ %d %d\n", min(y, Query(1, 1, n, x + 1, n)), st - 1, ed - 1);
                    // exit(0);
                    Update(1, 1, n, st, ed, 0);
                    printf("%d %d\n", st - 1, ed - 1);
                }
            } else if (t == 2) {
                printf("%d\n", y - x + 1 - Query(1, 1, n, x + 1, y + 1));
                Update(1, 1, n, x + 1, y + 1, 1);
            }
        }
        printf("\n");
    }
    
    return 0;
}
