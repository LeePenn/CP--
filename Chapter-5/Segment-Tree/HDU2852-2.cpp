#include <stdio.h>
#include <iostream>
#include <stack>
#include <complex>
#include <vector>
#include <cstring>
#include <map>
#include <algorithm>
// #include <queue>

// #define mytest
using namespace std;
#define lowbit(x) ((x)&(-x))
typedef long long LL;

const int maxm = 1e5+5;
const int INF = 0x3f3f3f3f;

int C[maxm], n;

void init() {
    memset(C, 0, sizeof(C));
}

void add(int pos, int val) {
    for(; pos <= maxm; pos += lowbit(pos))
        C[pos] += val;
}

int getsum(int pos) {
    int ret = 0;
    for(; pos; pos -= lowbit(pos))
        ret += C[pos];
    return ret;
}

int biSearch(int a, int k) {
    int l = 1, r = 99999, mid, ans = -1;
    while(l <= r) {
        mid = (l + r) >> 1;
        int t1 = getsum(mid), t2 = getsum(a);
        if(getsum(mid) - getsum(a) >= k) {
            ans = mid;
            r = mid - 1;
        } else 
            l = mid + 1;
    }
    return ans;
}

int main() {
    while(scanf("%d", &n) != EOF) {
        init();
        int type, t1, t2, jud;
        for(int i = 0; i < n; ++i) {
            scanf("%d", &type);
            if(type == 0) {
                scanf("%d", &t1);
                add(t1, 1);
            } else if(type == 1) {
                scanf("%d", &t1);
                if(getsum(t1) - getsum(t1-1) == 0)
                    printf("No Elment!\n");
                else
                    add(t1, -1);
            } else if(type == 2) {
                scanf("%d%d", &t1, &t2);
                jud = biSearch(t1, t2);
                if(jud == -1)
                    printf("Not Find!\n");
                else
                    printf("%d\n", jud);
            }
        }
    }
    return 0;
}