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
const int N = 100 + 5;
int n, m;
struct Line {
    double x1, x2, y;
    int t;
    bool operator < (const Line& rh) const {
        return y < rh.y;
    }
}line[N << 1];
struct ST {
    int l, r, cover;
    double len;
}tr[N << 3];
double x[N << 1];

void PushUp(int u) {
    if (tr[u].cover >= 1) {
        tr[u].len = x[tr[u].r] - x[tr[u].l - 1];
    } else {
        tr[u].len = tr[u << 1].len + tr[u << 1 | 1].len;
    }
}

void BuildTree(int u, int l, int r) {
    tr[u].l = l;
    tr[u].r = r;
    tr[u].len = tr[u].cover = 0;
    if (l == r) return;
    int mid = (l + r) >> 1;
    BuildTree(u << 1, l, mid);
    BuildTree(u << 1 | 1, mid + 1, r);
}

void Update(int u, int l, int r, int li, int ri, int v) {
    if (l >= li && r <= ri) {
        tr[u].cover += v;
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
    
    int kase = 1;
    while (scanf("%d", &n) == 1 && n) {
        double X1, Y1, X2, Y2;
        m = 0;
        for (int i = 0; i < n; ++i) {
            scanf("%lf%lf%lf%lf", &X1, &Y1, &X2, &Y2);
            line[i << 1].x1 = X1; line[i << 1].x2 = X2; line[i << 1].y = Y1; line[i << 1].t = 1;
            line[i << 1 | 1].x1 = X1; line[i << 1 | 1].x2 = X2; line[i << 1 | 1].y = Y2; line[i << 1 | 1].t = -1;
            x[++m] = X1; x[++m] = X2;
        }
        sort(x + 1, x + m + 1);
        m = unique(x + 1, x + m + 1) - x - 1;
        sort(line, line + (n << 1));
        BuildTree(1, 1, m);
        double ans = 0;
        int xid1 = lower_bound(x + 1, x + m + 1, line[0].x1) - x;
        int xid2 = lower_bound(x + 1, x + m + 1, line[0].x2) - x;
        Update(1, 1, m, xid1 + 1, xid2, line[0].t);
        for (int i = 1; i < (n << 1); ++i) {
            ans += (line[i].y - line[i - 1].y) * tr[1].len;
            xid1 = lower_bound(x + 1, x + m + 1, line[i].x1) - x;
            xid2 = lower_bound(x + 1, x + m + 1, line[i].x2) - x;
            Update(1, 1, m, xid1 + 1, xid2, line[i].t);
        }
        
        printf("Test case #%d\nTotal explored area: %.2lf\n", kase, ans);
    }
    
    return 0;
}
