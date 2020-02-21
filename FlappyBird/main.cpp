// 利用EasyX重构Flappy Bird游戏
// 画面大小350*600
// 鸟的大小100*70
// 柱子宽处宽度140，窄处宽度100，宽处厚度30，绿色

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <graphics.h>

//引用Windows Multimedia API
#pragma comment(lib, "Winmm.lib")

//相关函数
void print();
void begin();
void printstone();				//柱子
void bird();					//控制鸟的上升和下降
void judgement();				//判断语句
void scoleprint();
void endorretry();

//全局变量
int bird_x = 150, bird_y = 300;	//鸟的初始坐标
int i = 0, k = 0, t = 0;
int scole = 0;					//得分
int stone_x1, stone_y1;			//上半截柱子的左下点坐标
int stone_x2, stone_y2;			//下半截柱子的左下点坐标
int non;

//图片储存变量
IMAGE backgrand, bird1[4], bird2[4], scole1[10], scole2[10];
IMAGE stone_up1, stone_up2, stone_down1, stone_down2;
IMAGE stone_up3, stone_up4, stone_down3, stone_down4;

//定义鼠标消息
MOUSEMSG m;

int main()
{	
	//t判断游戏是否开始
	if (t == 0)
	{
		begin();
		t++;
	}

	if (t)
		print();
	_getch();					//制造停顿
	bird_y = 300;
	bird_x = 150;
	i = 0;
	k = 0;
	scole = 0;

	while (1)
	{
		bird();
		print();
		judgement();
	}
	closegraph();

	return 0;
}

void print()
{
	//背景图像
	putimage(0, 0, &backgrand);
	printstone();				//画柱子
	putimage(bird_x, bird_y, &bird1[i % 3], NOTSRCERASE);
	putimage(bird_x, bird_y, &bird2[i % 3], SRCINVERT);
	if (k % 5 == 0)
		i++;
	k++;
	scoleprint();
	FlushBatchDraw();			//绘制
}

//柱子移动规律
void printstone()
{
	Sleep(30);
	//此时画面存在两根柱子
	if (stone_x1 > 210)			
	{
		putimage(stone_x1, stone_y1, &stone_up2, NOTSRCERASE);
		putimage(stone_x1, stone_y1, &stone_up1, SRCINVERT);
		putimage(stone_x1, stone_y1 + 750, &stone_down2, NOTSRCERASE);
		putimage(stone_x1, stone_y1 + 750, &stone_down1, SRCINVERT);
		putimage(stone_x2, stone_y2, &stone_up4, NOTSRCERASE);
		putimage(stone_x2, stone_y2, &stone_up3, SRCINVERT);
		putimage(stone_x2, stone_y2 + 750, &stone_down4, NOTSRCERASE);
		putimage(stone_x2, stone_y2 + 750, &stone_down3, SRCINVERT);
		stone_x1--;
		stone_x2--;
	}
	//左柱子消失，将stone_x2, stone_y2值归位
	else if (stone_x1 == 210)	
	{
		stone_x2 = stone_x1;
		stone_y2 = stone_y1;
		putimage(stone_x1, stone_y1, &stone_up2, NOTSRCERASE);
		putimage(stone_x1, stone_y1, &stone_up1, SRCINVERT);
		putimage(stone_x1, stone_y1 + 750, &stone_down2, NOTSRCERASE);
		putimage(stone_x1, stone_y1 + 750, &stone_down2, SRCINVERT);
		stone_x1--;
		stone_x2--;
	}
	//画面只存在一根柱子的情况
	else if (stone_x1 < 210 && stone_x1 > 0)
	{
		putimage(stone_x1, stone_y1, &stone_up2, NOTSRCERASE);
		putimage(stone_x1, stone_y1, &stone_up1, SRCINVERT);
		putimage(stone_x1, stone_y1 + 750, &stone_down2, NOTSRCERASE);
		putimage(stone_x1, stone_y1 + 750, &stone_down1, SRCINVERT);
		stone_x1--;
		stone_x2--;
	}
	//柱子左端到站，生成新柱子
	if (stone_x1 == 0)
	{
		stone_y1 = rand() % 310 - 555;
		stone_x1 = 350;
		putimage(stone_x1, stone_y1, &stone_up2, NOTSRCERASE);
		putimage(stone_x1, stone_y1, &stone_up1, SRCINVERT);
		putimage(stone_x1, stone_y1 + 750, &stone_down2, NOTSRCERASE);
		putimage(stone_x1, stone_y1 + 750, &stone_down1, SRCINVERT);
		stone_x1--;
		stone_x2--;
	}
}

