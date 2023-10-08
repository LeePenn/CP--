#include<iostream>
#include<stdio.h>
#include<cstring> 
#include<algorithm>
using namespace std;

struct sen{
	int s,e,num;
}a[100001] = {};

bool cmp(sen x,sen y)
{
	if (x.s != y.s) return x.s<y.s;
	else return x.e>y.e;
}

int lowbit(int x)
{
	return x&-x;
}

int main()
{
	int n;
	while(scanf("%d",&n) && n != 0)
	{
		sen a[100001] = {};
		int c[100001] = {},d[100001] = {};
		int maxn = 0;
		for (int i = 1;i<=n;i++)
		{
			scanf("%d%d",&a[i].s,&a[i].e);
			a[i].num = i;
			maxn = max(maxn,a[i].e);
		}
		sort(a+1,a+n+1,cmp);
		for (int i = 1;i<=n;i++)
		{
			if (a[i].s == a[i-1].s && a[i].e == a[i-1].e) c[a[i].num] = c[a[i-1].num];//如果两条线段相同，则包含数一样 
			else//计算包含多少个 
			{
				int x = maxn,sum = 0;
				while (x > 0)
				{
					sum+=d[x];
					x -= lowbit(x);
				}
				x = a[i].e - 1;
				while (x>0)
				{
					sum-=d[x];
					x-= lowbit(x);
				}
				c[a[i].num] = sum;
			}
			int x = a[i].e;//更新 
			while (x <= maxn)
			{
				d[x]++;
				x  += lowbit(x);
			}
		}
		printf("%d",c[1]);
		for (int i = 2;i<=n;i++) printf(" %d",c[i]); 
		printf("\n");
	}	
} 
