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
int id[5000000 + 10];
struct Node {
    int k, p, sz;
    Node* son[2];
    void update() {
        sz = 1;
        if (son[0] != NULL) sz += son[0]->sz;
        if (son[1] != NULL) sz += son[1]->sz;
    }
};

void Zig(Node* &rt) {
    Node *s = rt->son[0];
    rt->son[0] = s->son[1];
    s->son[1] = rt;
    rt->update();
    s->update();
    rt = s;
}

void Zag(Node* &rt) {
    Node *s = rt->son[1];
    rt->son[1] = s->son[0];
    s->son[0] = rt;
    rt->update();
    s->update();
    rt = s;
}

void Insert(Node* &rt, int k) {
    if (rt == NULL) {
        rt = new Node();
        rt->k = k; rt->p = rand(); rt->sz = 1;
        rt->son[0] = rt->son[1] = NULL;
        return;
    }
    
    if (k < rt->k) {
        Insert(rt->son[0], k);
        rt->update();
        if (rt->p < rt->son[0]->p) Zig(rt);
    } else {
        Insert(rt->son[1], k);
        rt->update();
        if (rt->p < rt->son[1]->p) Zag(rt);
    }
}

int FindKth(Node *rt, int k) {
    if (rt == NULL || k <= 0 || k > rt->sz) return -1;
    
    int t = rt->son[1] == NULL ? 0 : rt->son[1]->sz;
    if (k == t + 1) return rt->k;
    if (k <= t) return FindKth(rt->son[1], k);
    return FindKth(rt->son[0], k - t - 1);
}

int FindRk(Node *rt, int k) {
    if (rt == NULL) return -1;
    if (rt->k == k) return rt->son[1] == NULL ? 1 : rt->son[1]->sz + 1;
    
    if (k < rt->k) {
        int t = FindRk(rt->son[0], k);
        if (t == -1) return -1;
        return rt->son[1] == NULL ? t + 1 : t + 1 + (rt->son[1]->sz);
    } 
    return FindRk(rt->son[1], k);
}

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    int k, g;
    while (scanf("%d", &n) == 1 && n) {
        scanf("%d %d", &k, &g);
        Node *rt = new Node();
        rt->k = g; rt->p = rand(); rt->sz = 1;
        rt->son[0] = rt->son[1] = NULL;
        id[g] = k;
        printf("%d %d\n", k, 1);
        for (int i = 1; i < n; ++i) {
            scanf("%d %d", &k, &g);
            id[g] = k;
            Insert(rt, g);
            int t = FindRk(rt, g);
            // printf("!! %d %d\n", g, t);
            int ans1, ans2, ans;
            ans1 = FindKth(rt, t - 1);
            ans2 = FindKth(rt, t + 1);
            // printf("## %d %d\n", ans1, ans2);
            if (ans1 != -1 && ans2 != -1) {
                ans = ans1 - g >= g - ans2 ? ans2 : ans1;
            } else if (ans1 == -1) {
                ans = ans2;
            } else ans = ans1;
            
            printf("%d %d\n", k, id[ans]);
        }
    }
    

    return 0;
}
