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

#define mytest

using namespace std;
typedef long long LL;
const int N = 21;
int n;
int g[N][N];

int Calc(int k) {
    int ret = 0;
    for (int i = n - 1; i >= 0; --i) {
        int c = (k >> i) & 1;
        for (int j = i - 1; j >= 0; --j) {
            if (((k >> j) & 1) != c) ret += g[i][j];
        }
    }
    return ret;
}

void Solve() {
    int ans = 0;
    for (int i = 0; i < (1 << (n - 1)); ++i) {
        ans = max(ans, Calc(i));
    }
    cout << ans << endl;
}

int main() {

#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    cin >> n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> g[i][j];
        }
    }
    
    
    Solve();
    
    
    return 0;
}