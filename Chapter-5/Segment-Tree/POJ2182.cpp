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
struct ST {
    int l, r, len;
    ST() { l = r = len = 0; }
    ST(int l, int r, int len): l(l), r(r), len(len) {}
}tr[N << 2];
int n, a[N], ans[N];

void BuildTree(int u, int l, int r) {
    tr[u] = ST(l, r, r - l + 1);
    if (l == r) {
        return;
    }
    
    int mid = (l + r) >> 1;
    BuildTree(u << 1, l , mid);
    BuildTree(u << 1 | 1, mid + 1, r);
}

int Query(int u, int num) {
    tr[u].len--;
    if (tr[u].l == tr[u].r) return tr[u].l;
    
    if (tr[u << 1].len < num) return Query(u << 1 | 1, num - tr[u << 1].len);
    else return Query(u << 1, num);
}

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    scanf("%d", &n);
    for (int i = 2; i <= n; ++i) {
        scanf("%d", &a[i]);
    }
    BuildTree(1, 1, n);
    for (int i = n; i >= 1; i--) {
        ans[i] = Query(1, a[i] + 1);
    }
    for (int i = 1; i <= n; ++i) printf("%d\n", ans[i]);

    return 0;
}
