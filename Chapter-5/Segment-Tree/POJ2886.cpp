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
const int N = 500000 + 10;
char s[N][10];
int n, k, v[N];
int f[N];
struct ST {
    int l, r;
    int num;
}tr[N];

void Init() {
    for (int i = 1; i < N; ++i) {
        for (int j = 1; i * j < N; ++j) f[i * j]++;
    }
    
    int maxv = 0;
    for (int i = 2; i < N; ++i) {
        if (f[i] > maxv) maxv = f[i];
        f[i] = maxv;
    }
}

void PushUp(int u) {
    tr[u].num = tr[u << 1].num + tr[u << 1 | 1].num;
}

void BuildTree(int u, int l, int r) {
    if (l == r) {
        tr[u].l = l; tr[u].r = r;
        tr[u].num = 1;
        return;
    }
    int mid = (l + r) >> 1;
    BuildTree(u << 1, l, mid);
    BuildTree(u << 1 | 1, mid + 1, r);
    PushUp(u);
}

int Update(int u, int l, int r, int pos, int v) {
    if (l == r) {
        tr[u].num = v;
        return l;
    }
    
    int mid = (l + r) >> 1;
    int ret;
    if (tr[u << 1].num >= pos) {
        ret = Update(u << 1, l, mid, pos, v);
    } else {
        ret = Update(u << 1 | 1, mid + 1, r, pos - tr[u << 1].num, v);
    }
    PushUp(u);
    return ret;
}

int Query(int u, int l, int r, int li, int ri) {
    if (l >= li && r <= ri) {
        return tr[u].num;
    }
    int mid = (l + r) >> 1;
    int ret = 0;
    if (mid >= li) ret += Query(u << 1, l, mid, li, ri);
    if (mid < ri) ret += Query(u << 1 | 1, mid + 1, r, li, ri);
    return ret;
}

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    Init();
    while (scanf("%d%d", &n, &k) == 2) {
        for (int i = 1; i <= n; ++i) {
            scanf("%s%d", s[i], &v[i]);
        }
        BuildTree(1, 1, n);
        
        int num = k, pos = Update(1, 1, n, num, 0);
        for (int i = 2; i <= n; ++i) {
            if (v[pos] >= 0) {
                num = v[pos] + Query(1, 1, n, 1, pos);
                num = (num - 1 + n - i + 1) % (n - i + 1) + 1;
                pos = Update(1, 1, n, num, 0);
            } else {
                num = -v[pos] + Query(1, 1, n, 1, pos);
                num %= (n - i + 1);
                num = (n - i + 1) - (num - 1);
                num = (num - 1) % (n - i + 1) + 1;
                pos = Update(1, 1, n, num, 0);
            }
            if (f[i] == f[n]) break;
        }
        
        printf("%s %d\n", s[pos], f[n]);
    }

    return 0;
}
