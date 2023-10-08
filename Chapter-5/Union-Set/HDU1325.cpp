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
int fa[N], in[N];
int Case;

void Init() {
    for (int i = 1; i < N; ++i) {
        fa[i] = i;
    }
    memset(in, 0, sizeof(in));
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
        fa[y] = x;
    }
}

bool Check() {
    int x, y;
    bool flag = false;
    set<int> node;
    while (1) {
        scanf("%d%d", &x, &y);
        if (x + y == 0) {
            break;
        }
        if (x < 0) exit(0);
        in[y]++;
        node.insert(x); node.insert(y);
        int fx = find(x), fy = find(y);
        if (fx == fy || in[y] > 1) {
            flag = true;
        }
        Uni(fx, fy);
    }
    int num = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        if (in[*it] == 0) {
            num++;
        }
    }
    if (flag || num > 1) return false;
    return true;
}

void Solve() {
    Init();
    bool k = Check();
    if (k) {
        printf("Case %d is a tree.\n", Case);
    } else {
        printf("Case %d is not a tree.\n", Case);
    }
    Case++;
}

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    Case = 1;
    while (1) Solve();
    
    
    return 0;
}