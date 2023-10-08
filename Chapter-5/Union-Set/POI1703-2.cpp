#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
using namespace std;
const int maxx=100000+50;
int fa[maxx],cun[maxx];
int n,m;
 
int findnum(int x)
{
    if(x==fa[x])return x;
    else{
        int root=findnum(fa[x]);
        cun[x]=(cun[x]+cun[fa[x]])%2;
        return fa[x]=root;
    }
}
 
void init(){
for(int i=0;i<=n;i++)fa[i]=i;
memset(cun,0,sizeof(cun));
}
 
/*
其实总的来说就是食物链的简化版本，把食物链中的三种关系简化成了两种关系。
做法是一样的，用0来表示同一帮派，1来表示不同帮派。那么如果字母是d，
那么连接两个根节点就可以用（(cun[a]+cun[b]+1)%2），cun数组存的是节点和其父亲节点的关系。
这题最坑的就是，不能用cin，（可以试一试）对于cin党的我来说，一直找优化算法。。。
并且 ios_base::sync_with_stdio(false);并没有起到什么作用。。。。最终抱着试一试的心态改了scanf，结果就不T了。
*/ 
int main(){
int t,a,b;char c[2];
scanf("%d",&t);
while(t--)
{
scanf("%d%d",&n,&m);
  init();
  while(m--)
    {
        scanf("%s%d%d",c,&a,&b);
            int a1=findnum(a);
            int b1=findnum(b);
        if(c[0]=='D')
        {//he
            fa[b1]=a1;
            cun[b1]=(cun[a]+cun[b]+1)%2;
        }
        else {
        if(a1!=b1)cout<<"Not sure yet."<<endl;//检查各自父节点，如果两个的根节点相同，那么就表示他们之间有关系，如果不相同忙就表示没有
        else {
            if((cun[a]+cun[b])%2==0)cout<<"In the same gang."<<endl;//如果两个之间有关系了，那么通过各自和根节点之间的关系可以判断是否在同一帮派
            else cout<<"In different gangs."<<endl;
        }
        }
    }
}
return 0;}