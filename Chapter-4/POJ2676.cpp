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
int T;
int b[9][9];
int r[9], c[9], box[9];
bool found;

int getBoxID(int i, int j) {
    return i / 3 * 3 + j / 3;
}

void Fill(int i, int j, int num) {
    r[i] |= 1 << (num - 1);
    c[j] |= 1 << (num - 1);
    box[getBoxID(i, j)] |= 1 << (num - 1);
}

void Remove(int i, int j, int num) {
    r[i] ^= 1 << (num - 1);
    c[j] ^= 1 << (num - 1);
    box[getBoxID(i, j)] ^= 1 << (num - 1);
}

void Print() {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) printf("%d", b[i][j]);
        printf("\n");
    }
}

int getCnt(int x) {
    int ret = 0;
    while (x) {
        x -= x & -x;
        ret++;
    }
    return 9 - ret;
}

void Dfs(int cnt) {
    if (found) return;
    
    if (cnt == 0) {
        Print();
        found = true;
        return;
    }

    int num = 9, x = -1, y = -1;
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (b[i][j] == 0) {
                int t = getCnt(r[i] | c[j] | box[getBoxID(i, j)]);
                if (t < num) {
                    num = t;
                    x = i, y = j;
                }
            }
        }
    }
    
    int cur = r[x] | c[y] | box[getBoxID(x, y)];
    // printf("x = %d, y = %d, box = %d, getCnt = %d\n", x, y, getBoxID(x, y), getCnt(cur));
    for (int i = 0; i < 9; ++i) {
        if ((cur >> i & 1) == 0) {
            b[x][y] = i + 1;
            Fill(x, y, i + 1);
            Dfs(cnt - 1);
            b[x][y] = 0;
            Remove(x, y, i + 1);
        }
    }
}

int main() {

#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    cin >> T;
    string s;
    while (T--) {
        memset(r, 0, sizeof(r));
        memset(c, 0, sizeof(c));
        memset(box, 0, sizeof(box));
        memset(b, 0, sizeof(b));
        int cnt = 0;
        found = false;
        for (int i = 0; i < 9; ++i) {
            cin >> s;
            for (int j = 0; j < 9; ++j) {
                b[i][j] = s[j] - '0';
                if (b[i][j] != 0) {
                    Fill(i, j, b[i][j]);
                } else {
                    cnt++;
                }
            }
        }
    
        Dfs(cnt);
    }
    
    
    return 0;
}