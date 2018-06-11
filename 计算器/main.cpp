#include "Header.h"

int main()
{
    int x = expressionevaluation();
    cout << x <<"end" <<endl;
    return 0;
}

int getnext(int *n)
{
    char c;
    *n = 0;
    while((c = getchar()) == ' ');
    if(!isdigit(c)) {
        if('a' <= c && c <= 'z') {
            *n = c;
            cout << *n << endl;;
            for(int i = 0; i < 3; i++){
                c = getchar();
            }
            ungetc(c,stdin);
        }
        else {
            *n = c;
            cout << *n << endl;
        }
        return 1;
    }
    do{
        *n = *n * 10 + (c-'0');
        c = getchar();
    }while(isdigit(c));
    ungetc(c,stdin);
    return 0;
}                                                    //得到输入的下一个字符或数字+或三角函数（思路源于网上各种大神）；

char compare(char a, char b)
{
    int i = 0,j = 0;
    
    char pre[10][10] = {
        {'>','>','>','>','>','>','>','<','>','>'},
        {'>','>','>','>','>','>','>','<','>','>'},
        {'>','>','>','>','>','>','>','<','>','>'},
        {'<','<','<','>','>','<','<','<','>','>'},
        {'<','<','<','>','>','<','<','<','>','>'},
        {'<','<','<','>','>','>','>','<','>','>'},
        {'<','<','<','>','>','>','>','<','>','>'},
        {'>','>','>','<','<','<','<','<','=','0'},
        {'<','<','<','>','>','>','>','0','>','>'},
        {'<','<','<','<','<','<','<','<','0','='},
    };
    switch(a) {
        case's':i = 0;break;
        case'c':i = 1;break;
        case't':i = 2;break;
        case'+':i = 3;break;
        case'-':i = 4;break;
        case'*':i = 5;break;
        case'/':i = 6;break;
        case'(':i = 7;break;
        case')':i = 8;break;
        case'#':i = 9;break;
    }
    switch(b) {
        case's':i = 0;break;
        case'c':i = 1;break;
        case't':i = 2;break;
        case'+':j = 3;break;
        case'-':j = 4;break;
        case'*':j = 5;break;
        case'/':j = 6;break;
        case'(':j = 7;break;
        case')':j = 8;break;
        case'#':j = 9;break;
    }
    return pre[i][j];
}

int expressionevaluation()
{
    int n;
    int c;
    int flag;
    int x;
    int operate;
    int a,b;
    char op[] = "+-*/()#";
    stack<int>num;
    stack<char>optr;
    optr.push('#');
    flag = getnext(&c);
    //cout << c << endl;
  //  cout << flag << endl;
    
    x = optr.top();
    
    while(c != '#' || x!= '#') {
        //cout << 1 << endl;
        if(flag == 0) {
          //  cout << 2 << endl;
            num.push(c);
            flag = getnext(&c);
        }
        else {
            x = optr.top();
            switch(compare(x, c)) {
                    case'<':
                    optr.push(c);
                    flag = getnext(&c);
                    break;
                    case'>':
                    operate = optr.top();
                    optr.pop();
                    if(operate != 's' && operate != 't' && operate != 'c') {
                        a = num.top();
                        num.pop();
                        b = num.top();
                        num.pop();
                        num.push(operation(a,operate,b));
                    }
                    else {
                        a = num.top();
                        num.pop();
                        num.push(operation2(a,operate));
                    }
                    break;
                    case'=':
                    operate = optr.top();
                    optr.pop();
                    flag = getnext(&c);
                    break;
                    case'0':
                    cout << "输入错误" << endl;
            }
        }
        x = optr.top();
        
    }
    c = num.top();

    return c;
    
}

int operation(int a, char operate, int b)
{
    int i,j,result = 0;
    i = a;
    j = b;
    
    switch(operate) {
        case'+':result = i + j;break;
        case'-':result = i - j;break;
        case'*':result = a * b;break;
        case'/':result = a / b;break;
    }
    return result;
}

int operation2(int a,char operate)
{
    int i = a;
    int result;
    switch(operate) {
        case's':result = sin(a);break;
        case'c':result = cos(a);break;
        case't':result = tan(a);break;
    }
    return result;
}








