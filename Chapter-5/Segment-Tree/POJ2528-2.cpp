/*poj 2528 线段树+离散化*/
//#define LOCAL
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<iostream>
#include<algorithm>

#define MAXN 10000010
#define maxn 10005
using namespace std;

struct node
{
    int st;
    int en;
}ss[maxn];

int lis[maxn<<1];  //离散化素组
int hash[MAXN];  //运用哈希表
int ans;
int vis[maxn];

struct post
{
    int lef,rig;
    int mid(){
      return lef+((rig-lef)>>1);
    }
  int id;  //颜色种类
  int type; //用于延迟
}poster[maxn<<3];

void build_seg(int left,int right,int pos)
{
    poster[pos].lef=left;
    poster[pos].rig=right;
    poster[pos].id=0;
    poster[pos].type=0;
    if(left==right)  return ;
    int mid=poster[pos].mid();
    build_seg(left,mid,pos<<1);
    build_seg(mid+1,right,pos<<1|1);
}

void Update(int left,int right,int pos,int id)
{
    if(poster[pos].lef>=left&&poster[pos].rig<=right)
    {
      poster[pos].id=id;
      poster[pos].type=id;
      return ;
    }
    if(poster[pos].type&&poster[pos].lef!=poster[pos].rig)
    {
      //向下更新一次
      poster[pos<<1].type=poster[pos<<1|1].type=poster[pos].type;
      poster[pos<<1].id=poster[pos<<1|1].id=poster[pos].id;
      poster[pos].type=0;
    }
    int mid=poster[pos].mid();
    if(mid>=left)
        Update(left,right,pos<<1,id);
    if(mid<right)
        Update(left,right,pos<<1|1,id);
     if(poster[pos].lef!=poster[pos].rig)
     {
      if(poster[pos<<1].id==poster[pos<<1|1].id)
          poster[pos].id=poster[pos<<1].id;
      else
         poster[pos].id=0;  //说明有多种可能，需要再向下查询统计
     }
}

void query(int left,int right,int pos)   //进行统计
{
    if(poster[pos].lef<left||poster[pos].rig>right)
         return ;
    if(poster[pos].id)
    {
      if(!vis[poster[pos].id])
      {
       ans++;
       vis[poster[pos].id]=true;
      }
      return;
    }
    if(poster[pos].lef!=poster[pos].rig){
     query(left,right,pos<<1);
     query(left,right,pos<<1|1);
    }
}

int main()
{
 #ifdef LOCAL
   freopen("test.in","r",stdin);
 #endif
  int cas,n;
  scanf("%d",&cas);
  while(cas--)
  {
      scanf("%d",&n);
      int k=0;
      memset(hash,0,sizeof(hash));
    memset(vis,0,sizeof(vis)); //初始化为0表示都没有访问过
      for(int i=0;i<n;i++)
    {
      scanf("%d %d",&ss[i].st,&ss[i].en);
        lis[k++]=ss[i].st;
        lis[k++]=ss[i].en;
    }
    sort(lis,lis+k);  //升序
    int j=0;
    for(int i=0;i<k;i++)
    {
       if(hash[lis[i]]==0)
          hash[lis[i]]=++j; //编号从1起
    }
     build_seg(1,j,1);
    for(int i=0;i<n;i++){
       Update(hash[ss[i].st],hash[ss[i].en],1,i+1);
    }
    ans=0;
    query(1,j,1);
    printf("%d\n",ans);
  }
  return 0;
}
