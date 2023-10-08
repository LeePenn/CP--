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
const int N = 1000000 + 5;
int T, n, m;
LL a[N], f[N];

void Solve() {
    memset(f, 0, sizeof(f));
    for (int j = 1; j <= m; ++j) {
        LL tmp = 0;
        for (int i = 1; i <= j; ++i) {
            tmp += a[i];
        }
        f[n] = tmp;
        for (int i = j + 1; i <= n; ++i) {
            tmp = max(f[i - 1], tmp) + a[i];
            f[i - 1] = f[n];
            f[n] = max(f[n], tmp);
        }   
    }
    printf("%lld\n", f[n]);
}

int main() {
    // POJ 上有时 scanf 比 cin 慢 = =！！
    ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    while (scanf("%d%d", &m, &n) == 2 && (n + m)) {
        for (int i = 1; i <= n; ++i) {
            scanf("%lld", &a[i]);
        }
        Solve();
    }
    
    
    return 0;
}
