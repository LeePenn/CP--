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
const int N = 1e5 + 5, P = 10007;
LL n, m;
struct ST {
    int l, r;
    LL sum1, sum2, sum3, add, mul, chg;
    void Change(LL v) {
        v %= P;
        sum1 = v * (r - l + 1) % P;
        sum2 = (v * v % P) * (r - l + 1) % P;
        sum3 = (v * v % P) * v % P * (r - l + 1) % P;
        add = 0;
        chg = v;
        mul = 1;
    }
    
    void Mul(LL v) {
        v %= P;
        sum1 = sum1 * v % P;
        sum2 = sum2 * v % P * v % P;
        sum3 = sum3 * v % P * v % P * v % P;
        add = add * v % P;
        mul = mul * v % P;
    }
    
    void Add(LL v) {
        v %= P;
        sum3 = (sum3 + 3 * v * sum2 % P + 3 * v % P * v % P * sum1 % P + (r - l + 1) * v % P * v % P * v % P) % P;
        sum2 = (sum2 + 2 * v % P * sum1 % P + (r - l + 1) * v % P * v % P) % P;
        sum1 = (sum1 + (r - l + 1) * v % P) % P;
        add = (add + v) % P;
    }
}tr[N << 2];

LL Add(LL a, LL b) {
    return ((a % P) + (b % P)) % P;
}

void PushUp(int u) {
    tr[u].sum1 = Add(tr[u << 1].sum1, tr[u << 1 | 1].sum1);
    tr[u].sum2 = Add(tr[u << 1].sum2, tr[u << 1 | 1].sum2);
    tr[u].sum3 = Add(tr[u << 1].sum3, tr[u << 1 | 1].sum3);
}

void PushDown(int u) {
    int ls = u << 1, rs = u << 1 | 1;
    if (tr[u].chg != 0) {
        tr[ls].Change(tr[u].chg);
        tr[rs].Change(tr[u].chg);
        tr[u].chg = 0;
    }
    if (tr[u].mul != 1) {
        tr[ls].Mul(tr[u].mul);
        tr[rs].Mul(tr[u].mul);
        tr[u].mul = 1;
    }
    if (tr[u].add != 0) {
        tr[ls].Add(tr[u].add);
        tr[rs].Add(tr[u].add);
        tr[u].add = 0;
    }
}

void BuildTree(int u, int l, int r) {
    tr[u].l = l;
    tr[u].r = r;
    tr[u].sum1 = tr[u].sum2 = tr[u].sum3 = tr[u].add = tr[u].chg = 0;
    tr[u].mul = 1;
    if (l == r) return;
    int mid = (l + r) >> 1;
    BuildTree(u << 1, l, mid);
    BuildTree(u << 1 | 1, mid + 1, r);
}

void UpdateAdd(int u, int l, int r, int li, int ri, LL v) {
    if (l >= li && r <= ri) {
        tr[u].Add(v);
        return;
    }
    PushDown(u);
    int mid = (l + r) >> 1;
    if (mid >= li) UpdateAdd(u << 1, l, mid, li, ri, v);
    if (mid < ri) UpdateAdd(u << 1 | 1, mid + 1, r, li, ri, v);
    PushUp(u);
}

void UpdateMul(int u, int l, int r, int li, int ri, LL v) {
    if (l >= li && r <= ri) {
        tr[u].Mul(v);
        return;
    }
    PushDown(u);
    int mid = (l + r) >> 1;
    if (mid >= li) UpdateMul(u << 1, l, mid, li, ri, v);
    if (mid < ri) UpdateMul(u << 1 | 1, mid + 1, r, li, ri, v);
    PushUp(u);
}

void UpdateChange(int u, int l, int r, int li, int ri, LL v) {
    if (l >= li && r <= ri) {
        tr[u].Change(v);
        return;
    }
    PushDown(u);
    int mid = (l + r) >> 1;
    if (mid >= li) UpdateChange(u << 1, l, mid, li, ri, v);
    if (mid < ri) UpdateChange(u << 1 | 1, mid + 1, r, li, ri, v);
    PushUp(u);
}

LL Query(int u, int l, int r, int li, int ri, int v) {
    if (l >= li && r <= ri) {
        if (v == 1) return tr[u].sum1;
        else if (v == 2) return tr[u].sum2;
        else return tr[u].sum3;
    }
    PushDown(u);
    LL ret = 0;
    int mid = (l + r) >> 1;
    if (mid >= li) ret = Add(ret, Query(u << 1, l, mid, li, ri, v));
    if (mid < ri) ret = Add(ret, Query(u << 1 | 1, mid + 1, r, li, ri, v));
    return ret;
}

int main() {
    // POJ 上有时 scanf 比 cin 慢 = =！！
    ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    LL t, x, y, z;
    while (scanf("%lld%lld", &n, &m) == 2 && (n + m)) {
        BuildTree(1, 1, n);
        for (int i = 1; i <= m; ++i) {
            scanf("%lld%lld%lld%lld", &t, &x, &y, &z);
            if (t == 1) {
                UpdateAdd(1, 1, n, x, y, z);
            } else if (t == 2) {
                UpdateMul(1, 1, n, x, y, z);
            } else if (t == 3) {
                UpdateChange(1, 1, n, x, y, z);
            } else {
                printf("%lld\n", Query(1, 1, n, x, y, z));
            }
        }
    }
    
    
    return 0;
}
