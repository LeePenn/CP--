#include <stdio.h>
#include <iostream>
#include <stack>

// #define mytest

using namespace std;
typedef long long LL;
const int N = 50000 + 10;
int n, m;
struct ST {
    int l, r;
    int max_sum, lsum, rsum;
}tr[N << 2];
int a[N];

void PushUp(int u) {
    ST t1 = tr[u << 1], t2 = tr[u << 1 | 1];
    tr[u].lsum = t1.lsum == (t1.r - t1.l + 1) ? t1.lsum + t2.lsum : t1.lsum;
    tr[u].rsum = t2.rsum == (t2.r - t2.l + 1) ? t2.rsum + t1.rsum : t2.rsum;
    
    tr[u].max_sum = max(max(t1.lsum, t2.rsum), t1.rsum + t2.lsum);
}

void BuildTree(int u, int l, int r) {
    tr[u].l = l;
    tr[u].r = r;
    if (l == r) {
        tr[u].l = tr[u].r = l;
        tr[u].max_sum = tr[u].lsum = tr[u].rsum = 1;
        return;
    }
    
    int mid = (l + r) >> 1;
    BuildTree(u << 1, l, mid);
    BuildTree(u << 1 | 1, mid + 1, r);
    PushUp(u);
}

void Update(int u, int l, int r, int pos, int x) {
    if (l == r && l == pos) {
        tr[u].lsum = tr[u].rsum = tr[u].max_sum = x;
        return;
    }
    int mid = (l + r) >> 1;
    if (mid >= pos) Update(u << 1, l, mid, pos, x);
    if (mid < pos) Update(u << 1 | 1, mid + 1, r, pos, x);
    PushUp(u);
}

int Query(int u, int l, int r, int pos) {
    if (tr[u].l == tr[u].r || tr[u].max_sum == 0 || tr[u].max_sum == (tr[u].r - tr[u].l + 1)) 
        return tr[u].max_sum;
    int mid = (l + r) >> 1;
    if (mid >= pos) {
        int d = mid - pos + 1;
        if (tr[u << 1].rsum >= d) return tr[u << 1].rsum + tr[u << 1 | 1].lsum;
        else return Query(u << 1, l, mid, pos);
    }
    if (mid < pos) {
        int d = pos - (mid + 1) + 1;
        if (tr[u << 1 | 1].lsum >= d) return tr[u << 1 | 1].lsum + tr[u << 1].rsum;
        else return Query(u << 1 | 1, mid + 1, r, pos);
    }
    return 0;
}

void Debug(int k) {
    for (int i = 1; i <= 13; ++i) {
        printf("Debug %d: %d %d %d %d %d\n", k, tr[i].l, tr[i].r, tr[i].max_sum, tr[i].lsum, tr[i].rsum);
    }
}

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    while (scanf("%d%d", &n, &m) == 2) {
        BuildTree(1, 1, n);
        for (int i = 1; i <= n; ++i) a[i] = 1;
        // Debug();
        // exit(0);
        stack<int> stk;
        char c;
        int x;
        getchar();
        for (int i = 1; i <= m; ++i) {
            c = getchar();
            if (c == 'R') {
                if (stk.size() == 0) {
                    getchar();
                    continue;
                }
                int cur = stk.top(); stk.pop();
                Update(1, 1, n, cur, 1);
                a[cur] = 1;
                // Debug(i);
                // exit(0);
            } else if (c == 'D') {
                scanf("%d", &x);
                stk.push(x);
                Update(1, 1, n, x, 0);
                a[x] = 0;
                // Debug(i);
                // exit(0);
            } else if (c == 'Q') {
                scanf("%d", &x);
                // printf("!! %d %d\n", x, a[x]);
                if (a[x] == 0) printf("0\n");
                else {
                    printf("%d\n", Query(1, 1, n, x));
                }
            }
            
            getchar();
        }
    }
    
    

    return 0;
}
