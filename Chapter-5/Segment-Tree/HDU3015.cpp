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
struct Tree {
    LL x, h;
    bool operator <(const Tree& rh) const {
        return h > rh.h;
    }
}t[N];
LL x[N], h[N];
LL trx[N], trx_cnt[N];
LL ans, sum;
int n;

int lowbit(int i) {
    return i & (-i);
}

void Update(LL tr[], int i, LL v) {
    while (i <= n) {
        tr[i] += v;
        i += lowbit(i);
    }
}

LL Query(LL tr[], int i) {
    LL ret = 0;
    while (i) {
        ret += tr[i];
        i -= lowbit(i);
    }
    return ret;
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
        for (int i = 1; i <= n; ++i) {
            scanf("%lld%lld", &x[i], &h[i]);
            t[i].x = x[i], t[i].h = h[i];
        }
        sort(t + 1, t + n + 1);
        sort(x + 1, x + n + 1);
        sort(h + 1, h + n + 1);
        
        for (int i = 1; i <= n; ++i) {
            t[i].h = lower_bound(h + 1, h + n + 1, t[i].h) - h;
            t[i].x = lower_bound(x + 1, x + n + 1, t[i].x) - x;
        }
        
        memset(trx, 0, sizeof(trx));
        memset(trx_cnt, 0, sizeof(trx_cnt));
        ans = 0;
        sum = 0;
        for (int i = 1; i <= n; ++i) {
            LL cur_x = t[i].x, cur_h = t[i].h;
            LL sum_left = Query(trx, cur_x), sum_left_cnt = Query(trx_cnt, cur_x);
            LL sum_right = sum - sum_left, sum_right_cnt = i - 1 - sum_left_cnt;
            ans += cur_h * (cur_x * sum_left_cnt - sum_left);
            ans += cur_h * (sum_right - cur_x * sum_right_cnt);
            Update(trx_cnt, cur_x, 1);
            Update(trx, cur_x, cur_x);
            sum += cur_x;
        }
        
        printf("%lld\n", ans);
    }
    

    return 0;
}
