#include <stdio.h>
#include <iostream>
#include <stack>
#include <complex>

// #define mytest

using namespace std;
typedef long long LL;
const int N = 1e5 + 10;
int n, m;
LL a[N];
struct ST {
    int l, r;
    // 少一个mx 操作也可以快10%
    LL sum, mx;
}tr[N << 2];

void PushUp(int u) {
    tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
    tr[u].mx = max(tr[u << 1].mx, tr[u << 1 | 1].mx); 
}

void BuildTree(int u, int l, int r) {
    tr[u].l = l;
    tr[u].r = r;
    if (l == r) {
        tr[u].sum = a[l];
        tr[u].mx = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    BuildTree(u << 1, l, mid);
    BuildTree(u << 1 | 1, mid + 1, r);
    PushUp(u);
}

void Update(int u, int l, int r, int li, int ri) {
    // if (r < li || l > ri) return;
    if (l == r) {
        tr[u].sum = sqrt(tr[u].sum);
        tr[u].mx = tr[u].sum;
        return;
    }
    if (l >= li && r <= ri && tr[u].mx == 1) {
        return;
    }
    int mid = (l + r) >> 1;
    if (mid >= li) Update(u << 1, l, mid, li, ri);
    if (mid < ri) Update(u << 1 | 1, mid + 1, r, li, ri);
    PushUp(u);
}

LL Query(int u, int l, int r, int li, int ri) {
    if (l >= li && r <= ri) {
        return tr[u].sum;
    }
    
    int mid = (l + r) >> 1;
    LL ret = 0;
    if (mid >= li) ret += Query(u << 1, l, mid, li, ri);
    if (mid < ri) ret += Query(u << 1 | 1, mid + 1, r, li, ri);
    return ret;
}

int main() {
    // 特别注意！！cin cout 加上同步后比 scanf 和 printf 要快1倍！！！！
    ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    int t, x, y;
    int kase = 1;
    while (cin >> n && n) {
        cout << "Case #" << kase << ":" << endl;
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
        }
        BuildTree(1, 1, n);
        cin >> m;
        for (int i = 1; i <= m; ++i) {
            cin >> t >> x >> y;
            if (x > y) swap(x, y);
            if (!t) {
                Update(1, 1, n, x, y);
            } else if (t) {
                cout << Query(1, 1, n, x, y) << endl;
            }
        }
        
        printf("\n");
        kase++;
    }
    
    

    return 0;
}
