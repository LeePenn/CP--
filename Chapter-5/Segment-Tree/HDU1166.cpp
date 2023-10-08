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
const int N = 5e4 + 10, INF = 100000000;
int kase;
LL n, a[N];
struct ST {
    int l, r;
    LL v, sum;
    ST() { l = r = v = sum = 0; }
    ST(int l, int r, LL v, LL sum): l(l), r(r), v(v), sum(sum) {}
}tr[N << 2];

void PushUp(int u) {
    tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
}

void BuildTree(int u, int l, int r) {
    tr[u] = ST(l, r, 0, 0);
    if (l == r) {
        tr[u].v = tr[u].sum = a[l];
        return;
    }
    
    int mid = (l + r) >> 1;
    BuildTree(u << 1, l, mid);
    BuildTree(u << 1 | 1, mid + 1, r);
    PushUp(u);
}

void Update(int u, int l, int r, int pos, LL x) {
    if (r < pos || l > pos) return;
    if (l == r && pos == l) {
        tr[u].v += x;
        tr[u].sum += x;
        return;
    }
    int mid = (l + r) >> 1;
    if (mid >= pos) Update(u << 1, l, mid, pos, x);
    else if (mid < pos) Update(u << 1 | 1, mid + 1, r, pos, x);
    PushUp(u);
}

LL Query(int u, int l, int r, int li, int ri) {
    if (r < li || l > ri) return 0;
    
    if (l >= li && r <= ri) {
        return tr[u].sum;
    }
    
    int mid = (l + r) >> 1;
    LL ret = 0;
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
    char c[10];
    LL x, y;
    for (int i = 1; i <= kase; ++i) {
        scanf("%lld", &n);
        for (int j = 1; j <= n; ++j) {
            scanf("%lld", &a[j]);
        }
        BuildTree(1, 1, n);
        getchar();
        printf("Case %d:\n", i);
        while (1) {
            scanf("%s", c);
            if (c[0] == 'E') break;
            scanf("%lld%lld", &x, &y);
            if (c[0] == 'A') {
                Update(1, 1, n, x, y);
            } else if (c[0] == 'S') {
                Update(1, 1, n, x, -y);
            } else if (c[0] == 'Q') {
                printf("%lld\n", Query(1, 1, n, x, y));
            }
            getchar();
        }
    }
    

    return 0;
}
