#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
 
 
using namespace std;
struct iterm
{
    int s;
    int e;
}a[110];
bool cmp(iterm x, iterm y)
{
    return x.e < y.e;
}
int main()
{
    int n;
    while(scanf("%d", &n) != EOF)
    {
        if(n == 0)
            break;
        memset(a,-1,sizeof(a));
        for(int i = 1; i <= n; i ++)
            scanf("%d %d", &a[i].s, &a[i].e);
            sort(a + 1, a + n + 1,cmp);
            int cnt = 0;
            int t = 0;
            for(int i = 1; i <= n; i ++)
            {
                if(t <= a[i].s)
                    {
                        cnt ++;
                        t = a[i].e;
                    }
            }
            printf("%d\n", cnt);
    }
    return 0;
}