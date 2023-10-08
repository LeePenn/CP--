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
const int N = 100000 + 5;
LL a[N], b[N], cnt;
LL n, k;

void Merge(int l, int mid, int r) {
    int i = l, j = mid + 1, t = l;
    while (i <= mid && j <= r) {
        if (a[i] > a[j]) {
            b[t] = a[j];
            t++, j++;
            cnt += mid - i + 1;
        } else {
            b[t] = a[i];
            t++, i++;
        }
    }
    while (i <= mid) {
        b[t] = a[i];
        t++, i++;
    }
    while (j <= r) {
        b[t] = a[j];
        t++, j++;
    }
    for (i = l; i <= r; ++i) a[i] = b[i];
}

void MergeSort(int l, int r) {
    if (l >= r) return;
    int mid = (l + r) >> 1;
    MergeSort(l, mid);
    MergeSort(mid + 1, r);
    Merge(l, mid, r);
}

int main() {
    // POJ 上有时 scanf 比 cin 慢 = =！！
    ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    while (scanf("%lld%lld", &n, &k) == 2) {
        cnt = 0;
        for (int i = 1; i <= n; ++i) scanf("%lld", &a[i]);
        MergeSort(1, n);
        if (cnt <= k) printf("0\n");
        else printf("%lld\n", cnt - k);
    }

    return 0;
}
