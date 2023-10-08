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
const int N = 10000 + 10;
int T, n, m;
int d;
LL x[N], y[N];
int g[N];
int fa[N];

void Init() {
    for (int i = 1; i <= n; ++i) fa[i] = i;
    memset(g, 0, sizeof(g));
}

double getDist(int i, int j) {
    return sqrt(((double)x[i] - x[j]) * ((double)x[i] - x[j]) + ((double)y[i] - y[j]) * ((double)y[i] - y[j]));
}

int find(int x) {
    if (fa[x] != x) fa[x] = find(fa[x]);
    return fa[x];
}

void Uni(int x, int y) {
    x = find(x), y = find(y);
    if (x != y) {
        fa[y] = x;
    }
}

void Fix(int u) {
    for (int v = 1; v <= n; ++v) {
        if (u == v) continue;
        if (g[v] && getDist(v, u) <= d) {
            Uni(u, v);
        }
    }
}

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    string s;
    char c;
    int u, v;
    while (scanf("%d %d", &n, &d) == 2) {
        Init();
        for (int i = 1; i <= n; ++i) {
            scanf("%lld %lld", &x[i], &y[i]);
        }
        getline(cin, s);
        c = getchar();
        while (c == 'S' || c == 'O') {
            if (c == 'O') {
                scanf("%d", &u);
                g[u] = true;
                Fix(u);
            } else if (c == 'S') {
                scanf("%d%d", &u, &v);
                if (find(u) == find(v)) printf("SUCCESS\n");
                else printf("FAIL\n");
            }
            getline(cin, s);
            c = getchar();
        }
        
    }
    return 0;
}