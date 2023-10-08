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
struct Loc {
    int x, step;
    Loc() { x = step = 0; }
    Loc(int _x, int _step) {
        x = _x;
        step = _step;
    }
};
bool vis[1000005];

int main() {

#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    cin >> n >> m;
    queue<Loc> q;
    q.push(Loc(n, 0));
    vis[n] = 1;
    while (!q.empty()) {
        Loc c = q.front(); q.pop();
        int cur = c.x, d = c.step;
        if (c.x == m) {
            cout << d << endl;
            break;
        }
        if (cur - 1 >= 0 && !vis[cur - 1]) { vis[cur - 1] = 1; q.push(Loc(cur - 1, d + 1)); }
        if (!vis[cur + 1]) { vis[cur + 1] = 1; q.push(Loc(cur + 1, d + 1)); }
        if (cur * 2 <= 200000 && !vis[cur * 2]) { vis[cur * 2] = 1; q.push(Loc(cur * 2, d + 1)); }
        
    }
    
    return 0;
}