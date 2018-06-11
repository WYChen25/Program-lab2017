//
//  user.cpp
//  my携程
//
//  Created by 琛琛~ on 17/3/22.
//  Copyright © 2017年 程设. All rights reserved.
//

#include "Header.h"
ordered *enter2(FILE *file);
extern void major(hotel *hotelh,ordered *order);
void user(hotel *hotelh, ordered *order);
void consult(hotel *hotelh,ordered *order);
void check(hotel *hotelh,ordered *order);
bool timecheck(int a, int b, int c);
int sumprice(int sdata,int edata,int price);

void userscreen(void)
{
    cout << endl;
    cout << "*请确认以用户身份登录" << endl;
    cout << "*1.查询酒店" << '\n' << "*2.查看订单" <<'\n' << "*3.返回上一级" << endl;
    cout <<'\n'<< "请选择所需服务" <<' ';
    
}

void consultscreen(void)
{
    cout << endl;
    cout << "*请选择以下服务" << endl;
    cout << "*1.输入位置" <<'\n' << "*2.查找酒店" <<'\n' << "*3，返回上一级"  << endl;
    cout << '\n'<<"请选择所需服务" <<' ';
}

void searchscreen(void)
{
    cout << endl;
    cout << "*请选择以下服务" << endl;
    cout << "*1.预订酒店" << '\n' << "*2.返回上一级" << endl;
}

void roomscreen(void) {
    
}                               //各种屏幕函数；

void preveorder(ordered *orderhead)
{
    ordered *temp = orderhead;
    FILE *orderfile = fopen("/Users/pingguo/Desktop/order.txt","w+");
    if(temp == 0) {
        cout << "没有要保存的订单信息" << endl;
    }
    
    
    while(temp!= 0 && temp->next != 0) {
        fprintf(orderfile,"%d,%s,%d,%d,%s,",temp->hotelnum,temp->name,temp->roomnum,temp->roomprice,temp->roomkind);
        fprintf(orderfile,"%d,%d,%d,%d,%d,%d,%d",temp->startdata/10000,(temp->startdata%10000)/100,temp->startdata%100,temp->enddata/10000,(temp->enddata%10000)/100,temp->enddata%100,temp->numprice);
        fprintf(orderfile,"%c",'\n');
        temp = temp->next;
    }
    if(temp != 0) {
        fprintf(orderfile,"%d,%s,%d,%d,%s,",temp->hotelnum,temp->name,temp->roomnum,temp->roomprice,temp->roomkind);
        fprintf(orderfile,"%d,%d,%d,%d,%d,%d,%d",temp->startdata/10000,(temp->startdata%10000)/100,temp->startdata%100,temp->enddata/10000,(temp->enddata%10000)/100,temp->enddata%100,temp->numprice);
    }
    fclose(orderfile);
}

