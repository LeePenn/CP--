#include<iostream>
#include<string.h>
#include<string>
#include<algorithm>
#include<math.h>
#include<string>
#include<string.h>
#include<vector>
#include<utility>
#include<map>
#include<queue>
#include<set>
#define mx 0x3f3f3f3f
#define ll long long
#define MAXN 100
using namespace std;
int tree[10005],a[10005];
int tree1[10005];

void insert()//二叉树建树
{
    memset(tree,-1,sizeof(tree));
    for(int i=0;a[i];i++)
    {
        int num=a[i]-'0';
        int j=1;
        while(tree[j]!=-1)
        {
            if(num>tree[j])
                j=j*2;
            else
                j=j*2+1;
        }
        tree[j]=num;
    }

}
int main()
{
    int n;
    while(cin>>n){
    if(n==0)
        break;
    string s;
    cin>>s;
    memset(tree,-1,sizeof(tree));
    for(int i=0;s[i];i++)
    {
        int num=s[i]-'0';
        int j=1;
        while(tree[j]!=-1)
        {
            if(num<tree[j])
                j=j*2;
            else
                j=j*2+1;
        }
        tree[j]=num;
    }
    
    while(n--)
    {
        string ss;
        cin>>ss;
        memset(tree1,-1,sizeof(tree1));
        for(int i=0;ss[i];i++)
        {
            int num=ss[i]-'0';
            int j=1;
            while(tree1[j]!=-1)
            {
                if(num<tree1[j])
                    j=j*2;
                else
                    j=j*2+1;
            }
            tree1[j]=num;
        }
        int i;
        for(i=1;i<=1024&&tree[i]==tree1[i];i++);
        if(i>1024)
            cout<<"YES"<<endl;
        else
            cout<<"NO"<<endl;
        
    }
}
    return 0;

}