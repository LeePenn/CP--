#include <istream>
#include <ostream>
#include <iostream>

#define mytest

using namespace std;
typedef long long LL;
const int N = 50000 + 3;
int T, n, m;
int fa[N];

void Init() {
    for (int i = 0; i < n; ++i) fa[i] = i;
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
    
    int k, x, y;
    while (cin >> n >> m && (n || m)) {
        Init();
        for (int i = 1; i <= m; ++i) {
            cin >> k;
            cin >> x;
            for (int j = 1; j < k; ++j) {
                cin >> y;
                if (x > y) Uni(y, x);
                else Uni(x, y);
            }
        }
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            if (find(fa[i]) == find(0)) ans++;
        }
        cout << ans << endl;
    }
    return 0;
}