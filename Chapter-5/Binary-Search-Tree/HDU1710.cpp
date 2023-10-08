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
const int N = 1000 + 10;
int n;
int preorder[N], inorder[N], postorder[N];
struct Node {
    int val;
    Node *left, *right;
    Node(int _val, Node* l = NULL, Node* r = NULL): val(_val), left(l), right(r) {}
};

void Init() {
    memset(preorder, 0, sizeof(preorder));
    memset(inorder, 0, sizeof(inorder));
    memset(postorder, 0, sizeof(postorder));
}

void Build(int &pos, int l, int r, Node* &rt) {
    if (pos > n) return;
    
    int k = 0;
    for (int i = l; i <= r; ++i) {
        if (preorder[pos] == inorder[i]) {
            k = i;
            break;
        }
    }
    if (k == 0) return;
    rt = new Node(inorder[k]);
    pos++;
    if (k > l) Build(pos, l, k - 1, rt->left);
    if (k < r) Build(pos, k + 1, r, rt->right);
}

void PrintPreOrder(Node* rt) {
    if (rt == NULL) return;
    printf("%d ", rt->val);
    PrintPreOrder(rt->left);
    PrintPreOrder(rt->right);
}

void PrintInOrder(Node* rt) {
    if (rt == NULL) return;
    PrintInOrder(rt->left);
    printf("%d ", rt->val);
    PrintInOrder(rt->right);
}

void PrintPostOrder(Node* rt) {
    if (rt == NULL) return;
    PrintPostOrder(rt->left);
    PrintPostOrder(rt->right);
    printf("%d ", rt->val);
}

void Delete(Node* rt) {
    if (rt == NULL) return;
    Delete(rt->left);
    Delete(rt->right);
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
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &preorder[i]);
        }
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &inorder[i]);
        }
        
        Node* rt;
        int pos = 1;
        Build(pos, 1, n, rt);
        PrintPostOrder(rt);
        printf("\n");
        Delete(rt);
    }

    return 0;
}
