#include <stdio.h>
#include <iostream>
#include <stack>
#include <complex>
#include <vector>
#include <cstring>
#include <map>
#include <algorithm>
#include <queue>
// #include <queue>

// #define mytest

using namespace std;
typedef long long LL;
const int N = 1000000 + 5;
int T;
double y;
double eps = 1e-8;

double Calc(double x) {
    return 6 * pow(x, 7.0) + 8 * pow(x, 6.0) + 7 * pow(x, 3.0) + 5 * pow(x, 2.0) - x * y;
}

void Solve() {
    double T, delta, x, now, ans;
    T = 100, delta = 0.98, x = 50;
    ans = Calc(x);
    int f[2] = {-1, 1};
    while (T > eps) {
        double nx = x + f[rand() % 2] * T;
        if (nx >= 0 && nx <= 100) {
            double nxv = Calc(nx);
            if (ans > nxv) {
                ans = nxv;
                x = nx;
            }          
        }
        T *= delta;
    }
    
    printf("%.4f\n", ans);
}

int main() {
    // POJ 上有时 scanf 比 cin 慢 = =！！
    ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    scanf("%d", &T);
    for (int i = 1; i <= T; ++i) {
        scanf("%lf", &y);
        Solve();
    }
    
    

    return 0;
}
