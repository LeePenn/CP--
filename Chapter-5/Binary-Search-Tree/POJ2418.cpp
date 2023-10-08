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
map<string, int> m;

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    char t[35];
    int ans = 0;
    while (fgets(t, sizeof(t), stdin)) {
        size_t len = strlen(t);
        if (len > 0 && t[len - 1] == '\n') {
            t[len - 1] = '\0';
        }
        m[t]++;
        ans++;
    }
    
    map<string, int>::iterator it;
    for (it = m.begin(); it != m.end(); it++) {
        printf("%s %.4lf\n", it->first.c_str(), 100.0 * (it->second) / ans);
    }
    

    return 0;
}
