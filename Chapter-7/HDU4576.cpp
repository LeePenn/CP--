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
const int N = 200 + 5;
int T, n, m, l, r;
int a[N];
double f[2][N];

void Solve() {
    memset(f, 0, sizeof(f));
    f[0][1] = 1.0;
    int t = 0;
    for (int j = 1; j <= m; ++j) {
        memset(f[t ^ 1], 0, sizeof(f[t ^ 1]));
        for (int i = 1; i <= n; ++i) {
            f[t ^ 1][(i + a[j] - 1) % n + 1] += f[t][i] * 0.5;
            f[t ^ 1][(n - (a[j] - i) - 1) % n + 1] += f[t][i] * 0.5;
        }
        t ^= 1;
    }
        
    double ans = 0.0;
    for (int i = l; i <= r; ++i) {
        ans += f[t][i];
    }
    printf("%.4f\n", ans);
}

int main() {
    // POJ 上有时 scanf 比 cin 慢 = =！！
    ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    while (scanf("%d%d%d%d", &n, &m, &l, &r) == 4 && (n + m + l + r)) {
        for (int i = 1; i <= m; ++i) {
            scanf("%d", &a[i]);
            a[i] %= n;
        }
        Solve();
    }
    
    
    return 0;
}
