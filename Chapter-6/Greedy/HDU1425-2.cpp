#include <cstdio>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
using namespace std;
 
int partition(int *arr, int low, int up)
{
	for (int i = low; i < up; i++)
		if (arr[i] >= arr[up]) swap(arr[low++], arr[i]);
 
	swap(arr[low], arr[up]);
	return low;
}
 
//K作为绝对下标位置处理
void randSelectK(int *arr, int low, int up, int K)
{
	int r = low + rand() % (up - low + 1);
	swap(arr[r], arr[up]);
 
	int idx = partition(arr, low, up);
	if (idx > K) randSelectK(arr, low, idx-1, K);
	else if (idx < K) randSelectK(arr, idx+1, up, K);
}
 
void randQuickSort(int *arr, int low, int up)
{
	if (low >= up) return ;//不能是low == up
 
	int r = low + rand() % (up - low + 1);
	swap(arr[r], arr[up]);
 
	int mid = partition(arr, low, up);
	randQuickSort(arr, low, mid-1);
	randQuickSort(arr, mid+1, up);
}
 
const int SIZE = 1000000;
int arr[SIZE];	
int main()
{
	int n, m;
	srand(unsigned(time(NULL)));
	while(~scanf("%d %d", &n, &m))
	{
		for (int i = 0; i < n; i++)
			scanf("%d", &arr[i]);
 
		randSelectK(arr, 0, n-1, m-1);
		randQuickSort(arr, 0, m-1);
		for (int i = 0; i < m-1; i++)
		{
			printf("%d ", arr[i]);
		}
		printf("%d\n", arr[m-1]);
	}
	return 0;
}