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
const int N = 200000 + 10;
int n, m;
int x, y;
struct ST {
    int l, r;
    int minn, maxx;
}tr[N << 2];

void PushUp(int u) {
    tr[u].minn = min(tr[u << 1].minn, tr[u << 1 | 1].minn);
    tr[u].maxx = max(tr[u << 1].maxx, tr[u << 1 | 1].maxx);
}

void BuildTree(int u, int l, int r) {
    if (l == r) {
        tr[u].l = l; tr[u].r = r;
        scanf("%d", &tr[u].minn);
        tr[u].maxx = tr[u].minn;
        return;
    }
    
    int mid = (l + r) >> 1;
    BuildTree(u << 1, l, mid);
    BuildTree(u << 1 | 1, mid + 1, r);
    PushUp(u);
}

int QueryMax(int u, int l, int r, int li, int ri) {
    if (r < li || l > ri) return 0;
    if (l >= li && r <= ri) {
        return tr[u].maxx;
    }
    
    int mid = (l + r) >> 1;
    int ret = 0;
    if (mid >= li) ret = max(ret, QueryMax(u << 1, l, mid, li, ri));
    if (mid < ri) ret = max(ret, QueryMax(u << 1 | 1, mid + 1, r, li, ri));
    return ret;
}

int QueryMin(int u, int l, int r, int li, int ri) {
    if (r < li || l > ri) return 100000000;
    if (l >= li && r <= ri) {
        return tr[u].minn;
    }
    
    int mid = (l + r) >> 1;
    int ret = 100000000;
    if (mid >= li) ret = min(ret, QueryMin(u << 1, l, mid, li, ri));
    if (mid < ri) ret = min(ret, QueryMin(u << 1 | 1, mid + 1, r, li, ri));
    return ret;
}

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    scanf("%d%d", &n, &m);
    BuildTree(1, 1, n);
    for (int i = 1; i <= m; ++i) {
        scanf("%d%d", &x, &y);
        printf("%d\n", QueryMax(1, 1, n, x, y) - QueryMin(1, 1, n, x, y));
    }
    

    return 0;
}
