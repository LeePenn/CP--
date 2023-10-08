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
const int N = 2e5 + 10, INF = 1000000000;
int tr[2000][2000];
int n;

void Update(int x, int y, int v) {
    for (int i = x; i <= n; i += i & (-i)) {
        for (int j = y; j <= n; j += j & (-j)) {
            tr[i][j] += v;
        }
    }
}

int GetSum(int x, int y) {
    int ret = 0;
    for (int i = x; i > 0; i -= i & (-i)) {
        for (int j = y; j > 0; j -= j & (-j)) {
            ret += tr[i][j];
        }
    }
    
    return ret;
}

int Query(int x1, int y1, int x2, int y2) {
    return GetSum(x2, y2) - GetSum(x1 - 1, y2) - GetSum(x2, y1 - 1) + GetSum(x1 - 1, y1 - 1);
}

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    int op;
    int a, b, c, d;
    while (scanf("%d", &op) == 1 && op == 0) {
        memset(tr, 0, sizeof(tr));
        scanf("%d", &n);
        while (scanf("%d", &op) == 1) {
            if (op == 1) {
                scanf("%d%d%d", &a, &b, &c);
                Update(a + 1, b + 1, c);
            } else if (op == 2) {
                scanf("%d%d%d%d", &a, &b, &c, &d);
                printf("%d\n", Query(a + 1, b + 1, c + 1, d + 1));
            } else if (op == 3) break;
        }
    }
    

    return 0;
}
