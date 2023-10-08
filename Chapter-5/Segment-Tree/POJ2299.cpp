#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <cmath>
#include <stack>
#include <queue>
#include <vector>
#include <map>
#include <set>
using namespace std;
#define INF 0x3f3f3f
#define zero 1e-7
//逆序对
typedef long long ll;
const int N=5e5+5;

int n, sum[N];

struct node {
    int v, id;
}a[N];

bool cmp(node x, node y) {
    return x.v<y.v;
}

int lowbit(int x) {
    return x&(-x);
}

void add(int x, int c) {
    while(x<=n) {
        sum[x]+=c;
        x+=lowbit(x);
    }
    return ;
}

int query(int x) {
    int ans=0;
    while(x) {
        ans+=sum[x];
        x-=lowbit(x);
    }
    return ans;
}

int main() {
    while(scanf("%d", &n), n) {
        for(int i=1; i<=n; i++) {
            scanf("%d", &a[i].v);
            a[i].id=i;
        }
        sort(a+1, a+n+1, cmp);
        //从最小的开始一个个除去，同时计算该数前面有多少个比它大的
        //所以要初始化第i个数的逆序数为它前面的数的个数，在树状数组里即为sun[i]=lowbit[i]
        for(int i=1; i<=n; i++)
            sum[i]=lowbit(i);
        ll ans=0;
        for(int i=1; i<=n; i++) {
            add(a[i].id, -1);
            ans+=(ll)(query(a[i].id-1));
        }
        printf("%I64d\n", ans);
    }
    return 0;
}

