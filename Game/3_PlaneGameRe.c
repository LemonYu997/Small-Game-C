//对2的飞机游戏进行函数式重构
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

//全局变量
int position_x, position_y;     //飞机的位置
int bullet_x, bullet_y;         //子弹位置
int enemy_x, enemy_y;           //敌人位置
int high, width;                //游戏画面尺寸
int score;                      //得分

void startup();
void gotoxy(int x, int y);
void HideCursor(); 
void show();
void updateWithoutInput();
void updateWithInput();    

//框架
int main()
{
    startup();                  //数据初始化
    while (1)
    {
        show();                 //显示画面
        updateWithoutInput();   //与用户输入无关的更新
        updateWithInput();      //与用户输入有关的更新
    }
}

//数据初始化
void startup()
{
    high = 20;
    width = 30;
    position_x = high / 2;
    position_y = width / 2;
    bullet_x = 0;
    bullet_y = position_y;
    enemy_x = 0;
    enemy_y = position_y;
    score = 0;
}

//类似清屏函数，光标移动到原点进行重画
void gotoxy(int x, int y)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle, pos);
}

//清除光标的函数
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
    //隐藏输入符号
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

//显示画面
void show()
{
    gotoxy(0, 0);               //光标移动到原点进行重画清屏，解决cls的闪屏问题
    HideCursor();               //清除光标显示
    system("color f0");         //改变控制台背景色，f表示背景色为白色，0表示文本（前景）色为黑色
    int i, j;
    for (i = 0; i < high; i++)
    {
        for (j = 0; j < width; j++)
        {
            if ((i == position_x) && (j == position_y))
                printf("*");    //输出飞机
            else if ((i == enemy_x) && (j == enemy_y))
                printf("+");    //输出敌人
            else if ((i == bullet_x) && (j == bullet_y))
                printf("|");    //输出子弹
            else
                printf(" ");    //输出空格
        }
        printf("\n");
    }
    printf("Score: %d\n", score);
}

//与用户输入无关的更新
void updateWithoutInput()
{   
    //子弹向上射出
    if (bullet_x > -1)
        bullet_x--;
    
    //判断子弹是否集中敌军
    if ((bullet_x == enemy_x) && (bullet_y == enemy_y))
    {
        score++;                //分数+1
        //产生新的飞机，随机位置
        enemy_x = -1;           
        enemy_y = rand() % width;
        bullet_x = -2;          //子弹无效
    }
    //敌机跑出显示屏幕
    if (enemy_x > high)
    {   
        //产生新的飞机
        enemy_x = -1;
        enemy_y = rand() % width;
    }

    //用来控制敌机乡下移动的速度，每隔计次循环，才移动一次敌机
    //用这样的方式修改，用户按键交互速度仍然很快，但敌人的移动可以降速
    static int speed = 0;
    if (speed < 10)
        speed++;
    if (speed == 10)
    {
        enemy_x++;
        speed = 0;
    }
}

//与用户输入有关的更新
void updateWithInput()
{
    char input;
    if (kbhit())                //判断是否有输入
    {
        input = getch();        //不用回车读取用户输入
        switch (input)
        {
            case 'a':
                position_y--;
                break;
            case 'd':
                position_y++;
                break;
            case 'w':
                position_x--;
                break;
            case 's':
                position_x++;
                break;
            case ' ':
                //发射子弹的初始位置在飞机正上方
                bullet_x = position_x - 1;
                bullet_y = position_y;
                break;
        }
    }
}