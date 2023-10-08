#include <stdio.h>
#include <iostream>
#include <stack>
#include <complex>
#include <vector>
#include <cstring>
#include <map>
#include <algorithm>
// #include <queue>

// #define mytest

using namespace std;
typedef long long LL;
const int N = 1000000 + 5;
int T;
int n, V, W;
int a[N];

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
        scanf("%d%d%d", &n, &V, &W);
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
        }
        sort(a + 1, a + n + 1);
        int ansV = 0;
        double ansTot = 0.0;
        for (int i = 1; i <= n; ++i) {
            if ((ansTot + 1.0 * a[i] * V) / (ansV + V) <= W) {
                ansV += V;
                ansTot += 1.0 * a[i] * V;
            }
        }
        printf("%d %.2f\n", ansV, ansV == 0 ? 0.0 : ansTot / ansV / 100);
    }
    

    return 0;
}
