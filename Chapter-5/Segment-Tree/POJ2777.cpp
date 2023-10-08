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
int n, c, op;
struct ST {
    int l, r;
    int color, lazy;
}tr[N << 2];
bool vis[40];

void PushUp(int u) {
    if (tr[u << 1].color == tr[u << 1 | 1].color) {
        tr[u].color = tr[u << 1].color;
    } else {
        tr[u].color = 0;
    }
}

void PushDown(int u) {
    if (tr[u].lazy != 0) {
        int col = tr[u].lazy;
        tr[u << 1].color = col; 
        tr[u << 1 | 1].color = col;
        
        tr[u << 1].lazy = col;
        tr[u << 1 | 1].lazy = col;
        
        tr[u].lazy = 0;
    }
}

void BuildTree(int u, int l, int r) {
    if (l == r) {
        tr[u].l = l; tr[u].r = r;
        tr[u].color = 1; tr[u].lazy = 0;
        return;
    }
    int mid = (l + r) >> 1;
    BuildTree(u << 1, l, mid);
    BuildTree(u << 1 | 1, mid + 1, r);
    PushUp(u);
}

void Update(int u, int l, int r, int li, int ri, int x) {
    if (r < li || l > ri) return;
    
    if (l >= li && r <= ri) {
        tr[u].color = x;
        tr[u].lazy = x;
        return;
    }
    
    PushDown(u);
    int mid = (l + r) >> 1;
    if (mid >= li) Update(u << 1, l, mid, li, ri, x);
    if (mid < ri) Update(u << 1 | 1, mid + 1, r, li, ri, x);
    PushUp(u);
}

void Query(int u, int l, int r, int li, int ri) {
    if (r < li || l > ri) return;
    
    if (l >= li && r <= ri) {
        if (tr[u].color != 0) {
            if (!vis[tr[u].color]) vis[tr[u].color] = true;
            return;
        } 
    }
    PushDown(u);
    int mid = (l + r) >> 1;
    if (mid >= li) Query(u << 1, l, mid, li, ri);
    if (mid < ri) Query(u << 1 | 1, mid + 1, r, li, ri);
}

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    scanf("%d%d%d", &n, &c, &op);
    BuildTree(1, 1, n);
    char ch;
    int x, y, z;
    getchar();
    for (int i = 1; i <= op; ++i) {
        ch = getchar();
        scanf("%d%d", &x, &y);
        if (x > y) swap(x, y);
        if (ch == 'C') {
            scanf("%d", &z);
            Update(1, 1, n, x, y, z);
        } else if (ch == 'P') {
            memset(vis, 0, sizeof(vis));
            Query(1, 1, n, x, y);
            int ans = 0;
            for (int i = 1; i <= c; ++i) {
                if (vis[i]) ans++;
            }
            printf("%d\n", ans);
        }
        
        getchar();
    }
    

    return 0;
}
