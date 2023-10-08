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
int T, n, a[6];
const int b[6] = {0, 1, 5, 10, 50, 100};
int ans[2];

void Solve() {
    int cnt = 0;
    int t = n;
    int tmp[6];
    int cpa[6];
    memcpy(cpa, a, sizeof(cpa));
    memset(tmp, 0, sizeof(tmp));
    for (int i = 5; i >= 1; --i) {
        int cur = min(t / b[i], a[i]);
        t -= cur * b[i];
        cnt += cur;
        tmp[i] = cur;
        cpa[i] -= cur;
        if (t == 0) break; 
    }
    if (t > 0) {
        ans[0] = ans[1] = -1;
        return;
    }
    ans[0] = cnt;
    
    for (int i = 5; i >= 1; --i) {
        if (tmp[i] == 0) continue;
        for (int j = i - 1; j >= 1; --j) {
            if (cpa[j] == 0) continue;
            int p = b[i] / b[j];
            int num = min(cpa[j] / p, tmp[i]);
            tmp[j] += num * p;
            tmp[i] -= num;
            cpa[j] -= num * p;
            cpa[i] += num;
            cnt = cnt - num + num * p;
        }
    }
    ans[1] = cnt;
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
    while (T--) {
        scanf("%d%d%d%d%d%d", &n, &a[1], &a[2], &a[3], &a[4], &a[5]);
        Solve();
        printf("%d %d\n", ans[0], ans[1]);
    }
    

    return 0;
}
