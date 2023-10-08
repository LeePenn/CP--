#include <iostream>
#include <cstdio>
using namespace std;
 
#define ll long long int
const int maxn = 1000011;
int N , P , K , mod[maxn] , C[maxn];
ll W[maxn] , ans;
 
int lowbit(int x){
    return x&(x^(x-1));
}
 
void build(){
    for(int i = 1; i <= P; i++){
        C[i] = min(C[i] , mod[i]);
        if(lowbit(i) <= P && lowbit(i) < maxn) C[lowbit(i)] = min(C[lowbit(i)] , C[i]);
    }
}
 
int querry(int l , int r){
    int t = mod[r];
    while(true){
        t = min(t , mod[r]);
        if(l==r) break;
        for(r=r-1; r-l >= lowbit(r); r -= lowbit(r)){
            t = min(t , C[r]);
        }
    }
    return t;
}
 
void initial(){
    for(int i = 0; i < maxn; i++){
        W[i] = 0;
        mod[i] = maxn*2;
        C[i] = 2*maxn;
    }
    ans = -1;
}
 
void readcase(){
    W[0] = 0;
    scanf("%d%d%d" , &N , &P , &K);
    for(int i = 1; i <= N; i++){
        scanf("%lld" , &W[i]);
    }
}
 
void computing(){
    mod[W[0]%P+1] = 0;
    for(int i = 1; i <= N; i++){
        W[i] += W[i-1];
        mod[W[i]%P+1] = min(mod[W[i]%P+1] , i);
    }
    build();
    for(int i = 1; i <= N; i++){
        int y = max(W[i]%P-K , (ll)0);
        int index = querry(y+1 , W[i]%P+1);
        if(index < i){
            ans = max(ans , (W[i]-W[index])/P);
        }
        y = min((ll)P , max(W[i]%P , W[i]%P+P-K));
        index = querry(y+1 , P+1);
        if(index < i){
            ans = max(ans , (W[i]-W[index])/P);
        }
        if(i == 0 && W[0]%P <= K || (i > 0 && (W[i]-W[i-1])%P <= K)) ans = max(ans , (ll)0);
    }
    printf("%lld\n" , ans);
}
 
int main(){
    int T;
    cin >> T;
    for(int i = 1; i <= T; i++){
        initial();
        readcase();
        printf("Case %d: " , i);
        computing();
    }
    return 0;
}