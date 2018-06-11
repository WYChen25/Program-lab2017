#include "Header.h"


bool look = false;
void blacktree(XMLElement *root)
{
    XMLElement *map = root->FirstChildElement("map");
    XMLElement *scene = map->FirstChildElement("scene1");
    XMLElement *scene2 = scene->NextSiblingElement("scene2");
    XMLElement *scene3 = scene2->NextSiblingElement("scene3");
    XMLElement *scene4 = scene3->NextSiblingElement("scene4");
    const XMLAttribute *scenename4 = scene4->FirstAttribute();
    XMLElement *describtion4 = scene4->FirstChildElement("describtion4");
    const XMLAttribute *dis = describtion4->FirstAttribute();
    XMLElement *describtion5 = describtion4->NextSiblingElement("describtion5");
    const XMLAttribute *dis2 = describtion5->FirstAttribute();
    XMLElement *monster = describtion5->NextSiblingElement("monster");
    cout << scenename4->Name() << ":" << scenename4->Value() << '\n' << dis->Value() << endl;
    // delay_sec(5);
    cout << dis2->Value() << endl;
    char word[20];
    while(1) {
        cin >> word;
        if(strcmp(word,"demand") == 0)
            checkrole();
        else if(strcmp(word,"go") == 0){
            const XMLAttribute *scenename1 = scene->FirstAttribute();
            const XMLAttribute *scenename2 = scene2->FirstAttribute();
            const XMLAttribute *scenename3 = scene3->FirstAttribute();
            const char *content1 = scenename1->Value();
            const char *content2 = scenename2->Value();
            const char *content3 = scenename3->Value();
            const char *content4 = scenename4->Value();
            cout << content1 << " " << content2 << " " << content3 <<" " << content4 << endl;
            char word2[20] = "\0";
            cin >> word2;
                if(strcmp(word2,content1) == 0) {
                    starttown(root);
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
            if(flag)break;
        }
        else if(strcmp(word,"look") == 0) {
            const XMLAttribute *boss = monster->FirstAttribute();
            XMLElement *talk = monster->FirstChildElement("Talk");
            const XMLAttribute *talkc = talk->FirstAttribute();
            cout << boss->Name() << ":" << boss->Value() << endl;
            cout << talkc->Value() << endl;
            insight = true;
        }
        else if(strcmp(word,"attack") == 0) {
            const XMLAttribute *boss = monster->FirstAttribute();
            const char *content = boss->Value();
            char word2[20] = "\0";
            cin >> word2;
            cout << content << endl;
            if(strcmp(word2,content) == 0) {
                if(look) {
                    cout << "您靠着天下无敌的假猪套打败了穿着万世铁马幽魂魔战套的[光头强]" <<endl;
                }
                else {
                    cout <<"您被光头强打败了，找熊二想想办法吧" << endl;
                }
            }
            else {
                cout << "您要打谁？" << endl;
            }
        }
        else if(strcmp(word,"end") == 0) {
            endgame(4);break;
        }
        else if(flag)break;
        else
            cout << "你要干什么？" << endl;
    }
}
