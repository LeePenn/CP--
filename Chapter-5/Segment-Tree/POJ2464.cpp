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
const int N = 200000 + 5;
int n;
int trl[N], trr[N];
struct Point {
    int x, y;
    bool operator <(const Point& rh) const {
        return x < rh.x;
    }
}p[N];
int y[N];
vector<int> ollie;

int lowbit(int i) {
    return i & (-i);
}

void Update(int tr[], int i, int v) {
    while (i <= n) {
        tr[i] += v;
        i += lowbit(i);
    }
}

int Query(int tr[], int i) {
    int ret = 0;
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
            scanf("%d%d", &p[i].x, &p[i].y);
            y[i] = p[i].y;
        }
        sort(y + 1, y + n + 1);
        int ycnt = unique(y + 1, y + n + 1) - y - 1;
        
        // printf("!! %d\n", ycnt);
        // for (int i = 1; i <= ycnt; ++i) printf("%d ", y[i]);
        // printf("\n");
        // exit(0);
        
        sort(p + 1, p + n + 1);
        for (int i = 1; i <= n; ++i) {
            p[i].y = lower_bound(y + 1, y + ycnt + 1, p[i].y) - y;
        }
        p[n + 1].x = p[n].x + 1;
        
        memset(trl, 0, sizeof(trl));
        memset(trr, 0, sizeof(trr));
        for (int i = 1; i <= n; ++i) {
            Update(trr, p[i].y, 1);
        }
        
        int st = 1;
        int stan = -1;
        for (int i = 1; i <= n; ++i) {
            if (p[i].x != p[i + 1].x) {
                for (int j = st; j <= i; ++j) {
                    Update(trr, p[j].y, -1);
                }
                int tmpo = -1, tmps = -1;
                for (int j = st; j <= i; ++j) {
                    int a = Query(trr, ycnt) - Query(trr, p[j].y) + Query(trl, p[j].y - 1);
                    int b = Query(trl, ycnt) - Query(trl, p[j].y) + Query(trr, p[j].y - 1);
                    if (b == tmpo) {
                        tmps = min(tmps, a);
                    }
                    if (b > tmpo) {
                        tmpo = b;
                        tmps = a;
                    }
                }
                if (tmps > stan) {
                    ollie.clear();
                    stan = tmps;
                } 
                if (tmps == stan) {
                    ollie.push_back(tmpo);
                }
                for (int j = st; j <= i; ++j) Update(trl, p[j].y, 1);
                st = i + 1;
            }
        }
        
        sort(ollie.begin(), ollie.end());
        int m = unique(ollie.begin(), ollie.end()) - ollie.begin();
        printf("Stan: %d; Ollie:", stan);
        for (int i = 0; i < m; ++i) printf(" %d", ollie[i]);
        printf(";\n");
        
    }
    

    return 0;
}
