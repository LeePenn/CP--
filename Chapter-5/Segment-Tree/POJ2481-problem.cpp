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
const int N = 1000000 + 5, MAXN = 131072;
int n;
struct Cow {
    int st, ed;
    int id;
    // bool operator <(const Cow& rh) const {
    //     return st < rh.st || (st == rh.st && ed >= rh.ed);
    // }
}c[N];
int tr[N];
int maxed;
int ans[N];

bool cmp(Cow a, Cow b) {
    return a.st < b.st || (a.st == b.st && a.ed >= b.ed);
}

inline int lowbit(int i) {
    return i & (-i);
}

inline void Update(int i, int x) {
    while (i <= maxed) {
        tr[i] += x;
        i += lowbit(i);
    }
}

inline int Query(int x) {
    int ret = 0;
    while (x) {
        ret += tr[x];
        x -= lowbit(x);
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
        memset(tr, 0, sizeof(tr));
        maxed = 0;
        for (int i = 1; i <= n; ++i) {
            scanf("%d%d", &c[i].st, &c[i].ed);
            c[i].id = i;
            maxed = max(maxed, c[i].ed);
        }
        sort(c + 1, c + n + 1, cmp);
        
        int i;
        for (i = 1; i <= n; ++i) {
            if (c[i].st == c[i - 1].st && c[i].ed == c[i - 1].ed) ans[c[i].id] = ans[c[i - 1].id];
            else {
                ans[c[i].id] = Query(maxed) - Query(c[i].ed - 1);
            }
            Update(c[i].ed, 1);
        }
        for (int i = 1; i <= n; ++i) printf("%d ", ans[i]);
        printf("\n");
    }

    return 0;
}
