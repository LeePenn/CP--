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
const int N = 3000 + 5, M = 60000 + 5, INF = 1000000000;
int n;
int c[6], num[6];
LL p[6];
LL f[6][6][6][6][6];
int m;
struct Offer {
    int n;
    int k[6], c[6];
    LL p;
}offer[103];
LL ans;
int base[5] = {0, 5, 25, 125, 625};

bool Check(const Offer &o, int i1, int i2, int i3, int i4, int i5) {
    for (int i = 1; i <= o.n; ++i) {
        if (o.c[i] != c[1] && o.c[i] != c[2] && o.c[i] != c[3] && o.c[i] != c[4] && o.c[i] != c[5]) return false;
        if (o.c[i] == c[1] && o.k[i] + i1 > num[1]) return false;
        if (o.c[i] == c[2] && o.k[i] + i2 > num[2]) return false;
        if (o.c[i] == c[3] && o.k[i] + i3 > num[3]) return false;
        if (o.c[i] == c[4] && o.k[i] + i4 > num[4]) return false;
        if (o.c[i] == c[5] && o.k[i] + i5 > num[5]) return false;
    }
    return true;
}

int main() {
    // POJ 上有时 scanf 比 cin 慢 = =！！
    ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    scanf("%d", &n);
    ans = 0;
    int tot = 0;
    memset(num, 0, sizeof(num));
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d%lld", &c[i], &num[i], &p[i]);
        ans += p[i] * num[i];
        tot += tot * 5 + num[i];
    }
    
    scanf("%d", &m);
    for (int i = 1; i <= m; ++i) {
        scanf("%d", &offer[i].n);
        for (int j = 1; j <= offer[i].n; ++j) {
            scanf("%d%d", &offer[i].c[j], &offer[i].k[j]);
        }
        scanf("%lld", &offer[i].p);
    }
    memset(f, 0x3f, sizeof(f));
    f[0][0][0][0][0] = 0;
    f[num[5]][num[4]][num[3]][num[2]][num[1]] = ans;
    // printf("! %d %d %d %d %d %lld\n", num[1], num[2], num[3], num[4], num[5], ans);
        
    for (int i1 = 0; i1 <= num[1]; ++i1) {
        for (int i2 = 0; i2 <= num[2]; ++i2) {
            for (int i3 = 0; i3 <= num[3]; ++i3) {
                for (int i4 = 0; i4 <= num[4]; ++i4) {
                    for (int i5 = 0; i5 <= num[5]; ++i5) {
                        for (int j = 1; j <= m; ++j) {
                            Offer o = offer[j];
                            // printf("## %d\n", o.n);
                            if (!Check(o, i1, i2, i3, i4, i5)) continue;
                            int ni1 = i1, ni2 = i2, ni3 = i3, ni4 = i4, ni5 = i5;
                            for (int k = 1; k <= o.n; ++k) {
                                if (o.c[k] == c[1]) ni1 += o.k[k];
                                if (o.c[k] == c[2]) ni2 += o.k[k];
                                if (o.c[k] == c[3]) ni3 += o.k[k];
                                if (o.c[k] == c[4]) ni4 += o.k[k];
                                if (o.c[k] == c[5]) ni5 += o.k[k];
                            }
                            if (f[i1][i2][i3][i4][i5] + o.p < f[ni1][ni2][ni3][ni4][ni5]) {
                                f[ni1][ni2][ni3][ni4][ni5] = f[i1][i2][i3][i4][i5] + o.p;
                                ans = min(ans, f[ni1][ni2][ni3][ni4][ni5] + p[1] * (num[1] - ni1) + p[2] * (num[2] - ni2) 
                                + p[3] * (num[3] - ni3) + p[4] * (num[4] - ni4) + p[5] * (num[5] - ni5));
                            }
                        }
                    }
                }
            }
        }
    }
    printf("%lld\n", ans);
    
    
    return 0;
}
