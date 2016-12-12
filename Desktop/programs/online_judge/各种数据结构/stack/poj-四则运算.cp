//
//  main.cpp
//  testtest
//  用来存放测试代码
/*
这里可以写心得
 &和|是按位与／或，但对于两个布尔值，可以当作||和&&使用。
 二分法：特判端点
 堆栈如果为空，调用top会炸
 switch case 每个case最后一定要加continue||break
 i++和++i的区别：前者返回一个拷贝，后者返回引用。当i为iterator之类的时前者速度慢
 数组a[i]的地址只能用&a[0]+i*sizeof表示，向量（class等）可用a.begin()
*/
//  Created by  WhitePhosphorus on 16/9/16.
//  Copyright © 2016年  WhitePhosphorus. All rights reserved.
//

/*还未检查以下错误：
  第一位为负数但之后没有数字：如-+2
  除数为零时返回的是inf
 有问题！！！参见c语言版对正负号的判定！！！
*/
#include <iostream>
#include <stack>
#define PARA_ERR 10;
#define STACK_EMPTY -1;
using namespace std;
stack<double> a;
stack<char> b;
string rst;

bool isNum(char c){
    return ((c>='0'&&c<='9')||c=='.');
}

int cal(){
    int i;
    char c;
    string s;
    double m,n;
    bool isN=false,isNeg=false;
    for(i=0;i<rst.size();i++){
        c=rst.at(i);
        if(isNum(c)){
            s+=c;isN=true;
            continue;
        }else if(c=='-'&&((i>0&&!isNum(rst.at(i-1))&&rst.at(i-1)!=')'&&rst.at(i-1)!=' ')||i==0)){
            isNeg=true;isN=true;
            s+=c;
        }else{
            if(isN)a.push(stod(s));
            isN=false;isNeg=false;
            s="";
        }
        switch(c){
            case '+':
                if(a.empty())return PARA_ERR;
                m=a.top();
                a.pop();
                if(a.empty())return PARA_ERR;
                n=a.top();
                a.pop();
                a.push(m+n);
                continue;
            case '-':
                if(isNeg)continue;
                if(a.empty())return PARA_ERR;
                m=a.top();
                a.pop();
                if(a.empty())return PARA_ERR;
                n=a.top();
                a.pop();
                a.push(n-m);
                continue;
            case '*':
                if(a.empty())return PARA_ERR;
                m=a.top();
                a.pop();
                if(a.empty())return PARA_ERR;
                n=a.top();
                a.pop();
                a.push(m*n);
                continue;
            case '/':
                if(a.empty())return PARA_ERR;
                m=a.top();
                a.pop();
                if(a.empty())return PARA_ERR;
                n=a.top();
                a.pop();
                a.push(n/m);
                continue;
            default:;continue;
        }
    }
    return 0;
}

int main(){
    string s;
    int i,re=STACK_EMPTY;
    char c;
    bool isN = false;
    bool isNeg = false;
    
    getline(cin,s);
    for(i=0;i<s.size();i++){
        c=s.at(i);
        if(isNum(c)){
            isN=true;
            rst+=c;
        }else if(c=='-'&&((i>0&&!isNum(s.at(i-1))&&s.at(i-1)!=')'&&s.at(i-1)!=')')||i==0)){
            isNeg=true;isN=true;
            rst+=c;
        }else{
            if(isN)rst+=" ";
            isN=false;isNeg=false;
        }
        if(c=='+'){
            while(!b.empty()&&b.top()!='('){
                rst+=" ";
                rst+=b.top();
                rst+=" ";
                b.pop();
            }
            b.push(c);
        }else if(c=='-'){
            if(isNeg)continue;
            while(!b.empty()&&b.top()!='('){
                rst+=" ";
                rst+=b.top();
                rst+=" ";
                b.pop();
            }
            b.push(c);
        }else if(c=='*'||c=='/'){
            while(!b.empty()&&(b.top()=='*'||b.top()=='/')){
                rst+=" ";
                rst+=b.top();
                rst+=" ";
                b.pop();
            }
            b.push(c);
        }else if(c=='('){
            b.push(c);
        }else if(c==')'){
            while(!b.empty()&&b.top()!='('){
                rst+=" ";
                rst+=b.top();
                rst+=" ";
                b.pop();
            }
            b.pop();
        }
    }
    while(!b.empty()){
        rst+=" ";
        rst+=b.top();
        b.pop();
    }
    rst+= " ";
    //cout << rst << endl;
    re=cal();
    if(!re&&!a.empty()){
        printf("%.2lf\n",a.top());
    }else{
        cout << "Err:" << re << endl;
    }
}


