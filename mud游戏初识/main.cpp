#include"Header.h"

const char* heroattri[20];
int heronum[20];
int heronum2[20];
int monsternum1[20];
int monsternum2[20];
bool flag = false;
bool silaimuflag = false;

int main()
{
    cout << "欢迎进入游戏，请问你要<continue>进行上次游戏，还是<new>开始新游戏" << endl;
    char command[20];
    
    while(1) {
        cin >> command;
        char word1[20] = "continue";
        char word2[20] = "new";
        if(strcmp(command, word2) == 0) {
            XMLDocument doc;
            doc.LoadFile("/home/chenchen/Documents/mud/new.xml");
            XMLElement *game = doc.RootElement();
            read(game);
            starttown(game);
            return 0;
        }
        else if(strcmp(command, word1) == 0) {
            XMLDocument doc;
            doc.LoadFile("/home/chenchen/Documents/mud/new.xml");
            XMLElement *game = doc.RootElement();
            read(game);
            FILE *ofile  = fopen("/home/chenchen/Documents/mud/preve.txt", "r");
            int i = 0;
            while(fgetc(ofile) != EOF) {
                if(i == 0) {
                    fseek(ofile,-1,SEEK_CUR);
                }
                fscanf(ofile, "%d",&heronum[i]);
                i++;
            }
            cout << heronum[i-1] << endl;
            if(heronum[i-1] == 1) {
                starttown(game);
            }
            else if(heronum[i-1] == 2) {
                greenground(game);
            }
            else if(heronum[i-1] == 3) {
                blackbear(game);
            }
            else if(heronum[i-1] == 4) {
                blacktree(game);
            }
            else {
                
            }
            return 0;
        }
        else {
            cout << "您想说什么？" << endl;
        }
    }
    //cout << "未知错误，程序终止" << endl;
    return 0;
}

void read(XMLElement *root)
{
    XMLElement *map = root->FirstChildElement("map");
    XMLElement *hero = map->NextSiblingElement();
    XMLElement *hero2 = hero->FirstChildElement();
    XMLElement *attribute = hero2->FirstChildElement();
    int i = 0;
    while(attribute) {
        const XMLAttribute *attri = attribute->FirstAttribute();
        heroattri[i] = attri->Name();
        const char *content = attri->Value();
        heronum[i] = change(content);
        attribute = attribute->NextSiblingElement();
        i++;
    }
    i = 0;
    XMLElement *hero3 = hero2->NextSiblingElement();
    XMLElement *attribute2 = hero3->FirstChildElement();
    while(attribute2) {
        heronum2[i] = change(attribute2->GetText());
        attribute2 = attribute2->NextSiblingElement();
        i++;
    }
    i = 0;
    XMLElement *scene = map->FirstChildElement("scene1");
    XMLElement *scene2 = scene->NextSiblingElement("scene2");
    XMLElement *dis = scene2->FirstChildElement("describtion2");
    XMLElement *monster = dis->NextSiblingElement();
    XMLElement *numa = monster->FirstChildElement();
    while(numa) {
        monsternum1[i] = change(numa->GetText());
        numa = numa->NextSiblingElement();
        i++;
    }
    i = 0;
    XMLElement *boss = monster->NextSiblingElement();
    XMLElement *numb = boss->FirstChildElement();
    while(numb) {
        monsternum2[i] = change(numb->GetText());
        numb = numb->NextSiblingElement();
        i++;
    }
    
}

int change(const char *str)
{
    int i = 0;
    while(str[i] != '\0')
        i++;
    int a = 0;
    for(int j = 0; j< i; j++) {
        a = a + (str[j] - '0')*pow(10,i-j-1);
        //cout << a << endl;
    }
    return a;
}

void checkrole()
{
    int i;
    for(i = 0; heroattri[i]!= 0; i++) {
        cout << heroattri[i] <<":" << heronum[i] << endl;
    }
    
}

void delay_sec(int sec)
{
    time_t start_time,cur_time;
    time(&start_time);
    do {
        time(&start_time);
    }while((cur_time - start_time) < sec);
}

void endgame(int a)
{
    //cout << 1 << endl;
    FILE *file  = fopen("/home/chenchen/Documents/mud/preve.txt", "w");
    for(int i = 0; i <= 6 ; i++) {
        fprintf(file, "%d",heronum[i]);
        fprintf(file, ",");
    }
    fprintf(file,"%d",a);
    flag = true;
    fclose(file);
}