void myorder(hotel *hotelh,ordered *order)
{
    cout << "请输入所要预定的酒店编号" << endl;
    int i;
    cin >> i;
    hotel *temp = hotelh;
    while(temp != 0 && temp->hotelnext != 0) {
        if(i == temp->num)
            break;
        else
            temp = temp->hotelnext;
    }
    if(temp != 0)
        cout << temp->num <<' '<< temp->name<<' '<< temp->city <<' '<< temp->station << endl;
    room *temp2 = temp->rooomlist;
    while(temp2 != 0 && temp2->next != 0) {
        cout << temp2->num<<' '<< temp2->price<<' '<< temp2->kind <<'|';
        temp2 = temp2->next;
    }
    if(temp2 != 0) {
        cout <<temp2->num<<' '<< temp2->price<<' '<< temp2->kind <<'|';
    }
    cout << endl;
    cout << "请确认所预订酒店信息正确，并输入所要预定房间编号" << endl;
    int j;
    cin >> j;
    temp2 = temp->rooomlist;
    while(temp2 != 0 && temp2->next != 0) {
        if(temp2->num == j)
            break;
        else
            temp2 = temp2->next;
    }
    cout << temp2->num << ' ' << temp2->price << ' ' << temp2->kind << endl;
    cout << "如果确认信息正确，请输入预定时间" << endl;
    int a,b,c,d,e,f;
    scanf("%d/%d/%d",&a,&b,&c);
    scanf("%d/%d/%d",&d,&e,&f);
    bool flag1 = timecheck(a,b,c);
    bool flag2 = timecheck(-d, e, f);
    ordered *orderhead = order;
    ordered *ordertail = order;
    int sdata = a*10000 + b*100 + c;
    int edata = -1*d*10000 + e*100 +f;
    if(sdata - edata > 0) {
        cout << "预定时间不合法，将返回上一级" << endl;
        consult(hotelh, order);
    }
    else if(flag1 && flag2) {                                    //未换行的if；
    bool flag = true;
    
    while(ordertail != 0 && ordertail->next!= 0) {
        ordered *k = ordertail;
        if(strcmp(k->name,temp->name) == 0 && strcmp(k->roomkind,temp2->kind) == 0) {
            int mul1 = k->startdata - sdata;
            int mul2 = k->enddata - sdata;
            int mul3 = k->startdata - edata;
            int mul4 = k->enddata - edata;
            if((mul1 <= 0 && mul2 >= 0 )|| (mul3 <= 0 && mul4 >=0) ||(mul1 >= 0 && mul4 <= 0))
                flag = false;
        }
        ordertail = ordertail->next;
    }
    
    if(ordertail != 0) {
        ordered *k = ordertail;
        if(strcmp(k->name,temp->name) == 0 && strcmp(k->roomkind,temp2->kind) == 0) {
            int mul1 = k->startdata - sdata;
            int mul2 = k->enddata - sdata;
            int mul3 = k->startdata - edata;
            int mul4 = k->enddata - edata;
            if(mul1 <= 0 || mul2 >= 0 || mul3 <= 0 || mul4 >=0)
                flag = false;
        }
    }
    
    if(flag) {
        ordered *p = new ordered;
        strcpy(p->name, temp->name);
        strcpy(p->roomkind,temp2->kind);
        p->roomnum = temp2->num;
        p->roomprice = temp2->price;
        p->enddata = edata;
        p->startdata = sdata;
        p->next = 0;
        p->numprice = sumprice(sdata,edata,p->roomprice);
        if(ordertail == 0){
            orderhead = p;
            p->hotelnum = 0;
        }
        else {
            ordertail->next = p;
            p->hotelnum = ordertail->hotelnum + 1;
        }
    }
    else{
        cout << "该房间已有预订者，请选择其他时间" << endl;
        consult(hotelh, order);
    }
    
    cout << "预订成功,输入2返回用户主界面,输入1保存订单" << endl;
    int n;
    cin >> n;
    if(n == 1) {
        preveorder(orderhead);
        consult(hotelh, order);
    }
    else
        consult(hotelh, order);
    } //未换行的if后括号；
    
    else if(!flag1 && flag2) {
        cout << "预定起始时间不合法，将返回上一级" << endl;
        consult(hotelh, order);
    }
    
    else if(flag1 && !flag2) {
        cout << "预定结束时间输入不合法，将返回上一级" << endl;
        consult(hotelh, order);
    }
    else {
        cout << "输入输出不合法，将返回上一级" << endl;
        consult(hotelh, order);
    }
}


void search(hotel *hotelh,ordered *order,char *checkplace)
{
    searchscreen();
    hotel *temp = hotelh;
    if(temp == 0) {
        cout << "暂无酒店信息" << endl;
    }
    while(temp != 0 && temp ->hotelnext != 0 ) {
        room *temp2 = temp->rooomlist;
        if(checkplace[0] == '\0' || strcmp(temp->city,checkplace) == 0) {
            cout << temp->num << '\t' << temp->name <<'\t' << temp->city << '\t' << temp->station << endl;
            while(temp2 != 0 &&temp2->next != 0) {
                cout <<temp2->num <<' '<<temp2->price <<' '<< temp2->kind<<'|';
                temp2 = temp2->next;
            }
            if(temp2 != 0) {
                cout <<temp2->num <<' '<<temp2->price <<' '<< temp2->kind<<endl;
            }
        }
        temp = temp->hotelnext;
        cout << endl;
    }
    
    if(temp != 0) {
        room *temp2 = temp->rooomlist;
        if(checkplace[0] == '\0'|| strcmp(temp->city,checkplace) == 0) {
            cout << temp->num << '\t' << temp->name <<'\t' << temp->city << '\t' << temp->station << endl;
            while(temp2 != 0 &&temp2->next != 0) {
                cout <<temp2->num <<' '<<temp2->price <<' '<< temp2->kind<<'|';
                temp2 = temp2->next;
            }
            if(temp2 != 0) {
                cout <<temp2->num <<' '<<temp2->price <<' '<< temp2->kind<<endl;
            }
        }

    }
    cout << endl;
    cout << "请选择所需服务" << ' ';
    int i;
    cin >> i;
    if(i == 1) {
        myorder(hotelh,order);
    }
    else
        consult(hotelh,order);
    
}


