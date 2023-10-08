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
const int N = 1000000 + 5;
int n, m;
int a[N];
int ansmin[N], ansmax[N];
int qmin[N], qmax[N];

int main() {
    // POJ 上有时 scanf 比 cin 慢 = =！！
    ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    // scanf("%d%d", &n, &m);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        // scanf("%d", &a[i]);
        cin >> a[i];
    }
    int minhh = 0, mintt = 1;
    int maxhh = 0, maxtt = 1;
    for (int i = 1; i <= n; ++i) {
        while (minhh >= mintt && a[qmin[minhh]] > a[i]) minhh--;
        while (maxhh >= maxtt && a[qmax[maxhh]] < a[i]) maxhh--;
            
        qmin[++minhh] = i;
        qmax[++maxhh] = i;
        
        while (minhh >= mintt && qmin[mintt] + m - 1 < i) mintt++;
        while (maxhh >= maxtt && qmax[maxtt] + m - 1 < i) maxtt++;
        
        ansmin[i] = a[qmin[mintt]];
        ansmax[i] = a[qmax[maxtt]];
        if (i >= m) {
            // printf("%d ", ansmin[i]);
            cout << ansmin[i] << " ";
        }
    }
    // printf("\n");
    cout << endl;
    for (int i = m; i <= n; ++i) {
        // printf("%d ", ansmax[i]);
        cout << ansmax[i] << " ";
    }
    // printf("\n");
    cout << endl;
        
    

    return 0;
}
