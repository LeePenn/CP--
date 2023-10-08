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
int pre[maxn];
set<int> e[maxn];
vector<int> ans;

int Find(int x) {
    return pre[x] != x ? pre[x] = Find(pre[x]) : x;
}

bool Union(int p, int q) {
    if (p != q) {
        if (e[p].size() > e[q].size())
            swap(p, q);
        for (auto it : e[p]) {
            if (it == q) return false;
            e[it].erase(p);
            e[it].insert(q);
            e[q].insert(it);
        }
    }
    pre[p] = q;
    return true;
}


int main() {
    int L = readint();
    int x, y, ee;
    int Max = -1;
    int siz = 0;
    for (int i = 1; i <= 100000; i++)
        pre[i] = i;
    for (int i = 1; i <= L; i++) {
        x = readint();
        y = readint();
        ee = readint();
        Max = max(Max, x);
        Max = max(Max, y);
        int p = Find(x);
        int q = Find(y);
        if (!ee) {
            if (p == q) {
                ans.push_back(i - siz);
                siz = i;
                for (int i = 1; i <= Max; i++)
                    pre[i] = i, e[i].clear();
                Max = -1;
                continue;
            }
            e[p].insert(q);
            e[q].insert(p);
        }
        else if (!Union(p, q)) {
            ans.push_back(i - siz);
            siz = i;
            for (int i = 1; i <= Max; i++)
                pre[i] = i, e[i].clear();
            Max = -1;
            continue;
        }
    }
    cout << ans.size() << '\n';
    for (int i = 0; i < ans.size(); i++)
        cout << ans[i] << '\n';
}
