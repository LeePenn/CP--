#include <bits/stdc++.h>

#define mytest

using namespace std;
typedef long long LL;
int n, m, a[6];

int main() {

#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    while (cin >> a[1] >> a[2] >> a[3] >> a[4] && (a[1] || a[2] || a[3] || a[4])) {
        bool flag = true;
        int p = a[1];
        while (1) { 
            if (a[1] != p) cout << endl;
            p = a[1];
            for (int i = 1; i <= 4; ++i) cout << a[i];
            cout << " ";
            flag = next_permutation(a + 1, a + 5);
            if (!flag) break;
        }
        cout << endl << endl;;
    }
}