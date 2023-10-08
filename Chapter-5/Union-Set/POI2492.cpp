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
const int N = 2000 + 10;
int T, n, m;
int fa[N << 1];

void Init() {
    for (int i = 1; i <= 2 * n; ++i) fa[i] = i;
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

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    scanf("%d", &T);
    int x, y;
    for (int i = 1; i <= T; ++i) {
        bool flag = true;
        scanf("%d%d", &n, &m);
        Init();
        for (int j = 1; j <= m; ++j) {
            scanf("%d%d", &x, &y);
            if (find(x) == find(y)) {
                flag = false;
            } else {
                Uni(x, y + n); Uni(x + n, y);
            }
        }
        if (!flag) printf("Scenario #%d:\nSuspicious bugs found!\n\n", i);
        else printf("Scenario #%d:\nNo suspicious bugs found!\n\n", i);
    }
    
    return 0;
}