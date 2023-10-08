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
const int N = 364000;
struct Node {
    int a[10], dist;
    int pos;
    char op;
    Node() { 
        op = ' ';
        memset(a, 0, sizeof(a));
        dist = 0;
        pos = 0;
    }
    Node(int _pos, int _a[], char _op, int _dist) {
        pos = _pos;
        memcpy(a, _a, sizeof(a));
        op = _op;
        dist = _dist;
    }
}q[N];
int st[10];
int pos;
bool vis[N];
int fac[10] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320};
int pre[N];
int dirs[4][2] = {
    {1, 0}, {-1, 0}, {0, 1}, {0, -1},
};

int Cantor(int a[]) {
    int ans = 0;
    for (int i = 0; i < 9; ++i) {
        int cnt = 0;
        for (int j = i + 1; j < 9; ++j) {
            if (a[j] < a[i]) cnt++;
        }
        ans += cnt * fac[8 - i];
    }
    return ans;
}

bool Check(int a[]) {
    for (int i = 0; i < 8; ++i) {
        if (a[i] != i + 1) return false;
    }
    return true;
}

void Print(int x) {
    Node cur = q[x];
    if (cur.op == ' ') return;
    Print(pre[x]);
    cout << cur.op;
}

bool Valid(int x, int y) {
    return x >= 0 && x < 3 && y >= 0 && y < 3;
}

char getOP(int i) {
    switch (i) {
        case 0:
            return 'd';
        case 1:
            return 'u';
        case 2:
            return 'r';
        default: 
            return 'l';
    }
}

void Bfs() {
    int hh = 1, tt = 1;
    q[1] = Node(pos, st, ' ', 0);
    vis[Cantor(st)] = 1;
    while (hh >= tt) {
        Node c = q[tt]; tt++;
        if (Check(c.a)) {
            Print(tt - 1);
            return;
        }
        int cur_pos = c.pos, d = c.dist;
        int cur_x = cur_pos / 3, cur_y = cur_pos % 3;
        int t[10];
        Node nx_node;
        for (int i = 0; i < 4; ++i) {
            memcpy(&nx_node, &c, sizeof(nx_node));
            int nx = cur_x + dirs[i][0], ny = cur_y + dirs[i][1];
            
            if (Valid(nx, ny)) {
                int nx_pos = nx * 3 + ny;
                swap(nx_node.a[cur_pos], nx_node.a[nx_pos]);
                if (!vis[Cantor(nx_node.a)]) {
                    vis[Cantor(nx_node.a)] = true;
                    nx_node.op = getOP(i);
                    nx_node.pos = nx_pos;
                    nx_node.dist = d + 1;
                    q[++hh] = nx_node;
                    pre[hh] = tt - 1;
                }
            }
        }
    }
    
    cout << "unsolvable" << endl;
}

int main() {

#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    char ch;
    int num = 0;
    while (1) {
        ch = getchar();
        if (isdigit(ch) || ch == 'x') {
            if (ch == 'x') {
                st[num] = 0;
                pos = num;
                num++;
            } else {
                st[num] = ch - '0';
                num++;
            }
        }
        
        if (num == 9) break;
    }
    
    // for (int i = 0; i < 9; ++i) cout << st[i];
    // return 0;
    // cout << endl;
    // cout << sx << " " << sy << endl;
    
    Bfs();
    
    
    return 0;
}