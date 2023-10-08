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
const int N = 10000 + 5;
int n, a[N];

void QuickSort(int l, int r) {
    if (l >= r) return;
    int mid = (l + r) >> 1;
    int i = l, j = r;
    while (i <= j) {
        while (a[i] < a[mid]) i++;
        while (a[j] > a[mid]) j--;
        if (i <= j) {
            int t = a[i];
            a[i] = a[j];
            a[j] = t;
            i++, j--;
        }
    }
    if (j > l) QuickSort(l, j);
    if (i < r) QuickSort(i, r);
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
    for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    QuickSort(1, n);
    printf("%d\n", a[(n + 1) >> 1]);
    

    return 0;
}
