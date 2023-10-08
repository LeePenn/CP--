#include <bits/stdc++.h>

#define mytest

using namespace std;
typedef long long LL;
struct Pat {
    int id, p;
    Pat() { id = p = 0; }
    Pat(int _id, int _p) {
        id = _id;
        p = _p;
    }
    
    bool operator < (const Pat &rh) const {
        return p < rh.p;
    }
}pat[2005];
int n;

int main() {

#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    while (cin >> n) {
        string s;
        int a, b;
        priority_queue<Pat> pq[4];
        int id = 1;
        for (int i = 1; i <= n; ++i) {
            cin >> s;
            if (s == "IN") {
                cin >> a >> b;
                pq[a].push(Pat(id, b));
                id++;
            } else {
                cin >> a;
                if (pq[a].empty()) {
                    cout << "EMPTY" << endl;
                } else {
                    Pat cur = pq[a].top(); pq[a].pop();
                    cout << cur.id << endl;
                }
            }
        }
    }
    
    return 0;
}