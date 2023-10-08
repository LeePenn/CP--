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
LL f[10000 + 5];

int main() {
    // POJ 上有时 scanf 比 cin 慢 = =！！
    ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    scanf("%d", &T);
    f[1] = 2;
    for (int i = 2; i <= 10000; ++i) {
        f[i] = f[i - 1] + 4 * (i - 1) + 1;
    }
    while (T--) {
        scanf("%d", &n);
        printf("%lld\n", f[n]);
    }
    
    return 0;
}
