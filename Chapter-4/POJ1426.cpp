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
int n, m;
LL f[1000000];

int main() {

#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    while (cin >> n && n) {
        f[1] = 1;
        int now = 1;
        for (int i = 1; ; ++i) {
            f[i << 1] = f[i] * 10;
            if (f[i << 1] % n == 0) {
                now = i << 1;
                break;
            } 
            f[i << 1 | 1] = f[i] * 10 + 1;
            if (f[i << 1 | 1] % n == 0) {
                now = i << 1 | 1;
                break;
            }
        }
        
        vector<int> ans;
        while (now) {
            ans.push_back(now & 1);
            now >>= 1;
        }
        for (int i = ans.size() - 1; i >= 0; --i) cout << ans[i];
        cout << endl;
    }
    
    
    return 0;
}