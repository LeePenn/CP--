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
const int N = 1e5 + 10, INF = 100000000;
LL n, q;
LL a[N];
struct ST {
    LL l, r;
    LL v, add, sum;
    ST() { l = r = v = add = sum = 0LL; }
    ST(LL l, LL r, LL v, LL add, LL sum): l(l), r(r), v(v), add(add), sum(sum) {}
}tr[N << 2];

void PushDown(LL u, LL l, LL r) {
    if (tr[u].add == 0) return;
    LL mid = (l + r) >> 1;
    tr[u << 1].add += tr[u].add;
    tr[u << 1].sum = tr[u << 1].sum + tr[u].add * (mid - l + 1);
    
    tr[u << 1 | 1].add += tr[u].add;
    tr[u << 1 | 1].sum = tr[u << 1 | 1].sum + tr[u].add * (r - mid);
    
    tr[u].add = 0;
}

void PushUp(LL u) {
    tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
}

void BuildTree(LL u, LL l, LL r) {
    if (l == r) {
        tr[u] = ST(l, r, a[l], 0, a[l]);
        return;
    }
    
    LL mid = (l + r) >> 1;
    BuildTree(u << 1, l, mid);
    BuildTree(u << 1 | 1, mid + 1, r);
    PushUp(u);
}

void Update(LL u, LL l, LL r, LL li, LL ri, LL x) {
    // if (r < li || l > ri) return;
    if (l >= li && r <= ri) {
        tr[u].sum = tr[u].sum + x * (r - l + 1);
        tr[u].add += x;
        return;
    }
    
    PushDown(u, l, r);
    LL mid = (l + r) >> 1;
    if (mid >= li) Update(u << 1, l, mid, li, ri, x);
    if (mid < ri) Update(u << 1 | 1, mid + 1, r, li, ri, x);
    PushUp(u);
}

LL Query(LL u, LL l, LL r, LL li, LL ri) {
    // if (r < li || l > ri) return 0;
    if (l >= li && r <= ri) return tr[u].sum;
    
    PushDown(u, l, r);
    LL mid = (l + r) >> 1;
    LL ret = 0;
    if (mid >= li) ret = ret + Query(u << 1, l, mid, li, ri);
    if (mid < ri) ret = ret + Query(u << 1 | 1, mid + 1, r, li, ri);
    return ret;
}

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    scanf("%lld%lld", &n, &q);
    for (int i = 1; i <= n; ++i) scanf("%lld", &a[i]);
    BuildTree(1, 1, n);
    char c;
    LL x, y;
    LL z;
    getchar();
    for (int i = 1; i <= q; ++i) {
        c = getchar();
        if (c == 'C') {
            scanf("%lld%lld%lld", &x, &y, &z);
            // printf("%c %d %d %lld\n", c, x, y, z);
            Update(1, 1, n, x, y, z);
        } else if (c == 'Q') {
            scanf("%lld%lld", &x, &y);
            // printf("%c %d %d\n", c, x, y);
            printf("%lld\n", Query(1, 1, n, x, y));
        }
        getchar();
    }

    return 0;
}
