#include <iostream>
#include <algorithm>
#include <map>
#define ll long long //答案是long long
#define N 1000000	 //质数的最大范围
#define M 100010	 //小于10^6的质数个数是78498个，这里开到100010

using namespace std;

map<int, int> mp;					//由于数据范围过大，需要开map，其实也可以用离散化，不过我太蒻了，所以用的map
int p[N + 10], mindiv[N + 10], tot; //线性筛用的，tot为质数个数
int a[N + 10];						//记录转换后的7位数
int c1[N + 10], c2[N + 10];			//树状数组，c1记录数的个数，c2记录质因数个数
int c[M];							//记录每一个数的质因数个数

//----------------------树状数组模板，不细讲了，有两个树状数组，所以要写两遍.
int lowbit(int k){
	return k & (-k);
}

void add1(int x, int y){
	for(int i = x; i <= N; i += lowbit(i)) //没有固定数据范围，所以要到最大值
		c1[i] += y;
}

void add2(int x, int y){
	for(int i = x; i <= N; i += lowbit(i))
		c2[i] += y;
}

ll getsum1(int x){
	ll ans = 0;
	for(int i = x; i > 0; i -= lowbit(i))
		ans += c1[i];
	return ans;
}

ll getsum2(int x){
	ll ans = 0;
	for(int i = x; i > 0; i -= lowbit(i))
		ans += c2[i];
	return ans;
}

//----------------------线性筛模板，也不讲了
void prime(){
	for(int i = 2; i <= N; i++){
		if(!mindiv[i]){
			mindiv[i] = i;
			p[++tot] = i;
		}
		for(int j = 1; j <= tot && p[j] * i <= N && p[j] <= mindiv[i]; j++)
			mindiv[p[j] * i] = p[j];
	}
}

//----------------------计算每一个经过转换后的6位数的质因数个数，至于为什么是6位数，请见代码上方的解释
void devide(int i){
	c[i] = 2;
	int tmp = a[i];
	for(int j = 1; j <= tot && p[j] * p[j] <= tmp; j++) //小优化，如果p[j]*p[j]>tmp,就不会再有tmp的质因数
		while(tmp % p[j] == 0)
			c[i]++, tmp /= p[j];
	if(tmp > 1) c[i]++;
}

//----------------------zh=转换,把每一个质数转换为新的6位数，值存在a数组中
int zh(int x){
	int ans = 0, t = 0;
	while(x)
		t++, ans = ans * 10 + x % 10, x /= 10;
	t = 6 - t;
	while(t)
		ans *= 10, t--;
	return ans;
}

//----------------------预处理
void prework(){
	for(int i = 1; i <= tot; i++) //转换
		a[i] = zh(p[i]);
	sort(a + 1, a + tot + 1);	   //从小到大排序
	for(int i = 1; i <= tot; i++) //存到map中
		mp[a[i]] = i;
	for(int i = 1; i <= tot; i++) //计算每一个转换后的数的质因数个数
		devide(i);
}

int main(){
	prime();
	prework();
	for(int i = 1; i <= tot; i++){ //初始化树状数组
		add1(i, 1);
		add2(i, c[i]);
	}
	char ch[5];
	int x;
	while(scanf("%s%d", ch, &x) != EOF){
		if(ch[0] == 'q'){
			x++;					 //注意，题目中下角标从0开始，这里从1开始算，所以加1
			int l = 1, r = tot, mid; //二分找答案，mid就是答案
			while(l <= r){
				mid = (l + r) >> 1;
				ll tmp = getsum1(mid);
				if(tmp == x) break;
				if(tmp < x) l = mid + 1;
				else r = mid - 1;
			}
			printf("%lld\n", getsum2(mid));
		}else{ //删数时因为转换的是6位数，所以要/10
			add1(mp[x / 10], -1);
			add2(mp[x / 10], -c[mp[x / 10]]);
		}
	}
	return 0;
}
