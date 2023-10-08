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
const int N = 1000 + 5, M = 60000 + 5, INF = 1000000000;
int n;
LL a[N], f[N];

int main() {
    // POJ 上有时 scanf 比 cin 慢 = =！！
    ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    while (scanf("%d", &n) == 1 && n) {
        for (int i = 1; i <= n; ++i) scanf("%lld", &a[i]);
        memset(f, 0, sizeof(f));
        LL ans = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = i - 1; j >= 0; --j) {
                if (a[i] <= a[j]) continue;
                f[i] = max(f[i], f[j] + a[i]);
            }
            ans = max(ans, f[i]);
        }
        printf("%lld\n", ans);
    }
    
    return 0;
}
