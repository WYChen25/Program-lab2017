#include<iostream>
#include<fstream>

using namespace std;

struct room {
    int num;
    int price;
    char kind[50];
    room *next;
};

struct hotel {
    int num;
    char name[50];
    char city[50];
    char station[100];
    room *rooomlist;
    hotel *hotelnext;
};

struct ordered {
    int hotelnum;
    char name[50];
    int roomnum;
    int roomprice;
    char roomkind[50];
    int startdata;
    int enddata;
    int numprice;
    ordered *next;
};



