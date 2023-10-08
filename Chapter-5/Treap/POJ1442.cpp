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
const int N = 30000 + 10;
int n, m;
int a[N], u[N];
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
    Node* s = rt->son[0];
    rt->son[0] = s->son[1];
    s->son[1] = rt;
    rt->update();
    s->update();
    rt = s;
}

void Zag(Node* &rt) {
    Node* s = rt->son[1];
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
    
    if (k <= rt->k) {
        Insert(rt->son[0], k);
        rt->update();
        if (rt->son[0]->p > rt->p) Zig(rt);
    } else if (k > rt->k) {
        Insert(rt->son[1], k);
        rt->update();
        if (rt->son[1]->p > rt->p) Zag(rt);
    }
}

int FindKthMin(Node* rt, int rk) {
    if (rt == NULL || rk <= 0 || rk > rt->sz) return -1;
    
    int t1 = rt->son[0] == NULL ? 0 : rt->son[0]->sz;
    int t2 = rt->son[1] == NULL ? 0 : rt->son[1]->sz;
    if (rk <= t1) {
        return FindKthMin(rt->son[0], rk);
    }
    if (rk <= t1 + 1) {
        return rt->k;
    }
    
    return FindKthMin(rt->son[1], rk - t1 - 1);
}

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) 
        scanf("%d", &a[i]);
    for (int i = 1; i <= m; ++i) 
        scanf("%d", &u[i]);
        
    int i = 1, j = 1;
    Node* rt = new Node();
    rt->k = a[1]; rt->p = rand(); rt->sz = 1;
    rt->son[0] = rt->son[1] = NULL;
    i++;
    int cnt = 0;
    while (j <= m) {
        while (i <= u[j]) {
            Insert(rt, a[i]);
            i++;
        }
        cnt++;
        printf("%d\n", FindKthMin(rt, cnt));
        // printf("%d %d\n", i, j);
        j++;
    }
    
    

    return 0;
}
