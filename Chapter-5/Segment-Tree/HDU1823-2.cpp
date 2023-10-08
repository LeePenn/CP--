#include<iostream>
#include<cstdio>
using namespace std;
#define maxn 2050
 
struct sub_Tree
{
    int l,r;
    int val;
};//子树
 
struct Tree
{
    int l,r;
    sub_Tree subtree[maxn<<2];
}tree[maxn<<2];//母树，其中的一个元素即为子线段树
 
void build_subTree(int l,int r,int sub_rt,int rt)
{
    tree[rt].subtree[sub_rt].l=l;
    tree[rt].subtree[sub_rt].r=r;
    tree[rt].subtree[sub_rt].val=-1;
    if(l==r) return ;
 
    int m=(l+r)>>1;
    build_subTree(l,m,sub_rt<<1,rt);
    build_subTree(m+1,r,sub_rt<<1|1,rt);
}//建立子树
 
void buildTree(int l,int r,int ll,int rr ,int rt)
{
    tree[rt].l=l;
    tree[rt].r=r;
    build_subTree(ll,rr,1,rt);
    if(l==r) return ;
    int m=(l+r)>>1;
    buildTree(l,m,ll,rr,rt<<1);
    buildTree(m+1,r,ll,rr,rt<<1|1);
}//建立母树
 
void update_subTree(int act,int lov,int sub_root,int rt)
{
    int l,r;
    l=tree[rt].subtree[sub_root].l;
    r=tree[rt].subtree[sub_root].r;
    if(l==r){
        tree[rt].subtree[sub_root].val=max(tree[rt].subtree[sub_root].val,lov);
        return ;
    }
    int m=(l+r)>>1;
    if(act<=m) update_subTree(act,lov,sub_root<<1,rt);
    else update_subTree(act,lov,sub_root<<1|1,rt);
    tree[rt].subtree[sub_root].val=max(tree[rt].subtree[sub_root<<1].val,tree[rt].subtree[sub_root<<1|1].val);
}//更新子线段树
 
void update(int act,int lov,int height,int rt)
{
    int l,r;
    l=tree[rt].l;
    r=tree[rt].r;
    update_subTree(act,lov,1,rt);
    if(l==r) return ;
    int m=(l+r)>>1;
    if(height<=m) update(act,lov,height,rt<<1);
    else update(act,lov,height,rt<<1|1);
}//更新母线段数
 
int query_subtree(int x,int y,int sub_root,int rt)
{
    int l,r;
    l=tree[rt].subtree[sub_root].l;
    r=tree[rt].subtree[sub_root].r;
    if(l==x&&r==y){
        return tree[rt].subtree[sub_root].val;
    }
    int m=(l+r)>>1;
    int ret=-1;
    if(x<=m) ret=max(ret,query_subtree(x,min(y,m),sub_root<<1,rt));
    if(y>m) ret=max(ret,query_subtree(max(m+1,x),y,sub_root<<1|1,rt));
    return ret;
}//询问子树
 
int query(int x,int y,int xx,int yy,int rt)
{
    int l,r;
    l=tree[rt].l;
    r=tree[rt].r;
    if(l==x&&r==y){
        return query_subtree(xx,yy,1,rt);
    }
    int m=(l+r)>>1;
    int ret=-1;
    if(x<=m) ret=max(ret,query(x,min(m,y),xx,yy,rt<<1));
    if(y>m) ret=max(ret,query(max(m+1,x),y,xx,yy,rt<<1|1));
    return ret;
}//询问母树
 
int main()
{
    int n;
    char op[5];
    while(scanf("%d",&n),n){
        buildTree(100,200,0,1000,1);
        while(n--){
            scanf("%s",op);
            int height1,height2;
            double act1,act2,lov;
            if(op[0]=='I'){
                scanf("%d%lf%lf",&height1,&act1,&lov);
       //         cout<<(int)(act1*10)<<" "<<(int)(lov*10)<<endl;
                update((int)(act1*10),(int)(lov*10),height1,1);
            }
            else{
                scanf("%d%d%lf%lf",&height1,&height2,&act1,&act2);
                if(height1>height2) swap(height1,height2);
                if(act1>act2) swap(act1,act2);
                double ans=query(height1,height2,(int)(act1*10),(int)(act2*10),1);
                if(ans<0) puts("-1");
                else printf("%.1lf\n",ans/10);
            }
        }
    }
    return 0;
}