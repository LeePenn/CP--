#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
//对区间操作
#define Key_value ch[ch[root][1]][0]
using namespace std;
const int maxn = 4e5 + 10;
int root, tot1;
int ch[maxn][2], pre[maxn], key[maxn], size[maxn], add[maxn], rev[maxn];
int s[maxn], tot2;
int n, q, k1, k2, pos, a[maxn];
void Update_Add(int r, int v)
{
    if(!r) return;
    key[r] += v;
    add[r] += v;
}
void Update_Rev(int r)
{
    if(!r) return;
    swap(ch[r][0], ch[r][1]);
    rev[r] ^= 1;
}
void PushUp(int r)
{
    size[r] = size[ch[r][0]] + size[ch[r][1]] + 1;
}
void PushDown(int r)
{
    if(add[r])
    {
        Update_Add(ch[r][0], add[r]);
        Update_Add(ch[r][1], add[r]);
        add[r] = 0;
    }
    if(rev[r])
    {
        Update_Rev(ch[r][0]);
        Update_Rev(ch[r][1]);
        rev[r] = 0;
    }
}
void NewNode(int &r, int fa, int v)
{
    if(tot2) r = s[tot2--];
    else r = ++tot1;
    ch[r][0] = ch[r][1] = add[r] = 0;
    size[r] = 1;
    pre[r] = fa;
    key[r] = v;
    rev[r] = 0;
    add[r] = 0;
}
void Build(int &x, int fa, int l, int r)
{
    if(l > r) return;
    int mid = (l + r) >> 1;
    NewNode(x, fa, a[mid]);
    Build(ch[x][0], x, l, mid-1);
    Build(ch[x][1], x, mid+1, r);
    PushUp(x);
}
void Init()
{
    pos = 1;
    root = tot1 = tot2 = 0;
    add[root] = ch[root][0] = ch[root][1] = pre[root] = key[root] = size[root] = 0;
    for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
    //放两个虚拟节点
    NewNode(root, 0, -1);
    NewNode(ch[root][1], root, -1);
    //建树
    Build(Key_value, ch[root][1], 1, n);
    PushUp(ch[root][1]);
    PushUp(root);
}
void Rotate(int x, int kind)
{
    int y = pre[x];
    PushDown(y);
    PushDown(x);
    ch[y][!kind] = ch[x][kind];
    pre[ch[x][kind]] = y;
    if(pre[y])
        ch[pre[y]][ch[pre[y]][1]==y] = x;
    pre[x] = pre[y];
    ch[x][kind] = y;
    pre[y] = x;
    PushUp(y);
}
void Splay(int r, int goal)
{
    PushDown(r);
    while(pre[r] != goal)
    {
        if(pre[pre[r]] == goal)
        {
            Rotate(r, ch[pre[r]][0]==r);
        }
        else
        {
            int y = pre[r];
            int kind = (ch[pre[y]][0]==y);
            if(ch[y][kind] == r)
                {
                    Rotate(r, !kind);
                    Rotate(r, kind);
                }
                else
                {
                    Rotate(y, kind);
                    Rotate(r, kind);
                }
        }
    }
    PushUp(r);
    if(goal == 0) root = r;
}
int Get_Max(int r)
{
    PushDown(r);
    while(ch[r][1])
    {
        r = ch[r][1];
        PushDown(r);
    }
    return r;
}
//得到序列第k个元素
int Kth(int r, int k)
{
    PushDown(r);
    int t = size[ch[r][0]] + 1;
    if(k == t) return r;
    else if(k < t) return Kth(ch[r][0], k);
    else return Kth(ch[r][1], k - t);
}
//将区间[l, r]放到尾部
void MoveLast(int l, int r)
{
    if(l > r) return;
    //首先将区间[l,r]旋转到root下面，并切割出来。
    Splay(Kth(root, l), 0);
    Splay(Kth(root, r+2), root);
    int rt = Key_value;
    Key_value = 0;
    PushUp(ch[root][1]);
    PushUp(root);
    //找到剩余区间中最后一个元素（注意：因为最后有个虚拟节点，所以这里取的是最后的虚拟节点）
    Splay(Get_Max(root), 0);
    int rtt = root;
    root = ch[root][0]; //把这个虚拟节点从原序列中删除
    pre[root] = 0;
    PushUp(root);
    //再找剩余区间中最后一个元素（这个就是真正的序列末元素了），并将区间[l,r]接到其后面
    Splay(Get_Max(root), 0);
    ch[root][1] = rt;
    pre[rt] = root;
    PushUp(root);
    //把删掉的虚拟节点加上
    ch[rtt][0] = root;
    pre[root] = rtt;
    root = rtt;
    pre[root] = 0;
    PushUp(root);
}
void Insert(int x)
{
    int r;
    Splay(Kth(root, pos+1), 0);
    Splay(Kth(root, pos+2), root);
    NewNode(r, ch[root][1], x);
    Key_value = r;
    PushUp(ch[root][1]);
    PushUp(root);
    ++n;
}
void erase(int r)
{
    if(!r) return;
    erase(ch[r][0]);
    erase(ch[r][1]);
    s[++tot2] = r;
}
void Delete()
{
    //这两步将第pos元素转到ch[root][1]下面
    Splay(Kth(root, pos), 0);
    Splay(Kth(root, pos+2), root);
    int r = Key_value;
    Key_value = 0;
    pre[r] = 0;
    erase(r);
    PushUp(ch[root][1]);
    PushUp(root);
    if(pos == n) pos = 1;
    --n;
}
void Move(int x)
{
    if(x == 1) pos = (pos > 1 ? pos-1 : n);
    else pos = (pos < n ? pos+1 : 1);
}
int Query()
{
    Splay(Kth(root, pos+1), 0);
    return key[root];
}
void Add(int x)
{
    MoveLast(1, pos-1);
    pos = 1;
    int l = pos, r = pos + k2 - 1;
    Splay(Kth(root, l), 0);
    Splay(Kth(root, r+2), root);
    Update_Add(Key_value, x);
}
void Reverse()
{
    MoveLast(1, pos-1);
    pos = 1;
    int l = pos, r = pos + k1 - 1;
    Splay(Kth(root, l), 0);
    Splay(Kth(root, r+2), root);
    Update_Rev(Key_value);
}
int main()
{
    int kase = 0;
    while(scanf("%d%d%d%d", &n, &q, &k1, &k2) == 4)
    {
        if(!n && !q && !k1 && !k2) break;
        char op[10];
        int x;
        Init();
        printf("Case #%d:\n", ++kase);
        for(int i = 1; i <= q; i++)
        {
            scanf("%s", op);
            if(op[0] == 'a')
            {
                scanf("%d", &x);
                Add(x);
            }
            else if(op[0] == 'r') Reverse();
            else if(op[0] == 'i')
            {
                scanf("%d", &x);
                Insert(x);
            }
            else if(op[0] == 'd') Delete();
            else if(op[0] == 'm')
            {
                scanf("%d", &x);
                Move(x);
            }
            else if(op[0] == 'q') printf("%d\n", Query());
        }
    }
    return 0;
}