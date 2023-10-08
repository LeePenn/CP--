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
const int N = 100000 + 10;
int n, m;
struct ST {
    int l, r;
    LL sum, min_sum, max_sum, lmin, lmax, rmin, rmax;
}tr[N << 2];
LL x, y;
LL a[N];

void PushUp(int u) {
    ST t1 = tr[u << 1], t2 = tr[u << 1 | 1];
    tr[u].sum = t1.sum + t2.sum;
    
    tr[u].min_sum = min(min(t1.min_sum, t2.min_sum), t1.rmin + t2.lmin);
    tr[u].max_sum = max(max(t1.max_sum, t2.max_sum), t1.rmax + t2.lmax);
    
    tr[u].lmin = min(t1.sum + t2.lmin, t1.lmin);
    tr[u].lmax = max(t1.sum + t2.lmax, t1.lmax);
    
    tr[u].rmin = min(t1.rmin + t2.sum, t2.rmin);
    tr[u].rmax = min(t1.rmax + t2.sum, t2.rmax);
}

void BuildTree(int u, int l, int r) {
    if (l == r) {
        tr[u].l = l; tr[u].r = r;
        tr[u].sum = tr[u].min_sum = tr[u].max_sum = a[l];
        tr[u].lmin = tr[u].lmax = tr[u].rmin = tr[u].rmax = a[l];
        return;
    }
    
    int mid = (l + r) >> 1;
    BuildTree(u << 1, l, mid);
    BuildTree(u << 1 | 1, mid + 1, r);
    PushUp(u);
}

void Update(int u, int l, int r, int pos, LL x) {
    if (l == r) {
        tr[u].sum = tr[u].min_sum = tr[u].max_sum = x;
        tr[u].lmin = tr[u].lmax = tr[u].rmin = tr[u].rmax = x;
        return;
    }
    
    int mid = (l + r) >> 1;
    if (mid >= pos) Update(u << 1, l, mid, pos, x);
    if (mid < pos) Update(u << 1 | 1, mid + 1, r, pos, x);
    PushUp(u);
}

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%lld", &a[i]);
    BuildTree(1, 1, n);
    scanf("%d", &m);
    for (int i = 1; i <= m; ++i) {
        scanf("%lld%lld", &x, &y);
        Update(1, 1, n, x, y);
        if (tr[1].sum == tr[1].max_sum) {
            printf("%lld\n", tr[1].sum - tr[1].min_sum);
        } else {
            printf("%lld\n", max(tr[1].max_sum, tr[1].sum - tr[1].min_sum));
        }
    }
    

    return 0;
}
