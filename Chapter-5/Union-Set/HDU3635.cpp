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
int fa[N], sz[N], trans[N];

void Init() {
    for (int i = 0; i < N; ++i) fa[i] = i, sz[i] = 1, trans[i] = 0;
}

int find(int x) {
    if (fa[x] != x) {
        int t = find(fa[x]);
        trans[x] += trans[fa[x]];
        fa[x] = t;
    }
    return fa[x];
}

void Uni(int x, int y) {
    x = find(x), y = find(y);
    if (x != y) {
        fa[x] = y;
        trans[x]++;
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
    scanf("%d", &T);
    int x, y;
    char c;
    for (int i = 1; i <= T; ++i) {
        scanf("%d%d", &n, &m);
        Init();
        getline(cin, s);
        printf("Case %d:\n", i);
        for (int j = 1; j <= m; ++j) {
            c = getchar();
            if (c == 'T') {
                scanf("%d%d", &x, &y);
                x = find(x), y = find(y);
                Uni(x, y);
            } else if (c == 'Q') {
                scanf("%d", &x);
                int t = find(x);
                // printf("## %d %d\n", x, t);
                printf("%d %d %d\n", t, sz[t], trans[x] + trans[t]);
            }
            getline(cin, s);
        }
        
    }
    
    
    
    return 0;
}