void consult(hotel *hotelh,ordered *order)
{
    consultscreen();
    int m;
    cin >> m;
    char checkplace[50];
    checkplace[0] = '\0';
    while(m == 1) {
        cout << "请输入位置" << endl;
        cin >>checkplace;
        cin >> m;
    }
    //cout << checkplace << endl;
    
    if(m == 2) {
        search(hotelh,order,checkplace);
    }
    else
        user(hotelh,order);
}

void checkscreen()
{
    cout << endl;
    cout << "*查看订单界面" << endl;
    cout << "*1.取消订单" <<'\n' <<"*2.返回上一级" << endl;
}

void cancelorder(hotel * hotelh,ordered *order)
{
    cout << "请输入要删除的酒店的编号" << endl;
    int i;
    cin >>i;
    ordered *temp = order;
    if(temp == 0) {
        cout << "无订单信息，返回用户界面"<< endl;
        user(hotelh,order);
    }
    else {
        bool flag = false;
        ordered *temp2 = 0;
        while(temp->next != 0) {
            if(i == temp->hotelnum) {
                flag = true;
                if(temp2 == 0){
                    temp = temp->next;
                    order = temp;
                    cout << "取消订单成功" << endl;
                    ordered *temp3 = temp;
                    while(temp3!= 0 && temp3->next != 0) {
                        temp3->hotelnum -- ;
                        temp3 = temp3->next;
                    }
                    if(temp3 != 0)
                        temp3->hotelnum--;
                
                }
                else{
                    temp2->next = temp->next;
                    delete temp;
                    ordered *temp3 = temp2->next;
                    while(temp3 != 0 && temp3->next != 0) {
                        temp3->hotelnum--;
                        temp3 = temp3->next;
                    }
                    if(temp3 != 0)
                        temp3->hotelnum--;
                }
                break;
            }
            temp2 = temp;
            temp = temp->next;
        }
        if(flag);
        else {
            if(i == temp->hotelnum) {
                delete temp;
                if(temp2 == 0)
                    order = 0;
                else
                    temp2->next = 0;
            }
        }
        preveorder(order);
        check(hotelh,order);
    }
    
}

void myprint(ordered *order)
{
    if(order == 0) {
        cout << "暂无订单信息" << endl;
    }
    else {
        ordered *temp = order;
        while(temp != 0 && temp->next != 0) {
            cout << temp->hotelnum <<' ' <<temp->name<<' '<<temp->roomnum<<' '<<temp->roomprice<<' '<<temp->roomkind<<' '<<temp->startdata/10000<<','<<(temp->startdata%10000)/100<<','<<temp->startdata%100<<'-'<<temp->enddata/10000<<','<<(temp->enddata%10000)/100<<','<<temp->enddata%100<< ' '  << temp->numprice << endl;
            temp = temp->next;
        }
        if(temp != 0) {
            cout << temp->hotelnum <<' ' <<temp->name<<' '<<temp->roomnum<<' '<<temp->roomprice<<' '<<temp->roomkind<<' '<<temp->startdata/10000<<','<<(temp->startdata%10000)/100<<','<<temp->startdata%100<<'-'<<temp->enddata/10000<<','<<(temp->enddata%10000)/100<<','<<temp->enddata%100<<' '  << temp->numprice <<endl;
        }
    }
}

void check(hotel *hotelh,ordered *order)
{
    checkscreen();
    FILE *checkorder = fopen("/Users/pingguo/Desktop/order.txt","r+");

    order = enter2(checkorder);
    myprint(order);
    cout << "请选择所需服务项目" <<' ';
    int i;
    cin >> i;
    if(i == 1) {
        cancelorder(hotelh,order);
    }
    else
        user(hotelh,order);
}


void user(hotel *hotelh,ordered *order)
{
    userscreen();
    int j;
    cin >> j;
    if(j == 1)
        consult(hotelh,order);
    else if(j == 2)
        check(hotelh,order);
    else
         major(hotelh,order);
}


