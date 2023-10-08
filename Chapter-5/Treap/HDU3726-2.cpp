//#include <bits/stdc++.h>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>

using namespace std;

#define LL long long 
#define pii pair<int, int>
#define MP make_pair
#define ls i << 1
#define rs ls | 1
#define md (ll + rr >> 1)
#define lson ll, md, ls
#define rson md + 1, rr, rs
#define inf 0x3f3f3f3f
#define N 3000010
#define M 100010

int ch[N][2];
int rand_val[N], key[N], sz[N], cnt[N], tot;

int creat(int val){
    ++tot;
    ch[tot][0] = ch[tot][1] = 0;
    key[tot] = val;
    rand_val[tot] = rand();
    sz[tot] = cnt[tot] = 1;
    return tot;
}
int cmp(int x, int val){
    if(key[x] == val) return -1;
    return key[x] < val ? 1 : 0;
}
void push_up(int x){
    sz[x] = cnt[x] + sz[ch[x][0]] + sz[ch[x][1]];
}
void rot(int &x, int d){
    int k = ch[x][d^1];
    ch[x][d^1] = ch[k][d];
    ch[k][d] = x;
    push_up(x);
    push_up(k);
    x = k;
}
void insert(int &x, int val){
    if(x == 0){
        x = creat(val);
        return ;
    }
    int d = cmp(x, val);
    if(d == -1){
        sz[x]++, cnt[x]++;
        return ;
    }
    insert(ch[x][d], val);
    if(rand_val[ch[x][d]] > rand_val[x]) rot(x, d ^ 1);
    push_up(x);
}
void dele(int &x, int val){
    if(x == 0) return ;
    int d = cmp(x, val);
    if(d == -1){
        if(cnt[x] > 1){
            cnt[x]--, sz[x]--;
            return ;
        }
        if(!ch[x][0]) x = ch[x][1];
        else if(!ch[x][1]) x = ch[x][0];
        else{
            int d2 = rand_val[ch[x][0]] > rand_val[ch[x][1]] ? 1 : 0;
            rot(x, d2);
            dele(ch[x][d2], val);
        }
    }
    else dele(ch[x][d], val);
    if(x) push_up(x);
}
int kth(int x, int k){
    if(!x) return -inf;
    int tmp = sz[ch[x][1]];
    if(k <= tmp) return kth(ch[x][1], k);
    k -= tmp;
    if(k <= cnt[x]) return key[x];
    return kth(ch[x][0], k - cnt[x]);
}

struct edge{
    int u, v;
    void input(){
        scanf("%d%d", &u, &v);
    }
};
struct oper{
    char s[3];
    int u, k;
    oper(){
        u = -1, k = -1;
    }
};

edge E[M];
oper Q[M*5];
int val[M], fa[M], rt[M];
bool del[M];
void unin(int a1, int a2){
    if(sz[rt[a1]] < sz[rt[a2]]) swap(a1, a2);
    while(1){
        int tmp = kth(rt[a2], 1);
        if(tmp == -inf) break;  
        insert(rt[a1], tmp);
        dele(rt[a2], tmp);
    }
    fa[a2] = a1;
    rt[a2] = 0;
}


int find(int x){
    if(fa[x] != x) fa[x] = find(fa[x]);
    return fa[x];
}
int main(){
    int n, m, cas = 0;
    while(scanf("%d%d", &n, &m) != EOF && (n || m)){
        memset(del, 0, sizeof del);
        for(int i = 1; i <= n; ++i)
            scanf("%d", &val[i]);
        for(int i = 1; i <= m; ++i)
            E[i].input();
        int q = 0;
        while(1){
            scanf("%s", Q[q].s);
            if(Q[q].s[0] == 'E') break;
            if(Q[q].s[0] == 'D'){
                scanf("%d", &Q[q].u);
                del[Q[q].u] = 1;
            }
            else{
                scanf("%d%d", &Q[q].u, &Q[q].k);
                if(Q[q].s[0] == 'C'){
                    int tmp = val[Q[q].u];
                    val[Q[q].u] = Q[q].k, Q[q].k = tmp;
                }
            }
            q++;
        }
        tot = 0;
        memset(rt, 0, sizeof rt);
        for(int i = 1; i <= n; ++i) fa[i] = i, insert(rt[i], val[i]);
        for(int i = 1; i <= m; ++i){
            if(!del[i]){
                int u = E[i].u, v = E[i].v;
                if(find(u) == find(v)) continue;
                unin(find(u), find(v));
            }
        }
        LL ans = 0;
        int tim = 0;
        for(int i = q - 1; i >= 0; --i){
            if(Q[i].s[0] == 'Q'){
                int v = find(Q[i].u);
                int ret = kth(rt[v], Q[i].k);
                if(ret != -inf)
                    ans += ret;
                tim++;
            }
            else if(Q[i].s[0] == 'C'){
                int v = find(Q[i].u);
                dele(rt[v], val[Q[i].u]);
                insert(rt[v], Q[i].k);
                val[Q[i].u] = Q[i].k;
            }
            else{
                int k = Q[i].u;
                int u = E[k].u, v = E[k].v;
                if(find(u) == find(v)) continue;
                unin(find(u), find(v));
            }
        }
        printf("Case %d: %.6f\n", ++cas, ans * 1.0 / tim);
    }

    return 0;
}