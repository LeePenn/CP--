#include<iostream>
#include<vector>
#include<string>
#include<cmath>
#include<set>
#include<algorithm>
#include<cstdio>
#include<map>
#include<cstring>

using namespace std;

// 小希的迷宫 HDU - 1272

/**
思路： 当图中的集合(连通子图)个数为1并且边数等于顶点数-1(即改图恰好为一棵生成树)时，输出Yes.
此题的坑：(1) 如果只输入0 0算作一组数据的话答案应该输出Yes
　　　　　(2) 输入数据可能并不是连通图，有可能一开始不连通，所以最后一定要判断其连通子图个数是不是1
*/

int Tree[100100];

int findRoot(int x)
{
    if(Tree[x] == -1)
        return x;

    // 路径压缩
    int tmp = findRoot(Tree[x]);
    Tree[x] = tmp;
    return tmp;
}

int main()
{
    int a, b;
    set<int> Set;    // 使用Set保存图中的所有顶点编号
    for(int i = 0; i <= 100000; ++i)
        Tree[i] = -1;

    int rimCnt = 0;
    while(cin >> a >> b)
    {
        if(a == -1 && b == -1)
            break;

        if(a == 0 && b == 0)
        {
            if(rimCnt == 0)        // 只有输入一组数据0 0的时候，应该输出Yes
            {
                cout << "Yes" << endl;
                continue;
            }
            int Vcnt = Set.size();    // 顶点计数
            int Scnt = 0;            // 图中的连通子图(集合)个数
            for(set<int>::iterator iter = Set.begin(); iter != Set.end(); ++iter)
            {
                if(Tree[*iter] == -1)
                {
                    Scnt++;
                }
            }

            // 当图中的集合只有一个并且总边数等于顶点数-1的时候，输出Yes
            if(Scnt == 1 && rimCnt == Vcnt - 1)
            {
                cout << "Yes" << endl;
            }
            else
            {
                cout << "No" << endl;
            }

            for(int i = 0; i <= 100000; ++i)
                Tree[i] = -1;
            Set.clear();    // 清空集合
            rimCnt = 0;     // 边数置零
            continue;
        }
        else
        {
            rimCnt++;    // 边计数
            Set.insert(a);
            Set.insert(b);
            int ra = findRoot(a);
            int rb = findRoot(b);
            if(ra != rb)
            {
                Tree[ra] = rb;
            }
        }

    }

    return 0;
}