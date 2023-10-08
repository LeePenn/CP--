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
int n;
map<int, int> m;
map<int, int>::iterator it, it2;

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    int k, g;
    while(scanf("%d", &n) == 1 && n) {
        m.clear();
        m[1000000000] = 1;
        for (int i = 1; i <= n; ++i) {
            scanf("%d%d", &k, &g);
            m[g] = k;
            it = m.find(g);
            if (it == m.begin()) {
                printf("%d", it->second);
                it++;
                printf(" %d\n", it->second);
                continue;
            }
            
            it2 = it;
            it2--, it++;
            if (g - it2->first <= it->first - g) {
                printf("%d %d\n", k, it2->second);
            } else {
                printf("%d %d\n", k, it->second);
            }
        }
    }

    return 0;
}
