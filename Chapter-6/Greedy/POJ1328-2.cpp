#include<cstdio>
#include<iostream>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
#define eps 1e-8
const int num=1005;

int n,d,vis[num],ans;
struct node{
    int x,y;
}island[num];
struct task{
    double s,t;
}radar[num];
bool cmp(task x,task y){
    return eps<y.t-x.t;
}

int main()
{
    int x,y,cas=1,maxy;
    double xx,yy;
    while(~scanf("%d%d",&n,&d)&&n&&d)
    {
        memset(vis,0,sizeof(vis));
        maxy=0;
        ans=0;
        for(int i=0;i<n;i++)
        {
            scanf("%d%d",&x,&y);
            island[i].x=x;
            island[i].y=y;
            if(y>maxy)  maxy=y;
        }
        printf("Case %d: ",cas++);
        if(maxy>d){
            printf("-1\n");
            continue;
        }
        for(int i=0;i<n;i++){
            xx=island[i].x-sqrt(d*d*1.0-island[i].y*island[i].y);
            yy=island[i].x+sqrt(d*d*1.0-island[i].y*island[i].y);
            radar[i].s=xx;
            radar[i].t=yy;
        }
        sort(radar,radar+n,cmp);
        for(int i=0;i<n;i++){
            if(!vis[i]){
                vis[i]=1;
                //cout<<i<<"%%%"<<endl;
                ans++;
                for(int j=0;j<n;j++){
                    if(radar[j].s<radar[i].t+eps&&!vis[j]){
                        vis[j]=1;
                    }
                }
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}