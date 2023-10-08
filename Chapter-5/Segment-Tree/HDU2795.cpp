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
int h, w, n;
struct ST {
    int l, r, mx;
    ST() { l = r = mx = 0; }
    ST(int l, int r, int mx): l(l), r(r), mx(mx) {}
}tr[N << 2];

void PushUp(int u) {
    tr[u].mx = max(tr[u << 1].mx, tr[u << 1 | 1].mx);
}

void BuildTree(int u, int l, int r) {
    tr[u] = ST(l, r, 0);
    if (l == r) {
        tr[u].mx = w;
        return;
    }
    int mid = (l + r) >> 1;
    BuildTree(u << 1, l, mid);
    BuildTree(u << 1 | 1, mid + 1, r);
    PushUp(u);
}

int Query(int u, int l, int r, int x) {
    if (l == r) {
        if (tr[u].mx < x) return -1;
        tr[u].mx -= x;
        return l;
    }
    
    int mid = (l + r) >> 1;
    int ret = -1;
    if (tr[u << 1].mx >= x) {
        ret = Query(u << 1, l, mid, x);
        if (ret != -1) {
            PushUp(u);
        }
    } else {
        ret = Query(u << 1 | 1, mid + 1, r, x);
        if (ret != -1) {
            PushUp(u);
        }
    }
    return ret;
}

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    int x;
    while (scanf("%d%d%d", &h, &w, &n) == 3) {
        if (h > n) h = n;
        BuildTree(1, 1, h);
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &x);
            printf("%d\n", Query(1, 1, h, x));
        }
    }
    

    return 0;
}
