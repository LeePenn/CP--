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
int n, fa[N];
set<int> e[N];
vector<int> ans;

void Init() {
    for (int i = 1; i < N; ++i) fa[i] = i;
}

int find(int x) {
    if (fa[x] != x) fa[x] = find(fa[x]);
    return fa[x];
}

bool Uni(int x, int y) {
    if (x != y) {
        if (e[x].size() < e[y].size()) {
            swap(x, y);
        }
        
        for (auto it : e[y]) {
            if (it == x) return false;
            e[it].erase(y);
            e[it].insert(x);
            e[x].insert(it);
        }
    }
    fa[y] = x;
    return true;
}

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    Init();
    scanf("%d", &n);
    int cur = 0;
    int x, y, t;
    int maxx = 0;
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d%d", &x, &y, &t);
        maxx = max(maxx, max(x, y));
        x = find(x), y = find(y);
        // equal
        if (t) {
            if (!Uni(x, y)) {
                ans.push_back(i - cur);
                for (int i = 1; i <= maxx; ++i) {
                    fa[i] = i;
                    e[i].clear();
                }
                cur = i;
                maxx = 0;
                continue;
            }
        } else {
            if (x == y) {
                ans.push_back(i - cur);
                for (int i = 1; i <= maxx; ++i) {
                    fa[i] = i;
                    e[i].clear();
                }
                cur = i;
                maxx = 0;
                continue;
            }
            e[x].insert(y);
            e[y].insert(x);
        }
    }
    printf("%lu\n", ans.size());
    for (int i = 0; i < ans.size(); ++i) {
        printf("%d\n", ans[i]);
    }
    
    
    
    return 0;
}