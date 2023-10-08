
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define maxn 40047
#define maxm 247
 
struct node
{
    int to,w,next;
} edge[maxn*2];
 
int n, m;		//点数，询问次数
int head[maxn];
int k;
int fa[maxn];		//父亲结点
int dis[maxn];		//到根节点距离
int vis[maxn];		//是否访问过
int s[maxm];		//询问起点
int e[maxm];		//询问终点
int lca[maxm];		//LCA(s,e) 最近公共祖先
 
int find(int x)
{
    if(fa[x]!=x) return fa[x]=find(fa[x]);
    return fa[x];
}
 
void init()
{
    k = 1;
    memset(head,0,sizeof(head));
    memset(dis,0,sizeof(dis));
    memset(vis,0,sizeof(vis));
}
 
void add(int u,int v,int w)
{
    edge[k].to = v;
    edge[k].w = w;
    edge[k].next = head[u];
    head[u] = k++;
}
 
void tarjan(int u)
{
    int i,v;
    fa[u] = u;
    vis[u] = 1;
    for(i = 0; i < m; i++)
    {
        if(e[i]==u && vis[s[i]])
            lca[i] = find(s[i]);	//若询问的两点中有一点已被访问过，则两点的LCA则为这一点的当前父节点
        if(s[i]==u && vis[e[i]])
            lca[i] = find(e[i]);
    }
    for(i = head[u]; i; i = edge[i].next)
    {
        v = edge[i].to;
        if(!vis[v]) //若没被访问过
        {
            dis[v] = dis[u]+edge[i].w;//更新距离
            tarjan(v);
            fa[v] = u;//回溯更新父节点
        }
    }
}
 
int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        init();
        scanf("%d%d",&n,&m);
        int u, v, w;
        for(int i = 0; i < n-1; i++)
        {
            scanf("%d%d%d",&u,&v,&w);
            add(u,v,w);
            add(v,u,w);
        }
        for(int i = 0; i < m; i++)
        {
            scanf("%d%d",&s[i],&e[i]);
        }
        tarjan(1);
 
        for(int i = 0; i < m; i++)
        {
            printf("%d\n",dis[s[i]]+dis[e[i]]-2*dis[lca[i]]);//两点距离为根节点到两点距离之和-根节点到LCA距离*2
        }
    }
    return 0;
}