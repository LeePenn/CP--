#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>

#define mytest

using namespace std;
typedef long long LL;
const int N = 1000 + 3;
struct Node {
    int id, step;
    Node() { id = step = 0; }
    Node(int _id, int _step) {
        id = _id;
        step = _step;
    }
}q[N];
int n, m;
bool vis[N];
vector<string> names;
map<string, int> namesID;
vector<int> g[N];
bool flag;
int ans;

void Bfs(int x) {
    
    int hh = 1, tt = 1;
    q[1] = Node(x, 0);
    memset(vis, 0, sizeof(vis));
    vis[x] = 1;
    int mx = 0;
    int cnt = 1;
    while (hh >= tt) {
        Node c = q[tt]; tt++;
        mx = max(mx, c.step);
        for (int i = 0; i < g[c.id].size(); ++i) {
            int nx = g[c.id][i];
            if (!vis[nx]) {
                q[++hh] = Node(nx, c.step + 1);
                vis[nx] = 1;
                cnt++;
            }
        }
    }
    
    if (cnt < n) flag = true;
    ans = max(ans, mx);
}

void Clear() {
    namesID.clear();
    names.clear();
    for (int i = 0; i < N; ++i) {
        g[i].clear();
    }
}

int main() {

#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    string s;
    string s1, s2;
    while (cin >> n && n) {
        Clear();
        for (int i = 0; i < n; ++i) {
            cin >> s;
            namesID[s] = names.size();
            names.push_back(s);
        }
        cin >> m;
        for (int i = 1; i <= m; ++i) {
            cin >> s1 >> s2;
            int id1 = namesID[s1], id2 = namesID[s2];
            g[id1].push_back(id2);
            g[id2].push_back(id1);
        }
        flag = false;
        ans = 0;
        for (int i = 0; i < n; ++i) {
            memset(vis, 0, sizeof(vis));
            Bfs(i);
        }
        
        
        if (flag) cout << -1 << endl;
        else cout << ans << endl;
    }
    
    
    
    return 0;
}