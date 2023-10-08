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
const int N = 10000;
struct Node {
    int x, y, z, step;
    Node() { x = y = z = step = 0; }
    Node(int _x, int _y, int _z, int _step) {
        x = _x;
        y = _y;
        z = _z;
        step = _step;
    }
}q[N];
char g[100][100][100];
int sx, sy, sz, ex, ey, ez;
int n;
bool vis[100][100][100];
int dirs[6][3] = {
    {1, 0, 0},
    {-1, 0, 0},
    {0, 1, 0},
    {0, -1, 0},
    {0, 0, 1},
    {0, 0, -1},
};

bool Valid(int x, int y, int z) {
    return x >= 0 && x < n && y >= 0 && y < n && z >= 0 && z < n;
}

void Bfs() {
    g[sx][sy][sz] = 'O';
    g[ex][ey][ez] = 'O';
    memset(vis, 0, sizeof(vis));
    vis[sx][sy][sz] = 1;
    int hh = 1, tt = 1;
    q[hh] = Node(sx, sy, sz, 0);
    while (hh >= tt) {
        Node c = q[tt]; tt++;
        if (c.x == ex && c.y == ey && c.z == ez) {
            cout << n << " " << c.step << endl;
            return;
        }
        Node nx;
        for (int i = 0; i < 6; ++i) {
            int nxx = c.x + dirs[i][0], nyy = c.y + dirs[i][1], nzz = c.z + dirs[i][2];
            if (Valid(nxx, nyy, nzz) && !vis[nxx][nyy][nzz] && g[nxx][nyy][nzz] == 'O') {
                nx.x = nxx, nx.y = nyy, nx.z = nzz, nx.step = c.step + 1;
                q[++hh] = nx;
                vis[nxx][nyy][nzz] = 1;
            }
        }
    }
    cout << "NO ROUTE" << endl;
}

int main() {

#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    string s;
    while (cin >> s >> n) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cin >> s;
                for (int k = 0; k < n; ++k) {
                    g[i][j][k] = s[k];
                }
            }
        }
        
        cin >> sx >> sy >> sz >> ex >> ey >> ez;
        cin >> s;
        Bfs();
    }
    
    
    return 0;
}