//数组实现飞机空战
//内容：飞机的显示、单个敌机、多个敌机、发射常规子弹、发射闪弹
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

//画面尺寸
#define High 15
#define Width 25

#define EnemyNum 5  //敌人个数

//全局变量
int position_x, position_y;                 //飞机的位置
int enemy_x[EnemyNum], enemy_y[EnemyNum];   //敌人位置
//二维数组存储游戏画布中对应的元素
// 0 为空格，1 为飞机 * ，2 为子弹 | ，3 为敌人 @
int canvas[High][Width] = {0};              //默认空画布

int score;                      //得分
int BulletWidth;                //子弹宽度
int EnemyMoveSpeed;             //敌机移动速度

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
    //初始飞机位置
    position_x = High - 1;
    position_y = Width / 2;
    canvas[position_x][position_y] = 1;     //1表示飞机

    //随机位置生成 EnemyNum 个敌人
    int k;
    for (k = 0; k < EnemyNum; k++)
    {   
        //敌人只会出现在前两行
        enemy_x[k] = rand() % 2;
        enemy_y[k] = rand() % Width;
        canvas[enemy_x[k]][enemy_y[k]] = 3;   //3表示敌人
    }

    score = 0;
    BulletWidth = 0;
    EnemyMoveSpeed = 20;
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
    for (i = 0; i < High; i++)
    {
        for (j = 0; j < Width; j++)
        {
            if (canvas[i][j] == 0)
                printf(" ");    //输出空格
            if (canvas[i][j] == 1)
                printf("*");    //输出飞机*
            if (canvas[i][j] == 2)
                printf("|");    //输出子弹|
            if (canvas[i][j] == 3)
                printf("@");    //输出飞机@
        }
        printf("\n");
    }
    printf("Score: %d\n", score);
    Sleep(20);
}

//与用户输入无关的更新
void updateWithoutInput()
{   
    int i, j, k;
    for (i = 0; i < High; i++)
    {
        for (j = 0; j < Width; j++)
        {   
            //子弹位置
            if (canvas[i][j] == 2)
            {   
                for (k = 0; k < EnemyNum; k++)
                {
                    //子弹位置与敌机位置重合
                    if ((i == enemy_x[k]) && (j == enemy_y[k]))
                    {
                        score++;    //得分
                        //到达一定积分敌机速度加快
                        if (score % 5 == 0 && EnemyMoveSpeed > 3)
                            EnemyMoveSpeed--;
                        //子弹加粗
                        if (score % 10 == 0 && BulletWidth < 2)
                            BulletWidth++;
                        //射中后敌机消失
                        canvas[enemy_x[k]][enemy_y[k]] = 0;
                        //产生新的敌机
                        enemy_x[k] = rand() % 2;
                        enemy_y[k] = rand() % Width;
                        canvas[enemy_x[k]][enemy_y[k]] = 3;
                        //子弹消失
                        canvas[i][j] = 0;
                    }
                }
                //子弹向上移动，当前位置变为0，上一个位置变为2(子弹)
                canvas[i][j] = 0;
                if (i > 0)
                    canvas[i - 1][j] = 2;
            }
        }
    }

    static int speed = 0;
    if (speed < EnemyMoveSpeed)
        speed++;

    for (k = 0; k < EnemyNum; k++)
    {   
        //自己撞到敌机，游戏结束
        if ((position_x == enemy_x[k]) && (position_y == enemy_y[k]))
        {
            printf("Game Over!\n");
            Sleep(3000);
            system("pause");
            exit(0);
        }
        //敌机跑出显示屏
        if (enemy_x[k] > High)
        {
            canvas[enemy_x[k]][enemy_y[k]] = 0;
            //产生新的敌机
            enemy_x[k] = rand() % 2;
            enemy_y[k] = rand() % Width;
            canvas[enemy_x[k]][enemy_y[k]] = 3;
            score--;    //减分
        }

        //根据前边的函数，得分越多，敌机下落需要的步数越少，下落就加快了
        if (speed == EnemyMoveSpeed)
        {
            //敌机下落
            for (k = 0; k < EnemyNum; k++)
            {
                canvas[enemy_x[k]][enemy_y[k]] = 0;
                enemy_x[k]++;
                speed = 0;
                canvas[enemy_x[k]][enemy_y[k]] = 3;
            }
        }
    }
}

//与用户输入有关的更新
void updateWithInput()
{
    char input;
    if (kbhit())                //判断是否有输入
    {
        input = getch();        //不用回车读取用户输入
        //位置左移
        if (input == 'a' && position_y > 0)
        {
            canvas[position_x][position_y] = 0;
            position_y--;       
            canvas[position_x][position_y] = 1;
        }
        //位置右移
        else if (input == 'd' && position_y > 0)
        {
            canvas[position_x][position_y] = 0;
            position_y++;       
            canvas[position_x][position_y] = 1;
        }
        //位置上移
        else if (input == 'w')
        {
            canvas[position_x][position_y] = 0;
            position_x--;       
            canvas[position_x][position_y] = 1;
        }
        //位置下移
        else if (input == 's')
        {
            canvas[position_x][position_y] = 0;
            position_x++;
            canvas[position_x][position_y] = 1;
        }
        //发射子弹
        else if (input == ' ')
        {   
            //子弹的范围
            int left = position_y - BulletWidth;
            int right = position_y + BulletWidth;
            //子弹不超边界
            if (left < 0)
                left = 0;
            if (right > Width - 1)
                right = Width - 1;
            int k;
            //发射子弹的初始位置在飞机的正上方
            for (k = left; k <= right; k++)
                canvas[position_x - 1][k] = 2;
        }
    }
}