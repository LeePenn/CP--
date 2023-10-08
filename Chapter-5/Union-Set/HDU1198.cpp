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
int T, n, m;
int fa[N];
char g[55][55];

int getID(int x, int y) {
    return x * m + y;
}

void Init() {
    for (int i = 1; i < N; ++i) {
        fa[i] = i;
    }
}

int find(int x) {
    if (fa[x] != x) {
        fa[x] = find(fa[x]);
    }
    return fa[x];
}

void Uni(int x, int y) {
    x = find(x), y = find(y);
    if (x != y) {
        fa[y] = x;
    }
}

bool Valid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

bool CanLink(int d, char c) {
    switch (d) {
        case 1:
            return c != 'A' && c != 'B' && c != 'F' && c != 'G';
        case 2:
            return c != 'C' && c != 'D' && c != 'F' && c != 'I';
        case 3:
            return c != 'A' && c != 'C' && c != 'E' && c != 'H';
        case 4:
            return c != 'B' && c != 'D' && c != 'E' && c != 'J';
        default:
            return false;
    }
}

void Link(int x, int y) {
    int upID = -1, downID = -1, leftID = -1, rightID = -1;
    if (Valid(x - 1, y)) upID = getID(x - 1, y);
    if (Valid(x + 1, y)) downID = getID(x + 1, y);
    if (Valid(x, y - 1)) leftID = getID(x, y - 1);
    if (Valid(x, y + 1)) rightID = getID(x, y + 1);
    int curID = getID(x, y);
    switch (g[x][y]) {
        case 'A':
            if (upID > 0 && CanLink(1, g[x - 1][y])) 
                Uni(curID, upID);
            if (leftID > 0 && CanLink(3, g[x][y - 1]))
                Uni(curID, leftID);
            break;
        case 'B':
            if (upID > 0 && CanLink(1, g[x - 1][y]))
                Uni(curID, upID);
            if (rightID > 0 && CanLink(4, g[x][y + 1]))
                Uni(curID, rightID);
            break;
        case 'C':
            if (leftID > 0 && CanLink(3, g[x][y - 1]))
                Uni(curID, leftID);
            if (downID > 0 && CanLink(2, g[x + 1][y])) 
                Uni(curID, downID);
            break;
        case 'D':
            if (rightID > 0 && CanLink(4, g[x][y + 1]))
                Uni(curID, rightID);
            if (downID > 0 && CanLink(2, g[x + 1][y])) 
                Uni(curID, downID);
            break;
        case 'E':
            if (upID > 0 && CanLink(1, g[x - 1][y]))
                Uni(curID, upID);
            if (downID > 0 && CanLink(2, g[x + 1][y])) 
                Uni(curID, downID);
            break;
        case 'F':
            if (leftID > 0 && CanLink(3, g[x][y - 1]))
                Uni(curID, leftID);
            if (rightID > 0 && CanLink(4, g[x][y + 1]))
                Uni(curID, rightID);
            break;
        case 'G':
            if (leftID > 0 && CanLink(3, g[x][y - 1]))
                Uni(curID, leftID);
            if (rightID > 0 && CanLink(4, g[x][y + 1]))
                Uni(curID, rightID);
            if (upID > 0 && CanLink(1, g[x - 1][y]))
                Uni(curID, upID);
            break;
        case 'H':
            if (leftID > 0 && CanLink(3, g[x][y - 1]))
                Uni(curID, leftID);
            if (downID > 0 && CanLink(2, g[x + 1][y])) 
                Uni(curID, downID);
            if (upID > 0 && CanLink(1, g[x - 1][y]))
                Uni(curID, upID);
            break;
        case 'I':
            if (leftID > 0 && CanLink(3, g[x][y - 1]))
                Uni(curID, leftID);
            if (downID > 0 && CanLink(2, g[x + 1][y])) 
                Uni(curID, downID);
            if (rightID > 0 && CanLink(4, g[x][y + 1]))
                Uni(curID, rightID);
            break;
        case 'J':
            if (upID > 0 && CanLink(1, g[x - 1][y]))
                Uni(curID, upID);
            if (downID > 0 && CanLink(2, g[x + 1][y])) 
                Uni(curID, downID);
            if (rightID > 0 && CanLink(4, g[x][y + 1]))
                Uni(curID, rightID);
            break;
        case 'K':
            if (upID > 0 && CanLink(1, g[x - 1][y]))
                Uni(curID, upID);
            if (downID > 0 && CanLink(2, g[x + 1][y])) 
                Uni(curID, downID);
            if (leftID > 0 && CanLink(3, g[x][y - 1]))
                Uni(curID, leftID);
            if (rightID > 0 && CanLink(4, g[x][y + 1]))
                Uni(curID, rightID);
            break;
        default:
            break;
    }
}

int Solve() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            // printf("%d ", getID(i, j));
            Link(i, j);
        }
    }
    
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (fa[getID(i, j)] == getID(i, j)) ans++;
        }
    }
    
    return ans;
}

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    char s[55];
    while (scanf("%d %d", &n, &m) == 2 && n > 0) {
        Init();
        for (int i = 0; i < n; ++i) {
            scanf("%s\n", s);
            for (int j = 0; j < m; ++j) {
                g[i][j] = s[j];
            }
        }
        
        printf("%d\n", Solve());
        
    }
    
    
    
    return 0;
}