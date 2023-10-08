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
const int N = 1000 + 5, Z = 500 + 5;
int T;
int n, m, zcnt, xcnt;
struct Point {
    int x, y, z;
}p[N << 1];
struct Block {
    Point a, b;
}b[N << 1];
struct Line {
    int x1, x2, y;
    int t;
    bool operator < (const Line& rh) const {
        return y < rh.y;
    }
}line[N << 1];
int x[N << 1], z[N << 1];
int sum1[N << 3], sum2[N << 3], sum3[N << 3], cover[N << 3];

void Init() {
    memset(sum1, 0, sizeof(sum1));
    memset(sum2, 0, sizeof(sum2));
    memset(sum3, 0, sizeof(sum3));
    memset(cover, 0, sizeof(cover));
}

void PushUp(int u, int l, int r) {
    int ls = u << 1, rs = u << 1 | 1;
    int d = x[r] - x[l - 1];
    if (cover[u] >= 3) {
        sum3[u] = d;
        sum1[u] = sum2[u] = 0;
    } else if (cover[u] == 2) {
        if (l == r) {
            sum3[u] = sum1[u] = 0;
            sum2[u] = d;
        } else {
            sum3[u] = sum3[ls] + sum3[rs] + sum2[ls] + sum2[rs] + sum1[ls] + sum1[rs];
            sum2[u] = d - sum3[u];
            sum1[u] = 0;
        }
    } else if (cover[u] == 1) {
        if (l == r) {
            sum3[u] = sum2[u] = 0;
            sum1[u] = d;
        } else {
            sum3[u] = sum3[ls] + sum3[rs] + sum2[ls] + sum2[rs];
            sum2[u] = sum1[ls] + sum1[rs];
            sum1[u] = x[r] - x[l - 1] - sum3[u] - sum2[u];
        }
    } else {
        if (l == r) {
            sum1[u] = sum2[u] = sum3[u] = 0;
        } else {
            sum3[u] = sum3[ls] + sum3[rs];
            sum2[u] = sum2[ls] + sum2[rs];
            sum1[u] = sum1[ls] + sum1[rs];
        }
    }
}

void Update(int u, int l, int r, int li, int ri, int v) {
    if (l >= li && r <= ri) {
        cover[u] += v;
        PushUp(u, l, r);
        return;
    }
    int mid = (l + r) >> 1;
    if (mid >= li) Update(u << 1, l, mid, li, ri, v);
    if (mid < ri) Update(u << 1 | 1, mid + 1, r, li, ri, v);
    PushUp(u, l, r);
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
    for (kase = 1; kase <= T; ++kase) {
        scanf("%d", &n);
        xcnt = zcnt = 0;
        for (int i = 1; i <= n; ++i) {
            scanf("%d%d%d%d%d%d", &b[i].a.x, &b[i].a.y, &b[i].a.z, &b[i].b.x, &b[i].b.y, &b[i].b.z);
            x[++xcnt] = b[i].a.x; x[++xcnt] = b[i].b.x;
            z[++zcnt] = b[i].a.z; z[++zcnt] = b[i].b.z;
        }
        
        if (n < 3) {
            printf("Case %d: 0\n", kase);
            continue;
        }
        sort(x + 1, x + xcnt + 1);
        xcnt = unique(x + 1, x + xcnt + 1) - x - 1;
        sort(z + 1, z + zcnt + 1);
        zcnt = unique(z + 1, z + zcnt + 1) - z - 1;
        
        LL ans = 0;
        for (int i = 1; i < zcnt; ++i) {
            Init();
            m = 0;
            for (int j = 1; j <= n; ++j) {
                if (b[j].a.z <= z[i] && b[j].b.z > z[i]) {
                    line[++m].x1 = b[j].a.x; line[m].x2 = b[j].b.x; line[m].y = b[j].a.y; line[m].t = 1;
                    line[++m].x1 = b[j].a.x; line[m].x2 = b[j].b.x; line[m].y = b[j].b.y; line[m].t = -1;
                }
            }
            sort(line + 1, line + m + 1);
            LL res = 0;
            int xid1 = lower_bound(x + 1, x + xcnt + 1, line[1].x1) - x;
            int xid2 = lower_bound(x + 1, x + xcnt + 1, line[1].x2) - x;
            Update(1, 1, xcnt, xid1 + 1, xid2, line[1].t);
            for (int j = 2; j <= m; ++j) {
                res += (LL)sum3[1] * (line[j].y - line[j - 1].y);
                xid1 = lower_bound(x + 1, x + xcnt + 1, line[j].x1) - x;
                xid2 = lower_bound(x + 1, x + xcnt + 1, line[j].x2) - x;
                Update(1, 1, xcnt, xid1 + 1, xid2, line[j].t);
            }
            ans += res * (z[i + 1] - z[i]);
        }
        printf("Case %d: %lld\n", kase, ans);
        
    }
    
    return 0;
}
