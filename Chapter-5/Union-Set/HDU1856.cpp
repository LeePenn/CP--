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
const int N = 100000 + 10;
int T, n, m;
int fa[N], sz[N];

void Init() {
    for (int i = 1; i < N; ++i) fa[i] = i, sz[i] = 1;
}

int find(int x) {
    if (fa[x] != x) {
        fa[x] = find(fa[x]);
    }
    return fa[x];
}

void Uni(int x, int y) {
    x = find(x), y = find(y);
    if (x != y) {
        fa[x] = y;
        sz[y] += sz[x];
    }
}

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    int x, y;
    while (scanf("%d", &n) == 1) {
        Init();
        int maxx = 1;
        for (int i = 1; i <= n; ++i) {
            scanf("%d%d", &x, &y);
            Uni(x, y);
            maxx = max(x, y);
        }
        int ans = 0;
        for (int i = 1; i <= maxx; ++i) {
            ans = max(ans, sz[fa[i]]);
        }
        printf("%d\n", ans);
    }
    
    
    
    return 0;
}