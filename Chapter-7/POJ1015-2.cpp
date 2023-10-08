#include<cstring>
#include<algorithm>
#include<queue>
#include<iostream>
#include<cstdio>
#define MAXN 100010
using namespace std;

int dp[21][810];
int n, m;
int d[210], j[210], v[210], s[210];
int path[21][810];
int id[21];

//判断i是否在A[j,k]的方案中

int find(int j, int x, int i){
    while(j > 0 && path[j][x] != i){
        x -= v[path[j][x]];
        j--;
    }
    return j ? 0 : 1;
}

int main(){
    int t = 1;
    while(scanf("%d %d", &n, &m) && (n != 0 && m != 0)){
        memset(dp, -1, sizeof(dp));
        memset(d, 0, sizeof(d));
        memset(j, 0, sizeof(j));
        memset(v, 0, sizeof(v));
        memset(s, 0, sizeof(s));
        memset(path, 0, sizeof(path));
        for (int i = 1;i <= n;i++){
            scanf("%d %d", &d[i], &j[i]);
            v[i] = d[i] - j[i];
            s[i] = d[i] + j[i];
        }
        int fix = m * 20;
        dp[0][fix] = 0;//平移解空间[-400,400]到[0,800]
        for (int j = 1;j <= m;j++){
            for (int x = 0;x <= 2*fix;x++){
                if (dp[j-1][x] >= 0){//DP需要用到的子问题的解
                    for(int k = 1;k <= n;k++){
                        if ((x + v[k] <= 2*fix) && (dp[j][x+v[k]] < dp[j-1][x] + s[k]) && find(j-1, x, k) == 1){
                            dp[j][x+v[k]] = dp[j-1][x] + s[k];
                            path[j][x+v[k]] = k;
                        }
                    }
                }
            }
        }
        int sumD = 0, sumJ = 0, dd = 0;
        for (int i = 0;i <= fix;i++) {
            if (dp[m][fix-i] >= 0 || dp[m][fix+i] >= 0){
                dd = i;
                break;
            }
        }

//公式求解
        int sum = dp[m][fix-dd] > dp[m][fix+dd] ? (fix-dd) : (fix+dd);
        sumD = (dp[m][sum] + sum - fix) / 2;
        sumJ = (dp[m][sum] - sum + fix) / 2;
        
        printf("Jury #%d\n", t++);
        printf("Best jury has value %d for prosecution and value %d for defence:\n", sumD, sumJ);
        for (int i = 0, j=m, k=sum;i<m;i++){
            id[i] = path[j][k];
            k -= v[id[i]];
            j--;
        }

//升序打印
        sort(id, id+m);
        for (int i = 0;i < m;i++){
            printf(" %d", id[i]);
        }
        printf("\n\n");
    }
    return 0;
}