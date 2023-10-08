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
int n, m;
struct Task {
    int x, y;
    bool operator <(const Task& rh) const {
        return x > rh.x || (x == rh.x && y > rh.y);
    }
}a[N], b[N];
int vis[105];

int main() {
    // POJ 上有时 scanf 比 cin 慢 = =！！
    ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    while (scanf("%d%d", &n, &m) == 2 && (n + m)) { 
        int x, y;
        for (int i = 1; i <= n; ++i) {
            scanf("%d%d", &a[i].x, &a[i].y);
        }
        for (int i = 1; i <= m; ++i) {
            scanf("%d%d", &b[i].x, &b[i].y);
        }
        sort(a + 1, a + n + 1);
        sort(b + 1, b + m + 1);
        memset(vis, 0, sizeof(vis));
        LL ans_profit = 0, ans_cnt = 0;
        int j = 1;
        for (int i = 1; i <= m; ++i) {
            Task c = b[i];
            while (j <= n && a[j].x >= c.x) {
                vis[a[j].y]++;
                j++;
            }
            for (int k = c.y; k <= 100; ++k) {
                if (vis[k]) {
                    vis[k]--;
                    ans_profit = ans_profit + (500 * b[i].x + 2 * b[i].y);
                    ans_cnt++;
                    break;
                }
            }
        }
        
        printf("%lld %lld\n", ans_cnt, ans_profit);
    }

    return 0;
}
