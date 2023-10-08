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
const int N = 20000 + 5;
int n;
struct Cow {
    LL v, p;
}c[N];
LL trp[N], trp_cnt[N];
LL max_p;

bool cmp(const Cow& a, const Cow& b) {
    return a.v < b.v;
}

int lowbit(int i) {
    return i & (-i);
}

void Update_P(int i, LL v) {
    while (i <= max_p) {
        trp[i] += v;
        i += lowbit(i);
    }
}

LL Query_P(int i) {
    LL ret = 0;
    while (i) {
        ret += trp[i];
        i -= lowbit(i);
    }
    return ret;
}

void Update_P_cnt(int i, LL v) {
    while (i <= max_p) {
        trp_cnt[i] += v;
        i += lowbit(i);
    }
}

LL Query_P_cnt(int i) {
    LL ret = 0;
    while (i) {
        ret += trp_cnt[i];
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
    
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld%lld", &c[i].v, &c[i].p);
        max_p = max(max_p, c[i].p);
    }
    sort(c + 1, c + n + 1, cmp);
    
    // for (int i = 1; i <= n; ++i) {
    //     printf("%lld %lld\n", c[i].v, c[i].p);
    // }
    // exit(0);
    
    LL ans = 0;
    LL sum = 0;
    
    for (int i = 1; i <= n; ++i) {
        Cow cur = c[i];
        LL sum_low = Query_P(cur.p), sum_low_cnt = Query_P_cnt(cur.p);
        LL sum_high = sum - sum_low, sum_high_cnt = i - 1 - sum_low_cnt;
        ans += cur.v * (sum_low_cnt * cur.p - sum_low);
        ans += cur.v * (sum_high - sum_high_cnt * cur.p);
        // printf("!! %lld, %lld\n", c[i].v, c[i].p);
        // printf("!! %lld, %lld, %lld, %lld, %lld\n", sum_low, sum_low_cnt, sum_high, sum_high_cnt, ans);
        Update_P_cnt(cur.p, 1);
        Update_P(cur.p, cur.p);
        sum += cur.p;
    }
    
    printf("%lld\n", ans);
    
    

    return 0;
}
