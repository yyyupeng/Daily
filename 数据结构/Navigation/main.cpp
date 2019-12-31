#include <iostream>
#include "user.h"
#include "map.h"

int login_menu();
void Menu();
void Search_menu();
int get_choice(char *);

user U;
map G;

int main()
{
    if(login_menu() == 0)
        return 0;
    G.CreatALGraph(G);
    Menu();
    G.DeleteEdge(G);

    return 0;
}

//登陆菜单
int login_menu()
{
    char choice_s[100];
    int choice;
    do
    {
        printf("\n\t\t\e[1;32m-----------------------------------\e[0m\n");
        printf("\t\t\e[1;32m|\e[0m              1.登陆             \e[1;32m|\e[0m\n");
        printf("\t\t\e[1;32m-----------------------------------\e[0m\n");
        printf("\t\t\e[1;32m|\e[0m              2.注册             \e[1;32m|\e[0m\n");
        printf("\t\t\e[1;32m-----------------------------------\e[0m\n");
        printf("\t\t\e[1;32m|\e[0m              0.退出             \e[1;32m|\e[0m\n");
        printf("\t\t\e[1;32m-----------------------------------\e[0m\n");
        printf("\t\t请选择：");
        scanf("%s",choice_s);
        choice = get_choice(choice_s);

        switch(choice)
        {
        case 1:
            if(U.login() == 1)
                return 1;
            break;
        case 2:
            U.registe();
            break;
        default:
            break;
        }
    }while(choice != 0);
    return 0;
}

//主菜单
void Menu()
{
    char choice_s[100];
    int choice;
    std::string name, nname;
    int w;
    VertexNode N;
    bzero(&N,sizeof(N));
    do
    {
        printf("\n\t\t\e[1;32m-----------------------------------\e[0m\n");
        printf("\t\t\e[1;32m|\e[0m     欢迎使用西邮长安校区导航    \e[1;32m|\e[0m\n");
        printf("\t\t\e[1;32m-----------------------------------\e[0m\n");
        printf("\t\t\e[1;32m|\e[0m            1.查询路径           \e[1;32m|\e[0m\n");
        printf("\t\t\e[1;32m-----------------------------------\e[0m\n");
        printf("\t\t\e[1;32m|\e[0m            2.总览信息           \e[1;32m|\e[0m\n");
        printf("\t\t\e[1;32m-----------------------------------\e[0m\n");
        printf("\t\t\e[1;32m|\e[0m            3.增添地点           \e[1;32m|\e[0m\n");
        printf("\t\t\e[1;32m-----------------------------------\e[0m\n");
        printf("\t\t\e[1;32m|\e[0m            4.修改地点           \e[1;32m|\e[0m\n");
        printf("\t\t\e[1;32m-----------------------------------\e[0m\n");
        printf("\t\t\e[1;32m|\e[0m            5.查询地点           \e[1;32m|\e[0m\n");
        printf("\t\t\e[1;32m-----------------------------------\e[0m\n");
        printf("\t\t\e[1;32m|\e[0m            6.增添道路           \e[1;32m|\e[0m\n");
        printf("\t\t\e[1;32m-----------------------------------\e[0m\n");
        printf("\t\t\e[1;32m|\e[0m            7.撤销道路           \e[1;32m|\e[0m\n");
        printf("\t\t\e[1;32m-----------------------------------\e[0m\n");
        printf("\t\t\e[1;32m|\e[0m            0.注销               \e[1;32m|\e[0m\n");
        printf("\t\t\e[1;32m-----------------------------------\e[0m\n");
        printf("\t\t请选择：");
        scanf("%s",choice_s);
        choice = get_choice(choice_s);
        
        switch(choice)
        {
        case 1:
            Search_menu();
            break;

        case 2:
            G.show(G);
            break;
           
        case 3:
            std::cout << "\t\t" << "请输入新增地点信息." << std::endl;
            std::cout << "\t\t" << "名称：";
            std::cin >> N.name;
            std::cout << "\t\t" << "坐标：";
            std::cin >> N.x >> N.y;
            std::cout << "\t\t" << "信息：";
            std::cin >> N.info;
            G.AddPlace(G, N);
            break;

        case 4:
            std::cout << "\t\t" << "请输入要修改地点名称：";
            std::cin >> name;
            G.RevPlace(G, name);
            break;

        case 5:
            std::cout << "\t\t" << "请输入要查询地点名称：";
            std::cin >> name;
            G.SearchPlace(G, name);
            break;

        case 6:
            std::cout << "\t\t" << "请输入新增道路信息." << std::endl;
            std::cout << "\t\t" << "地点1：";
            std::cin >> name;
            std::cout << "\t\t" << "地点2：";
            std::cin >> nname;
            std::cout << "\t\t" << "长度：";
            std::cin >> w;
            G.AddRoad(G, name, nname, w);
            break;

        case 7:
            std::cout << "\t\t" << "请输入要撤销道路信息." << std::endl;
            std::cout << "\t\t" << "地点1：";
            std::cin >> name;
            std::cout << "\t\t" << "地点2：";
            std::cin >> nname;
            G.DelRoad(G, name, nname);
            break;

        default:
            break;
        }
    }while(choice != 0);
}

