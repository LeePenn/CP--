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
const int N = 100000 + 5;
int T, n;
LL a[N];
LL f[N], len[N];

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
        memset(f, 0xcf, sizeof(f));
        memset(len, 0, sizeof(len));
        scanf("%d", &n);
        LL ans = -1;
        for (int i = 1; i <= n; ++i) {
            scanf("%lld", &a[i]);
            if (f[i - 1] + a[i] < a[i]) {
                f[i] = a[i];
                len[i] = 1;
            } else {
                f[i] = a[i] + f[i - 1];
                len[i] = len[i - 1] + 1;
            }
            if (ans == -1 || f[ans] < f[i]) {
                ans = i;
            }
        }
        
        printf("Case %d:\n%lld %lld %lld\n\n", kase, f[ans], ans - len[ans] + 1, ans);
    }
    
    return 0;
}
