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
#define lson rt<<1,l,mid
#define rson rt<<1|1,mid+1,r
 
typedef long long ll;
const int MAXN=1e5+7;
int sum1[MAXN], sum2[MAXN], sum3[MAXN];
int cover[MAXN];
int x[MAXN], z[MAXN];
int n;
 
struct Node{
    int l,r,h,f;
}line[MAXN];
 
struct point{
    int x,y,z;
};
 
struct node{
    point a,b;
}cube[MAXN];
 
void init(){
    memset(sum1, 0, sizeof(sum1));
    memset(sum2, 0, sizeof(sum2));
    memset(sum3, 0, sizeof(sum3));
    memset(cover, 0, sizeof(cover));
}
 
bool cmp(Node a, Node b){
    return a.h<b.h;
}
 
void push_up(int rt,int l,int r){
    if (cover[rt] > 2){
        sum3[rt]=x[r+1]-x[l];
        sum1[rt]=sum2[rt]=0;
    } else if (cover[rt] == 2){
        if (l==r){
            sum1[rt]=sum3[rt]=0;
            sum2[rt]=x[r+1]-x[l];
        } else{
            sum3[rt]=sum3[rt<<1]+sum3[rt<<1|1]+sum2[rt<<1]+sum2[rt<<1|1]+sum1[rt<<1]+sum1[rt<<1|1];
            sum2[rt]=x[r+1]-x[l]-sum3[rt];
            sum1[rt]=0;
        }
    } else if (cover[rt] == 1){
        if (l==r){
            sum2[rt]=sum3[rt]=0;
            sum1[rt]=x[r+1]-x[l];
        } else{
            sum3[rt]=sum3[rt<<1]+sum3[rt<<1|1]+sum2[rt<<1]+sum2[rt<<1|1];
            sum2[rt]=sum1[rt<<1]+sum1[rt<<1|1];
            sum1[rt]=x[r+1]-x[l]-sum3[rt]-sum2[rt];
        }
    } else {
        if (l==r){
            sum1[rt]=sum2[rt]=sum3[rt]=0;
        } else{
            sum3[rt]=sum3[rt<<1]+sum3[rt<<1|1];
            sum2[rt]=sum2[rt<<1]+sum2[rt<<1|1];
            sum1[rt]=sum1[rt<<1]+sum1[rt<<1|1];
        }
    }
}
 
void update(int rt, int l, int r, int ul, int ur, int val){
    if (ul<=l && r<=ur){
        cover[rt]+=val;
        push_up(rt,l,r);
        return;
    }
    int mid = (l+r)>>1;
    if (ul<=mid){
        update(lson,ul,ur,val);
    }
    if (mid<ur){
        update(rson,ul,ur,val);
    }
    push_up(rt,l,r);
}
 
 
int main(){
    int t,cas=0;
    scanf("%d", &t);
    while (t--){
        ll ans=0;
        int cntx=0,cntz=0;
        scanf("%d",&n);
        for (int i = 1; i <= n; ++i) {
            scanf("%d %d %d %d %d %d",&cube[i].a.x,&cube[i].a.y,&cube[i].a.z,&cube[i].b.x,&cube[i].b.y,&cube[i].b.z);
            x[++cntx]=cube[i].a.x;
            x[++cntx]=cube[i].b.x;
            z[++cntz]=cube[i].a.z;
            z[++cntz]=cube[i].b.z;
        }
        if (n<3) {
            printf("Case %d: 0\n",++cas);
            continue;
        }
        sort(x+1,x+1+cntx);
        sort(z+1,z+1+cntz);
        cntx= unique(x+1,x+1+cntx)-x-1;
        cntz= unique(z+1,z+1+cntz)-z-1;
        for (int i = 1; i < cntz; ++i) {
            int tot=0;
            for (int k = 1; k <= n; ++k) {
                if (cube[k].a.z<=z[i] && z[i]<cube[k].b.z){
                    int x1=cube[k].a.x, x2=cube[k].b.x;
                    int y1=cube[k].a.y, y2=cube[k].b.y;
                    line[++tot].l=x1,line[tot].r=x2,line[tot].h=y1,line[tot].f=1;
                    line[++tot].l=x1,line[tot].r=x2,line[tot].h=y2,line[tot].f=-1;
                }
            }
            init();
            sort(line+1,line+1+tot,cmp);
            ll res=0;
            for (int k = 1; k < tot; ++k) {
                int l = lower_bound(x+1,x+1+cntx,line[k].l)-x;
                int r = lower_bound(x+1,x+1+cntx,line[k].r)-x-1;
                update(1,1,cntx,l,r,line[k].f);
                res+=(ll)sum3[1]*(line[k+1].h-line[k].h);
            }
            ans+=res*(z[i+1]-z[i]);
        }
        printf("Case %d: %lld\n",++cas, ans);
    }
    return 0;
}