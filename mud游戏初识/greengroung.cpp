#include "Header.h"

void greenground(XMLElement *root)
{
    XMLElement *map = root->FirstChildElement("map");
    XMLElement *scene = map->FirstChildElement("scene1");
    XMLElement *scene2 = scene->NextSiblingElement("scene2");
    XMLElement *dis = scene2->FirstChildElement("describtion2");
    const XMLAttribute *scenename2 = scene2->FirstAttribute();
    const XMLAttribute *dis2 = dis->FirstAttribute();
    cout << scenename2->Name() << ":" << scenename2->Value() <<":"<<'\n'<<dis2->Value() << endl;
    XMLElement *scene3 = scene2->NextSiblingElement("scene3");
    const XMLAttribute *scenename3 = scene3->FirstAttribute();
    XMLElement *scene4 = scene3->NextSiblingElement("scene4");
    const XMLAttribute *scenename4 = scene4->FirstAttribute();
    
    XMLElement *monster = dis->NextSiblingElement();
    const XMLAttribute *attri = monster->FirstAttribute();
    const char *content1 = attri->Value();
    XMLElement *boss = monster->NextSiblingElement();
    const XMLAttribute *boss2 = boss->FirstAttribute();
    const char *content2 = boss2->Value();
    cout << content1 << " "<< content2 << endl;
    
    char word[20];
    while(1) {
        cin >> word;
        if(strcmp(word,"demand") == 0)
            checkrole();
        else if(strcmp(word,"go") == 0) {
            const XMLAttribute *scenename = scene->FirstAttribute();
            const char *content1 = scenename->Value();
            const char *content2 = scenename2->Value();
            const char *content3 = scenename3->Value();
            const char *content4 = scenename4->Value();
            char word2[20] = "\0";
            while(strcmp(word2,content2) != 0 && strcmp(word2, content1) != 0 && strcmp(word2,content3) !=0 && strcmp(word2,content4) != 0){
                cin >> word2;
                if(strcmp(word2,content1) == 0) {
                    starttown(root);
                    //cout << 2 << endl;
                }
                else if(strcmp(word2,content2) == 0)
                    greenground(root);
                else if(strcmp(word2,content3) == 0)
                    blackbear(root);
                else if(strcmp(word2,content4) == 0)
                    blacktree(root);
                else
                    cout << "您要去哪？" << endl;
                if(flag)
                    break;
            }
            //cout << 3 << endl;
            if(flag)
                break;
        }
        else if(strcmp(word,"attack") == 0) {
            char word2[20];
            cin >> word2;
            //cout << word2;
            //cout << strcmp(word2,content1);
            if(strcmp(word2,content1) == 0) {
                int temp = monsternum1[2];
                //cout << 1 << endl;
                while(heronum[2] > 0 && monsternum1[2] > 0) {
                    //cout << 2 << endl;
                    monsternum1[2] = monsternum1[2] - heronum[0] + monsternum1[1];
                    heronum[2] = heronum[2] - monsternum1[0] + heronum[1];
                }
                if(heronum[2] > 0) {
                    heronum[4] = heronum[4] + monsternum1[3];
                    if(heronum[4] >= heronum[5]) {
                        heronum[3] ++;
                        heronum[0] = heronum[0] + heronum2[0];
                        heronum[1] = heronum[1] + heronum2[1];
                        heronum[6] = heronum[6] + heronum2[2];
                        heronum[4] = heronum[4] - heronum[5];
                        cout << "恭喜您战胜了史莱姆，获得了" << monsternum1[3] << "点经验，并成功升至" << heronum[3] << "级" << endl;
                    }
                    else {
                        cout << "恭喜您战胜了史莱姆，您获得了" << monsternum1[3] << "点经验" << endl;
                    }
                }
                else {
                    cout << "您被史莱姆打败了，游戏结束" << endl;
                    endgame(1);break;
                }
                monsternum1[2] = temp;
            }
            else if(strcmp(word2,content2) == 0) {
                int temp = monsternum2[2];
                while(heronum[2] > 0 && monsternum2[2] > 0) {
                    monsternum2[2] = monsternum2[2] - heronum[0] + monsternum2[1];
                    heronum[2] = heronum[2] - monsternum2[0] + heronum[1];
                }
                if(heronum[2] > 0) {
                    cout << "恭喜你打败了史莱姆之王，并获得了" << monsternum2[3] << "点攻击力加成" << endl;
                    cout << "快把这个好消息告诉镇长吧！" << endl;
                    silaimuflag = true;
                    heronum[0] = heronum[0] + monsternum2[3];
                }
                else {
                    cout << "您被史莱姆之王打败了，游戏结束" << endl;
                    endgame(1);break;
                }
                monsternum2[2] = temp;
            }
            else
                cout << "您要攻击谁？" << endl;
        }
        else if(strcmp(word,"rest") == 0) {
            //cout << 1 << endl;
            if(heronum[2] + 50 < heronum[6]) {
                heronum[2] = heronum[2] + 50;
                cout << "您回复了50点血量" << endl;
            }
            else if(heronum[2] < heronum[6] && heronum[2] + 50 >= heronum[6]) {
                heronum[2] = heronum[6];
                cout << "您的血量回满了" << endl;
            }
            else
                cout << "您的血量已达上限，不休要休息了" << endl;
        }
        else if(strcmp(word,"end") == 0) {
            endgame(2);break;
        }
        else if(flag)
            break;
        else
            cout << "您要干什么？" << endl;
    }
}
