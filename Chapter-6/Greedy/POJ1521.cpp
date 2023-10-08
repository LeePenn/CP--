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
string s;


int main() {
    // POJ 上有时 scanf 比 cin 慢 = =！！
    ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    while (getline(cin, s) && s != "END") {
        priority_queue<int, vector<int>, greater<int> > pq;
        sort(s.begin(), s.end());
        int t = 1;
        int len = s.length();
        for(int i = 0; i < len; i++){
			if(s[i] != s[i + 1]){
				pq.push(t);
				t = 1;
			} else{
				++t;
			}
		}
        int ans = 0;
        if (pq.size() == 1) ans = pq.top();
        while (pq.size() > 1) {
            int a = pq.top(); pq.pop();
            int b = pq.top(); pq.pop();
            pq.push(a + b);
            ans += (a + b);
        }
        
        printf("%d %d %.1f\n", len * 8, ans, 8.0 * len / ans);
    }
    

    return 0;
}
