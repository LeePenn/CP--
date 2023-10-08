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
const int N = 2e4 + 10, INF = 100000000;
struct Poster {
    int l, r;
    Poster() { l = r = 0; }
    Poster(int l, int r): l(l), r(r) {}
}p[N];
int kase, n, a[N], tot, m;
bool vis[N];
struct ST {
    int l, r, col, type;
    ST() { l = r = col = type = 0; }
    ST(int l, int r, int col, int type): l(l), r(r), col(col), type(type) {}
}tr[N << 2];
int hs[10000010];
int ans;

void BuildTree(int u, int l, int r) {
    if (l > r) return;
    
    tr[u] = ST(l, r, 0, 0);
    if (l == r) return;
    int mid = (l + r) >> 1;
    BuildTree(u << 1, l, mid);
    BuildTree(u << 1 | 1, mid + 1, r);
}

void PushDown(int u) {
    if (tr[u].type == 0) return;
    
    tr[u << 1].col = tr[u << 1 | 1].col = tr[u].col;
    tr[u << 1].type = tr[u << 1 | 1].type = tr[u].type;
    tr[u].type = 0;
}

void PushUp(int u) {
    if (tr[u << 1].col == tr[u << 1 | 1].col) tr[u].col = tr[u << 1].col;
    else tr[u].col = 0;
}

void Update(int u, int l, int r, int li, int ri, int id) {
    if (l > r) return;
    
    if (l >= li && r <= ri) {
        tr[u].col = tr[u].type = id;
        return;
    }
    PushDown(u);
    
    int mid = (l + r) >> 1;
    if (mid >= li) Update(u << 1, l, mid, li, ri, id);
    if (mid < ri) Update(u << 1 | 1, mid + 1, r, li, ri, id);
    PushUp(u);
}

void Query(int u, int l, int r, int li, int ri) {
    if (r < li || l > ri) return;
    if (tr[u].col != 0) {
        if (!vis[tr[u].col]) {
            ans++;
            vis[tr[u].col] = true;
        }
        return;
    }
    // PushDown(u);
    int mid = (l + r) >> 1;
    if (mid >= li) Query(u << 1, l, mid, li, ri);
    if (mid < ri) Query(u << 1 | 1, mid + 1, r, li, ri);
}

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    scanf("%d", &kase);
    while (kase--) {
        scanf("%d", &n);
        memset(vis, 0, sizeof(vis));
        memset(hs, 0, sizeof(hs));
        tot = 0;
        for (int i = 1; i <= n; ++i) {
            scanf("%d%d", &p[i].l, &p[i].r);
            a[++tot] = p[i].l; a[++tot] = p[i].r;
        }
        sort(a + 1, a + tot + 1);
        m = unique(a + 1, a + tot + 1) - a - 1;
        for (int i = 1; i <= m; ++i) {
            hs[a[i]] = i;
        }
        BuildTree(1, 1, m);
        for (int i = 1; i <= n; ++i) {
            // printf("%d %d\n", mp[p[i].l], mp[p[i].r]);
            Update(1, 1, m, hs[p[i].l], hs[p[i].r], i);
        }
        ans = 0;
        Query(1, 1, m, 1, m);
        printf("%d\n", ans);
    }

    return 0;
}
