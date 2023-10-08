//HDU 3092
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;
int N,M,prime[3010],cnt=0;//cnt标记1...3000的素数个数；prime[]存素数
bool isprime[3010];//标记是否为素数的数组
double dp[3010];//取对数之后的结果
int ans[3010];//存求模后的结果
void init()//优化后的线性素数筛，查找并存储3000以内的素数
{
    memset(isprime,1,sizeof(isprime));//初始默认所有的数都是素数
    isprime[0]=isprime[1]=0;//0和1不是素数
    for(int i=2;i<=3000;i++)//对查找2...3000之间的素数
    {
        if(isprime[i])
            prime[cnt++]=i;//保存素数
        for(int j=0;j<cnt&&prime[j]*i<=3000;j++)//j为素数数组中的下标，遍历0...cnt；i为素数要乘的倍数
            isprime[prime[j]*i]=0;//筛掉小于等于i的素数和由i的乘积构成的素数
    }
}
int main()
{
    init();//得到素数数组
    while(~scanf("%d%d",&N,&M))
    {
        memset(dp,0,sizeof(dp));//数组初始化
        for(int i=0;i<=N;i++)
            ans[i]=1;//数组初始化
        for(int i=0;i<cnt&&prime[i]<=N;i++)//在素数数组中开始遍历查找，且不能超过N
        {
            double tmp=log(prime[i]*1.0);//log的参数是double类型，暂存素数取对数后的结果值
            for(int j=N;j>=prime[i];j--)//因为要找最大的最小公倍数，所以质数从大的开始找
                for(int q=1,p=prime[i];p<=j;p*=prime[i],q++)//q记录素数prime[i]被选取的次数，即p中prime[i]的幂的次数，便于对dp数组更新的操作
                    if(dp[j]<dp[j-p]+q*tmp)
                    {
                        dp[j]=dp[j-p]+q*tmp;
                        ans[j]=(ans[j-p]*p)%M;
                    }
        }
        printf("%d\n",ans[N]);
    }
    return 0;
}