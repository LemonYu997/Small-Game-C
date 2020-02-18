//一个简单的飞机游戏
//内容：飞机显示、控制移动、发射子弹、击中敌机等
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

int main()
{   
    //利用scanf输入不同的字符，asdw控制飞机 * 上下左右移动
    int i, j;
    int x = 10;
    int y = 20;
    char input;
    int isFire = 0;         //判断飞机是否处于会发射子弹的状态

    //靶子
    int target = 5;         //放在第一行，第5列上
    int target_v = 1;       //靶子移动速度
    int isKilled = 0;       //是否命中靶子

    while (1)
    {
        system("cls");      //清屏函数
        
        //生成靶子
        if (!isKilled)
        {   
            //移动靶子
            target = target + target_v;
            if ((target == 20) || (target == 5))
                target_v = -target_v;

            for (j = 0; j < target; j++)
                printf(" ");
            printf("+\n");  //用+表示靶子
        }
        //没有开火时
        if (isFire == 0)
        {
            //输出飞机上面的空行
            for (i = 0; i < x; i++)
                printf("\n"); 
        }
        //输出飞机上面的激光竖线
        else            
        {
            for (i = 0; i < x; i++)
            {
                for (j = 0; j < y; j++)
                {
                    for (j = 0; j < y; j++)
                        printf(" ");
                    printf("  |\n");
                }
                //击中靶子
                if (y + 2 == target)
                    isKilled = 1;    
                isFire = 0;
            }
        }
        
        //输出一个复杂的飞机
        for (j = 0; j < y; j++)
            printf(" ");
        printf("  *\n");
        for (j = 0; j < y; j++)
            printf(" ");
        printf("*****\n");
        for (j = 0; j < y; j++)
            printf(" ");
        printf(" * * \n");

        //根据用户的不同输入来移动
        if (kbhit())        //判断是否有输入
        {   
            //根据用户的不同输入来移动，不需要回车
            input = getch();
            switch (input)
            {
                case 'a':
                    y--;
                    break;
                case 'd':
                    y++;
                    break;
                case 'w':
                    x--;
                    break;
                case 's':
                    x++;
                    break;
                case ' ':
                    isFire = 1;
                    break;
            }        
        }

        //输出结果
        if (isKilled == 1)
            printf("You are win!");
    }
}
