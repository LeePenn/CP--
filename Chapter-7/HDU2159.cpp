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
int T;
int n, m, k, s;
int f[105][105];
int e[105], dur[105];

int main() {
    // POJ 上有时 scanf 比 cin 慢 = =！！
    ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    
    while (scanf("%d%d%d%d", &n, &m, &k, &s) == 4) {
        for (int i = 1; i <= k; ++i) {
            scanf("%d%d", &e[i], &dur[i]);
        }
        memset(f, 0x3f, sizeof(f));
        f[0][0] = 0;
        for (int i = 1; i <= k; ++i) {
            for (int j = e[i]; j <= n; ++j) {
                for (int p = dur[i]; p <= m; ++p) {
                    f[j][p] = min(f[j][p], f[j - e[i]][p - dur[i]] + 1);
                }
            }
        }
        int ans = -1;
        for (int i = 0; i <= m; ++i) {
            if (f[n][i] != 0x3f3f3f3f && f[n][i] <= s) {
                ans = m - i;
                break;
            }
        }
        printf("%d\n", ans);
    }
    
    return 0;
}
