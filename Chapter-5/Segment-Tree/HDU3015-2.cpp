#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<sstream>
#include<cmath>
#include<stack>
#include<cstdlib>
#include <vector>
#include<queue>
using namespace std;

#define ll long long
#define llu unsigned long long
#define INF 0x3f3f3f3f
#define PI acos(-1.0)
const int maxn =  2e5+5;
const int  mod = 1e9+7;

struct node
{
    ll x,h;
}T[100005];
int n;

bool cmp(node s1,node s2)
{
    return s1.x<s2.x;
}
bool cmp1(node s1,node s2)
{
    return s1.h<s2.h;
}
int lowbit(int x)
{
    return x&(-x);
}
void add(int i,int val,int *s)
{
    while(i<=n)
    {
        s[i] += val;
        i += lowbit(i);
    }
}
int sum(int i,int *s)
{
    int res=0;
    while(i>0)
    {
        res += s[i];
        i -= lowbit(i);
    }
    return res;
}

int main()
{
    while(~scanf("%d",&n))
    {
        int c[100005],c1[100005];
        for (int i = 1; i <= n; i++)
            scanf("%lld %lld", &T[i].x, &T[i].h);
        sort(T + 1, T + n + 1, cmp);
        int xx = T[1].x;
        T[1].x = 1;
        for (int i = 2; i <= n; i++) //将T[i].x按照从小到大排序
        {
            if (T[i].x == xx)
                T[i].x = T[i - 1].x;
            else {
                xx = T[i].x;
                T[i].x = i;
            }
        }
        int xxmaxn = T[n].x;
        sort(T + 1,T + n +1,cmp1);
        xx = T[1].h;
        T[1].h = 1;
        for (int i = 2; i <= n; i++)   //将T[i].h按照从小到大排序
        {
            if (T[i].h == xx)
                T[i].h = T[i - 1].h;
            else {
                xx = T[i].h;
                T[i].h = i;
            }
        }
        ll ans = 0;
        sort(T+1,T+1+n,cmp1);
        memset(c,0,sizeof c);
        memset(c1,0,sizeof c1);
        for(int i=1;i<=n;i++)
        {
            add(T[i].x,T[i].x,c);   // 记录所有比这个数小的和，把每个等级的数放到对应的位置上
            add(T[i].x,1,c1);       //记录所有比这个数小的个数 每个点上记为1
        }
        int xiao,da;                //xiao 表示比对应的数a小，反之亦然
        for(int i = 1;i<n;i++)
        {
            xiao = sum(T[i].x-1,c1) * T[i].x - sum(T[i].x-1,c);     //找出比这个数小的个数*这个数-比这个数小的所有数之和
            da = (sum(xxmaxn,c) - sum(T[i].x,c)) - (sum(xxmaxn,c1) - sum(T[i].x,c1)) * T[i].x;      //找出比这个数大的数和-这个数*比这个数大的个数
            ans += (xiao + da) * T[i].h;
            add(T[i].x,-T[i].x,c);      //把这个用过的数删除
            add(T[i].x,-1,c1);          //把这个数位置上减去1
        }
        printf("%lld\n",ans);
    }

}