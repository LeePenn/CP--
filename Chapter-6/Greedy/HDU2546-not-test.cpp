#include <stdio.h>
#include <iostream>
#include <stack>
#include <complex>
#include <vector>
#include <cstring>
#include <map>
#include <algorithm>
#include <queue>

// #define mytest

using namespace std;
typedef long long LL;
const int N = 1000 + 5;
int n, m, a[N];
int f[N];

int main() {
    // POJ 上有时 scanf 比 cin 慢 = =！！
    ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    while (scanf("%d", &n) == 1 && n) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
        }
        sort(a + 1, a + n + 1);
        scanf("%d", &m);
        memset(f, 0, sizeof(f));
        for (int i = 1; i < n; ++i) {
            for (int j = m - 5; j >= a[i]; --j) {
                f[j] = max(f[j], f[j - a[i]] + a[i]);
            }
        }
        
        printf("%d\n", m - f[m - 5] - a[n]);
    }
    

    return 0;
}
