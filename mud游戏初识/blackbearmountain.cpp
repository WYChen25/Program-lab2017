#include "Header.h"

bool npc1talk1 = false;
bool npc1talk2 = false;
bool insight = false;
void blackbear(XMLElement *root)
{
    //cout << "去你妈的敢来劳资光头强的地盘" << endl;
    XMLElement *map = root->FirstChildElement("map");
    XMLElement *scene = map->FirstChildElement("scene1");
    XMLElement *scene2 = scene->NextSiblingElement("scene2");
    XMLElement *scene3 = scene2->NextSiblingElement("scene3");
    XMLElement *scene4 = scene3->NextSiblingElement("scene4");
    const XMLAttribute *scenename3 = scene3->FirstAttribute();
    XMLElement *describtion3 = scene3->FirstChildElement("describtion3");
    const XMLAttribute *dis = describtion3->FirstAttribute();
    cout << scenename3->Name() << ":" << scenename3->Value() << '\n' << dis->Value() << endl;
    
    char word[20];
    while(1) {
        cin >> word;
        if(strcmp(word,"demand") == 0)
            checkrole();                                            //demand语句；
        else if(strcmp(word,"go") == 0) {
            const XMLAttribute *scenename1 = scene->FirstAttribute();
            const XMLAttribute *scenename2 = scene2->FirstAttribute();
            const XMLAttribute *scenename4 = scene4->FirstAttribute();
            const char *content1 = scenename1->Value();
            const char *content2 = scenename2->Value();
            const char *content3 = scenename3->Value();
            const char *content4 = scenename4->Value();
            char word2[20] = "\0";
            while(strcmp(word2,content1) != 0 && strcmp(word2, content2) != 0 && strcmp(word2,content3) !=0 && strcmp(word2,content4) != 0) {
                cin >> word2;
                if(strcmp(word2,content1) == 0) {
                    starttown(root);
                }
                else if(strcmp(word2,content2) == 0) {
                    greenground(root);
                }
                else if(strcmp(word2,content3) == 0) {
                    blackbear(root);
                }
                else if(strcmp(word2,content4) == 0) {
                    blacktree(root);
                }
                else {
                    cout << "您要去哪？" << endl;
                }
                if(flag)break;
            }
            if(flag)break;
        }                                                           // go语句
        else if(strcmp(word,"talk") == 0) {
            XMLElement *NPC1 = describtion3->NextSiblingElement("NPC1");
            XMLElement *NPC2 = NPC1->NextSiblingElement("NPC2");
            const XMLAttribute *npcname1 = NPC1->FirstAttribute();
            const char *name1 = npcname1->Value();
            const XMLAttribute *npcname2 = NPC2->FirstAttribute();
            const char *name2 = npcname2->Value();
            char word2[20] = "\0";
            while(strcmp(word2,name1) != 0 && strcmp(word2,name2) != 0) {
                cout << name1 << " " << name2 << endl;
                cin >> word2;
                if(strcmp(word2,name1) == 0) {
                    XMLElement *talk1 = NPC1->FirstChildElement("Talk1");
                    XMLElement *talk2 = talk1->NextSiblingElement("Talk2");
                    if(npc1talk1) {
                        const XMLAttribute *talk2c = talk2->FirstAttribute();
                        cout << talk2c->Value() << endl;
                        npc1talk2 = true;
                        //cout<< 1 << endl;
                    }
                    else{
                        const XMLAttribute *talk1c = talk1->FirstAttribute();
                        cout << talk1c->Value() << endl;
                        npc1talk1 = true;
                        //cout << 1 << endl;
                    }
                    break;
                        
                }
                else if(strcmp(word2,name2) == 0) {
                    XMLElement *talk0 = NPC2->FirstChildElement("Talk0");
                    XMLElement *talk1 = NPC2->FirstChildElement("Talk1");
                    XMLElement *talk2 = NPC2->FirstChildElement("Talk2");
                    if(npc1talk2 && !insight) {
                        const XMLAttribute *talk1c = talk1->FirstAttribute();
                        cout << talk1c->Value() << endl;
                        //cout << 1 << endl;
                    }
                    else if(insight) {
                        const XMLAttribute *talk2c = talk2->FirstAttribute();
                        cout << talk2c->Value() << endl;
                        look = true;
                        //cout << 1 << endl;
                    }
                    else {
                        const XMLAttribute *talk0c = talk0->FirstAttribute();
                        cout << talk0c->Value() << endl;
                        //cout << 1 << endl;
                    }
                    break;
                }
                else
                    cout << "你要和谁说话？" << endl;
                //cout << 2 << endl;
            }
            //cout << 3 << endl;
        }
        else if(strcmp(word,"end") == 0) {
            endgame(3);
        }
        else if(flag) {
            break;
        }
        else
            cout << "你要干什么？" << endl;
        //cout << 4 << endl;
        
    }
}