void begin()
{	
	//背景音乐
	mciSendString("open \"sounds\\bgm.mp3\" alias music ", NULL, 0, NULL);
	mciSendString("play music", NULL, 0, NULL);
	//画面窗口
	initgraph(350, 600);
	//获取窗口句柄
	HWND hwnd = GetHWnd();
	//设置窗口标题文字
	SetWindowText(hwnd, "yujian study");
	IMAGE beforegame;
	loadimage(&beforegame, "image\\beforegame.jpg");
	putimage(0, 0, &beforegame);
	Sleep(1000);
	_getch();
	//开启批量绘图摸屎
	BeginBatchDraw();
	//载入背景图片
	loadimage(&backgrand, "image\\backgroundfd.jpg");
	//鸟
	loadimage(&bird2[0], "image\\bird1-2.gif");
	loadimage(&bird1[0], "image\\bird1-1.gif");
	loadimage(&bird2[1], "image\\bird2-2.gif");
	loadimage(&bird1[1], "image\\bird2-1.gif");
	loadimage(&bird2[2], "image\\bird3-2.gif");
	loadimage(&bird1[2], "image\\bird3-1.gif");
	loadimage(&bird2[3], "image\\bird4-2.gif");
	loadimage(&bird1[3], "image\\bird4-1.gif");
	//柱子
	loadimage(&stone_up1, "image\\stone_up1.gif");
	loadimage(&stone_up2, "image\\stone_up2.gif");
	loadimage(&stone_down1, "image\\stone_down1.gif");
	loadimage(&stone_down2, "image\\stone_down2.gif");
	loadimage(&stone_up3, "image\\stone_up1.gif");
	loadimage(&stone_up4, "image\\stone_up2.gif");
	loadimage(&stone_down3, "image\\stone_down1.gif");
	loadimage(&stone_down4, "image\\stone_down2.gif");
	//数字
	loadimage(&scole1[0], "image\\0_1.jpg");
	loadimage(&scole2[0], "image\\0_2.jpg");
	loadimage(&scole1[1], "image\\1_1.jpg");
	loadimage(&scole2[1], "image\\1_2.jpg");
	loadimage(&scole1[2], "image\\2_1.jpg");
	loadimage(&scole2[2], "image\\2_2.jpg");
	loadimage(&scole1[3], "image\\3_1.jpg");
	loadimage(&scole2[3], "image\\3_2.jpg");
	loadimage(&scole1[4], "image\\4_1.jpg");
	loadimage(&scole2[4], "image\\4_2.jpg");
	loadimage(&scole1[5], "image\\5_1.jpg");
	loadimage(&scole2[5], "image\\5_2.jpg");
	loadimage(&scole1[6], "image\\6_1.jpg");
	loadimage(&scole2[6], "image\\6_2.jpg");
	loadimage(&scole1[7], "image\\7_1.jpg");
	loadimage(&scole2[7], "image\\7_2.jpg");
	loadimage(&scole1[8], "image\\8_1.jpg");
	loadimage(&scole2[8], "image\\8_2.jpg");
	loadimage(&scole1[9], "image\\9_1.jpg");
	loadimage(&scole2[9], "image\\9_2.jpg");
	//初始化种子
	srand(time(0));
	print();
	//第一根柱子，初始化
	stone_y1 = rand() % 310 - 555;
	stone_x1 = 350;
	stone_x2 = stone_y2 = -9999;
}

