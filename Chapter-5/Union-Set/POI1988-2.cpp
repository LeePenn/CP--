#include<cstdio>
#include<cstring>
#include<algorithm>
#define MAXN 30005
using namespace std;

int u[MAXN], under[MAXN], sum[MAXN];

int find(int x){      
    if(x == u[x])
        return x;
    int a = find(u[x]);
    under[x]+=under[u[x]];    //在压缩路径的时候，要动态更新under数组的值
    u[x] = a;
    return u[x];
}

void un(int a, int b){     //把a所在的堆的所有放在b堆之上
    a = find(a); 
    b = find(b);
    if(a == b)  
        return;
    u[a] = b;
    under[a] = sum[b];     //*a放在了b之上，当然a的下面有sum[b]个
    sum[b]+=sum[a];        //*摞上去之后，b堆总数要加a堆总数
}

int main()
{
    int n;
    while(scanf("%d", &n)!=EOF){
        getchar();
        for(int i = 0; i < MAXN; i++){
            u[i] = i;
            under[i] = 0;
            sum[i] = 1;
        }

        int a, b;
        char c;
        for(int i = 0; i < n; i++){
            c = getchar();
            if(c == 'M'){
                scanf("%d %d", &a, &b);
                getchar();
                un(a, b);
            }
            else if(c == 'C'){
                scanf("%d", &a);
                getchar();
                find(a);                //这一句一定不能少，最后输出的时候更新下under数组
                printf("%d\n", under[a]);
            }
        }
    }
    return 0;
}