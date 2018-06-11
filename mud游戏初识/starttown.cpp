#include "Header.h"

void starttown(XMLElement *root)
{
    XMLElement *map = root->FirstChildElement("map");
    XMLElement *scene = map->FirstChildElement("scene1");
    const XMLAttribute *scenename = scene->FirstAttribute();
    XMLElement *des = scene->FirstChildElement("describtion");
    //cout << des << endl;
    const XMLAttribute *attributeOfsurface = des->FirstAttribute();
    cout<<scenename->Name()<< ":" << scenename->Value() << ":" <<'\n'<< attributeOfsurface-> Value() << endl;
    char word[20];
    while(1) {
        cin >> word;
        if(strcmp(word,"talk") == 0){
            XMLElement *NPC = des->NextSiblingElement("NPC");
            const XMLAttribute *npc1 = NPC->FirstAttribute();
            const char* content = npc1->Value();
            cout << content <<":"<< endl;
            char word2[20] = "\0";
            while(strcmp(word2,content) != 0) {
                cin >> word2;
                if(strcmp(word2,content) == 0 && !silaimuflag) {
                    XMLElement *talk = NPC->FirstChildElement("talk1");
                    const XMLAttribute *mastertalk = talk->FirstAttribute();
                    cout << mastertalk->Value() << endl;
                }
                else if(strcmp(word2,content) == 0 && silaimuflag) {
                    XMLElement *talk = NPC->FirstChildElement("talk1");
                    XMLElement *talk2 = talk->NextSiblingElement("talk2");
                    const XMLAttribute *mastertalk2 = talk2->FirstAttribute();
                    cout << mastertalk2->Value() << endl;
                }
                else
                    cout << "抱歉，您要和谁说话？" << endl;
            }
        }
        else if(strcmp(word,"go") == 0) {
            XMLElement *scene2 = scene->NextSiblingElement("scene2");
            //cout << scene2 << endl;
            const char *content1 = scenename->Value();
            const XMLAttribute *scenename2 = scene2->FirstAttribute();
            const char *content2 = scenename2->Value();
            //cout << content2;
            
            XMLElement *scene3 = scene2->NextSiblingElement("scene3");
            const XMLAttribute *scenename3 = scene3->FirstAttribute();
            const char *content3 = scenename3->Value();
            
            XMLElement *scene4 = scene3->NextSiblingElement("scene4");
            const XMLAttribute *scenename4 = scene4->FirstAttribute();
            const char *content4 = scenename4->Value();
            char word2[20] = "\0";
            while(strcmp(word2,content2) != 0 && strcmp(word2, content1) != 0 && strcmp(word2, content3) != 0 && strcmp(word,content4) != 0) {
                cin >> word2;
                if(strcmp(word2,content2) == 0) {
                    greenground(root);
                    if(flag == true) {
                        break;
                    }
                }
                else if(strcmp(word2,content1) == 0) {
                    starttown(root);
                }
                else if(strcmp(word2,content3) == 0) {
                    blackbear(root);
                }
                else if(strcmp(word2,content4) == 0) {
                    blacktree(root);
                }
                else if(flag == true) {
                    break;
                }
                else
                    cout << "您要去哪？" << endl;
                if(flag)break;
            }
            if(flag == true)
                break;
        }
        else if(strcmp(word,"demand") == 0) {
            checkrole();
        }
        else if(strcmp(word,"end") == 0) {
            endgame(1);break;
        }
        else if(flag == true)
            break;
        else
            cout << "抱歉，我不懂你在说什么" << endl;
    }

}