void bird()
{
	char space;

	//读取空格
	if (_kbhit())
	{
		space = _getch();
		if (space == ' ')
		{
			bird_y -= 80;
		}
		else if (space == 27)
			_getch();
	}
	else
	{
		bird_y += 3;
	}
	while (MouseHit())
	{
		//获取第一条鼠标消息
		m = GetMouseMsg();
		switch (m.uMsg)
		{
			case WM_LBUTTONDOWN:
				bird_y -= 80;
				break;
			case WM_RBUTTONDOWN:
				_getch();
				break;
		}
	}
}


void judgement()
{	
	//结束游戏
	if ((stone_x1 > 10 && stone_x1 < 20) || (stone_x1 > 174 && stone_x1 < 184))
	{	
		if ((bird_y > (stone_y1 + 576) && bird_y < (stone_y1 + 600)) || ((bird_y > (stone_y1 + 726)) && bird_y < (stone_y1 + 750)))
			endorretry();
	}
	else if (stone_x1 >= 20 && stone_x1 <= 174)
	{
		if (!(bird_y > (stone_y1 + 600) && bird_y < (stone_y1 + 726)))
			endorretry();
	}
	if (bird_y > 576)
		endorretry();
	//得分
	if (stone_x1 == 150)
		scole++;
}

void endorretry()
{
	if (bird_y < 550 && stone_x1>160)
	{
		while (bird_y < 550)
		{
			//背景图像
			putimage(0, 0, &backgrand);
			putimage(stone_x1, stone_y1, &stone_up2, NOTSRCERASE);
			putimage(stone_x1, stone_y1, &stone_up1, SRCINVERT);
			putimage(stone_x1, stone_y1 + 750, &stone_down2, NOTSRCERASE);
			putimage(stone_x1, stone_y1 + 750, &stone_down1, SRCINVERT);
			putimage(stone_x2, stone_y2, &stone_up4, NOTSRCERASE);
			putimage(stone_x2, stone_y2, &stone_up3, SRCINVERT);
			putimage(stone_x2, stone_y2 + 750, &stone_down4, NOTSRCERASE);
			putimage(stone_x2, stone_y2 + 750, &stone_down3, SRCINVERT);
			putimage(bird_x, bird_y, &bird1[3], NOTSRCERASE);
			putimage(bird_x, bird_y, &bird2[3], SRCINVERT);
			FlushBatchDraw();
			bird_y++;
		}
	}
	IMAGE gameover1, gameover2, atlast;
	loadimage(&gameover1, "image\\gameover1.gif");
	loadimage(&gameover2, "image\\gameover2.gif");
	putimage(80, 200, &gameover1, NOTSRCERASE);
	putimage(80, 200, &gameover2, SRCINVERT);
	FlushBatchDraw();
	Sleep(1000);
	loadimage(&atlast, "image\\atlast.jpg");
	putimage(0, 0, &atlast);
	scoleprint();
	FlushBatchDraw();
	_getch();
	//第一根柱子
	stone_y1 = rand() % 310 - 555;
	stone_x1 = 350;
	stone_x2 = stone_y2 = -9999;
	bird_y = 300;
	scole = 0;
	main();
}


void scoleprint()
{
	IMAGE* fen1[6], * fen2[6];
	int he, weishu = 1, i = 0, sdsf = scole;
	if (sdsf == 0)
	{
		putimage(250, 50, &scole1[0], NOTSRCERASE);
		putimage(250, 50, &scole2[0], SRCINVERT);

	}
	while (sdsf > 0)
	{
		he = sdsf % 10;
		fen1[i] = &scole1[he];
		fen2[i] = &scole2[he];
		putimage(300 - 50 * weishu, 50, fen1[i], NOTSRCERASE);
		putimage(300 - 50 * weishu, 50, fen2[i], SRCINVERT);
		sdsf /= 10;
		i++;
		weishu++;
	}
}