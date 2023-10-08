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
    int lc, rc;
    Node() { val = lc = rc = 0; }
    Node(int _val, int _lc, int _rc): val(_val), lc(_lc), rc(_rc) {}
}tr[N];
int tot;

void Init() {
    memset(tr, 0, sizeof(tr));
    tot = 0;
}

int Build(int &pos, int l, int r) {
    if (pos > n) return 0;
    
    int k = 0;
    for (int i = l; i <= r; ++i) {
        if (preorder[pos] == inorder[i]) {
            k = i;
            break;
        }
    }
    if (k == 0) return 0;
    tr[++tot].val = inorder[k];
    // must declare a tmp, remember that tot is a global variable
    int tmp = tot;
    pos++;
    if (k > l) tr[tmp].lc = Build(pos, l, k - 1);
    if (k < r) tr[tmp].rc = Build(pos, k + 1, r);
    return tmp;
}

void PrintPreOrder(Node rt) {
    if (rt.val == 0) return;
    printf("%d ", rt.val);
    PrintPreOrder(tr[rt.lc]);
    PrintPreOrder(tr[rt.rc]);
}

void PrintInOrder(Node rt) {
    if (rt.val == 0) return;
    PrintInOrder(tr[rt.lc]);
    printf("%d ", rt.val);
    PrintInOrder(tr[rt.rc]);
}

void PrintPostOrder(Node rt) {
    if (rt.val == 0) return;
    PrintPostOrder(tr[rt.lc]);
    PrintPostOrder(tr[rt.rc]);
    printf("%d ", rt.val);
}

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    while (scanf("%d", &n) == 1) {
        Init();
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &preorder[i]);
        }
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &inorder[i]);
        }
        
        int pos = 1;
        Build(pos, 1, n);
        PrintPostOrder(tr[1]);
        printf("\n");
    }

    return 0;
}
