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
const int N = 3000 + 5, M = 60000 + 5, INF = 1000000000;
int n, m;
int fix;
int f[22][805], path[22][805];
int d[210], p[210], nd[210], np[210];
int id[22];

void Init() {
    memset(f, -1, sizeof(f));
    memset(path, 0, sizeof(path));
    memset(id, 0, sizeof(id));
    memset(d, 0, sizeof(d));
    memset(p, 0, sizeof(p));
    memset(nd, 0, sizeof(nd));
    memset(np, 0, sizeof(np));
}

bool find(int i, int j, int k) {
    while (i > 0 && path[i][j] != k) {
        j -= nd[path[i][j]];
        i--;
    }
    return i > 0 ? 1 : 0;
}

/*!SECTION
常规想法，f(i, j) 表示i 个人中|dj - pj|为 j 情况下 dj + pj 最大的值，但是发现如果新加入一个人决策，会替换之前 i - 1个人的情况，整个决策路径会发生变化
这样就不满足 DP 的无后效性的使用条件，所以这个状态表示是错误的，需要重新设计，使用 f(i, j) i表示1 - m的选择人后，新加入一个决策，不会改变之前决定的路径
因此可行
*/
int main() {
    // POJ 上有时 scanf 比 cin 慢 = =！！
    ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    int kase = 0;
    while (scanf("%d%d", &n, &m) == 2 && (n + m)) {
        kase++;
        Init();
        for (int i = 1; i <= n; ++i) {
            scanf("%d%d", &d[i], &p[i]);
            nd[i] = d[i] - p[i];
            np[i] = d[i] + p[i];
        }
        fix = m * 20;
        f[0][fix] = 0;
        for (int i = 1; i <= m; ++i) {
            for (int j = 0; j <= (fix << 1); ++j) {
                if (f[i - 1][j] >= 0) {
                    for (int k = 1; k <= n; ++k) {
                        if ((j + nd[k] <= (fix << 1)) && (f[i][j + nd[k]] < f[i - 1][j] + np[k]) && !find(i - 1, j, k)) {
                            f[i][j + nd[k]] = f[i - 1][j] + np[k];
                            path[i][j + nd[k]] = k;
                        }
                    }
                }
            }
        }
        
        int sumd = 0, sump = 0, dd = 0;
        for (int i = 0; i <= fix; ++i) {
            if (f[m][fix - i] >= 0 || f[m][fix + i] >= 0) {
                dd = i;
                break;
            }
        }
        
        int sum = f[m][fix - dd] > f[m][fix + dd] ? fix - dd : fix + dd;
        sumd = (f[m][sum] + sum - fix) / 2;
        sump = (f[m][sum] - sum + fix) / 2;
        
        printf("Jury #%d\n", kase);
        printf("Best jury has value %d for prosecution and value %d for defence:\n", sumd, sump);
        
        int tot = 0;
        // 这里不能用 while (m--), m会在循环中就变成 m - 1
        for (int i = m; i > 0; --i) {
            id[++tot] = path[i][sum];
            sum -= nd[path[i][sum]];
        }
        
        sort(id + 1, id + m + 1);
        for (int i = 1; i <= m; i++){
            printf(" %d", id[i]);
        }
        printf("\n\n");
    }
    
    
    return 0;
}
