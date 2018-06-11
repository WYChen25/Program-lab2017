

#include "Header.h"
extern void major(hotel *hotelh, ordered *order);
hotel *enter(FILE *file);
void admin(hotel *hotelh,ordered *order);
void preve(hotel *hotelh);

void check(hotel *hotelh)
{
    hotel *p = hotelh;
    if(p == 0)
        cout << "无酒店信息" << endl;
    while(p != 0 && p->hotelnext != 0) {
        cout <<p->num << '\t' <<p->name << '\t' << p->city <<'\t' << p->station << '|';
        room *q = p->rooomlist;
        while(q != 0 && q->next != 0) {
            cout << q->num << '\t' << q->price << '\t' << q->kind << '|';
            q = q->next;
        }
        if(q != 0) {
            cout << q->num << '\t' << q->price << '\t' << q->kind << endl;
        }
        p = p->hotelnext;
    }
    if(p != 0) {
        cout <<p->num <<'\t'<< p->name << '\t' << p->city <<'\t' << p->station << '|';
        room *q = p->rooomlist;
        while(q != 0 && q->next != 0) {
            cout << q->num << '\t' << q->price << '\t' << q->kind << '\t';
            q = q->next;
        }
        if(q != 0) {
            cout << q->num << '\t' << q->price << '\t' << q->kind << endl;
        }
    }
}


void setin(hotel *hotelh)
{
    //hotel *temp2 = hotelh;
    /*
    while(temp2->hotelnext != 0) {
        hotel *p = temp2;
        temp2 = p->hotelnext;
        delete p;
    }
    */
    FILE *hotelfile = fopen("/Users/pingguo/Desktop/hotel2.txt","r+");
    hotelh = enter(hotelfile);
    
    check(hotelh);
}

void adminscreen(void)
{
    cout << endl;
    cout << "如确认您是管理员，请选择所需操作：" << endl;
    cout << "*1.导入信息：" << endl;
    cout << "*2.添加酒店" << endl;
    cout << "*3.删除酒店" << endl;
    cout << "*4.保存信息" << endl;
    cout << "*5.返回上一级" << endl;
}

void addhotel(hotel *hotelh,ordered *order)
{
    hotel *p = hotelh;
    int i = 0;
    while(p != 0 && p->hotelnext != 0) {
        p = p->hotelnext;
        i++;
    }
    //cout << p->name << endl;
    hotel *q = new hotel;
    //p->hotelnext = q;
    if(p == 0)
        q->num = 0;
    else
        q->num = i+1;
    cout << "输入酒店信息（名称，城市，位置）" << endl;
    cin >> q->name >> q->city >> q->station;
    q->hotelnext = 0;
    cout << "若要输入房间请输入1" << endl;;
    int j;
    cin >> j;
    room *roomhead = 0, *roomtail = 0;
    int n = 0;
    while(j == 1) {
        room *m = new room;
        cout << "请输入房间信息(价格+类型）：" << endl;
        cin >> m->price >> m->kind;
        m->num = n;
        m->next = 0;
        if(roomtail == 0)
            roomhead = m;
        else
            roomtail->next = m;
        roomtail = m;
        cout << "继续输入请输入1，结束操作请输入0:" << endl;
        cin >> j;
        n++;
    }
    q->rooomlist = roomhead;
    if(p == 0)
        hotelh = q;
    else
        p->hotelnext = q;
    //check(hotelh);
    cout << "添加成功" << endl;
    admin(hotelh,order);
}

void deletehotel(hotel *hotelh, ordered *order)
{
    
    cout << "请输入您要删除的酒店编号" << endl;
    hotel *temp1 = hotelh, *temp = 0;
    ordered *temp2 = order;
    int j;
    cin >> j;
    for(int i = 0; i < j; i++) {
        temp = temp1;
        temp1 = temp1->hotelnext;
    }
    if(j == 0) {
        bool flag = true;
        while(temp2 != 0 && temp2->next != 0) {
            if(strcmp(temp2->name,temp1->name) == 0)
                flag = false;
            temp2 = temp2->next;
        }
        if(temp2 != 0)
            if(strcmp(temp2->name,temp1->name) == 0)
                flag = false;
        if(flag) {
            hotelh = hotelh->hotelnext;
            delete temp1;
            temp = hotelh;
            while(temp != 0 && temp->hotelnext != 0) {
                temp->num = temp->num - 1;
                temp = temp->hotelnext;
            }
            if(temp != 0) {
                temp->num = temp->num - 1;
            }

        }
        else
            cout << "该酒店已有订单，无法消除" << endl;
    }
    else {
        bool flag = true;
        while(temp2 != 0 && temp2->next != 0) {
            if(strcmp(temp2->name,temp1->name) == 0)
                flag = false;
            temp2 = temp2->next;
        }
        if(temp2 != 0)
            if(strcmp(temp2->name,temp1->name) == 0)
                flag = false;
        if(flag) {
            temp->hotelnext = temp1->hotelnext;
            delete temp1;
            temp = temp->hotelnext;
            while(temp != 0 && temp->hotelnext != 0) {
                temp->num --;
                temp = temp->hotelnext;
            }
            if(temp != 0)
                temp->num --;
        }
        else
            cout << "酒店已有订单，无法删除" << endl;
    }
    preve(hotelh);
    cout << "删除成功，将返回上一级" << endl;
    admin(hotelh, order);
     
}



void preve(hotel *hotelh)
{
    hotel *temp = hotelh;
    //cout << temp->hotelnext << endl;
   
    FILE *prefile = fopen("/Users/pingguo/Desktop/hotel2.txt","w+");
    
    
    while(temp != 0 && temp->hotelnext != 0) {
        //cout << 1 << endl;
        fprintf(prefile,"%d,""%s,""%s,""%s|",temp->num,temp->name,temp->city,temp->station);
        room *rtemp = temp->rooomlist;
        while(rtemp != 0 && rtemp->next != 0) {
            fprintf(prefile,"%d,""%d,""%s|",rtemp->num,rtemp->price,rtemp->kind);
            rtemp = rtemp->next;
        }
        fprintf(prefile,"%d,""%d,""%s|",rtemp->num,rtemp->price,rtemp->kind);
        fprintf(prefile,"%c",'\n');
        temp = temp->hotelnext;
    }
    if(temp != 0) {
        fprintf(prefile,"%d,""%s,""%s,""%s|",temp->num,temp->name,temp->city,temp->station);
        room *rtemp = temp->rooomlist;
        while(rtemp != 0 && rtemp->next != 0) {
            fprintf(prefile,"%d,""%d,""%s|",rtemp->num,rtemp->price,rtemp->kind);
            rtemp = rtemp->next;
        }
        if(rtemp != 0) {
            fprintf(prefile,"%d,""%d,""%s|",rtemp->num,rtemp->price,rtemp->kind);
        }
    }
    fclose(prefile);
    
}

void admin(hotel *hotelh,ordered *order)
{
    cout <<'\n'<< "*请输入所需服务项目:" << ' ';
    int j;
    cin >> j;
    if(j == 1) {
        setin(hotelh);
        cout << "导入成功" << endl;
        admin(hotelh,order);
    }
    else if(j == 2) {
        addhotel(hotelh,order);
        //cout << "添加成功" << endl;
        //check(hotelh);
        //admin(hotelh,order);
    }
    else if(j == 3) {
        deletehotel(hotelh,order);
        cout << "删除成功" << endl;
    }
    
    else if(j == 4) {
        preve(hotelh);
        cout << "保存成功" << endl;
        admin(hotelh,order);
    }
    else
        major(hotelh,order);
    
}









