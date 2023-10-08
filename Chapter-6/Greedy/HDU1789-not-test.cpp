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
// #include <queue>

// #define mytest

using namespace std;
typedef long long LL;
const int N = 1000 + 5;
int T;
struct HW {
    int d, v;
    bool operator <(const HW& rh) const {
        return v > rh.v || (v == rh.v && d < rh.d);
    }
}a[N];
int n;
bool vis[N];

void Solve() {
    memset(vis, 0, sizeof(vis));
    sort(a + 1, a + n + 1);
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        HW c = a[i];
        int t = a[i].d;
        while (vis[t]) {
            t--;
        }
        if (t == 0) ans += c.v;
        else {
            vis[t] = true;
        }   
    }
    printf("%d\n", ans);
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
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &a[i].d);
        }
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &a[i].v);
        }
        Solve();
    }
    
    

    return 0;
}
