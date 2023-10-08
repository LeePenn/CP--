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
int g[8][8];
int cpyg[30][8][8];
int T, n;
int dep;
int ans;
int cnt[4];
char path[30];

bool Check() {
    int a = g[3][3];
    return g[3][4] == a && g[3][5] == a && g[4][3] == a && g[4][5] == a
    && g[5][3] == a && g[5][4] == a && g[5][5] == a;
}

void Print() {
    for (int i = 1; i <= 7; ++i) {
        for (int j = 1; j <= 7; ++j) cout << g[i][j] << " ";
        cout << endl;
    }
}

int gj() {
    memset(cnt, 0, sizeof(cnt));
    for (int i = 3; i <= 5; ++i) {
        cnt[g[3][i]]++;
        cnt[g[5][i]]++;
    }
    cnt[g[4][3]]++; cnt[g[4][5]]++;
    return 8 - max(cnt[3], max(cnt[1], cnt[2]));
}

void MoveRow(bool left, int r) {
    int tmp;
    if (left) {
        tmp = g[r][1];
        for (int i = 1; i < 7; ++i) {
            g[r][i] = g[r][i + 1];
        }
        g[r][7] = tmp;
    
        return;
    } 
    
    tmp = g[r][7];
    for (int i = 7; i > 1; --i) {
        g[r][i] = g[r][i - 1];
    }
    g[r][1] = tmp;
}

void MoveCol(bool up, int c) {
    int tmp;
    if (up) {
        tmp = g[1][c];
        for (int i = 1; i < 7; ++i) {
            g[i][c] = g[i + 1][c];
        }
        g[7][c] = tmp;
        
        return;
    }

    tmp = g[7][c];
    for (int i = 7; i > 1; --i) {
        g[i][c] = g[i - 1][c];
    }
    g[1][c] = tmp;
}

void Move(int x) {
    switch (x) {
        case 0:
            MoveCol(true, 3);
            break;
        case 1:
            MoveCol(true, 5);
            break;
        case 2:
            MoveRow(false, 3);
            break;
        case 3:
            MoveRow(false, 5);
            break;
        case 4:
            MoveCol(false, 5);
            break;
        case 5:
            MoveCol(false, 3);
            break;
        case 6:
            MoveRow(true, 5);
            break;
        case 7:
            MoveRow(true, 3);
            break;
        default:
            break;
    }
}

bool IDA(int d) {
    if (Check()) return true;
    
    if (d + gj() > dep) return false;
    
    memcpy(cpyg[d], g, sizeof(cpyg[d]));
    
    
    for (int i = 0; i < 8; ++i) {
        Move(i);
        // if (d == 0 && i == 0) Print(), exit(0);
        path[d] = i + 'A';
        if (IDA(d + 1)) return true;
        memcpy(g, cpyg[d], sizeof(g));
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
    
    while (cin >> g[1][3] && g[1][3]) {
        cin >> g[1][5] >> g[2][3] >> g[2][5];
        for (int i = 1; i <= 7; ++i) {
            cin >> g[3][i];
        }
        cin >> g[4][3] >> g[4][5];
        for (int i = 1; i <= 7; ++i) {
            cin >> g[5][i];
        }
        for (int i = 6; i <= 7; ++i) {
            cin >> g[i][3] >> g[i][5];
        }
        
        // Print();
        // return 0;
        
        for (dep = 0; ; ++dep) {
            if (IDA(0)) break;
        }
        if (dep == 0) {
            printf("No moves needed");
        } else {
            for (int i = 0; i < dep; ++i) {
                printf("%c", path[i]);
            }
        }
        printf("\n%d\n", g[3][3]);
    }
    
    return 0;
}