void Search_menu()
{
    char choice_s[100];
    int choice;
    std::string name, nname;
    do
    {
        printf("\n\t\t\e[1;32m---------------------------------------\e[0m\n");
        printf("\t\t\e[1;32m|\e[0m            ***路径查询***           \e[1;32m|\e[0m\n");
        printf("\t\t\e[1;32m---------------------------------------\e[0m\n");
        printf("\t\t\e[1;32m|\e[0m            1.所有简单路径           \e[1;32m|\e[0m\n");
        printf("\t\t\e[1;32m---------------------------------------\e[0m\n");
        printf("\t\t\e[1;32m|\e[0m            2.最短简单路径           \e[1;32m|\e[0m\n");
        printf("\t\t\e[1;32m---------------------------------------\e[0m\n");
        printf("\t\t\e[1;32m|\e[0m            3.最佳访问路径           \e[1;32m|\e[0m\n");
        printf("\t\t\e[1;32m---------------------------------------\e[0m\n");
        printf("\t\t\e[1;32m|\e[0m            0.返回                   \e[1;32m|\e[0m\n");
        printf("\t\t\e[1;32m---------------------------------------\e[0m\n");

        printf("\t\t请选择：");
        scanf("%s",choice_s);
        choice = get_choice(choice_s);

        switch(choice)
        {
        case 1:
            std::cout << "\t\t" << "起始地点：";
            std::cin >> name;
            std::cout << "\t\t" << "目标地点：";
            std::cin >> nname;
            G.SearchAllDfs(G, name, nname);
            break;

        case 2:
            std::cout << "\t\t" << "起始地点：";
            std::cin >> name;
            std::cout << "\t\t" << "目标地点：";
            std::cin >> nname;
            G.SearchShortBfs(G, name, nname);
            break;

        case 3:
            std::cout << "\t\t" << "起始地点：";
            std::cin >> name;
            std::cout << "\t\t" << "目标地点：";
            std::cin >> nname;
            G.Dijkstra(G, name, nname);
            break;

        default:
            break;
        }
    }while(choice != 0);
}

//为避免输入时出现的意外错误，进行字符串解析
int get_choice(char *choice_t)
{
    int choice = 0;
    for(int i = 0; i < strlen(choice_t); i++)
        if(choice_t[i] < '0' || choice_t[i] > '9')
            return -1;
    for(int i = 0; i < strlen(choice_t); i++)
    {
        int t = 1;
        for(int j = 1; j < strlen(choice_t) - i; j++)
        {
            t *= 10;
        }
        choice += t*(int)(choice_t[i] - 48);
    }
    return choice;
}

