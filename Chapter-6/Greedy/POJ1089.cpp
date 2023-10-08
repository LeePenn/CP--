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
const int N = 500000 + 5;
struct Interval {
    int s, e;
    bool operator <(const Interval& rh) const {
        return s < rh.s || (s == rh.s && e > rh.e);
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
    
    while (scanf("%d", &n) == 1 && n) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d%d", &a[i].s, &a[i].e);
        }
        sort(a + 1, a + n + 1);
        vector<Interval> ans;
        int last_st = a[1].s, last_ed = a[1].e;
        for (int i = 1; i <= n; ++i) {
            if (a[i].s <= last_ed) last_ed = max(last_ed, a[i].e);
            else {
                ans.push_back({last_st, last_ed});
                last_st = a[i].s, last_ed = a[i].e;
            }
        }
        ans.push_back({last_st, last_ed});
        for (size_t i = 0; i < ans.size(); ++i) {
            printf("%d %d\n", ans[i].s, ans[i].e);
        }
    }

    return 0;
}
