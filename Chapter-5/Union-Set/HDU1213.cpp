#include <istream>
#include <ostream>
#include <iostream>

#define mytest

using namespace std;
typedef long long LL;
const int N = 10000 + 3;
int T, n, m;
int f[N];

void Init() {
    for (int i = 1; i <= n; ++i) f[i] = i;
}

int Find(int a) {
    if (f[a] != a) f[a] = Find(f[a]);
    return f[a];
}

void Uni(int a, int b) {
    a = Find(a), b = Find(b);
    if (a != b) f[b] = a;
    return;
}

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    cin >> T;
    int x, y;
    while (T--) {
        cin >> n >> m;
        Init();
        for (int i = 1; i <= m; ++i) {
            cin >> x >> y;
            Uni(x, y);
        }
        
        int ans = 0;
        for (int i = 1; i <= n; ++i) {
            if (f[i] == i) ans++;
        }
        cout << ans << endl;
    }
    
    return 0;
}