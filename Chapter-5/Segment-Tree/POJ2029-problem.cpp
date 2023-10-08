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
const int N = 100 + 5;
int n, m, T, w, h;
int x[N], y[N];
int tr[N][N];
int mx_x, mx_y;
int ans;

inline int lowbit(int i) {
    return i & (-i);
}

void Update(int x, int y, int v) {
    for (int i = x; i <= m; i += lowbit(i)) {
        for (int j = y; j <= n; j += lowbit(j)) {
            tr[i][j] += v;
        }
    }
}

int Query(int a, int b) {
    int ret = 0;
    for (int i = a; i > 0; i -= lowbit(i)) {
        for (int j = b; j > 0; j -= lowbit(j)) {
            ret += tr[i][j];
        }
    }
    return ret;
}

int getSum(int a, int b) {
    return Query(a, b) - Query(a - w, b) - Query(a, b - h) + Query(a - w, b - h);
}

void Solve() {
    ans = 0;
    for (int i = h; i <= n; ++i) {
        for (int j = w; j <= m; ++j) {
            ans = max(ans, getSum(j, i));
        }
    }
    printf("%d\n", ans);
}

int main() {
    // POJ 上有时 scanf 比 cin 慢 = =！！
    ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    while (scanf("%d", &T) == 1 && T) {
        memset(tr, 0, sizeof(tr));
        scanf("%d%d", &m, &n);
        for (int i = 1; i <= T; ++i) {
            scanf("%d%d", &x[i], &y[i]);
        }
        for (int i = 1; i <= T; ++i) Update(x[i], y[i], 1);
        scanf("%d%d", &w, &h);
        Solve();
    }

    return 0;
}
