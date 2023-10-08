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
const int N = 1050000 + 5;
int T, n, m;
int a[50];
LL f[2][N];

void Solve() {
    memset(f, 0, sizeof(f));
    f[0][0] = 1;
    int t = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < 1000000; ++j) {
            f[t ^ 1][j] = f[t][j] + f[t][j ^ a[i]];
        }
        t ^= 1;
    }
    
    LL ans = 0;
    for (int i = m; i < 1000000; ++i) {
        ans += f[t][i];
    }
    printf("%lld\n", ans);
}

int main() {
    // POJ 上有时 scanf 比 cin 慢 = =！！
    ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    scanf("%d", &T);
    int kase;
    for (kase = 1; kase <= T; ++kase) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
        }
        printf("Case #%d: ", kase);
        Solve();
    }
    
    return 0;
}
