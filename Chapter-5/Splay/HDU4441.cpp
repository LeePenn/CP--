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
const int N = 300000 + 5, M = 60000 + 5, INF = 1000000000;
#define KEY ch[ch[rt][1]][0]
int n, m;
int rt, tot, ch[N][2], pre[N], sz[N], val[N];
int pos[N][2], pcnt[N][2];
LL sum[N];
priority_queue<int, vector<int>, greater<int> > q;

void NewNode(int &u, int fa, int v) {
    u = ++tot;
    ch[u][0] = ch[u][1] = 0;
    pre[u] = fa;
    sz[u] = 1;
    val[u] = sum[u] = v;
    pcnt[u][v < 0] = 1;
    pcnt[u][v > 0] = 0;
    pos[abs(v)][v < 0] = u;
}

void Init() {
    pre[0] = ch[0][0] = ch[0][1] = 0;
    sz[0] = sum[0] = pcnt[0][0] = pcnt[0][1] = 0;
    tot = rt = 0;
    NewNode(rt, 0, 1);
    NewNode(ch[rt][1], rt, -1);
}

void PushUp(int u) {
    sz[u] = sz[ch[u][0]] + sz[ch[u][1]] + 1;
    sum[u] = sum[ch[u][0]] + sum[ch[u][1]] + val[u];
    pcnt[u][0] = pcnt[ch[u][0]][0] + pcnt[ch[u][1]][0] + (val[u] > 0);
    pcnt[u][1] = pcnt[ch[u][0]][1] + pcnt[ch[u][1]][1] + (val[u] < 0);
}

int KthMin(int u, int k) {
    int t = sz[ch[u][0]];
    if (k < t) return KthMin(ch[u][0], k);
    if (k == t) return u;
    return KthMin(ch[u][1], k - t - 1);
}

void Rotate(int x, int d) {
    int y = pre[x];
    ch[y][d ^ 1] = ch[x][d];
    pre[ch[x][d]] = y;
    if (pre[y]) {
        ch[pre[y]][ch[pre[y]][1] == y] = x;
    }
    pre[x] = pre[y];
    ch[x][d] = y;
    pre[y] = x;
    PushUp(y);
}

void Splay(int x, int goal) {
    while (pre[x] != goal) {
        int y = pre[x];
        if (pre[y] == goal) {
            Rotate(x, ch[y][0] == x);
        } else {
            int d = ch[pre[y]][0] == y;
            if (ch[y][d] == x) {
                Rotate(x, d ^ 1);
                Rotate(x, d);
            } else {
                Rotate(y, d);
                Rotate(x, d);
            }
        }
    }
    PushUp(x);
    if (goal == 0) rt = x;
}

void Insert(int pos, int v) {
    int r = KthMin(rt, pos);
    Splay(r, 0);
    r = KthMin(rt, pos + 1);
    Splay(r, rt);
    NewNode(KEY, ch[rt][1], v);
    PushUp(ch[rt][1]);
    PushUp(rt);
}

void Del(int u) {
    Splay(u, 0);
    if (!ch[u][0]) {
        rt = ch[u][1];
        pre[rt] = 0;
        return;
    }
    int r = ch[u][0];
    while (ch[r][1]) r = ch[r][1];
    Splay(r, rt);
    ch[r][1] = ch[rt][1];
    pre[ch[rt][1]] = r;
    pre[r] = 0;
    rt = r;
    PushUp(rt);
}

int Find(int p) {
    int r = KthMin(rt, p + 1);
    Splay(r, 0);
    int k = pcnt[ch[rt][0]][0];
    int t = rt;
    while (1) {
        if (pcnt[ch[t][0]][1] >= k) {
            t = ch[t][0];
        } else if (pcnt[ch[t][0]][1] + (val[t] < 0) == k) {
            break;
        } else {
            k -= pcnt[ch[t][0]][1] + (val[t] < 0);
            t = ch[t][1];
        }
    }
    Splay(t, 0);
    return sz[ch[rt][0]] - 1;
}

LL Query(int l, int r) {
    Splay(l, 0);
    Splay(r, rt);
    return sum[ch[ch[rt][1]][0]];
}

int main() {
    // POJ 上有时 scanf 比 cin 慢 = =！！
    ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    int x, kase = 0;
    char op[10];
    while (scanf("%d", &n) == 1 && n) {
        kase++;
        printf("Case #%d:\n", kase);
        Init();
        while (!q.empty()) q.pop();
        int now = 1;
        while (n--) {
            scanf("%s%d", op, &x);
            if (op[0] == 'i') {
                if (q.empty()) q.push(now);
                now++;
                int v = q.top(); q.pop();
                Insert(x, v);
                int pos = Find(x);
                Insert(pos, -v);
            } else if (op[0] == 'r') {
                int t = pos[x][0];
                Del(t);
                t = pos[x][1];
                Del(t);
                q.push(x);
            } else {
                int l = pos[x][0], r = pos[x][1];
                printf("%lld\n", Query(l, r));
            }
        }
    }
    
    
    return 0;
}
