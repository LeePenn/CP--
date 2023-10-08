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
const int N = 30000 + 10;
int n, m;
int fa[N], sz[N], under[N];

void Init() {
    for (int i = 0; i < N; ++i) fa[i] = i, sz[i] = 1, under[i] = 0;
}

int find(int x) {
    if (fa[x] != x) {
        int t = find(fa[x]);
        under[x] += under[fa[x]];
        fa[x] = t;
    }
    return fa[x];
}

void Uni(int x, int y) {
    x = find(x), y = find(y);
    if (x != y) {
        fa[x] = y;
        under[x] = sz[y];
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
    
    string s;
    scanf("%d", &n);
    int x, y;
    Init();
    getline(cin, s);
    char c;
    for (int i = 1; i <= n; ++i) {
        c = getchar();
        if (c == 'M') {
            scanf("%d%d", &x, &y);
            Uni(x, y);
        } else if (c == 'C') {
            scanf("%d", &x);
            find(x);
            printf("%d\n", under[x]);
        }
        getline(cin, s);
    }
    
    return 0;
}