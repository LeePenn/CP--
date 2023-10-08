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
LL f[22][2];
LL c[22][22];

int main() {
    // POJ 上有时 scanf 比 cin 慢 = =！！
    ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    
    c[1][0] = c[1][1] = 1;
    for (int i = 2; i <= 20; ++i) {
        c[i][0] = c[i][i] = 1;
        for (int j = 1; j < i; ++j) {
            c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
        }
    }   
    
    f[0][0] = f[0][1] = f[1][0] = f[1][1] = 1;
    for (int i = 2; i <= 20; ++i) {
        LL t = 0;
        for (int j = 0; j <= i - 1; ++j) {
            t += f[j][0] * f[i - j - 1][1] * c[i - 1][j];
        }
        f[i][0] = f[i][1] = t >> 1;
    }
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        printf("%d ", n);
        if (m == 1) {
            printf("1\n");
        } else printf("%lld\n", f[m][0] << 1);
    }
    
    return 0;
}
