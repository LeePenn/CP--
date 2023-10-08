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
LL f[55];

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
        f[n] = 1; f[n + 1] = 1;
        for (int i = n + 2; i <= m; ++i) {
            f[i] = f[i - 1] + f[i - 2];
        }
        printf("%lld\n", f[m]);
    }
    
    return 0;
}
