#include<cstdio>
#include<cstring>
#include<map>
#include<cmath>
#include<algorithm>
using namespace std;
const int MAXN=5e5+5;
struct node
{
    int l,r,num;
}tree[MAXN<<2];
char s[MAXN][11];
int p[MAXN],add[MAXN],n,k;
void table()
{
    for(int i=1;i<MAXN;i++)p[i]=1;
    for(int i=2;i<MAXN;i++)
        for(int j=i;j<MAXN;j+=i)
            p[j]++;
    int maxv=0;
    for(int i=2;i<MAXN;i++)
    {
        if(p[i]>maxv)maxv=p[i];
        p[i]=maxv;
    }
}
void pushup(int o)
{
    tree[o].num=tree[o<<1].num+tree[o<<1|1].num;
}
void build(int l,int r,int o)
{
    tree[o].l=l,tree[o].r=r;
    if(l==r){tree[o].num=1;return;}
    int mid=(l+r)>>1;
    build(l,mid,o<<1);
    build(mid+1,r,o<<1|1);
    pushup(o);
}
int update(int ad,int o)
{
    int res;
    if(tree[o].l==tree[o].r){tree[o].num=0;return tree[o].l;}
    if(ad>tree[o<<1].num)res=update(ad=ad-tree[o<<1].num,o<<1|1);
    else res=update(ad,o<<1);
    pushup(o);
    return res;
}
int query(int L,int R,int o)
{
    if(tree[o].l==L&&tree[o].r==R)return tree[o].num;
    int mid=(tree[o].l+tree[o].r)>>1;
    if(mid>=R)return query(L,R,o<<1);
    else if(mid<L)return query(L,R,o<<1|1);
    else return query(L,mid,o<<1)+query(mid+1,R,o<<1|1);
}
int main()
{
    table();
    while(scanf("%d%d",&n,&k)!=EOF)
    {
        for(int i=1;i<=n;i++)
            scanf("%s%d",s[i],&add[i]);
        build(1,n,1);
        int num=k,pos=update(num,1);
        for(int i=2;i<=n;i++)
        {
            if(add[pos]>=0)
            {
                num=add[pos]+query(1,pos,1);
                num=(num-1+n-i+1)%(n-i+1)+1;
                pos=update(num,1);
            }
            else
            {
                num=-add[pos]+query(pos,n,1);
                num%=(n-i+1);
                num=(n-i+1)-(num-1);
                num=(num-1)%(n-i+1)+1;
                pos=update(num,1);
            }
            if(p[i]==p[n])break;
        }
        printf("%s %d\n",s[pos],p[n]);
    }
    return 0;
}