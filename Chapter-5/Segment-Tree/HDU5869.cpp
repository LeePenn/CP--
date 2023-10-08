#include <stdio.h>
#include <iostream>
#include <stack>
#include <complex>
#include <vector>
#include <cstring>

// #define mytest

using namespace std;
typedef long long LL;
const int N = 110000;
int n, q;
int a[N];
int x, y;
vector<pair<int, int> > vec1[N], vec2[N];
int tr[N], pre[N * 10];
int ans[N];

void Debug() {
    for (int i = 1; i <= n; ++i) {
        printf("######## %d\n", i);
        size_t len = vec1[i].size();
        for (int j = 0; j < len; ++j) {
            printf("!! %d %d !!\n", vec1[i][j].first, vec1[i][j].second);
        }
        
        len = vec2[i].size();
        for (int j = 0; j < len; ++j) {
            printf("@@ %d %d @@\n", vec2[i][j].first, vec2[i][j].second);
        }
        printf("########\n");
    }
}

int Gcd(int x, int y) {
    return !y ? x : Gcd(y, x % y);
}

void Init() {
    memset(vec1, 0, sizeof(vec1));
    memset(vec2, 0, sizeof(vec2));
    
    for (int i = 1; i <= n; ++i) {
        vector<pair<int, int> > pv = vec1[i - 1];
        size_t len = pv.size();
        vec1[i].push_back(make_pair(i, a[i]));
        int last = a[i];
        for (int j = 0; j < len; ++j) {
            pair<int, int> cur = pv[j];
            int g = Gcd(last, cur.second);
            if (g != last) {
                vec1[i].push_back(make_pair(cur.first, g));
                last = g;
            }
        }
    }
    
    for (int i = 1; i <= q; ++i) {
        cin >> x >> y;
        vec2[y].push_back(make_pair(x, i));
    }
    
    // Debug();
}

int lowbit(int u) {
    return u & (-u);
}

void Update(int u, int x) {
    while (u <= n) {
        tr[u] += x;
        u += lowbit(u);
    }
}

int Query(int u) {
    int ret = 0;
    while (u) {
        ret += tr[u];
        u -= lowbit(u);
    }
    return ret;
}

void Solve() {
    memset(tr, 0, sizeof(tr));
    memset(pre, 0, sizeof(pre));
    
    for (int i = 1; i <= n; ++i) {
        vector<pair<int, int> > v = vec1[i];
        size_t len = v.size();
        for (int j = 0; j < len; ++j) {
            pair<int, int> cur = v[j];
            if (pre[cur.second]) Update(pre[cur.second], -1);
            pre[cur.second] = cur.first;
            Update(cur.first, 1);
        }
        
        v = vec2[i];
        len = v.size();
        for (int j = 0; j < len; ++j) {
            pair<int, int> cur = v[j];
            ans[cur.second] = Query(i) - Query(cur.first - 1);
        }
    }
    
    for (int i = 1; i <= q; ++i) cout << ans[i] << endl;
    
}

int main() {
    // 特别注意！！cin cout 加上取消同步后比 scanf 和 printf 要快
    ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    while (cin >> n >> q) {
        for (int i = 1; i <= n; ++i) cin >> a[i];
        
        Init();
        
        Solve();
        
    }
    
    

    return 0;
}
