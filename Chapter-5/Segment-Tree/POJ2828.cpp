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
int n;
int pos[N], val[N];
struct ST {
    int l, r;
    int num;
    ST() { l = r = num = 0; }
    ST(int l, int r, int num): l(l), r(r), num(num) {}
}tr[N << 2];
int ans[N];

void PushUp(int u) {
    tr[u].num = tr[u << 1].num + tr[u << 1 | 1].num;
}

void BuildTree(int u, int l, int r) {
    tr[u] = ST(l, r, 1);
    if (l == r) return;
    int mid = (l + r) >> 1;
    BuildTree(u << 1, l, mid); 
    BuildTree(u << 1 | 1, mid + 1, r);
    PushUp(u);
}

void Update(int u, int l, int r, int p, int x) {
    if (l == r && l == p) {
        tr[u].num += x;
        return;
    }
    int mid = (l + r) >> 1;
    if (mid >= p) Update(u << 1, l, mid, p, x);
    if (mid < p) Update(u << 1 | 1, mid + 1, r, p, x);
    PushUp(u);
}

int Query(int u, int l, int r, int num) {
    if (l == r) {
        return l;
    }
    int mid = (l + r) >> 1;
    if (tr[u << 1].num >= num) return Query(u << 1, l, mid, num);
    else return Query(u << 1 | 1, mid + 1, r, num - tr[u << 1].num);
}

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    while (scanf("%d", &n) == 1) {
        for (int i = 1; i <= n; ++i) scanf("%d%d", &pos[i], &val[i]);
        BuildTree(1, 1, n);
        for (int i = n; i >= 1; --i) {
            int t = Query(1, 1, n, pos[i] + 1);
            ans[t] = val[i];
            Update(1, 1, n, t, -1);
            
        }
        for (int i = 1; i <= n; ++i) printf("%d ", ans[i]);
        printf("\n");
    }
    

    return 0;
}
