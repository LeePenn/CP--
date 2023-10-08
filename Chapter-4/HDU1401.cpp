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

struct point{
    int x,y;
    
    //是否超出边界 
    bool check(){
        return x>=0&&x<8&&y>=0&&y<8;
    }
};

struct node{
    point p[4]; 
    int step;
}st,ed;//开始状态，目标状态 

//将四个点的位置按从小到大的顺序排序
//避免相同情况重复统计 
bool cmp(point a, point b){
    int p1 = a.y * 8 + a.x;
    int p2 = b.y * 8 + b.x;
    
    return p1 < p2;
}
 
char visited[64][64][64][64] = {'0'};

//将当前状态标记为"已被搜索" 
void set_visited(node n, char c){
    int p1 = n.p[0].y * 8 + n.p[0].x;
    int p2 = n.p[1].y * 8 + n.p[1].x;
    int p3 = n.p[2].y * 8 + n.p[2].x;
    int p4 = n.p[3].y * 8 + n.p[3].x;
    
    visited[p1][p2][p3][p4] = c;
}

//获取当前状态的标记信息 
char get_visited(node n){
    int p1 = n.p[0].y * 8 + n.p[0].x;
    int p2 = n.p[1].y * 8 + n.p[1].x;
    int p3 = n.p[2].y * 8 + n.p[2].x;
    int p4 = n.p[3].y * 8 + n.p[3].x;
    
    return visited[p1][p2][p3][p4];
}

int dir[4][2] = {{0,-1}, {0,1}, {-1,0}, {1,0}};

//四个点的位置 
int p_map[8][8];

//标记四个点的位置信息 
void set_map(node n){
    memset(p_map, 0, sizeof(p_map));
    
    p_map[n.p[0].y][n.p[0].x] = 1;
    p_map[n.p[1].y][n.p[1].x] = 1;
    p_map[n.p[2].y][n.p[2].x] = 1;
    p_map[n.p[3].y][n.p[3].x] = 1;
}

//判断是否跳棋 
bool jump(point p){
    //若目标位置已存在棋子，则跳棋 
    if(p_map[p.y][p.x] == 1){
        return true;
    }
    return false;
}

bool bfs(){
    memset(visited, '0', sizeof(visited));
    
    //双向BFS，故某一状态存在两种情况
    //正向被搜索到 
    //逆向被搜索到 
    set_visited(st, '1');
    set_visited(ed, '2');
    
    st.step = 0;
    ed.step = 0;
    
    //声明两个队列，分别记录节点信息 
    queue<node> q1,q2;
    q1.push(st);
    q2.push(ed);
    
    node next;
    while(!q1.empty() || !q2.empty()){
        //正向搜索 
        if(!q1.empty()){
            st = q1.front();
            q1.pop();
            
            //已经正向搜索了四步 
            if(st.step >= 4){
                continue;
            }
            
            //当前状态已经被反向搜索到 
            if(get_visited(st) == '2'){
                return true;
            }
            
            //标记四点位置信息 
            set_map(st);
            
            //尝试移动四个点中的一个 
            for(int i=0;i<4;i++){
                //尝试四个方向 
                for(int j=0;j<4;j++){
                    next = st;
                    next.p[i].x += dir[j][0];
                    next.p[i].y += dir[j][1];
                    next.step++;
                    
                    //超出范围 
                    if(!next.p[i].check()){
                        continue;
                    }
                    
                    //跳棋 
                    if(jump(next.p[i])){
                        next.p[i].x += dir[j][0];
                        next.p[i].y += dir[j][1];
                        
                        //超出范围 
                        if(!next.p[i].check()){
                            continue;
                        }
                    }
                    
                    //将节点按位置信息排序，避免重复统计 
                    sort(next.p, next.p+4, cmp);
                    
                    char flag = get_visited(next);
                    //当前状态没有被搜索到过 
                    if(flag == '0'){
                        //做正向搜索标记 
                        set_visited(next, '1');                        
                        q1.push(next);
                    }
                    else if(flag == '2'){//当前状态被反向搜索到过 
                        return true;
                    }    
                }
            }
        }
        
        //反向搜素，同理 
        if(!q2.empty()){
            ed = q2.front();
            q2.pop();
            
            if(ed.step >= 4){
                continue;
            }
            
            if(get_visited(ed) == '1'){
                return true;
            }
            
            set_map(ed);
            
            for(int i=0;i<4;i++){
                for(int j=0;j<4;j++){
                    next = ed;
                    next.p[i].x = ed.p[i].x + dir[j][0];
                    next.p[i].y = ed.p[i].y + dir[j][1];
                    next.step++;
                    
                    if(!next.p[i].check()){
                        continue;
                    }
                    
                    if(jump(next.p[i])){
                        next.p[i].x += dir[j][0];
                        next.p[i].y += dir[j][1];
                        
                        if(!next.p[i].check()){
                            continue;
                        }
                    }
                    
                    sort(next.p, next.p+4, cmp);
                    
                    char flag = get_visited(next);
                    if(flag == '0'){
                        set_visited(next, '2');
                        q2.push(next);
                    }
                    else if(flag == '1'){
                        return true;
                    }    
                }
            }
        }
    }
    //8步内不能到达 
    return false;    
}

int main(){
    while(~scanf("%d%d", &st.p[0].y, &st.p[0].x)){
        for(int i=1;i<4;i++){
            scanf("%d%d", &st.p[i].y, &st.p[i].x);
        }
        for(int i=0;i<4;i++){
            scanf("%d%d", &ed.p[i].y, &ed.p[i].x);
        }
        
        for(int i=0;i<4;i++){
            st.p[i].x--;
            st.p[i].y--;
            ed.p[i].x--;
            ed.p[i].y--;
        }
        
        sort(st.p, st.p+4, cmp);
        sort(ed.p, ed.p+4, cmp);
        
        bool result = bfs();
        
        if(result){
            printf("YES\n");
        }
        else{
            printf("NO\n");
        }
    }
}