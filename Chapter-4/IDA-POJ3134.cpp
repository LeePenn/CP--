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
const int N = 1000 + 3;
int n;
int dep;
int a[100];

int gj(int x, int y) {
    return x << y;
}

bool IDA(int cur) {
    if (a[cur] == n) {
        return true;
    }
    
    if (gj(a[cur], dep - cur) < n) return false;
    if (cur >= dep) return false;
    
    for (int i = 0; i <= cur; ++i) {
        a[cur + 1] = a[i] + a[cur];
        if (IDA(cur + 1)) return true;
        a[cur + 1] = abs(a[i] - a[cur]);
        if (IDA(cur + 1)) return true;
    }
    return false;
}

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    a[0] = 1;
    while (cin >> n && n) {
        for (dep = 0; ; ++dep) {
            if (IDA(0)) break;
        }
        cout << dep << endl;
    }
    
    return 0;
}