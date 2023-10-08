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
const int N = 100000 + 5;
int tr[N];
int n;
struct OP {
    int t, x, y;
}op[N];
int maxn;

int lowbit(int i) {
    return i & (-i);
}

void Update(int i, int v) {
    while (i <= maxn) {
        tr[i] += v;
        i += lowbit(i);
    }
}

int Query(int i) {
    int ret = 0;
    while (i) {
        ret += tr[i];
        i -= lowbit(i);
    }
    return ret;
}

int Solve(int a, int k) {
    int l = a + 1, r = maxn;
    int ans = -1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (Query(mid) - Query(a) >= k) {
            ans = mid;
            r = mid - 1;
        } else l = mid + 1;
    }
    return ans;
}

int main() {
    // POJ 上有时 scanf 比 cin 慢 = =！！
    ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    while (scanf("%d", &n) == 1 && n) {
        maxn = 0;
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &op[i].t);
            if (op[i].t == 2) {
                scanf("%d%d", &op[i].x, &op[i].y);
            } else {
                scanf("%d", &op[i].x);
                maxn = max(maxn, op[i].x);
            }
        }
        memset(tr, 0, sizeof(tr));
        for (int i = 1; i <= n; ++i) {
            if (op[i].t == 0) Update(op[i].x, 1);
            else if (op[i].t == 1) {
                int c = Query(op[i].x) - Query(op[i].x - 1);
                if (!c) printf("No Elment!\n");
                else Update(op[i].x, -1);
            } else {
                int x = Solve(op[i].x, op[i].y);
                if (x == -1) printf("Not Find!\n");
                else printf("%d\n", x);
            }
        }
    }
    
    

    return 0;
}
