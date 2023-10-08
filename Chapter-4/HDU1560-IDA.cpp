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
int ptr[10];
int cpyptr[80][10];
int T, n;
string s[10];
int dep;
int ans;
char ch[4] = {'A', 'C', 'G', 'T'};

bool Check() {
    for (int i = 1; i <= n; ++i) {
        if (ptr[i] < s[i].length()) return false;
    }
    return true;
}

int gj() {
    int ret = 0;
    for (int i = 1; i <= n; ++i) {
        ret = max(ret, (int)s[i].length() - ptr[i]);
    }
    return ret;
}

bool Can(int i) {
    for (int j = 1; j <= n; ++j) {
        if (s[j][ptr[j]] == ch[i]) return true;
    }
    return false;
}

bool IDA(int cur) {
    if (Check()) return true;
    if (gj() + cur > dep) return false;
    
    memcpy(cpyptr[cur], ptr, sizeof(cpyptr[cur]));
    for (int i = 0; i < 4; ++i) {
        if (!Can(i)) continue;
        for (int j = 1; j <= n; ++j) {
            if (ptr[j] < s[j].length() && s[j][ptr[j]] == ch[i]) {
                ptr[j]++;
            }
        }
        if (IDA(cur + 1)) return true;
        memcpy(ptr, cpyptr[cur], sizeof(ptr));
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
    
    cin >> T;
    while (T--) {
        cin >> n;
        ans = 0;
        for (int i = 1; i <= n; ++i) {
            cin >> s[i];
            ans += s[i].length();
        }
        
        memset(ptr, 0, sizeof(ptr));
        for (dep = 1; ; ++dep) {
            if (IDA(0)) break;
        }
        cout << dep << endl;
    }
    
    return 0;
}