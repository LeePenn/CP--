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
const int N = 1000 + 5;
int T, n, m;
struct Line {
    double x1, x2, y;
    int t;
    bool operator < (const Line& rh) const {
        return y < rh.y;
    }
}line[N << 1];
struct ST {
    int l, r, cnt;
    double len1, len2;
}tr[N << 3];
double x[N << 1];

void PushUp(int u) {
    if (tr[u].cnt > 1) {
        tr[u].len2 = x[tr[u].r] - x[tr[u].l - 1];
        tr[u].len1 = 0;
    } else if (tr[u].cnt == 1) {
        if (tr[u].l == tr[u].r) tr[u].len2 = 0;
        else tr[u].len2 = tr[u << 1].len2 + tr[u << 1].len1 + tr[u << 1 | 1].len2 + tr[u << 1 | 1].len1;
        tr[u].len1 = x[tr[u].r] - x[tr[u].l - 1] - tr[u].len2;
    } else {
        if (tr[u].l == tr[u].r) tr[u].len1 = tr[u].len2 = 0;
        else {
            tr[u].len2 = tr[u << 1].len2 + tr[u << 1 | 1].len2;
            tr[u].len1 = tr[u << 1 | 1].len1 + tr[u << 1 | 1].len1;
        }
    }
}

void BuildTree(int u, int l, int r) {
    tr[u].l = l;
    tr[u].r = r;
    tr[u].cnt = 0;
    tr[u].len1 = tr[u].len2 = 0.0;
    if (l == r) return;
    int mid = (l + r) >> 1;
    BuildTree(u << 1, l, mid);
    BuildTree(u << 1 | 1, mid + 1, r);
    // PushUp(u);
}

void Update(int u, int l, int r, int li, int ri, int v) {
    if (l >= li && r <= ri) {
        tr[u].cnt += v;
        PushUp(u);
        return;
    }
    int mid = (l + r) >> 1;
    if (mid >= li) Update(u << 1, l, mid, li, ri, v);
    if (mid < ri) Update(u << 1 | 1, mid + 1, r, li, ri, v);
    PushUp(u);
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
        scanf("%d", &n);
        int m = 0;
        double X1, Y1, X2, Y2;
        for (int i = 0; i < n; ++i) {
            scanf("%lf%lf%lf%lf", &X1, &Y1, &X2, &Y2);
            line[i << 1].x1 = X1; line[i << 1].x2 = X2; line[i << 1].y = Y1; line[i << 1].t = 1;
            line[i << 1 | 1].x1 = X1; line[i << 1 | 1].x2 = X2; line[i << 1 | 1].y = Y2; line[i << 1 | 1].t = -1;
            x[++m] = X1; x[++m] = X2;
        }
        sort(x + 1, x + m + 1);
        m = unique(x + 1, x + m + 1) - x - 1;
        // for (int i = 1; i <= m; ++i) {
        //     printf("!! %.2f, %ld\n", x[i], lower_bound(x + 1, x + m + 1, x[i]) - x);
        // }
        sort(line, line + (n << 1));
        // for (int i = 0; i < (n << 1); ++i) {
        //     printf("!! %.2f, %.2f, %.2f\n", line[i].x1, line[i].x2, line[i].y);
        // }
        BuildTree(1, 1, m);
        int xid1 = lower_bound(x + 1, x + m + 1, line[0].x1) - x;
        int xid2 = lower_bound(x + 1, x + m + 1, line[0].x2) - x;
        // 特别注意，xid 对应的是区间 id，从前线段树计算的都是区间内所有的点，与这道题不同，所以 xid1需要+1
        Update(1, 1, m, xid1 + 1, xid2, line[0].t);
        double ans = 0;
        for (int i = 1; i < (n << 1); ++i) {
            ans += (line[i].y - line[i - 1].y) * tr[1].len2;
            xid1 = lower_bound(x + 1, x + m + 1, line[i].x1) - x;
            xid2 = lower_bound(x + 1, x + m + 1, line[i].x2) - x;
            Update(1, 1, m, xid1 + 1, xid2, line[i].t);
        }
        printf("%.2f\n", ans);
    }
    
    return 0;
}
