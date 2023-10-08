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
int a[N];
struct Node {
    int val;
    Node *l, *r;
    Node(int val, Node* l = NULL, Node* r = NULL): val(val), l(l), r(l){}
};

Node* Build(int val, Node* rt) {
    if (rt == NULL) {
        rt = new Node(val, NULL, NULL);
        return rt;
    }
    
    if (val < rt->val) {
        rt->l = Build(val, rt->l);
    } else if (val >= rt->val) {
        rt->r = Build(val, rt->r);
    }
    return rt;
}

void PrintPreOrder(Node *rt) {
    if (rt == NULL) return;
    printf("%d ", rt->val);
    PrintPreOrder(rt->l);
    PrintPreOrder(rt->r);
}

void PrintInOrder(Node *rt) {
    if (rt == NULL) return;
    PrintInOrder(rt->l);
    printf("%d ", rt->val);
    PrintInOrder(rt->r);
}

void PrintPostOrder(Node *rt) {
    if (rt == NULL) return;
    PrintPostOrder(rt->l);
    PrintPostOrder(rt->r);
    printf("%d ", rt->val);
}

void Delete(Node *rt) {
    if (rt == NULL) return;
    Delete(rt->l);
    Delete(rt->r);
    delete rt;
}

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    while (scanf("%d", &n) == 1) {
        Node* rt = NULL;
        scanf("%d", &a[1]);
        rt = Build(a[1], rt);
        for (int i = 2; i <= n; ++i) {
            scanf("%d", &a[i]);
            rt = Build(a[i], rt);
        }
        PrintPreOrder(rt);
        printf("\n");
        Delete(rt);
    }

    return 0;
}
