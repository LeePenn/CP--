#include <stdio.h>
#include <iostream>
#include <stack>

// #define mytest

using namespace std;
typedef long long LL;
const int N = 2050;
struct SubST {
    int al, ar;
    int Lmax;
};

struct ST {
    int hl, hr;
    SubST subtr[N << 2];
}tr[N << 2];
int n;

void Debug(int k) {
    
}

void BuildSubTree(int fu, int u, int l, int r) {
    tr[fu].subtr[u].al = l;
    tr[fu].subtr[u].ar = r;
    tr[fu].subtr[u].Lmax = -1;
    if (l == r) return;
    int mid = (l + r) >> 1;
    BuildSubTree(fu, u << 1, l, mid);
    BuildSubTree(fu, u << 1 | 1, mid + 1, r);
}

void BuildTree(int u, int hl, int hr, int al, int ar) {
    tr[u].hl = hl;
    tr[u].hr = hr;
    BuildSubTree(u, 1, al, ar);
    if (hl == hr) return;
    int mid = (hl + hr) >> 1;
    BuildTree(u << 1, hl, mid, al, ar);
    BuildTree(u << 1 | 1, mid + 1, hr, al, ar);
}

void PushUp(int fu, int u) {
    tr[fu].subtr[u].Lmax = max(tr[fu].subtr[u << 1].Lmax, tr[fu].subtr[u << 1 | 1].Lmax);
}

void UpdateSubTree(int fu, int u, int ax, int lx) {
    int l = tr[fu].subtr[u].al, r = tr[fu].subtr[u].ar;
    if (l == r) {
        // 必须这么写，怀疑有重复身高和活泼的数据
        tr[fu].subtr[u].Lmax = max(tr[fu].subtr[u].Lmax, lx);
        return;
    }
    
    int mid = (l + r) >> 1;
    if (mid >= ax) UpdateSubTree(fu, u << 1, ax, lx);
    if (mid < ax) UpdateSubTree(fu, u << 1 | 1, ax, lx);
    PushUp(fu, u);
}

void Update(int u, int hx, int ax, int lx) {
    int l = tr[u].hl, r = tr[u].hr;
    // 必须这么写，因为是二维树套树，不能因为不在 x 范围内，就不更新范围内的 y
    UpdateSubTree(u, 1, ax, lx);
    if (l == r) {
        return;
    }
    int mid = (l + r) >> 1;
    if (mid >= hx) Update(u << 1, hx, ax, lx);
    if (mid < hx) Update(u << 1 | 1, hx, ax, lx);
}

int QuerySubTree(int fu, int u, int li, int ri) {
    int l = tr[fu].subtr[u].al, r = tr[fu].subtr[u].ar;
    if (l >= li && r <= ri) {
        return tr[fu].subtr[u].Lmax;
    }
    
    int mid = (l + r) >> 1;
    int ret = -1;
    if (mid >= li) ret = max(ret, QuerySubTree(fu, u << 1, li, ri));
    if (mid < ri) ret = max(ret, QuerySubTree(fu, u << 1 | 1, li, ri));
    return ret;
}

int Query(int fu, int hx1, int hx2, int ax1, int ax2) {
    int l = tr[fu].hl, r = tr[fu].hr;
    if (l >= hx1 && r <= hx2) {
        return QuerySubTree(fu, 1, ax1, ax2);
    }
    int mid = (l + r) >> 1;
    int ret = -1;
    if (mid >= hx1) ret = max(ret, Query(fu << 1, hx1, hx2, ax1, ax2));
    if (mid < hx2) ret = max(ret, Query(fu << 1 | 1, hx1, hx2, ax1, ax2));
    return ret;
}

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    char c;
    int h1, h2;
    double a1, a2, z;
    while (scanf("%d", &n) == 1 && n) {
        BuildTree(1, 100, 200, 0, 1000);
        getchar();
        for (int i = 1; i <= n; ++i) {
            c = getchar();
            if (c == 'I') {
                scanf("%d%lf%lf", &h1, &a1, &z);
                Update(1, h1, (int)(a1 * 10), (int)(z * 10));
                // printf("@@ %d %d %d \n", h1, (int)(a1 * 10), (int)(z * 10));
                // printf(
                // "@@ %.1lf\n", 
                // 1.0 * Query(1, 166, 177, 505, 505) / 10
                // );
                // exit(0);
            } else if (c == 'Q') {
                scanf("%d%d%lf%lf", &h1, &h2, &a1, &a2);
                if (h1 > h2) swap(h1, h2);
                if (a1 > a2) swap(a1, a2);
                double ans = Query(1, h1, h2, (int)(a1 * 10), (int)(a2 * 10));
                if (ans < 0) printf("-1\n");
                else printf("%.1lf\n", ans / 10);
            }
            getchar();
        }
    }
    
    

    return 0;
}
