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
    int val;
    Node* l, *r;
    Node(int val = 0, Node* l = NULL, Node* r = NULL):val(val), l(l), r(r) {}
};

Node* Build(int v, Node* rt) {
    if (rt == NULL) {
        rt = new Node(v, NULL, NULL);
        return rt;
    }
    
    if (v < rt->val) {
        rt->l = Build(v, rt->l);
    } else if (v >= rt->val) {
        rt->r = Build(v, rt->r);
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

bool Check(Node* &rt1, Node* &rt2) {
    if (rt1 == NULL && rt2 == NULL) return true;
    if (rt1 == NULL || rt2 == NULL) {
        return false;
    }
    if (rt1->val != rt2->val) {
        return false;
    }
    return Check(rt1->l, rt2->l) && Check(rt1->r, rt2->r);
}

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    string s;
    while (scanf("%d", &n) == 1 && n) {
        Node *rt1 = NULL;
        cin >> s;
        int len = s.length();
        for (int i = 0; i < len; ++i) {
            rt1 = Build(s[i] - '0', rt1);
        }
        // PrintPreOrder(rt1);
        // printf("\n");
        // PrintInOrder(rt1);
        // printf("\n");
        for (int i = 1; i <= n; ++i) {
            cin >> s;
            len = s.length();
            Node *rt2 = NULL;
            for (int j = 0; j < len; ++j) {
                rt2 = Build(s[j] - '0', rt2);
            }
            if (Check(rt1, rt2)) {
                printf("YES");
            } else {
                printf("NO");
            }
            printf("\n");
            Delete(rt2);
        }
        Delete(rt1);
    }

    return 0;
}
