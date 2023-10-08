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
 struct Node
 {
     int x,pos;
 };
 
 const int MAX=1000005;
 Node a[MAX],Q[MAX];
 int head,tail,n,P,K,pos[MAX],C,num=0;
 __int64 sum[MAX];
 
 int cmp(Node a,Node b)
 {
     if(a.x!=b.x) return a.x<b.x;
     return a.pos<b.pos;
 }
 
 void deal()
 {
     __int64 ans=-1;
     int i,t;
 
     head=tail=0;
     for(i=1;i<=n;i++)
     {
         while(head<tail&&a[i].pos<Q[tail-1].pos) tail--;
         Q[tail++]=a[i];
         while(head<tail&&a[i].x-Q[head].x>K) head++;
         t=a[i].pos;
         if(sum[t]%P<=K) ans=max(ans,sum[t]/P);
         if(head<tail&&Q[head].pos<t)
         {
             ans=max(ans,(sum[t]-sum[Q[head].pos])/P);
         }
     }
     printf("Case %d: %I64d\n",++num,ans);
 }
 
 int main()
 {
     for(scanf("%d",&C);C--;)
     {
         scanf("%d%d%d",&n,&P,&K);
         sum[0]=0;
         int i;
         for(i=1;i<=n;i++)
         {
             scanf("%I64d",&sum[i]);
             sum[i]+=sum[i-1];
             a[i].pos=i;
             a[i].x=sum[i]%P;
         }
         sort(a+1,a+n+1,cmp);
         deal();
     }
     return 0;
 }