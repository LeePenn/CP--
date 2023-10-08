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
const int N = 1000 + 5;
char s1[N], s2[N];
int f[N][N];

void Solve() {
    int l1 = strlen(s1 + 1), l2 = strlen(s2 + 1);
    memset(f, 0, sizeof(f));
    for (int i = 1; i <= l1; ++i) {
        for (int j = 1; j <= l2; ++j) {
            f[i][j] = max(f[i - 1][j], f[i][j - 1]);
            if (s1[i] == s2[j]) f[i][j] = max(f[i][j], f[i - 1][j - 1] + 1);
        }
    }
    printf("%d\n", f[l1][l2]);
}

int main() {
    // POJ 上有时 scanf 比 cin 慢 = =！！
    ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    char ch;
    while (scanf("%s%s", s1 + 1, s2 + 1) == 2) {
        Solve();
    }
    
    return 0;
}
