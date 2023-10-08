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
int T, n;
int rel[26][26];
int station[26];
int ans;

int getCnt(int cur) {
    int ret = 0;
    for (int i = 0; i < cur; ++i) {
        ret |= station[i];
    }
    int cnt = 0;
    while (ret) {
        ret -= ret & (-ret);
        cnt++;
    }
    return cnt;
}

bool Check(int cur, int c) {
    for (int j = 0; j < n; ++j) {
        if (rel[cur][j] == 0) continue;
        if ((station[j] >> c & 1) == 1) return false;
    }
    return true;
}

void Dfs(int cur) {
    if (getCnt(cur) >= ans) return;

    if (cur == n) {
        int tot = getCnt(cur);
        if (ans > tot) {
            ans = tot;
        }
        return;
    }
    
    for (int i = 0; i < n; ++i) {
        if (!Check(cur, i)) continue;
        station[cur] |= 1 << i;
        Dfs(cur + 1);
        station[cur] ^= 1 << i;
    }
}

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    string s;
    while (cin >> n && n) {
        memset(rel, 0, sizeof(rel));
        memset(station, 0, sizeof(station));
        ans = n;
        for (int j = 0; j < n; ++j) {
            cin >> s;
            int c = s[0] - 'A';
            for (int i = 2; i < s.length(); ++i) {
                int t = s[i] - 'A';
                rel[c][t] = rel[t][c] = 1;
            }
        }
        
        
        Dfs(0);
        if (ans > 1) {
            printf("%d channels needed.\n", ans);
        } else {
            printf("%d channel needed.\n", ans);
        }
    }
    
    
    return 0;
}