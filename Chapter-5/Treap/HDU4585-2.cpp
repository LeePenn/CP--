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

// #define mytest

using namespace std;
typedef long long LL;
const int N = 100000 + 10;
int n;
struct Node {
    int val, sz, rk;
    Node *son[2];
    bool operator < (const Node &a) const {
        return rk < a.rk;
    }
    int cmp(int x) const {
        if (x == val) return -1;
        return x < val ? 0 : 1;
    }
    void update() {
        sz = 1;
        if (son[0] != NULL) sz += son[0]->sz;
        if (son[1] != NULL) sz += son[1]->sz;
    }
};
int id[5000000 + 10];

void Rotate(Node* &rt, int d) {
    Node* s = rt->son[d];
    rt->son[d] = s->son[d ^ 1];
    s->son[d ^ 1] = rt;
    rt->update();
    s->update();
    rt = s;
}

void Insert(Node* &rt, int x) {
    if (rt == NULL) {
        rt = new Node();
        rt->son[0] = rt->son[1] = NULL;
        rt->rk = rand(); rt->val = x; rt->sz = 1;
        return;
    }
    
    int d = rt->cmp(x);
    Insert(rt->son[d], x);
    rt->update();
    if (rt < rt->son[d]) {
        Rotate(rt, d);
    }
}

int Find(Node* rt, int k) {
    if (rt == NULL) return -1;
    int d = rt->cmp(k);
    if (d == -1) {
        return rt->son[1] == NULL ? 1 : rt->son[1]->sz + 1;
    }
    
    if (d == 1) return Find(rt->son[d], k);
    
    int tmp = Find(rt->son[d], k);
    if (tmp == -1) return -1;
    return rt->son[1] == NULL ? tmp + 1 : tmp + 1 + rt->son[1]->sz;
}

int Kth(Node* rt, int k) {
    if (rt == NULL || k <= 0 || k > rt->sz) return -1;
    
    int tmp = rt->son[1] == NULL ? 0 : rt->son[1]->sz;
    if (k == tmp + 1) return rt->val;
    if (k <= tmp) return Kth(rt->son[1], k);
    return Kth(rt->son[0], k - tmp - 1);
}

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    int k, g;
    while(scanf("%d", &n) == 1 && n) {
        srand(time(NULL));
        scanf("%d%d", &k, &g);
        Node *rt = new Node();
        rt->son[0] = rt->son[1] = NULL;
        rt->rk = rand(); rt->val = g; rt->sz = 1;
        id[g] = k;
        printf("%d %d\n", k, 1);
        for (int i = 2; i <= n; ++i) {
            scanf("%d%d", &k, &g);
            id[g] = k;
            Insert(rt, g);
            int t = Find(rt, g);
            int ans1, ans2, ans;
            ans1 = Kth(rt, t - 1);
            ans2 = Kth(rt, t + 1);
            if (ans1 != -1 && ans2 != -1) {
                ans = ans1 - g >= g - ans2 ? ans2 : ans1;
            } else if (ans1 == -1) ans = ans2;
            else ans = ans1;
            printf("%d %d\n", k, id[ans]);
        }
    }

    return 0;
}
