//1255
#include <cstdio>
#include <algorithm>
using namespace std;

const int N=1010*2;
struct segment
{
    double x1,x2,h;
    int v;
    segment(){}
    segment(double t1,double t2,double th,double tv):
        x1(t1),x2(t2),h(th),v(tv){}
    bool operator < (const segment& t)const
    {
        return h<t.h;
    }
}seg[N];
struct segtree
{
    int l,r,c;
    double s1,s2;
    int m() {return (l+r)>>1;}
}st[N*4];
double val[N*2];
int bfind(double x,int l,int r)
{
    while(l<r)
    {
        int m=(l+r)>>1;
        if(x==val[m]) return m;
        else if(x<val[m]) r=m;
        else l=m+1;
    }
    return l;
}
void build(int l,int r,int rt)
{
    st[rt].l=l; st[rt].r=r;
    st[rt].s1=st[rt].s2=st[rt].c=0;
    if(l==r) return;
    int m=st[rt].m();
    build(l,m,rt*2);
    build(m+1,r,rt*2+1);
}
void pushup(int rt)
{
    int l=st[rt].l, r=st[rt].r;
    if(st[rt].c>1)
    {
        st[rt].s2=val[r]-val[l-1];
        st[rt].s1=0;
    }
    else if(st[rt].c==1)
    {
        if(l==r) st[rt].s2=0;
        else st[rt].s2=st[rt*2].s1+st[rt*2].s2+st[rt*2+1].s1+st[rt*2+1].s2;
        st[rt].s1=val[r]-val[l-1]-st[rt].s2;
    }
    else
    {
        if(l==r) st[rt].s2=st[rt].s1=0;
        else
        {
            st[rt].s1=st[rt*2].s1+st[rt*2+1].s1;
            st[rt].s2=st[rt*2].s2+st[rt*2+1].s2;
        }
    }
}
void update(int a,int b,int x,int rt)
{
    int l=st[rt].l, r=st[rt].r;
    if(a<=l && r<=b)
    {
        st[rt].c+=x;
        pushup(rt);
        return;
    }
    int m=st[rt].m();
    if(a<=m) update(a,b,x,rt*2);
    if(b>m) update(a,b,x,rt*2+1);
    pushup(rt);
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int n;
        scanf("%d",&n);
        int nx=0,ny=0;
        for(int i=1;i<=n;i++)
        {
            double x1,x2,y1,y2;
            scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
            val[nx++]=x1; val[nx++]=x2;
            seg[ny++]=segment(x1,x2,y1,1);
            seg[ny++]=segment(x1,x2,y2,-1);
        }
        sort(seg,seg+ny);
        sort(val,val+nx);
        int m=1;
        for(int i=1;i<nx;i++)
            if(val[i]!=val[i-1]) val[m++]=val[i];
        m--;
        double ans=0;
        build(1,m,1);
        for(int i=0;i<ny;i++)
        {
            int x1=bfind(seg[i].x1,0,m)+1;
            int x2=bfind(seg[i].x2,0,m);
            update(x1,x2,seg[i].v,1);
            ans+=(seg[i+1].h-seg[i].h)*st[1].s2;
        }
        printf("%.2lf\n",ans);
    }
    return 0;
}
