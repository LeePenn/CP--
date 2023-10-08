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
int n, m;
LL a[105], c[105];
bool f[100000 + 10];
int num[100000 + 10];

int main() {
    // POJ 上有时 scanf 比 cin 慢 = =！！
    ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    while (scanf("%d%d", &n, &m) == 2 && (n + m)) {
        for (int i = 1; i <= n; ++i) {
            scanf("%lld", &a[i]);
        }
        for (int i = 1; i <= n; ++i) scanf("%lld", &c[i]);
        memset(f, 0, sizeof(f));
        f[0] = 1;
        int ans = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) num[j] = 0;
            for (int j = a[i]; j <= m; j++) {
                if (!f[j] && f[j - a[i]] && num[j - a[i]] < c[i]) {
                    ans++;
                    num[j] = num[j - a[i]] + 1;
                    f[j] = 1;
                }
            }
        }
        printf("%d\n", ans);
    }
    
    return 0;
}
