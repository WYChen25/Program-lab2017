#include"Header.h"
//#include"admi.cpp"
//#include"user.cpp"
void check(hotel *hotelh);
void adminscreen(void);

hotel *enter(FILE *file)                                    //导入hotel文件至程序中始；
{
    //cout << 3 << endl;
    int i = 1;
    hotel *head = 0, *tail = 0;
    while(fgetc(file) != EOF) {
        if(i == 1) {
            fseek(file,-1,SEEK_CUR);
        }
        
        //cout << 1 << endl;
        hotel *p = new hotel;
        p->hotelnext = 0;
        fseek(file,-1,SEEK_CUR);
        fscanf(file,"%d",&p->num);
        fseek(file,1,SEEK_CUR);
        //cout << p->num << endl;
        fscanf(file,"%[^,]",p->name);
        //cout << p->name << endl;
        fseek(file,1,SEEK_CUR);
        fscanf(file,"%[^,]",p->city);
        //cout << p->city << endl;
        fseek(file,1,SEEK_CUR);
        fscanf(file,"%[^|]",p->station);
        //cout << p->station << endl;
        fseek(file,1,SEEK_CUR);
        room *head1 = 0, *tail1 = 0;
        int j = 1;
        fseek(file,-1,SEEK_CUR);
        while(fgetc(file) != '\n' && fgetc(file) != EOF) {
            if(j != 1) {
                fseek(file,-1,SEEK_CUR);
            }
            room *q = new room;
            q->next = 0;
            fseek(file,-1,SEEK_CUR);
            fscanf(file,"%d",&q->num);
            fseek(file,1,SEEK_CUR);
            fscanf(file,"%d",&q->price);
            fseek(file, 1, SEEK_CUR);
            fscanf(file,"%[^|]",q->kind);
            if(tail1 == 0)
                head1 = q;
            else
                tail1->next = q;
            tail1 = q;
            j++;
            //cout << q->num <<'\t'<< q->price <<'\t'<< q->kind<< endl;
            fseek(file,1,SEEK_CUR);
        }
        p->rooomlist = head1;
        
        if(tail == 0)
            head = p;
        else
            tail->hotelnext = p;
        //cout << p->num << '\t' << p->name << '\t' << p->city << '\t' << p->station << endl;
        //cout << p->rooomlist->num << '\t' << p->rooomlist->price << '\t' << p->rooomlist->kind << endl;
        tail = p;
        i++;
    }
    //cout << "finish";
    return head;
}                                             //导入hotel文件至程序函数末；

ordered *enter2(FILE *file)
{
    ordered *head = 0, *tail = 0;
    if(file == 0) {
        head = 0;
        return head;
    }
    int i = 1;
    while(fgetc(file) != EOF) {
        if(i == 1) {
            fseek(file,-1,SEEK_CUR);
        }
        ordered *p = new ordered;
        p->next = 0;
        fscanf(file,"%d",&p->hotelnum);
        fseek(file,1,SEEK_CUR);
        //cout << p->hotelnum << endl;;
        fscanf(file,"%[^,]",p->name);
        fseek(file,1,SEEK_CUR);
        //cout << p->name << endl;
        fscanf(file,"%d",&p->roomnum);
        fseek(file,1, SEEK_CUR);
        //cout << p->roomnum << endl;
        fscanf(file,"%d",&p->roomprice);
        fseek(file,1, SEEK_CUR);
        //cout << p->roomprice << endl;
        fscanf(file,"%[^,]",p->roomkind);
        fseek(file,1,SEEK_CUR);
        //cout << p->roomkind << endl;
        int a,b,c,d,e,f;
        fscanf(file,"%d,%d,%d,",&a,&b,&c);
        fscanf(file,"%d,%d,%d,%d",&d,&e,&f,&p->numprice);
        p->startdata = a*10000 + b * 100 + c;
        p->enddata = d*10000 + e*100 +f;
        //cout <<p->enddata << p->startdata << endl;
        if(tail == 0)
            head = p;
        else
            tail->next = p;
        tail = p;
        
    }
    return head;
}


void mainscreen(void);
extern void admin(hotel *hotelh,ordered *order);
extern void user(hotel *hotelh,ordered *order);
void major(hotel *hotelh,ordered *order);

int main()
{
    FILE *hotelfile = fopen("/Users/pingguo/Desktop/hotel2.txt","r+");
    FILE *orderfile = fopen("/Users/pingguo/Desktop/order.txt","r+");
    if(!hotelfile) {
        cout << false;
        return 0;
    }
    if(!orderfile) {
        cout << false;
        return 0;
    }
    //cout << 2 << endl;
    
    hotel *hotelh = enter(hotelfile);
   // cout << hotelh->hotelnext << endl;
    
    ordered *order = enter2(orderfile);
    //cout << order << endl;
    
    //check(hotelh);
    
    major(hotelh,order);
    
    return 0;
}

void major(hotel *hotelh,ordered *order)
{
    int i;
    mainscreen();
    cin >> i;
    if(i == 1) {
        adminscreen();
        admin(hotelh,order);
    }
    else if(i == 2) {
        user(hotelh,order);
    }
    else {
        cout << "退出程序成功，欢迎您再次使用" << endl;
    }
}

void mainscreen(void)
{
    cout <<'\n' << endl;
    cout <<'*' <<"欢迎使用本酒店预订系统，请选择服务项目" << endl;
    cout <<'*' <<"1.管理员入口：" << endl;
    cout <<'*' <<"2.用户入口：" << endl;
    cout <<'*' << "3.退出程序" << endl;
    cout << '\n' << '*' << "请输入所需服务项目:" <<' ';
}







