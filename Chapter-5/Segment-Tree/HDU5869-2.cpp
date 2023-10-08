#include<bits/stdc++.h>
#define LL long long
#define bug puts("**************")
using namespace std;
const int N=110000;
int a[N];
int pre[N*10];
int sum[N];
int gcd(int a,int b){
    return b==0?a:gcd(b,a%b);
}
int n,m;
vector<pair<int,int> > vec1[N],vec2[N];
///vec1[i] i为右边下标 first为左边下标     second 为 [j,i]连续区间元素的gcd
///vec2[i] i为右边下标 first为左边坐标     second为序号（第几个访问的）
 
int lowbit(int x){
    return x&(-x);
}
void add(int x,int d){
    while(x<=n){
        sum[x]+=d;
        x+=lowbit(x);
    }
}
int getsum(int x){
    int ans=0;
    while(x){
        ans+=sum[x];
        x-=lowbit(x);
    }
    return ans;
}
int ans[N];
void solve(){
    memset(sum,0,sizeof(sum));
    memset(pre,0,sizeof(pre));
 
    ///此区间是逐渐增大的，并且是包含关系，所以可以用树状数组
    for(int i=1;i<=n;i++){        ///从小到大 枚举右坐标，
        int len=vec1[i].size();
        for(int j=0;j<len;j++){
            pair<int,int> tmp=vec1[i][j];    ///表示以i结尾的连续序列的gcd
 
            if(pre[tmp.second]) add(pre[tmp.second],-1);   ///去除以前统计过的,去重，(为了统计不同的个数)
            pre[tmp.second]=tmp.first;
            add(tmp.first,1);
        }
 
        len=vec2[i].size();
        for(int j=0;j<len;j++){
            pair<int,int>tmp=vec2[i][j];
 
            ///访问顺序      ///右坐标   左坐标
            ans[tmp.second]=getsum(i)-getsum(tmp.first-1);
        }
    }
    //bug;
    for(int i=1;i<=m;i++){
        printf("%d\n",ans[i]);
    }
}
int main(){
 
    while(~scanf("%d%d",&n,&m)){
        memset(vec1,0,sizeof(vec1));
        memset(vec2,0,sizeof(vec2));
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
        }
 
        for(int i=1;i<=n;i++){
            int pos=i;
            int len=vec1[i-1].size();
            int tmpval=a[i];
            vec1[i].push_back(make_pair(i,a[i]));
            for(int j=0;j<len;j++){
                pair<int,int> tmp=vec1[i-1][j];
                int Gcd=gcd(tmp.second,tmpval);
                pos=tmp.first;
                if(tmpval!=Gcd){
                    vec1[i].push_back(make_pair(pos,Gcd));
                    tmpval=Gcd;
                }
            }
        }
        for(int i=1;i<=m;i++){
            int u,v;
            scanf("%d%d",&u,&v);
            vec2[v].push_back(make_pair(u,i));
        }
//        for(int i=1;i<=n;i++){
//               // cout<<vec1[i].size();
//            for(int j=0;j<vec1[i].size();j++){
//                printf("%d ",vec1[i][j].second);
//            }
//            puts("");
//        }
 
        solve();
    }
    return 0;
}
 