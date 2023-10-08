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
const int N = 1e5 + 10, INF = 1000000000;
int kase, q, n;
struct ST {
    int l, r, change, sum;
    ST() { l = r = change = sum = 0; }
    ST(int l, int r, int change, int sum): l(l), r(r), change(change), sum(sum) {}
}tr[N << 2];

void PushUp(int u) {
    tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
}

void PushDown(int u) {
    if (tr[u].change != 0) {
        int t = tr[u].change;
        tr[u << 1].sum = t * (tr[u << 1].r - tr[u << 1].l + 1);
        tr[u << 1 | 1].sum = t * (tr[u << 1 | 1].r - tr[u << 1 | 1].l + 1);
        
        tr[u << 1].change = t;
        tr[u << 1 | 1].change = t;
        
        tr[u].change = 0;
    }
}

void BuildTree(int u, int l, int r) {
    tr[u] = ST(l, r, 0, 1);
    if (l == r) {
        return;
    }
    int mid = (l + r) >> 1;
    BuildTree(u << 1, l, mid);
    BuildTree(u << 1 | 1, mid + 1, r);
    PushUp(u);
}

void Update(int u, int l, int r, int li, int ri, int x) {
    if (r < li || l > ri) return;
    if (l >= li && r <= ri) {
        tr[u].sum = x * (r - l + 1);
        tr[u].change = x;
        return;
    }
    
    PushDown(u);
    int mid = (l + r) >> 1;
    Update(u << 1, l, mid, li, ri, x);
    Update(u << 1 | 1, mid + 1, r, li, ri, x);
    PushUp(u);
}

int Query(int u, int l, int r, int li, int ri) {
    if (r < li || r > ri) return 0;
    if (l >= li && r <= ri) return tr[u].sum;
    
    PushDown(u);
    int mid = (l + r) >> 1;
    int ret = 0;
    if (mid >= li) ret += Query(u << 1, l, mid, li, ri);
    if (mid < ri) ret += Query(u << 1 | 1, mid + 1, r, li, ri);
    return ret;
}

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    scanf("%d", &kase);
    int x, y, z;
    for (int i = 1; i <= kase; ++i) {
        scanf("%d", &n);
        BuildTree(1, 1, n);
        scanf("%d", &q);
        for (int i = 1; i <= q; ++i) {
            scanf("%d%d%d", &x, &y, &z);
            Update(1, 1, n, x, y, z);
        }
        printf("Case %d: The total value of the hook is %d.\n", i, Query(1, 1, n, 1, n));
        
    }
    

    return 0;
}
