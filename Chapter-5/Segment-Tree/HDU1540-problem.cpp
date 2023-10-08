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
const int N = 50000 + 10;
int n, m;
int tr[N];
int a[N];
int repair[N], cnt;

int lowbit(int i) {
    return i & (-i);
}

void Init() {
    memset(tr, 0, sizeof(tr));
    for (int i = 1; i <= n; ++i) {
        a[i] = 1;
        tr[i] = lowbit(i);
    }
    cnt = 0;
}

void Update(int i, int x) {
    while (i <= n) {
        tr[i] += x;
        i += lowbit(i);
    }
}

int Query(int i) {
    int ret = 0;
    while (i) {
        ret += tr[i];
        i -= lowbit(i);
    }
    return ret;
}

int Solve(int pos, bool left) {
    int ret;
    if (left) {
        int l = 1, r = pos;
        while (l <= r) {
            int mid = (l + r) >> 1;
            int dist = pos - mid + 1;
            int k = Query(pos) - Query(mid - 1);
            if (k >= dist) {
                ret = k;
                r = mid - 1;
            } else l = mid + 1;
        }
    } else {
        int l = pos, r = n;
        while (l <= r) {
            int mid = (l + r) >> 1;
            int dist = mid - pos + 1;
            int k = Query(mid) - Query(pos - 1);
            if (k >= dist) {
                ret = k;
                l = mid + 1;
            } else r = mid - 1;
        }
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
    
    while (scanf("%d%d", &n, &m) == 2) {
        Init();
        char c;
        int x;
        getchar();
        for (int i = 1; i <= m; ++i) {
            c = getchar();
            if (c == 'R') {
                if (cnt == 0) {
                    getchar();
                    continue;
                }
                Update(repair[cnt], 1);
                a[repair[cnt]] = 1;
                cnt--;
            } else if (c == 'D') {
                scanf("%d", &x);
                repair[++cnt] = x;
                Update(x, -1);
                a[x] = 0;
            } else if (c == 'Q') {
                scanf("%d", &x);
                if (a[x] == 0) printf("0\n");
                else {
                    int t1 = Solve(x, true), t2 = Solve(x, false);
                    printf("%d\n", t1 + t2 - 1);
                }
            }
            getchar();
        }
    }
    
    

    return 0;
}
