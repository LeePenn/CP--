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
const int N = 3000 + 5, M = 60000 + 5, INF = 1000000000;
int n, m;
double f[N];
int ans[N];
int prime[N], v[N], tot;

void Init() {
    for (int i = 2; i <= N; ++i) {
        if (!v[i]) {
            prime[++tot] = i;
            v[i] = i;
        }
        for (int j = 1; j <= tot; ++j) {
            if (prime[j] > i || prime[j] * i > N) break;
            v[prime[j] * i] = prime[j];
        }
    }
}

int main() {
    // POJ 上有时 scanf 比 cin 慢 = =！！
    ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    Init();
    // printf("%d\n", tot);
    // for (int i = 1; i <= tot; ++i) printf("%d ", prime[i]);
    while (scanf("%d%d", &n, &m) == 2 && (n + m)) {
        memset(f, 0, sizeof(f));
        for (int i = 0; i <= n; ++i) ans[i] = 1;
        for (int i = 1; i <= tot && prime[i] <= n; ++i) {
            double tmp = log(prime[i] * 1.0);
            for (int j = n; j >= prime[i]; --j) {
                for (int k1 = 1, k2 = prime[i]; k2 <= j; k2 *= prime[i], k1++) {
                    if (f[j] < f[j - k2] + k1 * tmp) {
                        f[j] = f[j - k2] + k1 * tmp;
                        ans[j] = (ans[j - k2] * k2) % m;
                    }
                }
            }
        }
        printf("%d\n", ans[n]);
    }
    
    return 0;
}
