#include <istream>
#include <ostream>
#include <iostream>

#define mytest

using namespace std;
typedef long long LL;
const int N = 150000 + 3;
int n, k;
int fa[N];

void Init() {
    for (int i = 1; i <= 3 * n; ++i) fa[i] = i;
}

int find(int x) {
    if (fa[x] != x) fa[x] = find(fa[x]);
    return fa[x];
}

void Uni(int x, int y) {
    x = find(x), y = find(y);
    if (x != y) {
        fa[y] = x;
    }
}

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    scanf("%d%d", &n, &k);
    Init();
    int ans = 0;
    int a, b, c;
    for (int i = 1; i <= k; ++i) {
        scanf("%d%d%d", &a, &b, &c);
        if (b > n || c > n) {
            ans++;
            continue;
        }
        if (a == 1) {
            if (find(b) == find(c + n) || find(b) == find(c + 2 * n)) {
                ans++;
            } else {
                Uni(b, c); Uni(b + n, c + n); Uni(b + 2 * n, c + 2 * n);
            }
        } else if (a == 2) {
            if (find(b) == find(c) || find(b) == find(c + n)) {
                ans++;
            } else {
                Uni(b, c + 2 * n); Uni(b + n, c); Uni(b + 2 * n, c + n);
            }
        }
    }
    printf("%d\n", ans);
    
    
    return 0;
}