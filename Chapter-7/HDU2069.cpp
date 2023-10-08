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
const int N = 250 + 5;
int n, m;
int a[6] = {0, 1, 5, 10, 25, 50};
LL f[N][100 + 5];


int main() {
    // POJ 上有时 scanf 比 cin 慢 = =！！
    ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    while (scanf("%d", &n) == 1 && n) {
        memset(f, 0, sizeof(f));
        f[0][0] = 1;
        for (int i = 1; i <= 5; ++i) {
            for (int j = 1; j <= 100; ++j) {
                for (int k = a[i]; k <= n; ++k) {
                    f[k][j] += f[k - a[i]][j - 1];
                }
            }
        }
        LL ans = 0;
        for (int i = 0; i <= 100; ++i) {
            ans += f[n][i];
        }
        printf("%lld\n", ans);
    }
    
    
    return 0;
}
