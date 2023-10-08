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
const int N = 40000 + 10;
int T;
LL n, m;
LL f[N][20];
LL dist[N];
struct Edge {
    LL v, nxt, c;
    Edge() { v = nxt = c = 0; }
    Edge(LL _v, LL _nxt, LL _c) {
        v = _v;
        nxt = _nxt;
        c = _c;
    }
}e[N << 1];
LL hd[N], tot, dep[N];

void Init() {
    memset(f, 0, sizeof(f));
    memset(dist, 0, sizeof(dist));
    memset(hd, 0, sizeof(hd));
    memset(dep, 0, sizeof(dep));
    tot = 0;
}

void AddEdge(LL x, LL y, LL z) {
    e[++tot] = Edge(y, hd[x], z);
    hd[x] = tot;
}

void Dfs(LL u, LL pa) {
    dep[u] = dep[pa] + 1;
    for (int i = 1; i < 20; ++i) {
        f[u][i] = f[f[u][i - 1]][i - 1];
    }
    
    for (int i = hd[u]; i; i = e[i].nxt) {
        LL v = e[i].v, c = e[i].c;
        if (v == pa) continue;
        f[v][0] = u;
        dist[v] = dist[u] + c;
        Dfs(v, u);
    }
}

LL Lca(LL u, LL v) {
    if (dep[u] < dep[v]) swap(u, v);
    for (int i = 19; i >= 0; --i) {
        if (dep[f[u][i]] >= dep[v]) {
            u = f[u][i];
        }
        if (u == v) return u;
    }
    for (int i = 19; i >= 0; --i) {
        if (f[u][i] != f[v][i]) {
            u = f[u][i];
            v = f[v][i];
        }
    }
    return f[u][0];
}

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    scanf("%d", &T);
    LL x, y, z;
    while (T--) {
        Init();
        scanf("%lld%lld", &n, &m);
        for (int i = 1; i < n; ++i) {
            scanf("%lld%lld%lld", &x, &y, &z);
            AddEdge(x, y, z); AddEdge(y, x, z);
        }
        Dfs(1, 0);
        
        for (int i = 1; i <= m; ++i) {
            scanf("%lld%lld", &x, &y);
            // printf("!! %lld %lld %lld %lld\n", dist[x], dist[y], Lca(x, y), dist[Lca(x, y)]);
            printf("%lld\n", dist[x] + dist[y] - 2 * dist[Lca(x, y)]);
        }
    }

    return 0;
}
