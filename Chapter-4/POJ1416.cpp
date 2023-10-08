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

#define mytest

using namespace std;
typedef long long LL;
const int N = 21;
LL target;
char num[N];
LL ans;
bool same;
int len;
vector<LL> ans_list;
vector<LL> tmp_list;

LL getNum(int l, int r) {
    LL ret = 0;
    for (int i = l; i <= r; ++i) {
        ret = ret * 10 + num[i] - '0';
    }
    return ret;
}

LL getLeft(int l) {
    LL res = 0;
    for (int i = l; i <= len; ++i) {
        res += num[i] - '0';
    }
    return res;
}

void Dfs(int cur, LL sum) {
    if (cur > len) {
        if (sum > ans) {
            ans = sum;
            ans_list.clear();
            for (int i = 0; i < tmp_list.size(); ++i) {
                ans_list.push_back(tmp_list[i]);
            }
            same = false;
        } else if (sum == ans) {
            same = true;
        }
        return;
    }
    
    for (int i = cur; i <= len; ++i) {
        LL t = getNum(cur, i);
        if (t + sum > target) break;
        LL left = getLeft(i + 1);
        if (t + sum + left > target) break;
        tmp_list.push_back(t);
        Dfs(i + 1, sum + t);
        tmp_list.erase(tmp_list.begin() + tmp_list.size() - 1);
    }
}

int main() {

#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    while (scanf("%lld %s", &target, num + 1) == 2 && target && num[1] != '0') {
        ans = -1;
        same = false;
        tmp_list.clear();
        ans_list.clear();
        len = strlen(num + 1);
        LL a = getNum(1, len);
        if (a == target) {
            printf("%lld %lld\n", target, a);
            continue;
        }
        Dfs(1, 0);
        if (same) {
            printf("rejected\n");
            continue;
        }
        
        if (ans == -1) {
            printf("error\n");
            continue;
        }
        
        printf("%lld ", ans);
        for (int i = 0; i < ans_list.size(); ++i) {
            printf("%lld ", ans_list[i]);
        }
        printf("\n");
        
        // printf("%lld %lld\n", target, a);
    }
    
    
    return 0;
}