#include "Header.h"

bool timecheck(int a, int b, int c)
{
    bool flag = false;
    if(a%400 == 0 || (a%4 == 0 && a%100 != 0)) {
        flag = true;
    }
    if(b == 1) {
        if(1 <= c && c <= 31)
            return true;
        else
            return false;
    }
    else if(b == 2) {
        if(flag){
            if(1 <= c && c <= 29)
                return true;
            else
                return false;
        }
        else {
            if(1 <= c && c <= 28)
                return true;
            else
                return false;
        }
    }
    else if(b == 3) {
        if(1 <= c && c <= 31)
            return true;
        else
            return false;
    }
    else if(b == 4) {
        if(1 <= c && c <= 30)
            return true;
        else
            return false;
    }
    else if(b == 5) {
        if(1 <= c && c <= 31)
            return true;
        else
            return false;
    }
    else if(b == 6) {
        if(1 <= c && c <= 30)
            return true;
        else
            return false;
    }
    else if(b == 7) {
        if(1 <= c && c <= 31)
            return true;
        else
            return false;
    }
    else if(b == 8) {
        if(1 <= c && c <= 31)
            return true;
        else
            return false;
    }
    else if(b == 9) {
        if(1 <= c && c <= 30)
            return true;
        else
            return false;
    }
    else if(b == 10) {
        if(1 <= c && c <= 31)
            return true;
        else
            return false;
    }
    else if(b == 11) {
        if(1 <= c && c <= 30)
            return true;
        else
            return false;
    }
    else if(b == 12) {
        if(1 <= c && c <= 31)
            return true;
        else
            return false;
    }
    else
        return false;
    
}

int sumprice(int sdata,int edata,int price)
{
    int sumprice = 0;
    int syear = sdata/10000;
    int smounth = (sdata%10000)/100;
    int sday = sdata%100;
    int eyear = edata/10000;
    int emounth = (edata%10000)/100;
    int eday = edata%100;
    
    int y2,m2,d2,y1,m1,d1;
    m1 = (smounth + 9)%12;
    y1 = syear - m1/10;
    d1 = 365*y1 + y1/4 - y1/100 + y1/400 + (m1 * 306 + 5)/10 + (sday-1);
    m2 = (emounth + 9)%12;
    y2 = eyear - m2/10;
    d2 = 365*y2 + y2/4 - y2/100 + y2/400 + (m2*306 + 5)/10 + (eday-1);
    sumprice = (d2-d1)*price;
    
    return sumprice;
}


