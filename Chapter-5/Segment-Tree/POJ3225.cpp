#include <stdio.h>
#include <iostream>
#include <stack>
#include <complex>
#include <vector>
#include <cstring>
// #include <algorithm>
// #include <queue>

// #define mytest

using namespace std;
typedef long long LL;
const int N = 140000 + 5, MAXN = 131072;
struct ST {
    int l, r;
    int cover, XOR;
}tr[N << 2], trinit[N << 2];
bool vis[N];

void UpdateXOR(int u) {
    if (tr[u].cover != -1) tr[u].cover ^= 1;
    else tr[u].XOR ^= 1;
}

void PushDown(int u) {
    if (tr[u].cover != -1) {
        tr[u << 1].cover = tr[u << 1 | 1].cover = tr[u].cover;
        tr[u << 1].XOR = tr[u << 1 | 1].XOR = 0;
        tr[u].cover = -1;
    }
    if (tr[u].XOR) {
        UpdateXOR(u << 1);
        UpdateXOR(u << 1 | 1);
        tr[u].XOR = 0;
    }
}

void BuildTree(int u, int l, int r) {
    tr[u].l = l;
    tr[u].r = r;
    tr[u].cover = tr[u].XOR = 0;
    if (l == r) return;
    int mid = (l + r) >> 1;
    BuildTree(u << 1, l, mid);
    BuildTree(u << 1 | 1, mid + 1, r);
}

void Update(int u, int l, int r, int li, int ri, char op) {
    if (l >= li && r <= ri) {
        if (op == 'U') {
            tr[u].cover = 1;
            tr[u].XOR = 0;
        } else if (op == 'D') {
            tr[u].cover = 0;
            tr[u].XOR = 0;
        } else if (op == 'C' || op == 'S') {
            UpdateXOR(u);
        }
        return;
    }
    PushDown(u);
    int mid = (l + r) >> 1;
    if (mid >= li) Update(u << 1, l, mid, li, ri, op);
    else if (op == 'I' || op == 'C') {
        tr[u << 1].XOR = tr[u << 1].cover = 0;
    }
    if (mid < ri) Update(u << 1 | 1, mid + 1, r, li, ri, op);
    else if (op == 'I' || op == 'C') {
        tr[u << 1 | 1].XOR = tr[u << 1 | 1].cover = 0;
    } 
}

void Query(int u, int l, int r) {
    if (tr[u].cover == 1) {
        for (int i = l; i <= r; ++i) {
            vis[i] = true;
        }
        return;
    } else if (tr[u].cover == 0) return;
    
    if (l == r) return;
    PushDown(u);
    int mid = (l + r) >> 1;
    Query(u << 1, l, mid);
    Query(u << 1 | 1, mid + 1, r);
}

int main() {
    // POJ 上有时 scanf 比 cin 慢 = =！！
    ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    BuildTree(1, 0, MAXN);
    memcpy(trinit, tr, sizeof(trinit));
    char op, l, r;
    int a, b;
    while (scanf("%c %c%d,%d%c\n", &op, &l, &a, &b, &r) == 5) {
        a <<= 1;
        b <<= 1;
        if (l == '(') a++;
        if (r == ')') b--;
        if (a > b) {
            if (op == 'C' || op == 'I') {
                memcpy(tr, trinit, sizeof(tr));
            }
        } else Update(1, 0, MAXN, a, b, op);
    }
    Query(1, 0, MAXN);
    bool flag = false;
    int st = -1, ed;
    for (int i = 0; i <= MAXN; ++i) {
        if (vis[i]) {
            if (st == -1) st = i;
            ed = i;
        } else {
            if (st != -1) {
                if (flag) printf(" ");
                flag = true;
                printf("%c%d,%d%c", st & 1 ? '(' : '[', st >> 1, (ed + 1) >> 1, ed & 1 ? ')' : ']');
                st = -1;
            }
        }
    }
    
    if (!flag) printf("empty set");
    printf("\n");

    return 0;
}
