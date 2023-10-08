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
const int N = 32000 + 10;
int n;
int x[N], x1[N], y[N];
int ans[N];
int tr[N];
int mxx, mxy;
int ID[N];

int lowbit(int x) {
    return x & (-x);
}

void Update(int a, int x) {
    while (a <= mxx) {
        tr[a] += x;
        a += lowbit(a);
    }
}

int Query(int a) {
    int ret = 0;
    while (a) {
        ret += tr[a];
        a -= lowbit(a);
    }
    return ret;
}

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    scanf("%d", &n);
    mxx = 0, mxy = 0;
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d", &x[i], &y[i]);
        x1[i] = x[i];
        mxx = max(mxx, x[i]);
    }
    sort(x1 + 1, x1 + n + 1);
    int m = unique(x1 + 1, x1 + n + 1) - x1 - 1;
    for (int i = 1; i <= m; ++i) {
        ID[x1[i]] = i;
    }
    mxx = ID[mxx];
    for (int i = 1; i <= n; ++i) {
        ans[Query(ID[x[i]])]++;
        Update(ID[x[i]], 1);
    }
    for (int i = 0; i < n; ++i) {
        printf("%d\n", ans[i]);
    }
    

    return 0;
}
