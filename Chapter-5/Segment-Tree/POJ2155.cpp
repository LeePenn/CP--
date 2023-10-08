#include <stdio.h>
#include <iostream>
#include <stack>
#include <complex>
#include <vector>
#include <cstring>

// #define mytest

using namespace std;
typedef long long LL;
const int N = 1000 + 5;
int kase;
int n, m;
int tr[N][N];
char ch;
int xx1, yy1, xx2, yy2;

void Debug() {
    
}

int lowbit(int x) {
    return x & (-x);
}

int Query(int x, int y) {
    int ret = 0;
    for (int i = x; i > 0; i -= lowbit(i)) {
        for (int j = y; j > 0; j -= lowbit(j)) {
            ret += tr[i][j];
        }
    }
    return ret;
}

void SubUpdate(int x, int y, int v) {
    for (int i = x; i <= n; i += lowbit(i)) {
        for (int j = y; j <= n; j += lowbit(j)) {
            tr[i][j] += v;
        }
    }
}

void Update(int x1, int y1, int x2, int y2) {
    SubUpdate(x1, y1, 1);
    if (x2 < n) SubUpdate(x2 + 1, y1, -1);
    if (y2 < n) SubUpdate(x1, y2 + 1, -1);
    if (x2 < n && y2 < n) SubUpdate(x2 + 1, y2 + 1, 1);
}

int main() {
    // 特别注意！！cin cout 加上取消同步后比 scanf 和 printf 要快
    ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    // cin >> kase;
    scanf("%d", &kase);
    while (kase--) {
        // cin >> n >> m;
        scanf("%d%d", &n, &m);
        getchar();
        memset(tr, 0, sizeof(tr));
        for (int i = 1; i <= m; ++i) {
            ch = getchar();
            // cin >> xx1 >> yy1;
            scanf("%d%d", &xx1, &yy1);
            if (ch == 'C') {
                // cin >> xx2 >> yy2;
                scanf("%d%d", &xx2, &yy2);
                Update(xx1, yy1, xx2, yy2);
            } else {
                printf("%d\n", Query(xx1, yy1) % 2);
                // cout << (Query(xx1, yy1) % 2) << endl;
            }
            getchar();
        }
        printf("\n");
    }
    

    return 0;
}