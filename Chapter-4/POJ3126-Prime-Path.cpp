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
const int N = 10000;
int n, p1, p2;
int prime[N], tot, v[N], p[N], rev[N], cnt;
bool vis[N];
vector<int> g[N];
int que[N], head, tail, dist[N];
bool v2[N];

void Init() {
    for (int i = 2; i < N; ++i) {
        if (!v[i]) {
            prime[++tot] = i;
            v[i] = i;
        }
        
        for (int j = 1; j <= tot; ++j) {
            if (prime[j] > v[i] || prime[j] * i >= N) break;
            v[prime[j] * i] = prime[j];
        }
    }
    
    for (int i = 2; i <= tot; ++i) {
        if (prime[i] >= 1000) {
            p[++cnt] = prime[i];
            rev[prime[i]] = cnt;
        }
    }
}

bool Check(int p1, int p2) {
    int cnt = 0;
    while (p1 || p2) {
        if ((p1 % 10) != (p2 % 10)) cnt++;
        p1 /= 10;
        p2 /= 10;
    }
    return cnt == 1;
}

void Build() {
    for (int i = 1; i <= cnt; ++i) {
        int cp = p[i];
        for (int j = 1; j <= cnt; ++j) {
            int cp2 = p[j];
            if (Check(cp, cp2)) {
                g[i].push_back(j);
            }
        }
    }
}

int main() {

#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    Init();
    Build();
    cin >> n;
    int p1, p2;
    while (n--) {
        cin >> p1 >> p2;
        head = 1, tail = 1;
        que[head] = rev[p1];
        memset(dist, 0, sizeof(dist));
        dist[rev[p1]] = 0;
        memset(v2, 0, sizeof(v2));
        v2[rev[p1]] = true;
        while (head >= tail) {
            int cp = que[tail]; tail++;
            if (cp == rev[p2]) {
                cout << dist[cp] << endl;
                break;
            }
            int sz = g[cp].size();
            for (int i = 0; i < sz; ++i) {
                int np = g[cp][i];
                if (!v2[np]) {
                    que[++head] = np;
                    dist[np] = dist[cp] + 1;
                    v2[np] = true;
                }
            }
        }
    }
    
    
    return 0;
}