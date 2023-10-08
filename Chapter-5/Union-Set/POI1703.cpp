#include <ios>
#include <iosfwd>
#include <istream>
#include <ostream>
#include <iostream>
#include <string>
#include <cstring>

#define mytest

using namespace std;
typedef long long LL;
const int N = 500000 + 3;
int T, n, m;
int fa[N];

void Init() {
    for (int i = 1; i <= 2 * n; ++i) fa[i] = i;
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
    ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    int x, y;
    char c;
    scanf("%d", &T);
    string s;
    getline(cin, s);
    while (T--) {
        scanf("%d %d", &n, &m);
        getline(cin, s);
        Init();
        for (int i = 1; i <= m; ++i) {
            c = getchar();
            scanf("%d %d", &x, &y);
            getline(cin, s);
            if (c == 'A') {
                if (find(x + n) == find(y) && find(x) == find(y + n)) {
                    printf("In different gangs.\n");
                } else if (find(x) == find(y)) {
                    printf("In the same gang.\n");
                } else printf("Not sure yet.\n");
            } else if (c == 'D') {
                Uni(x, y + n); Uni(x + n, y);
            }
            // printf("%c %d %d\n", c, x, y);
        }
    }
    return 0;
}