#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <vector>
using namespace std;
#define MAXN 200010
 
int ny[MAXN];
int sl[MAXN], sr[MAXN];
int n, stan, st, tot;
vector<int> ollie;
 
inline int lowbit(int x)
{
    return x & -x;
}
 
int sum(int s[], int i)
{
    int ret = 0;
    while(i > 0)
    {
        ret += s[i];
        i -= lowbit(i);
    }
    return ret;
}
 
void add(int s[], int i, int val)
{
    while(i <= n)
    {
        s[i] += val;
        i += lowbit(i);
    }
}
 
struct Point
{
    int x, y;
    bool operator <(const Point &argu) const
    {
        return x < argu.x;
    }
}pp[MAXN];
 
int main()
{
//    freopen("C.in", "r", stdin);
 
    while(scanf("%d", &n) && n)
    {
        for(int i = 0; i < n; i++) scanf("%d%d", &pp[i].x, &pp[i].y), ny[i] = pp[i].y;
        sort(ny, ny + n);
 
        int cnty = 0;
        for(int i = 0; i < n; i++) if(ny[cnty] != ny[i]) ny[++cnty] = ny[i]; cnty++;
        for(int i = 0; i < n; i++) pp[i].y = lower_bound(ny, ny + cnty, pp[i].y) - ny + 1;
 
        sort(pp, pp + n); pp[n].x = pp[n - 1].x + 1;
 
        memset(sr, 0, sizeof(sr));
        memset(sl, 0, sizeof(sl));
        for(int i = 0; i < n; i++) add(sr, pp[i].y, 1);
 
        stan = -1, st = 0;
        for(int i = 0; i < n; i++)
        {
            if(pp[i].x != pp[i + 1].x)
            {
                for(int j = st; j <= i; j++) add(sr, pp[j].y, -1);
                int tmps = -1, tmpo = -1;
                for(int j = st; j <= i; j++)
                {
                    int a = sum(sr, cnty) - sum(sr, pp[j].y) + sum(sl, pp[j].y - 1);
                    int b = sum(sl, cnty) - sum(sl, pp[j].y) + sum(sr, pp[j].y - 1);
                    if(b == tmpo) tmps = min(tmps, a);
                    if(b >  tmpo) tmps = a, tmpo = b;
                }
                if(tmps >  stan) stan = tmps, ollie.clear();
                if(tmps == stan) ollie.push_back(tmpo);
                for(int j = st; j <= i; j++) add(sl, pp[j].y, 1);
                st = i + 1;
            }
        }
        sort(ollie.begin(), ollie.end());
        tot = unique(ollie.begin(), ollie.end()) - ollie.begin();
        printf("Stan: %d; Ollie:", stan);
        for(int i = 0; i < tot; i++) printf(" %d", ollie[i]);
        puts(";");
    }
    return 0;
}