#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>
using namespace std;
#define N 100050
int find(int fa[],int x)
{
    if (x==fa[x])return x;
    return fa[x]=find(fa,fa[x]);
}
bool pd()
{
    static int f[N],bl[N];
    set<int>Q;
    memset(f,0,sizeof(f));
    for(int i=1;i<N;i++)bl[i]=i;
    int num=0,x,y,flag=1;
    while(1)
    {
        scanf("%d %d",&x,&y);
        if (x+y==0)break;
        if (x<0)exit(0);
        Q.insert(x);
        Q.insert(y);
        f[y]++;
        int fx=find(bl,x),fy=find(bl,y);
        if  (fx==fy||f[y]>1)flag=0;
        bl[fx]=fy;
    }
    for(auto it=Q.begin();it!=Q.end();it++) if (f[*it]==0)num++;
    if (flag&&num<=1)return 1;
    return 0;
}
void work()
{
    static int cas=0;
    bool k=pd();
    printf("Case %d is ",++cas);
    if (!k)printf("not ");
    printf("a tree.\n");
}
int main()
{
// #ifndef ONLINE_JUDGE
//     freopen("aa.in","r",stdin);
// #endif
    while(1)work();
}
