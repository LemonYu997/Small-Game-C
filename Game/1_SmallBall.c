//控制台实现  《弹跳小球》
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

//在坐标(x, y)处输出一个小球
int main()
{
    int i, j;
    int x = 1;
    int y = 10;

    //小球的速度，用x和y方向实现斜向弹跳
    int velocity_x = 1;
    int velocity_y = 1;

    //边界，调整边界使小球
    int left = 0;
    int right = 30;
    int top = 0;
    int bottom = 10;

    //改变小球坐标，让小球下落
    while (1)
    {   
        //更新小球的位置，旧位置+速度
        x = x + velocity_x;
        y = y + velocity_y;
        system("cls");          //清屏函数，头文件在stdlib.h中
        
        //输出小球上面的空行
        for (i = 0; i < x; i++)
            printf("\n");
    
        //输出小球左边的空格
        for (j = 0; j < y; j++)
            printf(" ");
        
        //输出一个小球，用o表示
        printf("o");
        printf("\n");

        //等待50毫秒，从而控制小球弹跳速度 头文件在windows.h中
        Sleep(50);

        if ((x == top) || (x == bottom))         //到达边界时改变方向
            velocity_x = -velocity_x;
        if ((x == left) || (y == right))
            velocity_y = -velocity_y;
    }
        
    return 0;
}