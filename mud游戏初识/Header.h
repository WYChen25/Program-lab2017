//
//  Header.h
//  在出错你就去死吧
//
//  Created by 琛琛~ on 17/4/20.
//  Copyright © 2017年 程设. All rights reserved.
//

#ifndef Header_h
#define Header_h


#endif /* Header_h */

#include"tinyxml2.h"
#include<iostream>
#include<cmath>
using namespace std;
using namespace tinyxml2;


void starttown(XMLElement *root);
void read(XMLElement *root);
int change(const char *str);
void checkrole(void);
void greenground(XMLElement *root);
void endgame(int a);
void blackbear(XMLElement *root);
void blacktree(XMLElement *root);
void delay_sec(int sec);

extern const char* heroattri[20];
extern int heronum[20];
extern int monsternum1[20];
extern int monsternum2[20];
extern bool flag;
extern int heronum2[20];
extern bool silaimuflag;
extern bool insight;
extern bool look;
extern bool npc1talk1;
extern bool npc1talk2;
