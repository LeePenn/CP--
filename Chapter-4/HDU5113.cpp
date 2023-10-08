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
int T, n, m, k;
int g[6][6];
int ans[6][6];
int color[30];
int flag;
int dirs[2][2] = {
    {-1, 0}, {0, -1},
};

bool Valid(int r, int c) {
    return r >= 1 && r <= n && c >= 1 && c <= m;
}

void Dfs(int r, int c, int cnt) {
    if (flag) return;
    
    if (cnt == n * m) {
        flag = true;
        memcpy(ans, g, sizeof(ans));
        return;
    }
    
    for (int i = 1; i <= k; ++i) {
        if (color[i] * 2 > n * m - cnt + 1) return;
    }
    
    for (int i = 1; i <= k; ++i) {
        if (color[i] == 0) continue;
        int cur_col = i;
        bool can = true;
        for (int j = 0; j < 2; ++j) {
            int nr = r + dirs[j][0], nc = c + dirs[j][1];
            if (!Valid(nr, nc)) continue;
            if (g[nr][nc] == cur_col) {
                can = false;
                break;
            }
            
        }
        if (!can) continue;
        
        g[r][c] = cur_col;
        color[i]--;
        // cout << cur.first << " " << cur.second << " " << cnt << endl;
        Dfs(r + (c + 1) / (m + 1), c % m + 1, cnt + 1);
        g[r][c] = 0;
        color[i]++;
    }
}

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    cin >> T;
    for (int i = 1; i <= T; ++i) {
        cin >> n >> m >> k;
        memset(g, 0, sizeof(g));
        memset(ans, 0, sizeof(ans));
        memset(color, 0, sizeof(color));
        for (int j = 1; j <= k; ++j) {
            cin >> color[j];
        }
        
        
        flag = false;
        Dfs(1, 1, 0);
        
        printf("Case #%d:\n", i);
        if (flag) {
            printf("YES\n");
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= m; ++j) {
                    printf("%d", ans[i][j]);
                    if (j != m) printf(" ");
                }
                printf("\n");
            }
        } else {
            printf("NO\n");
        }
        
    }
    
    return 0;
}