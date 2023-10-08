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
const int N = 100000 + 10, INF = 100000000;
int T;
int n, m;
struct Node {
    int val, id;
    bool operator <(const Node &rh) const {
        if (val == rh.val) return id < rh.id;
        return val < rh.val;
    }
}node[N];
int root;
int tree[N][2], rev[N], pre[N], sz[N];

void Pushup(int x) {
    sz[x] = sz[tree[x][0]] + sz[tree[x][1]] + 1;
}

void UpdateRev(int x) {
    if (!x) return;
    swap(tree[x][0], tree[x][1]);
    rev[x] ^= 1;
}

void Pushdown(int x) {
    if (rev[x]) {
        UpdateRev(tree[x][0]);
        UpdateRev(tree[x][1]);
        rev[x] = 0;
    }
}

void Newnode(int &x, int fa, int val) {
    x = val;
    pre[x] = fa;
    sz[x] = 1;
    rev[x] = 0;
    tree[x][0] = tree[x][1] = 0;
}

void Buildtree(int &x, int l, int r, int fa) {
    if (l > r) return;
    int mid = (l + r) >> 1;
    Newnode(x, fa, mid);
    Buildtree(tree[x][0], l, mid - 1, x);
    Buildtree(tree[x][1], mid + 1, r, x);
    Pushup(x);
}

void Init(int n) {
    root = 0;
    tree[root][0] = tree[root][1] = pre[root] = sz[root] = 0;
    Buildtree(root, 1, n, 0);
}

void Rotate(int x, int c) {
    int y = pre[x];
    Pushdown(y);
    Pushdown(x);
    tree[y][!c] = tree[x][c];
    pre[tree[x][c]] = y;
    if (pre[y]) {
        tree[pre[y]][tree[pre[y]][1] == y] = x;
    }
    pre[x] = pre[y];
    tree[x][c] = y;
    pre[y] = x;
    Pushup(y);
}

void Splay(int x, int goal) {
    Pushdown(x);
    while (pre[x] != goal) {
        if (pre[pre[x]] == goal) {
            Pushdown(pre[x]); Pushdown(x);
            Rotate(x, tree[pre[x]][0] == x);
        } else {
            Pushdown(pre[pre[x]]); Pushdown(pre[x]); Pushdown(x);
            int y = pre[x];
            int c = (tree[pre[y]][0] == y);
            if (tree[y][c] == x) {
                Rotate(x, !c);
                Rotate(x, c);
            } else {
                Rotate(y, c);
                Rotate(x, c);
            }
        }
    }
    
    Pushup(x);
    if (goal == 0) root = x;
}

int GetMax(int x) {
    Pushdown(x);
    while (tree[x][1]) {
        x = tree[x][1];
        Pushdown(x);
    }
    return x;
}

void DelRoot() {
    if (tree[root][0] == 0) {
        root = tree[root][1];
        pre[root] = 0;
    } else {
        int m = GetMax(tree[root][0]);
        Splay(m, root);
        tree[m][1] = tree[root][1];
        pre[tree[root][1]] = m;
        root = m;
        pre[root] = 0;
        Pushup(root);
    }
}

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    while (scanf("%d", &n) && n) {
        Init(n);
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &node[i].val);
            node[i].id = i;
        }
        sort(node + 1, node + n + 1);
        for (int i = 1; i < n; ++i) {
            Splay(node[i].id, 0);
            UpdateRev(tree[root][0]);
            printf("%d ", i + sz[tree[root][0]]);
            DelRoot();
        }
        
        printf("%d\n", n);
    }
    
    

    return 0;
}
