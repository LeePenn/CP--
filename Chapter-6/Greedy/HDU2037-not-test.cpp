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
const int N = 1000000 + 5, W = 33000;
struct Node {
    int st, ed;
    bool operator <(const Node& rh) const {
        return ed < rh.ed;
    }
}a[N];
int n;

int main() {
    // POJ 上有时 scanf 比 cin 慢 = =！！
    ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    while (scanf("%d", &n) && n) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d%d", &a[i].st, &a[i].ed);
        }
        sort(a + 1, a + n + 1);
        int ans = 0;
        int last = -1;
        for (int i = 1; i <= n; ++i) {
            if (a[i].st < last) continue;
            ans++;
            last = a[i].ed;
        }
        printf("%d\n", ans);
    }
    

    return 0;
}
