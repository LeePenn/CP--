#include <iostream>
#include <queue>
using namespace std;
 
int n, m, sx, sy, ex, ey, answer = -1;  //注意初始化
int room[1005][1005];
int temp[4][2] = { {1,0},{0,1},{-1,0},{0,-1} };
int visited[1005][1005];
 
void DFS(int x,int y,int flag,int kk) {
	int d, k, now;
	if (x == ex && y == ey && flag <= 2) {
		answer = flag;
		return;
	}
	else if (flag > 2 || answer != -1)
		return;
	else if(flag <= 2 && answer == -1){
		for (int i = 0; i < 4 && answer == -1; i++) {
			d = x + temp[i][0];
			k = y + temp[i][1];
			if ((room[d][k] == 0 && d >= 1 && d <= n && k >= 1 && k <= m && visited[d][k] == 0) || (d == ex && k == ey && visited[d][k] == 0)) {
				visited[d][k] = 1;
				if (i != kk)
					DFS(d, k, flag + 1, i);
				else
					DFS(d, k, flag, i);
				visited[d][k] = 0;
			}
		}
	}
	return;
}
int main() {
	int h;
	while (cin >> n >> m) {
		memset(room, 0, sizeof(room));
		if (n == 0 && m == 0)
			break;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				cin >> room[i][j];
			}
		}
		cin >> h;
		for (int i = 1; i <= h; i++) {
			answer = -1;
			cin >> sx >> sy >> ex >> ey;
			if (room[sx][sy] == 0 || room[ex][ey] == 0 || room[sx][sy] != room[ex][ey]) {
				cout << "NO" << endl;
				continue;
			}
			memset(visited, 0, sizeof(visited));
			DFS(sx, sy, -1, -1);
			if (answer != -1)
				cout << "YES" << endl;
			else
				cout << "NO" << endl;
		}
	}
	system("pause");
	return 0;
}