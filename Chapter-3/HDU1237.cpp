#include <bits/stdc++.h>

#define mytest

using namespace std;
typedef long long LL;
LL n, m;
string s;
stack<double> num;
stack<char> op;

int youxianji(char ch) {
    int ret = 0;
    switch (ch) {
        case '+':
            ret = 1;
            break;
        case '-':
            ret = 1;
            break;
        case '*':
            ret = 2;
            break;
        case '/':
            ret = 2;
            break;
        default:
            break;
    }
    return ret;
}

void getOp() {
    double n1 = num.top(); num.pop();
    double n2 = num.top(); num.pop();
    char o = op.top(); op.pop();
    switch (o) {
        case '+':
            num.push(n2 + n1);
            return;
        case '-':
            num.push(n2 - n1);
            return;
        case '*':
            num.push(n2 * n1);
            return;
        case '/':
            num.push(n2 / n1);
            return;
        default:
            return;
    }
}

void Calc() {
    int len = s.length();
    int i = 0;
    while (i < len) {
        if (s[i] == ' ') {
            i++;
            continue;
        } else if (s[i] == '(') {
            op.push(s[i]);
            i++;
            continue;
        } else if (isdigit(s[i])) {
            int k = 0;
            while (isdigit(s[i])) {
                k = k * 10 + s[i] - '0';
                i++;
            }
            num.push(1.0 * k);
        } else if (s[i] == ')') {
            while (!op.empty() && op.top() != '(') {
                getOp();
            }
            op.pop();
            i++;
        } else {
            while (!op.empty() && youxianji(op.top()) >= youxianji(s[i])) {
                getOp();
            }
            op.push(s[i]);
            i++;
        }
        
    }
    while (!op.empty()) getOp();
    printf("%.2lf\n", num.top());
    num.pop();
    // cout << op.size() << " " << num.size() << endl;
}

int main() {

#ifdef mytest
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    while (1) {
        getline(cin, s);
        if (s == "0") break;
        
        Calc();
    }
    
    
    
    
    return 0;
}