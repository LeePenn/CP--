#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>

// #define mytest

using namespace std;
typedef long long LL;
const int N = 1e4 + 10, INF = 1000000000;
int n, a[N];
int b[N], c[N];
LL cnt, ans;
int tr[N];

void MergeSort(int l, int r) {
    if (l >= r) return;
    int mid = (l + r) >> 1;
    MergeSort(l, mid); MergeSort(mid + 1, r);
    int i, j, k;
    i = l, j = mid + 1, k = l;
    while (i <= mid && j <= r) {
        if (b[i] <= b[j]) {
            c[k] = b[i];
            k++, i++;
        } else {
            c[k] = b[j];
            cnt = cnt + (mid - i + 1);
            k++, j++;
        }
    }
    while (i <= mid) {
        c[k] = b[i];
        k++, i++;
    }
    while (j <= r) {
        c[k] = b[j];
        k++, j++;
    }
    for (i = l; i <= r; ++i) b[i] = c[i];
}

void Update(int i, int x) {
    while (i <= n) {
        tr[i] += x;
        i += i & (-i);
    }
}

int Query(int i) {
    int ret = 0;
    while (i) {
        ret += tr[i];
        i -= i & (-i);
    }
    return ret;
}

void Solve() {
    for (int i = 1; i <= n; ++i) {
        Update(a[i], 1);
    }
    
    for (int i = 1; i < n; ++i) {
        int t1 = Query(a[i] - 1);
        // printf("!! %d %d\n", i, t1);
        cnt -= t1;
        Update(a[i], -1);
        int t2 = Query(n) - Query(a[i + n]);
        // printf("## %d %d\n", i, t2);
        cnt += t2;
        ans = min(ans, cnt);
        Update(a[i + n], 1);
    }
    
    printf("%lld\n", ans);
}

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    while (scanf("%d", &n) == 1 && n) {
        memset(tr, 0, sizeof(tr));
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
            a[i]++;
        }
        memcpy(b, a, sizeof(b));
        cnt = 0;
        MergeSort(1, n);
        // printf("%lld\n", cnt);
        for (int i = 1; i <= 2 * n; ++i) {
            a[i + n] = a[i];
        }
        ans = cnt;
        Solve();
    }
    

    return 0;
}
