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
LL a[N], w[N];
LL f[N];

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
        scanf("%d%d", &n, &m);
        memset(f, 0, sizeof(f));
        for (int i = 1; i <= n; ++i) {
            scanf("%lld", &w[i]);
        }
        for (int i = 1; i <= n; ++i) {
            scanf("%lld", &a[i]);
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = m; j >= a[i]; --j) {
                f[j] = max(f[j], f[j - a[i]] + w[i]);
            }
        }
        
        LL ans = 0;
        for (int i = 0; i <= m; ++i) {
            ans = max(ans, f[i]);
        }
        printf("%lld\n", ans);
    }
    
    
    return 0;
}
