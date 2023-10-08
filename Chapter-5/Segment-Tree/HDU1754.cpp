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
const int N = 2e5 + 10, INF = 1000000000;
int kase, q, n;
struct ST {
    int l, r, v, mx;
    ST() { l = r = v = mx = 0; }
    ST(int l, int r, int v, int mx): l(l), r(r), v(v), mx(mx) {}
}tr[N << 2];
int a[N];

void PushUp(int u) {
    tr[u].mx = max(tr[u << 1].mx, tr[u << 1 | 1].mx);
}

void PushDown(int u) {
    
}

void BuildTree(int u, int l, int r) {
    tr[u] = ST(l, r, 0, 0);
    if (l == r) {
        scanf("%d", &tr[u].v);
        tr[u].mx = tr[u].v;
        return;
    }
    int mid = (l + r) >> 1;
    BuildTree(u << 1, l, mid);
    BuildTree(u << 1 | 1, mid + 1, r);
    PushUp(u);
}

void Update(int u, int l, int r, int pos, int x) {
    if (r < pos || l > pos) return;
    if (l == r && l == pos) {
        tr[u].v = x;
        tr[u].mx = x;
        return;
    }
    
    int mid = (l + r) >> 1;
    if (mid >= pos) Update(u << 1, l, mid, pos, x);
    else if (mid < pos) Update(u << 1 | 1, mid + 1, r, pos, x);
    PushUp(u);
}

int Query(int u, int l, int r, int li, int ri) {
    if (r < li || l > ri) return -1;
    if (l >= li && r <= ri) return tr[u].mx;
    
    int mid = (l + r) >> 1;
    int ret = 0;
    if (mid >= li) ret = max(ret, Query(u << 1, l, mid, li, ri));
    if (mid < ri) ret = max(ret, Query(u << 1 | 1, mid + 1, r, li, ri));
    return ret;
}

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    char c;
    int x, y;
    while (scanf("%d%d", &n, &q) == 2) {
        // for (int i = 1; i <= n; ++i) {
        //     scanf("%d", &a[i]);
        // }
        BuildTree(1, 1, n);
        getchar();
        while (q--) {
            c = getchar();
            if (c == 'U') {
                scanf("%d%d", &x, &y);
                Update(1, 1, n, x, y);
                // printf("%c %d %d\n", c, x, y);
            } else if (c == 'Q') {
                scanf("%d%d", &x, &y);
                // printf("%c %d %d\n", c, x, y);
                printf("%d\n", Query(1, 1, n, x, y));
            }
            getchar();
        }
    }
    

    return 0;
}
