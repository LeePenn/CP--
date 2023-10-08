#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std;

int maze[105][105];
int w, h;

int lowbit(int x)
{
    return x & -x;
}

void update(int x, int y)
{
    for (int i = x; i <= w; i += lowbit(i))
    {
        for (int j = y; j <= h; j += lowbit(j))
        {
            maze[i][j]++;
        }
    }
}

int GetSum(int x, int y)
{
    int sum = 0;
    for (int i = x; i >= 1; i -= lowbit(i))
    {
        for (int j = y; j >= 1; j -= lowbit(j))
        {
            sum += maze[i][j];
        }
    }
    return sum;
}

int main()
{
    int n;
    int s, t, ans;
    while(scanf("%d", &n) != EOF && n != 0)
    {
        ans = -1;
        memset(maze, 0, sizeof(maze));
        scanf("%d%d", &w, &h);
        int x, y;
        for (int i = 0; i < n; i++)
        {
            scanf("%d%d", &x, &y);
            update(x, y);
        }
        scanf("%d%d", &s, &t);
        for (int i = s; i <= w; i++)
        {
            for (int j = t; j <= h; j++)
            {
                ans = max(ans, GetSum(i, j) - GetSum(i - s, j) - GetSum(i, j - t) + GetSum(i - s, j - t));
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}