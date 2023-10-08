#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<vector>
#include<algorithm>
#include<cstring>
#include<set>
#include<map>
#include<queue>
#include<stack>
#include<string>
#include<cmath>
#include<climits>
 
using namespace std;
#define lson l,mid,rt<<1
#define rson mid+1,r,rt<<1|1
typedef long long ll;
const int MAXN=5e4+5;
int l_t[MAXN],r_t[MAXN];
int degree[MAXN];
ll tree[MAXN<<3];
vector<int> edge[MAXN];
int N,tot;
 
void dfs(int rt){
    l_t[rt]=++tot;
    for (int i = 0; i < edge[rt].size(); ++i) {
        dfs(edge[rt][i]);
    }
    r_t[rt]=++tot;
}
 
void build(int l,int r,int rt){
    tree[rt]=-1;
    if (l==r) return;
    int mid=(l+r)>>1;
    build(lson);
    build(rson);
}
 
void push_down(int rt){
    if (tree[rt]!=-1){
        tree[rt<<1]=tree[rt];
        tree[rt<<1|1]=tree[rt];
        tree[rt]=-1;
    }
}
 
void update(int L,int R,int val,int l,int r,int rt){
    if (L<=l && r<=R){
        tree[rt]=val;
        return;
    }
    push_down(rt);
    int mid=(l+r)>>1;
    if (L<=mid){
        update(L,R,val,lson);
    }
    if (R>mid){
        update(L,R,val,rson);
    }
}
 
int query(int L,int l,int r,int rt){
    if (l==r && L==l) return tree[rt];
    push_down(rt);
    int mid=(l+r)>>1;
    if (L<=mid){
        return query(L,lson);
    } else {
        return query(L,rson);
    }
}
 
int main(){
    scanf("%d", &N);
    int n,u,v,m,x,y;
    int kase=0;
    while (N--){
        tot = 0;
        memset(degree, 0, sizeof(degree));
        for (int i = 0; i < MAXN; ++i) {
            edge[i].clear();
        }
        scanf("%d", &n);
        for (int i = 1; i < n; ++i) {
            scanf("%d %d",&u,&v);
            edge[v].push_back(u);
            degree[u]++;
        }
        int root=-1;
        for (int i = 1; i <= n; ++i) {
            if (!degree[i]){
                root=i;
                break;
            }
        }
        dfs(root);
        build(1,2*n,1);
        printf("Case #%d:\n",++kase);
        scanf("%d",&m);
        while (m--){
            char op[2];
            scanf("%s",op);
            if (op[0]=='C'){
                scanf("%d",&x);
                printf("%d\n", query(l_t[x],1,2*n,1));
            }else{
                scanf("%d %d",&x,&y);
                update(l_t[x],r_t[x],y,1,2*n,1);
            }
        }
    }
    return 0;
}