#include <stdio.h>
#include <iostream>
#include <stack>
#include <complex>
#include <vector>
#include <cstring>
#include <map>
#include <algorithm>
#include <queue>
#include <set>

// #define mytest

using namespace std;
typedef long long LL;
const int N = 4e5 + 5, M = 60000 + 5, INF = 1000000000;
#define KEY ch[ch[rt][1]][0]
int n, m;
int pre[N], val[N], sz[N], rev[N], add[N], ch[N][2];
int rt, tot1, tot2;
int s[N];
int pos, a[N], k1, k2;

void NewNode(int &u, int fa, int v) {
    if (tot2) u = s[tot2--];
    else u = ++tot1;
    ch[u][0] = ch[u][1] = 0;
    val[u] = v;
    pre[u] = fa;
    sz[u] = 1;
    rev[u] = add[u] = 0;
}

void PushUp(int u) {
    sz[u] = sz[ch[u][0]] + sz[ch[u][1]] + 1;
}

void Build(int &u, int fa, int l, int r) {
    if (l > r) return;
    int mid = (l + r) >> 1;
    NewNode(u, fa, a[mid]);
    Build(ch[u][0], u, l, mid - 1);
    Build(ch[u][1], u, mid + 1, r);
    PushUp(u);
}

void Init() {
    pos = 1;
    rt = tot1 = tot2 = 0;
    add[rt] = ch[rt][0] = ch[rt][1] = pre[rt] = val[rt] = sz[rt] = 0;
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }
    NewNode(rt, 0, -1);
    NewNode(ch[rt][1], rt, -1);
    Build(KEY, ch[rt][1], 1, n);
    PushUp(ch[rt][1]);
    PushUp(rt);
}

void Update_Add(int u, int v) {
    if (!u) return;
    add[u] += v;
    val[u] += v;
}

void Update_Rev(int u) {
    if (!u) return;
    swap(ch[u][0], ch[u][1]);
    rev[u] ^= 1;
}

void PushDown(int u) {
    if (add[u]) {
        Update_Add(ch[u][0], add[u]);
        Update_Add(ch[u][1], add[u]);
        add[u] = 0;
    }
    
    if (rev[u]) {
        Update_Rev(ch[u][0]);
        Update_Rev(ch[u][1]);
        rev[u] = 0;
    }
}

void Rotate(int x, int d) {
    int y = pre[x];
    PushDown(y);
    PushDown(x);
    ch[y][!d] = ch[x][d];
    pre[ch[x][d]] = y;
    if (pre[y]) {
        ch[pre[y]][ch[pre[y]][1] == y] = x;
    }
    pre[x] = pre[y];
    ch[x][d] = y;
    pre[y] = x;
    PushUp(y);
}

void Splay(int u, int goal) {
    PushDown(u);
    while (pre[u] != goal) {
        if (pre[pre[u]] == goal) {
            Rotate(u, ch[pre[u]][0] == u);
        } else {
            int y = pre[u];
            int d = (ch[pre[y]][0] == y);
            if (ch[y][d] == u) {
                Rotate(u, !d);
                Rotate(u, d);
            } else {
                Rotate(y, d);
                Rotate(u, d);
            }
        }
    }
    PushUp(u);
    if (goal == 0) rt = u;
}

int Kth(int u, int k) {
    PushDown(u);
    int t = sz[ch[u][0]] + 1;
    if (k == t) return u;
    if (k < t) return Kth(ch[u][0], k);
    return Kth(ch[u][1], k - t);
}

int GetMax(int u) {
    PushDown(u);
    while (ch[u][1]) {
        u = ch[u][1];
        PushDown(u);
    }
    return u;
}

void MoveLast(int l, int r) {
    if (l > r) return;
    Splay(Kth(rt, l), 0);
    Splay(Kth(rt, r + 2), rt);
    int tmp_rt = KEY;
    KEY = 0;
    PushUp(ch[rt][1]);
    PushUp(rt);
    Splay(GetMax(rt), 0);
    int tmp_rtt = rt;
    rt = ch[rt][0];
    pre[rt] = 0;
    PushUp(rt);
    Splay(GetMax(rt), 0);
    ch[rt][1] = tmp_rt;
    pre[tmp_rt] = rt;
    PushUp(rt);
    ch[tmp_rtt][0] = rt;
    pre[rt] = tmp_rtt;
    rt = tmp_rtt;
    pre[rt] = 0;
    PushUp(rt);
}

void Add(int v) {
    MoveLast(1, pos - 1);
    pos = 1;
    int l = pos, r = pos + k2 - 1;
    Splay(Kth(rt, l), 0);
    Splay(Kth(rt, r + 2), rt);
    Update_Add(KEY, v);
}

void Reverse() {
    MoveLast(1, pos - 1);
    pos = 1;
    int l = pos, r = pos + k1 - 1;
    Splay(Kth(rt, l), 0);
    Splay(Kth(rt, r + 2), rt);
    Update_Rev(KEY);
}

void erase(int r) {
    if (!r) return;
    erase(ch[r][0]);
    erase(ch[r][1]);
    s[++tot2] = r;
}

void Insert(int v) {
    int r;
    Splay(Kth(rt, pos + 1), 0);
    Splay(Kth(rt, pos + 2), rt);
    NewNode(r, ch[rt][1], v);
    KEY = r;
    PushUp(ch[rt][1]);
    PushUp(rt);
    ++n;
}

void Delete() {
    Splay(Kth(rt, pos), 0);
    Splay(Kth(rt, pos + 2), rt);
    int r = KEY;
    KEY = 0;
    pre[r] = 0;
    erase(r);
    PushUp(ch[rt][1]);
    PushUp(rt);
    if (pos == n) pos = 1;
    --n;
}

void Move(int x) {
    if (x == 1) pos = (pos > 1 ? pos - 1 : n);
    else pos = (pos < n ? pos + 1 : 1);
}

int Query() {
    Splay(Kth(rt, pos + 1), 0);
    return val[rt];
}

int main() {
    // POJ 上有时 scanf 比 cin 慢 = =！！
    ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    int kase = 0;
    char op[10];
    int x;
    while (scanf("%d%d%d%d", &n, &m, &k1, &k2) == 4 && (n + m + k1 + k2)) {
        kase++;
        Init();
        printf("Case #%d:\n", kase);
        
        for (int i = 1; i <= m; ++i) {
            scanf("%s", op);
            if (op[0] == 'a') {
                scanf("%d", &x);
                Add(x);
            }
            if (op[0] == 'r') Reverse();
            if (op[0] == 'i') {
                scanf("%d", &x);
                Insert(x);
            }
            if (op[0] == 'd') Delete();
            if (op[0] == 'm') {
                scanf("%d", &x);
                Move(x);
            }
            if (op[0] == 'q') printf("%d\n", Query());
        }
        
    }
    
    return 0;
}
