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
const int N = 100000;
int A, B, C;
struct Pots {
    int a, b;
    // 1 fill 2 drop 3 pour 
    int op, dist;
    Pots() { a = b = op = dist = 0; }
    Pots(int _a, int _b, int _op, int _dist) {
        a = _a;
        b = _b;
        op = _op;
        dist = _dist;
    }
}pot[N];
int pre[N];
bool vis[N];

int Gcd(int a, int b) {
    return !b ? a : Gcd(b, a % b);
}

int getHash(const Pots &p) {
    return (p.a << 10) + p.b;
}

void Print(const Pots &p) {
    if (p.dist == 0) return;
    
    int pp = pre[getHash(p)];
    Print(pot[pp]);
    // fill
    if (p.op / 10 == 1) {
        if (p.op % 10 == 1) printf("FILL(1)\n");
        else printf("FILL(2)\n");
        return;
    }
    
    if (p.op / 10 == 2) {
        if (p.op % 10 == 1) printf("DROP(1)\n");
        else printf("DROP(2)\n");
        return;
    }
    
    if (p.op % 10 == 1) {
        printf("POUR(1,2)\n");
    } else printf("POUR(2,1)\n");
}

int main() {

#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    cin >> A >> B >> C;
    if (C % Gcd(A, B) != 0) {
        cout << "impossible" << endl;
        return 0;
    }
    
    int hh = 1, tt = 1;
    pot[1] = Pots(0, 0, 0, 0);
    pre[getHash(pot[1])] = 0;
    vis[getHash(pot[1])] = true;
    while (hh >= tt) {
        Pots cur = pot[tt]; tt++;
        if (cur.a == C || cur.b == C) {
            cout << cur.dist << endl;
            Print(cur);
            break;
        }
        // printf("a = %d, b = %d, op = %d, dist = %d\n", cur.a, cur.b, cur.op, cur.dist);
        
        // fill a
        if (cur.a < A) {
            Pots nx;
            nx.a = A, nx.b = cur.b, nx.op = 11, nx.dist = cur.dist + 1;
            if (!vis[getHash(nx)]) {
                pot[++hh] = nx;
                pre[getHash(nx)] = tt - 1;
                vis[getHash(nx)] = true;
            }
        }
        // fill b
        if (cur.b < B) {
            Pots nx;
            nx.a = cur.a, nx.b = B, nx.op = 12, nx.dist = cur.dist + 1;
            if (!vis[getHash(nx)]) {
                pot[++hh] = nx;
                pre[getHash(nx)] = tt - 1;
                vis[getHash(nx)] = true;
            }
        }
        // drop a
        if (cur.a > 0) {
            Pots nx;
            nx.a = 0, nx.b = cur.b, nx.op = 21, nx.dist = cur.dist + 1;
            if (!vis[getHash(nx)]) {
                pot[++hh] = nx;
                pre[getHash(nx)] = tt - 1;
                vis[getHash(nx)] = true;
            }
        }
        // drop b
        if (cur.b > 0) {
            Pots nx;
            nx.a = cur.a, nx.b = 0, nx.op = 22, nx.dist = cur.dist + 1;
            if (!vis[getHash(nx)]) {
                pot[++hh] = nx;
                pre[getHash(nx)] = tt - 1;
                vis[getHash(nx)] = true;
            }
        }
        // pour a b
        if (cur.a > 0 && cur.b < B) {
            Pots nx;
            nx.a = max(cur.a - (B - cur.b), 0);
            nx.b = min(cur.a + cur.b, B), nx.op = 31, nx.dist = cur.dist + 1;
            if (!vis[getHash(nx)]) {
                pot[++hh] = nx;
                pre[getHash(nx)] = tt - 1;
                vis[getHash(nx)] = true;
            }
        }
        // pour b a
        if (cur.a < A && cur.b > 0) {
            Pots nx;
            nx.a = min(cur.a + cur.b, A);
            nx.b = max(cur.b - (A - cur.a), 0), nx.op = 32, nx.dist = cur.dist + 1;
            if (!vis[getHash(nx)]) {
                pot[++hh] = nx;
                pre[getHash(nx)] = tt - 1;
                vis[getHash(nx)] = true;
            }
        }
    }
    
    return 0;
}