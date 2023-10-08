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
const int N = 50000 + 5;
int T;
int n, m;
int a, b, k;
int d[105];
LL f[2][105];

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
        scanf("%d%d%d%d", &n, &a, &b, &k);
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &d[i]);
        }
        memset(f, 0, sizeof(f));
        f[0][1] = d[1];
        int t = 0;
        for (int j = 1; j <= k; ++j) {
            for (int i = 2; i <= n; ++i) {
                for (int p = a; p <= b; ++p) {
                    if (i - p >= 1) {
                        f[t ^ 1][i] = max(f[t ^ 1][i], f[t][i - p] + d[i]);
                    }
                }
            }
            t ^= 1;
        }
        printf("%lld\n", f[t][n]);
        
    }
    
    return 0;
}
