/*
正方型的田，若相邻的田水管接口可以相连，则他们之间联通。
统计联通子图的个数。
*/
#include<iostream>
#include<stdio.h>
using namespace std;
#define N 55

int map[55][55];
int dir[4][2]={0,-1,-1,0,0,1,1,0};
int n,m,f[N*N];

int farm[11][4]={
    {1,0,0,1},
    {1,1,0,0},
    {0,0,1,1},
    {0,1,1,0},
    {1,0,1,0},
    {0,1,0,1},
    {1,1,0,1},
    {1,0,1,1},
    {0,1,1,1},
    {1,1,1,0},
    {1,1,1,1}
};


int find(int x)
{
    return f[x]!=x?f[x]=find(f[x]):f[x];
}

void merge(int x,int y)
{
    int a=find(x),b=find(y);
    if(a==b) return;
    if(a<b) f[a]=b;
        else f[b]=a;
}

int main()
{
    int i,j,k,dx,dy;
    char str[51];
    
//  freopen("test.txt","r",stdin);
    while(scanf("%d%d",&n,&m)) 
    {
        if(n==-1&&m==-1)
            break;
        
        for(i=0;i<n;i++)
        {
            scanf("%s",str);
            for(j=0;j<m;j++)
                map[i][j]=str[j]-'A';   
        }
        for(i=0;i<N*N;i++)
            f[i]=i;
            
        for(i=0;i<n;i++)
        {
            for(j=0;j<m;j++)
            {
                for(k=0;k<4;k++)
                {
                    dx=i+dir[k][0];
                    dy=j+dir[k][1];
                    if(dx<0||dx>=n||dy<0||dy>=m) 
                        continue;
                    
                    if(k==0)//左边连起来 
                    {
                        if(farm[map[dx][dy]][1]&&farm[map[i][j]][3])
                            merge(dx*m+dy,i*m+j);
                    }
                    else if(k==1)//上边连起来 
                    {
                        if(farm[map[dx][dy]][2]&&farm[map[i][j]][0])
                            merge(dx*m+dy,i*m+j);
                    }
                    else if(k==2)//右边连起来 
                    {
                        if(farm[map[dx][dy]][3]&&farm[map[i][j]][1])
                            merge(dx*m+dy,i*m+j);
                    }
                    else if(k==3)//下边连起来 
                    {
                        if(farm[map[dx][dy]][0]&&farm[map[i][j]][2])
                            merge(dx*m+dy,i*m+j);
                    }
                }
            }
        }
        int cnt=0;
        for(i=0;i<n*m;i++)
            if(f[i]==i)
                ++cnt;
        printf("%d\n",cnt);
    }
    return 0;
}