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
const int N = 100000 + 10, INF = 100000000;
struct Node {
    int val;
    char s[300];
    int len;
    bool operator <(const Node &rh) const {
        return len < rh.len;
    }
    
    void print() {
        printf("%d %d\n", val, len);
        for (int i = 1; i <= len; ++i) printf("%c", s[i]);
        printf("\n");
    }
}node[300];
int tot;
int tr[300], lc[300], rc[300], trtot;
bool flag;

void Init() {
    for (int i = 1; i < 300; ++i) node[i].len = 100000;
    tot = 0;
    trtot = 0;
    memset(tr, 0, sizeof(0));
    memset(lc, 0, sizeof(lc));
    memset(rc, 0, sizeof(rc));
}

void Solve() {
    if (!flag) {
        printf("not complete\n");
        return;
    }
    sort(node + 1, node + tot + 1);
    if (node[1].len != 0) {
        printf("not complete\n");
        return;
    }
    tr[++trtot] = node[1].val;
    int rt = 1;
    for (int i = 2; i <= tot; ++i) {
        // node[i].print();
        int rt = 1;
        for (int j = 1; j < node[i].len; ++j) {
            int k = node[i].s[j] == 'L' ? lc[rt] : rc[rt];
            if (!tr[k]) {
                // node[i].print();
                printf("not complete\n");
                return;
            }
            rt = k;
        }
        int t = rt;
        if (node[i].s[node[i].len] == 'L') {
            t = lc[rt];
        } else {
            t = rc[rt];
        }
        if (tr[t]) {
            printf("not complete\n");
            return;
        }
        tr[++trtot] = node[i].val;
        if (node[i].s[node[i].len] == 'L') {
            lc[rt] = trtot;
        } else {
            rc[rt] = trtot;
        }
    }
    
    rt = 1;
    int q[300], hh = 1, tt = 1;
    q[hh] = 1;
    while (hh <= tt) {
        int cur = q[hh]; hh++;
        printf("%d ", tr[cur]);
        if (lc[cur]) q[++tt] = lc[cur];
        if (rc[cur]) q[++tt] = rc[cur];
    }
    printf("\n");
}

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    char c;
    char tmp[300];
    Init();
    flag = true;
    while ((c = getchar()) && c != EOF) {
        if (c == '(') {
            c = getchar();
            if (c == ')') {
                Solve();
                Init();
                // for (int i = 1; i <= tot; ++i) {
                //     node[i].print();
                // }
                continue;
            } else if (isdigit(c)) {
                if (c == ',') flag = false;
                int num = 0;
                while (isdigit(c)) {
                    num = num * 10 + (c - '0');
                    c = getchar();
                }
                c = getchar();
                int cnt = 0;
                while (isalpha(c)) {
                    tmp[++cnt] = c;
                    c = getchar();
                }
                node[++tot].len = cnt;
                node[tot].val = num;
                memcpy(node[tot].s, tmp, sizeof(node[tot].s));
            }
        }
    }
    

    return 0;
}
