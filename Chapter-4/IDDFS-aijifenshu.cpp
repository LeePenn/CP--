// #include <algorithm>
// #include <bitset>
// #include <complex>
// #include <deque>
// #include <exception>
// #include <fstream>
// #include <functional>
// #include <iomanip>
// #include <ios>
// #include <iosfwd>
// #include <iostream>
// #include <istream>
// #include <iterator>
// #include <limits>
// #include <list>
// #include <locale>
// #include <map>
// #include <memory>
// #include <new>
// #include <numeric>
// #include <ostream>
// #include <queue>
// #include <set>
// #include <sstream>
// #include <stack>
// #include <stdexcept>
// #include <streambuf>
// #include <string>
// #include <typeinfo>
// #include <utility>
// #include <valarray>
// #include <vector>
#include <bits/stdc++.h>

// #define mytest

using namespace std;
typedef long long LL;
const int N = 1000 + 3;
LL T, a, b;
LL ans[50], len;
LL tmp[50];
int depth;
bool flag;

LL Gcd(LL x, LL y) {
    return !y ? x : Gcd(y, x % y);
}

void Dfs(LL x, LL y, int d) {
    if (y <= tmp[d - 1]) return;
    if (x == 1) {
        if (!flag || y < ans[d]) {
            tmp[d] = y;
            memcpy(ans, tmp, sizeof(ans));
            len = d;
            flag = true;
            return;
        }
    }
    if (d >= depth) return;
    
    
    for (LL i = tmp[d - 1] + 1; ; ++i) {
        if (x * i < y) continue;
        if (x * i > y * (len - d + 1)) return;
        
        tmp[d] = i;
        LL nx = i * x - y, ny = y * i;
        if (nx == 0) {
            Dfs(nx, ny, d + 1);
            return;
        }
        LL g = Gcd(nx, ny);
        nx /= g, ny /= g;
        Dfs(nx, ny, d + 1);
    }
}

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
// #ifdef mytest
//     freopen("input.txt", "r", stdin);
//     freopen("output.txt", "w", stdout);
// #endif
    
    cin >> a >> b;
    LL g = Gcd(a, b);
    a /= g, b /= g;
    // printf("%lld %lld\n", a, b);
    tmp[0] = 0;
    for (depth = 1; ; ++depth) {
        len = 40;
        flag = false;
        Dfs(a, b, 1);
        if (flag) break;
    }
    
    for (int i = 1; i <= len; ++i) printf("%lld ", ans[i]);
    cout << endl;
    
    return 0;
}