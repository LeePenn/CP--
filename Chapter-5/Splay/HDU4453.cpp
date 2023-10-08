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
#define Key_value ch[ch[root][1]][0]

using namespace std;
typedef long long LL;
const int N = 4e5 + 10, INF = 100000000;
int n, q, k1, k2, pos, a[N];
int root, tot1;
int ch[N][2], pre[N], key[N], sz[N], add[N], rev[N];
// 节点池，记录删除的节点，创建时，如果有删除的节点，从里面拿
int s[N], tot2;

void NewNode(int &r, int fa, int v) {
    if (tot2) r = s[tot2--];
    else r = ++tot1;
    ch[r][0] = ch[r][1] = add[r] = 0;
    sz[r] = 1;
    pre[r] = fa;
    key[r] = v;
    rev[r] = add[r] = 0;
}

void Update_Add(int r, int v) {
    if (!r) return;
    key[r] += v;
    add[r] += v;
}

void Update_Rev(int r) {
    if (!r) return;
    swap(ch[r][0], ch[r][1]);
    rev[r] ^= 1;
}

void PushUp(int r) {
    sz[r] = sz[ch[r][0]] + sz[ch[r][1]] + 1;
}

void PushDown(int r) {
    if (add[r]) {
        Update_Add(ch[r][0], add[r]);
        Update_Add(ch[r][1], add[r]);
        add[r] = 0;
    }
    if (rev[r]) {
        Update_Rev(ch[r][0]);
        Update_Rev(ch[r][1]);
        rev[r] = 0;
    }
}

void Build(int &x, int fa, int l, int r) {
    if (l > r) return;
    int mid = (l + r) >> 1;
    NewNode(x, fa, a[mid]);
    Build(ch[x][0], x, l, mid - 1);
    Build(ch[x][1], x, mid + 1, r);
    PushUp(x);
}

void Init() {
    pos = 1;
    root = tot1 = tot2 = 0;
    add[root] = ch[root][0] = ch[root][1] = pre[root] = key[root] = sz[root] = 0;
    for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    NewNode(root, 0, -1);
    NewNode(ch[root][1], root, -1);
    Build(Key_value, ch[root][1], 1, n);
    PushUp(ch[root][1]);
    PushUp(root);
}

void Rotate(int x, int k) {
    int y = pre[x];
    PushDown(y); PushDown(x);
    ch[y][!k] = ch[x][k];
    pre[ch[x][k]] = y;
    if (pre[y]) {
        ch[pre[y]][ch[pre[y]][1] == y] = x;
    }
    pre[x] = pre[y];
    ch[x][k] = y;
    pre[y] = x;
    PushUp(y);
}

void Splay(int r, int goal) {
    PushDown(r);
    while (pre[r] != goal) {
        if (pre[pre[r]] == goal) {
            Rotate(r, ch[pre[r]][0] == r);
        } else {
            int y = pre[r];
            int k = (ch[pre[y]][0] == y);
            if (ch[y][k] == r) {
                Rotate(r, !k);
                Rotate(r, k);
            } else {
                Rotate(y, k);
                Rotate(r, k);
            }
        }
    }
    PushUp(r);
    if (goal == 0) root = r;
}

int Kth(int r, int k) {
    PushDown(r);
    int t = sz[ch[r][0]] + 1;
    if (k == t) return r;
    if (k < t) return Kth(ch[r][0], k);
    return Kth(ch[r][1], k - t);
}

int Get_Max(int r) {
    PushDown(r);
    while (ch[r][1]) {
        r = ch[r][1];
        PushDown(r);
    }
    return r;
}

// 因为有2个虚节点，对应 MIN 和 MAX，l = 1时其实提的是MIN，这部分一定要画图
void MoveLast(int l, int r) {
    if (l > r) return;
    Splay(Kth(root, l), 0);
    Splay(Kth(root, r + 2), root);
    int rt = Key_value;
    Key_value = 0;
    PushUp(ch[root][1]);
    PushUp(root);
    Splay(Get_Max(root), 0);
    int rtt = root;
    root = ch[root][0];
    pre[root] = 0;
    PushUp(root);
    Splay(Get_Max(root), 0);
    ch[root][1] = rt;
    pre[rt] = root;
    PushUp(root);
    ch[rtt][0] = root;
    pre[root] = rtt;
    root = rtt;
    pre[root] = 0;
    PushUp(root);
}

void Insert(int x) {
    int r;
    Splay(Kth(root, pos + 1), 0);
    Splay(Kth(root, pos + 2), root);
    NewNode(r, ch[root][1], x);
    Key_value = r;
    PushUp(ch[root][1]);
    PushUp(root);
    ++n;
}

void Erase(int r) {
    if (!r) return;
    Erase(ch[r][0]);
    Erase(ch[r][1]);
    s[++tot2] = r;
}

void Delete() {
    Splay(Kth(root, pos), 0);
    Splay(Kth(root, pos + 2), root);
    int r = Key_value;
    Key_value = 0;
    pre[r] = 0;
    Erase(r);
    PushUp(ch[root][1]);
    PushUp(root);
    if (pos == n) pos = 1;
    --n;
}

void Move(int x) {
    if (x == 1) pos = (pos > 1 ? pos - 1 : n);
    else pos = (pos < n ? pos + 1 : 1);
}

int Query() {
    Splay(Kth(root, pos + 1), 0);
    return key[root];
}

void Add(int x) {
    MoveLast(1, pos - 1);
    pos = 1;
    int l = pos, r = pos + k2 - 1;
    Splay(Kth(root, l), 0);
    Splay(Kth(root, r + 2), root);
    Update_Add(Key_value, x);
}

void Reverse() {
    MoveLast(1, pos - 1);
    pos = 1;
    int l = pos, r = pos + k1 - 1;
    Splay(Kth(root, l), 0);
    Splay(Kth(root, r + 2), root);
    Update_Rev(Key_value);
}

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    int kase = 0;
    while (scanf("%d%d%d%d", &n, &q, &k1, &k2) == 4) {
        if (!n && !q && !k1 && !k2) break;
        
        char op[10];
        int x;
        Init();
        printf("Case #%d:\n", ++kase);
        for (int i = 1; i <= q; ++i) {
            scanf("%s", op);
            if (op[0] == 'a') {
                scanf("%d", &x);
                Add(x);
            } else if (op[0] == 'r') Reverse();
            else if (op[0] == 'i') {
                scanf("%d", &x);
                Insert(x);
            } else if (op[0] == 'd') Delete();
            else if (op[0] == 'm') {
                scanf("%d", &x);
                Move(x);
            } else if (op[0] == 'q') printf("%d\n", Query());
        }
    }
    

    return 0;
}
