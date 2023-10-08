#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstdio>
using namespace std;
const int MAXN = 10010;
int data[MAXN];
int partition(int left,int right)
{
	int i=left;
	int temp=data[right];//把尾部的数看成基准数
	for(int j=left;j<right;j++){
		if(data[j]<temp){
			swap(data[j],data[i]);
			i++;
		}
	}
	swap(data[i],data[right]);
	return i;//返回基准数的位置
}
void quicksort(int left,int right)
{
	if(left<right){
		int i=partition(left,right);//划分
		quicksort(left,i-1);//分治，i左边的继续递归划分
		quicksort(i+1,right);//分治，i右边的继续递归划分
	}
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&data[i]);
	quicksort(1,n);
	printf("%d\n",data[(n+1)/2]);
	return 0;
}
