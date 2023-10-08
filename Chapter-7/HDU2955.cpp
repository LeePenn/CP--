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
int prob, n, mon[105], p[105];
int f[105];

int main() {
    // POJ 上有时 scanf 比 cin 慢 = =！！
    ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    scanf("%d", &T);
    double x;
    while (T--) {
        scanf("%lf%d", &x, &n);
        prob = x * 100;
        for (int i = 1; i <= n; ++i) {
            scanf("%d%lf", &mon[i], &x);
            p[i] = x * 100;
        }
        memset(f, 0, sizeof(f));
        for (int i = 1; i <= n; ++i) {
            for (int j = prob; j >= p[i]; --j) {
                f[j] = max(f[j], f[j - p[i]] + mon[i]);
            }
        }
        int ans = 0;
        for (int i = 0; i <= 100; ++i) {
            ans = max(ans, f[i]);
        }
        printf("%d\n", ans);
    }
    
    return 0;
}
