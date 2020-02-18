//FlappyBird的简单实现
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

//全局变量
int high, width;                        //游戏画面大小
int bird_x, bird_y;                     //小鸟的坐标
int bar1_y, bar1_xDown, bar1_xTop;      //障碍物
int score;                              //得分

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
    high = 15;
    width = 20;

    bird_x = high / 2;
    bird_y = width / 3;

    //墙的参数
    bar1_y = width / 2;
    bar1_xDown = high / 3;
    bar1_xTop = high / 2;

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
            if ((i == bird_x) && (j == bird_y))
                printf("@");    //输出小鸟
            else if ((j == bar1_y) && ((i < bar1_xDown) || (i > bar1_xTop)))
                printf("*");    //输出墙壁
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
    //小鸟慢慢下落
    bird_x++;
    //墙壁移动
    bar1_y--;
    //判断得分
    if (bird_y == bar1_y)
    {
        if ((bird_x >= bar1_xDown) && (bird_x <= bar1_xTop))
            score++;
        else
        {   
            //退出游戏
            printf("Game Over\n");
            system("pause");
            exit(0);
        }
    }
    //重新随机生成障碍物
    if (bar1_y <= 0)
    {
        bar1_y = width;
        int temp = rand() % (int)(high * 0.8);
        bar1_xDown = temp - high / 10;
        bar1_xTop = temp + high / 10;
    }

    Sleep(150);
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
            //空格就向上跳
            case ' ':
                bird_x = bird_x - 2;
                break;
        }
    } 
}