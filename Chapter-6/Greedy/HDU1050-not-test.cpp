#include <stdio.h>
#include <iostream>
#include <stack>
#include <complex>
#include <vector>
#include <cstring>
#include <map>
#include <algorithm>
#include <queue>
// #include <queue>

// #define mytest

using namespace std;
typedef long long LL;
const int N = 200 + 5;
int T, n;
struct Table {
    int s, e;
    bool operator <(const Table& rh) const {
        return e < rh.e;
    }
}a[N], b[N];

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
            scanf("%d%d", &a[i].s, &a[i].e);
        }   
        
        int ans = 0;
        int tot = n;
        int cnt = 0;
        sort(a + 1, a + tot + 1);
        while (1) {
            ans++;
            cnt = 0;
            int last = -1;
            for (int i = 1; i <= tot; ++i) {
                if (a[i].s <= last) {
                    b[++cnt] = a[i];
                } else {
                    last = a[i].e;
                }
            }
            if (cnt == 0) break;
            tot = cnt;
            memcpy(a, b, sizeof(a));
        }
        printf("%d\n", ans * 10);
    }
    

    return 0;
}
