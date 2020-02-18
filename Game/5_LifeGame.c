//生命游戏
//假设有int Cells[30][30]，也即有30×30个小格子，每个小格子里面可以有细胞生命，
//或者细胞死亡。通过把这些状态输出出来，就可以显示出相应的图案。

/*
生命游戏演化的规则：
每个矩阵方格可以包含一个有机体，不在边上的有机体有8个相邻方格。
1． 如果一个细胞周围有3个细胞为生，则该细胞为生
（即该细胞若原先为死，则转为生，若原先为生，则保持不变）
2． 如果一个细胞周围有2个细胞为生，则该细胞的生死状态保持不变
3． 在其它情况下，该细胞为死（即该细胞若原先为生，则转为死，若原先为死，则保持不变）
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

//游戏画面尺寸
#define High 25
#define Width 50

//全局变量
//所有细胞生1或死0
int cells[High][Width];

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
    int i, j;
    srand((unsigned)time(NULL));    //随机数种子
    //随机初始化
    for (i = 0; i < High; i++)
    {
        for (j = 0; j < Width; j++)
        {   
            //用2取余使结果只有1（生）和0（死）
            cells[i][j] = rand() % 2;
        }
    }
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
    for (i = 0; i <= High; i++)
    {
        for (j = 0; j <= Width; j++)
        {
            if (cells[i][j] == 1)
                printf("*");    //输出活细胞
            else
                printf(" ");    //输出死细胞
        }
        printf("\n");
    }
    Sleep(50);
}


//与用户输入无关的更新
void updateWithoutInput()
{   
    //下一帧的细胞情况
    int NewCells[High][Width];
    int NeibourNumber;           //统计邻居的个数
    int i, j;
    for (i = 1; i <= High - 1; i++)
    {
        for (j = 1; j <= Width - 1; j++)
        {   
            //把周围八个邻居的值相加得邻居存活个数
            NeibourNumber = cells[i-1][j-1] + cells[i-1][j] + cells[i-1][j+1] + cells[i][j-1] + cells[i][j+1] + cells[i+1][j-1] + cells[i+1][j] + cells[i+1][j+1];
            //如果一个细胞周围有3个细胞为生，则该细胞为生
            if (NeibourNumber == 3)
                NewCells[i][j] = 1;
            //如果一个细胞周围有2个细胞为生，则该细胞的生死状态保持不变
            else if (NeibourNumber == 2)
                NewCells[i][j] = cells[i][j];
            //在其它情况下，该细胞为死
            else
                NewCells[i][j] = 0;
        }
    }
    //更新界面
    for (i = 1; i <= High - 1; i++)
        for (j = 1; j <= Width; j++)
            cells[i][j] = NewCells[i][j];
}

//与用户输入有关的更新
void updateWithInput()
{

}