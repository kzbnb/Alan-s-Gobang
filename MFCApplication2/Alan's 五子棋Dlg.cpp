
// MFCApplication2Dlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "MFCApplication2Dlg.h"
#include "afxdialogex.h"
#include <tchar.h> 
#include "pch.h"
#include<iostream>
#include<conio.h>
#include<graphics.h>
#include<mmsystem.h>
#include <string>
#include"point.h"
#include"shu.h"
#include"situation.h"
#include <sstream>

#pragma comment(lib,"winmm.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif




using namespace std;

//棋盘大小
int const Size_of_chessborad = 20;

//记录想玩几子棋
int gaoxiao = 0;

//记录赢后的选择
int the_end = 0;

//记录黑白棋各赢多少次
int black_win = 0;
int white_xin = 0;

//黑子为2，白子为3
int playernow = 2;

bool qiuzhu = 0;

//定义全局变量a,b,即五子棋的横纵坐标
int a = 0, b = 0, c = 0, d = 0;

//记录棋子
int chessbroad[Size_of_chessborad][Size_of_chessborad] = { 0 };

//胜者记录
int winner = 0;
int blood = 0;

//判断输赢的函数
int judge(int  a, int b)
{

	//定义出每个方向的棋子数
	int shuiping = 1;
	int shuzhi = 1;
	int zuoxie = 1;
	int youxie = 1;
	int cursor_x = a, cursor_y = b;

	//开始水平检查
	//向右
	for (int a = 1; a < 5 + gaoxiao; a++)
	{
		if (cursor_x + a < Size_of_chessborad && chessbroad[cursor_x + a][cursor_y] == playernow)
		{
			shuiping++;
		}
		else
			break;
	}

	//向左
	for (int a = 1; a < 5 + gaoxiao; a++)
	{
		if (cursor_x - a >= 0 && chessbroad[cursor_x - a][cursor_y] == playernow)
		{
			shuiping++;
		}
		else
			break;
	}
	if (shuiping > 4 + gaoxiao)
	{
		return playernow;
	}

	//开始竖直检查
	//向上
	for (int a = 1; a < 5 + gaoxiao; a++)
	{
		if (cursor_y + a < Size_of_chessborad&&chessbroad[cursor_x][cursor_y + a] == playernow)
		{
			shuzhi++;
		}
		else
			break;
	}

	//向下
	for (int a = 1; a < 5 + gaoxiao; a++)
	{
		if (cursor_y - a >= 0 && chessbroad[cursor_x][cursor_y - a] == playernow)
		{
			shuzhi++;
		}
		else
			break;
	}
	if (shuzhi > 4 + gaoxiao)
	{
		return playernow;
	}

	//开始右斜检查
	//向上
	for (int a = 1; a < 5 + gaoxiao; a++)
	{
		if (cursor_x + a < Size_of_chessborad  &&  cursor_y + a < Size_of_chessborad   &&  chessbroad[cursor_x + a][cursor_y + a] == playernow)
		{
			youxie++;
		}
		else
			break;
	}

	//向下
	for (int a = 1; a < 5 + gaoxiao; a++)
	{
		if (cursor_x - a >= 0 && cursor_y - a >= 0 && chessbroad[cursor_x - a][cursor_y - a] == playernow)
		{
			youxie++;
		}
		else
			break;
	}
	if (youxie > 4 + gaoxiao)
	{
		return playernow;
	}

	//开始左斜检查
	//向上
	for (int a = 1; a < 5 + gaoxiao; a++)
	{
		if (cursor_x - a >= 0 && cursor_y + a < Size_of_chessborad  &&  chessbroad[cursor_x - a][cursor_y + a] == playernow)
		{
			zuoxie++;
		}
		else
			break;
	}

	//向下
	for (int a = 1; a < 5 + gaoxiao; a++)
	{
		if (cursor_x + a < Size_of_chessborad && cursor_y - a >= 0 && chessbroad[cursor_x + a][cursor_y - a] == playernow)
		{
			zuoxie++;
		}
		else
			break;
	}



	if (zuoxie > 4 + gaoxiao)
	{
		return playernow;
	}


	return 0;


}

//AI的声明
void AI();

void blood_fight()
{
	if (blood != 1)
	{
		//停止旧音乐
		mciSendString(L"stop 1.mp3", NULL, 0, NULL);
		mciSendString(L"stop xiaqi.wav", NULL, 0, NULL);

		//打开音乐文件
		int r = mciSendString(L"open 8.mp3", 0, 0, 0);

		//播放音乐文件
		int q = mciSendString(L"play 8.mp3", 0, 0, 0);

	}

	//已开始血战到底
	blood = 1;

	//设置字体颜色
	setcolor(RED);

	//初始化字符数组
	TCHAR kzb[5] = { 0 };

	//将数字转字符
	swprintf_s(kzb, _T("%d"), black_win);

	//输出
	outtextxy(605, 320, _T("进入  血战到底  模式！！！"));
	setcolor(WHITE);
	outtextxy(605, 380, _T("黑棋获胜次数： "));
	outtextxy(605, 400, kzb);

	//同理
	TCHAR kzbb[5] = { 0 };
	swprintf_s(kzbb, _T("%d"), white_xin);
	outtextxy(605, 450, _T("白棋获胜次数： "));
	outtextxy(605, 470, kzbb);




	//窗口句柄
	HWND hwnd;

	//将其置前
	hwnd = GetHWnd();


	//10次后结束游戏
	if (black_win >= 10)
	{

		mciSendString(L"close 2.mp3", 0, 0, 0);
		mciSendString(L"play  3280.mp3", 0, 0, 0);
		MessageBox(hwnd, L"你赢了！！怎么也赢够了吧！点击确定退出游戏", L"五子棋", MB_OK);

		exit(0);

	}
	if (white_xin >= 10)
	{

		mciSendString(L"close 2.mp3", 0, 0, 0);
		mciSendString(L"play  3280.mp3", 0, 0, 0);
		MessageBox(hwnd, L"你输了！！怎么也输够了吧！点击确定退出游戏", L"五子棋", MB_OK);
		exit(0);
	}
}



//游戏初始化
void init()
{

	
	//黑子为2，白子为3
	playernow = 2;


	//定义全局变量a,b,即五子棋的横纵坐标
	a = 0, b = 0, c = 0, d = 0;

	//记录棋子
	int chessbroad[Size_of_chessborad][Size_of_chessborad] = { 0 };

	//胜者记录
	winner = 0;

	//定义一个图形对象
	IMAGE bakcground;

	//将一张照片加载进这个对象
	loadimage(&bakcground, L"4.jpg");

	//定义变量记录下照片的大小
	int width = bakcground.getwidth();
	int height = bakcground.getheight();

	//初始化照片大小
	initgraph(950, 650);

	//在左上角的位置开始放置图片
	putimage(0, 0, &bakcground);

	//music
	//打开音乐文件
	mciSendString(L"open 1.mp3", 0, 0, 0);

	//播放音乐文件
	mciSendString(L"play 1.mp3", 0, 0, 0);

	//开始画棋盘
	//黑线
	setlinecolor(BLACK);

	// 开始划线
	for (int i = 1; i < 20; i++)
	{
		//画竖线
		line(i * 30, 0, i * 30, 600);

		//画横线
		line(0, i * 30, 600, i * 30);
	}

	//画实线
	setlinestyle(PS_SOLID, 3);

	//实线的位置
	line(600, 0, 600, 600);
	line(0, 600, 600, 600);

	SetConsoleTitle(_T("ALAN's 五子棋"));

}

//人机对战模块
void paly_PVE()
{

	outtextxy(605, 120, _T("玩家：黑棋"));
	outtextxy(605, 240, _T("电脑：白棋"));


	//声明一个m，获取鼠标消息
	MOUSEMSG m;
	int  x = 0, y = 0;

	//窗口句柄
	HWND hwnd;

	//将其置前
	hwnd = GetHWnd();

	//不断重复
	while (1)
	{
		outtextxy(601, 280, _T("点击此处让电脑帮你下一步黑棋"));
		//得到命令
		m = GetMouseMsg();

		//将鼠标点击的位置取距离最近的点
		//同时记录下来
		if (m.x < 600 && m.y < 600)
		{
			for (int i = 1; i < 20; i++)
			{
				for (int j = 1; j < 20; j++)
				{


					if (abs(m.x - i * 30) < 14 && abs(m.y - j * 30) < 14)
					{

						//a,b为数组里的坐标
						a = i;
						b = j;

						//x,y为实际的坐标
						x = i * 30;
						y = j * 30;
					}

				}
			}
		}

		//如果有点击
		//同时点击在棋盘之内
		if (m.uMsg == WM_LBUTTONDOWN && m.x < 585 && m.y < 585)
		{

			//判断棋盘是否已经有子
			if (chessbroad[a][b] != 0)
			{

				//弹出已经有子
				MessageBox(hwnd, L"已经有子", L"wuziqi", MB_OK);

				//继续循环
				continue;
			}

			//设置为黑子
			setfillcolor(BLACK);

			//画棋子
			solidcircle(x, y, 10);

			mciSendString(L"close xiazi.wav", NULL, 0, NULL);
			//打开音乐文件
			mciSendString(L"open xiazi.wav", 0, 0, 0);

			//播放音乐文件
			mciSendString(L"play xiazi.wav", 0, 0, 0);


			//数组记录，黑子下
			chessbroad[a][b] = 2;


			//调用AI函数
			AI();

			//先判断黑子有没赢
			playernow = 2;

			winner = judge(a, b);


			//如果黑子没赢，判断白子有没赢
			if (winner == 0)
			{
				playernow = 3;
				winner = judge(c, d);
			}
			int end = 0;
			//若黑子胜
			if (winner == 2)
			{	//窗口句柄

				black_win++;
				//打开音乐文件
				mciSendString(L"open 3280.wav", 0, 0, 0);

				//播放音乐文件
				mciSendString(L"play 3280.wav", 0, 0, 0);

				if (blood == 0)
				{

					//打开音乐文件
					mciSendString(L"open 3280.wav", 0, 0, 0);

					//播放音乐文件
					mciSendString(L"play 3280.wav", 0, 0, 0);

					end = MessageBox(hwnd, L"你赢了！点击“终止”退出游戏，“重试”开始一局新游戏，“忽略”开启“血战到底”", L"五子棋", MB_ABORTRETRYIGNORE);
				}
				if (end == 3)
				{
					exit(0);

				}

				if (end == 4)
				{
					the_end = 4;

					//把原棋子记录清零
					memset(chessbroad, 0, Size_of_chessborad*Size_of_chessborad * sizeof(int));
					break;


				}

				if (end == 5)
				{
					the_end = 5;
				}

			}
			//若白子胜
			if (winner == 3)
			{

				white_xin++;
				//打开音乐文件
				mciSendString(L"open 3280.wav", 0, 0, 0);

				//播放音乐文件
				mciSendString(L"play 3280.wav", 0, 0, 0);

				if (blood == 0)
				{


					end = MessageBox(hwnd, L"电脑赢了！点击“终止”退出游戏，“重试”开始一局新游戏，“忽略”开启“血战到底”", L"五子棋", MB_ABORTRETRYIGNORE);
				}
				if (end == 3)
				{
					exit(0);

				}

				if (end == 4)
				{
					the_end = 4;
					//把原棋子记录清零
					memset(chessbroad, 0, Size_of_chessborad*Size_of_chessborad * sizeof(int));
					break;

				}

				if (end == 5)
				{
					the_end = 5;
				}
			}

			//关音乐
			mciSendString(L"close 3280.wav", 0, 0, 0);

		}

		//if (m.uMsg == WM_LBUTTONDOWN && m.x < 585 && m.y < 585)
		if (m.uMsg == WM_LBUTTONDOWN && m.x > 585)
		{
			//提示走（黑子
			qiuzhu = 1;
			AI();

			//白子
			AI();

			//先判断黑子有没赢
			playernow = 2;

			winner = judge(a, b);


			//如果黑子没赢，判断白子有没赢
			if (winner == 0)
			{
				playernow = 3;
				winner = judge(c, d);
			}
			int end = 0;
			//若黑子胜
			if (winner == 2)
			{	//窗口句柄

				black_win++;
				//打开音乐文件
				mciSendString(L"open 3280.wav", 0, 0, 0);

				//播放音乐文件
				mciSendString(L"play 3280.wav", 0, 0, 0);

				if (blood == 0)
				{

					//打开音乐文件
					mciSendString(L"open 3280.wav", 0, 0, 0);

					//播放音乐文件
					mciSendString(L"play 3280.wav", 0, 0, 0);

					end = MessageBox(hwnd, L"你赢了！点击“终止”退出游戏，“重试”开始一局新游戏，“忽略”开启“血战到底”", L"五子棋", MB_ABORTRETRYIGNORE);
				}
				if (end == 3)
				{
					exit(0);

				}

				if (end == 4)
				{
					the_end = 4;
					memset(chessbroad, 0, Size_of_chessborad*Size_of_chessborad * sizeof(int));
					break;


				}

				if (end == 5)
				{
					the_end = 5;
				}

			}
			//若白子胜
			if (winner == 3)
			{

				white_xin++;
				//打开音乐文件
				mciSendString(L"open 3280.wav", 0, 0, 0);

				//播放音乐文件
				mciSendString(L"play 3280.wav", 0, 0, 0);

				if (blood == 0)
				{


					end = MessageBox(hwnd, L"电脑赢了！点击“终止”退出游戏，“重试”开始一局新游戏，“忽略”开启“血战到底”", L"五子棋", MB_ABORTRETRYIGNORE);
				}
				if (end == 3)
				{
					exit(0);

				}

				if (end == 4)
				{
					the_end = 4;
					memset(chessbroad, 0, Size_of_chessborad*Size_of_chessborad * sizeof(int));
					break;

				}

				if (end == 5)
				{
					the_end = 5;
				}
			}

			//关音乐
			mciSendString(L"close 3280.wav", 0, 0, 0);

		}


		//开启血战到底
		if (the_end == 5)
		{
			blood_fight();

			//初始化输赢次数
			if (winner == 2 && blood == 0)
			{
				black_win = 1;
			}
			if (winner == 3 && blood == 0)
				white_xin = 1;
		}
	}


	//重启
	if (the_end == 4)
	{
		init();
		paly_PVE();
	}



}

void paly_PVP()
{



	outtextxy(605, 120, _T("玩家1：黑棋"));
	outtextxy(605, 240, _T("玩家2：白棋"));



	//声明一个m，获取鼠标消息
	MOUSEMSG m;
	int  x = 0, y = 0;

	//窗口句柄
	HWND hwnd;

	//将其置前
	hwnd = GetHWnd();
	int heibai = 2;
	int end = 0;
	//不断重复
	while (1)
	{

		//得到命令
		m = GetMouseMsg();

		//将鼠标点击的位置取距离最近的点
		//同时记录下来
		for (int i = 1; i < 20; i++)
		{
			for (int j = 1; j < 20; j++)
			{
				if (abs(m.x - i * 30) < 14 && abs(m.y - j * 30) < 14)
				{

					//a,b为数组里的坐标
					a = i;
					b = j;

					//x,y为实际的坐标
					x = i * 30;
					y = j * 30;
				}
			}
		}

		//如果有点击
		if (m.uMsg == WM_LBUTTONDOWN)
		{

			//判断棋盘是否已经有子
			if (chessbroad[a][b] != 0)
			{

				//弹出已经有子
				MessageBox(hwnd, L"已经有子", L"wuziqi", MB_OK);

				//继续循环
				continue;
			}

			//判断下子者
			//如果是黑棋
			if (playernow == 2)
			{
				mciSendString(L"close xiazi.wav", NULL, 0, NULL);

				heibai++;
				//颜色为黑
				setfillcolor(BLACK);

				//画棋子
				solidcircle(x, y, 10);

				//数组记录，黑子下
				chessbroad[a][b] = 2;

				//打开音乐文件
				mciSendString(L"open xiazi.wav", 0, 0, 0);

				//播放音乐文件
				mciSendString(L"play xiazi.wav", 0, 0, 0);


				//下棋后判断输赢
				winner = judge(a, b);
			}
			else
			{
				mciSendString(L"close xiazi.wav", NULL, 0, NULL);


				heibai--;
				//颜色为白
				setfillcolor(WHITE);

				//画棋子
				solidcircle(x, y, 10);

				//数组记录，白子下
				chessbroad[a][b] = 3;

				//打开音乐文件
				mciSendString(L"open xiazi.wav", 0, 0, 0);

				//播放音乐文件
				mciSendString(L"play xiazi.wav", 0, 0, 0);


				//下棋后判断输赢
				winner = judge(a, b);
			}








			//若黑子胜
			if (winner == 2)
			{	//窗口句柄

				black_win++;

				//打开音乐文件
				mciSendString(L"open 3280.wav", 0, 0, 0);

				//播放音乐文件
				mciSendString(L"play 3280.wav", 0, 0, 0);

				if (blood == 0)
				{
					end = MessageBox(hwnd, L"1号玩家赢了！点击“终止”退出游戏，“重试”开始一局新游戏，“忽略”开启“血战到底”", L"五子棋", MB_ABORTRETRYIGNORE);
				}
				if (end == 3)
				{
					exit(0);

				}

				if (end == 4)
				{
					the_end = 4;
					memset(chessbroad, 0, Size_of_chessborad*Size_of_chessborad * sizeof(int));
					break;


				}

				if (end == 5)
				{
					the_end = 5;
				}

				mciSendString(L"close 3280.wav", 0, 0, 0);

			}
			//若白子胜
			if (winner == 3)
			{

				white_xin++;
				//打开音乐文件
				mciSendString(L"open 3280.wav", 0, 0, 0);

				//播放音乐文件
				mciSendString(L"play 3280.wav", 0, 0, 0);

				if (blood == 0)
				{
					end = MessageBox(hwnd, L"2号玩家赢了！点击“终止”退出游戏，“重试”开始一局新游戏，“忽略”开启“血战到底”", L"五子棋", MB_ABORTRETRYIGNORE);
				}

				//退出
				if (end == 3)
				{
					exit(0);

				}

				//重启
				if (end == 4)
				{
					the_end = 4;
					memset(chessbroad, 0, Size_of_chessborad*Size_of_chessborad * sizeof(int));
					break;

				}

				//血战到底
				if (end == 5)
				{
					the_end = 5;
				}
				mciSendString(L"close 3280.wav", 0, 0, 0);
			}

			//血战到底
			if (the_end == 5)
			{
				blood_fight();

				//初始化输赢次数
				if (winner == 2 && blood == 0)
				{
					black_win = 1;
				}
				if (winner == 3 && blood == 0)
					white_xin = 1;
			}




		}


		//确定下棋的人
		if (heibai == 2)
		{
			playernow = 2;
		}


		if (heibai == 3)
		{
			playernow = 3;
		}
	}

	//初始化
	if (the_end == 4)
	{
		init();
		paly_PVP();
	}


}




//将机器设为白子
int gamer = 3;




shu point::count(int a, int b, int c)
{
	//定义出每个方向的棋子数
	int shuiping = 1;
	int shuzhi = 1;
	int zuoxie = 1;
	int youxie = 1;
	int cursor_x = a, cursor_y = b;
	int playernow = c;

	//开始水平检查
	//向右
	for (int a = 1; a < 5; a++)
	{
		if (/*cursor_x + a < Size_of_chessborad &&*/ chessbroad[cursor_x + a][cursor_y] == playernow)
		{
			shuiping++;
		}
		else
			break;
	}

	//向左
	for (int a = 1; a < 5; a++)
	{
		if (/*cursor_x - a >= 0 &&*/ chessbroad[cursor_x - a][cursor_y] == playernow)
		{
			shuiping++;
		}
		else
			break;
	}


	//开始竖直检查
	//向上
	for (int a = 1; a < 5; a++)
	{
		if (cursor_y + a < Size_of_chessborad&&chessbroad[cursor_x][cursor_y + a] == playernow)
		{
			shuzhi++;
		}
		else
			break;
	}

	//向下
	for (int a = 1; a < 5; a++)
	{
		if (cursor_y - a >= 0 && chessbroad[cursor_x][cursor_y - a] == playernow)
		{
			shuzhi++;
		}
		else
			break;
	}


	//开始右斜检查
	//向上
	for (int a = 1; a < 5; a++)
	{
		if (cursor_x + a < Size_of_chessborad  &&  cursor_y + a < Size_of_chessborad   &&  chessbroad[cursor_x + a][cursor_y + a] == playernow)
		{
			youxie++;
		}
		else
			break;
	}

	//向下
	for (int a = 1; a < 5; a++)
	{
		if (cursor_x - a >= 0 && cursor_y - a >= 0 && chessbroad[cursor_x - a][cursor_y - a] == playernow)
		{
			youxie++;
		}
		else
			break;
	}


	//开始左斜检查
	//向上
	for (int a = 1; a < 5; a++)
	{
		if (cursor_x - a >= 0 && cursor_y + a < Size_of_chessborad  &&  chessbroad[cursor_x - a][cursor_y + a] == playernow)
		{
			zuoxie++;
		}
		else
			break;
	}

	//向下
	for (int a = 1; a < 5; a++)
	{
		if (cursor_x + a < Size_of_chessborad && cursor_y - a >= 0 && chessbroad[cursor_x + a][cursor_y - a] == playernow)
		{
			zuoxie++;
		}
		else
			break;
	}

	shu number;
	number.shuiping = shuiping;
	number.shuzhi = shuzhi;
	number.zuoxie = zuoxie;
	number.youxie = youxie;




	return number;




}

//设置一个变量
int tricker = 0;


void AI()
{

	point fianlpoint;

	if (tricker == 1 && c != 0 && d != 0 && qiuzhu == 0)
	{
		setfillcolor(WHITE);

		solidcircle(c * 30, d * 30, 10);
	}

	if (qiuzhu == 0)
	{

		//计算出棋子应下的位置
		fianlpoint.after_score();
		//颜色为白
		setfillcolor(RGB(243, 248, 170));
		//画棋子
		solidcircle(fianlpoint.x * 30, fianlpoint.y * 30, 10);

		//数组记录，白子下
		chessbroad[fianlpoint.x][fianlpoint.y] = 3;

		//将白子下子位置记录于全局变量
		c = fianlpoint.x;
		d = fianlpoint.y;
		tricker = 1;
	}


	if (qiuzhu == 1)
	{

		//计算出棋子应下的位置
		fianlpoint.after_score();
		//颜色为白
		setfillcolor(BLACK);
		//画棋子
		fillcircle(fianlpoint.x * 30, fianlpoint.y * 30, 10);

		//数组记录，白子下
		chessbroad[fianlpoint.x][fianlpoint.y] = 2;

		//将下子位置记录于全局变量

		qiuzhu = 0;
	}

}

void point::after_score()
{
	//声明两个变量表示AI或者玩家最后的分数
	int AI_final_score = 0;
	int player_final_score = 0;

	//声明四个变量表示AI或者玩家最后的点
	int AI_final_x = 0, AI_final_y = 0, player_final_x = 0, player_final_y = 0;

	//声明两个situation对象数组装下AI或者玩家的四条线分别的情况
	situation AI_situation[4], player_situation[4];

	//遍历棋盘每一个子
	//横坐标
	for (int m = 1; m < Size_of_chessborad; m++)
	{
		//纵坐标
		for (int n = 1; n < Size_of_chessborad; n++)
		{

			//初始化数组用于装4个方向分别的分数
			int AI_score[4] = { 0 }, player_score[4] = { 0 };

			//记录单个点的最高分数
			int AI_all = 0, player_all = 0;

			//用于记录每个方向相同棋子的数量
			shu AI_count, player_count;

			//为该点创建point对象
			point every(m, n);

			//接下来AI和player两方面同步进行
			int gam = 2;
			if (gamer == 3)
			{
				gam = 2;
			}
			else gam = 3;

			//先计算每个方向的棋子数
			AI_count = every.count(every.x, every.y, gamer);
			player_count = every.count(every.x, every.y, gam);

			//于是将每个方向的棋子数分别给到判定该方向情形的函数
			//然后存到记录情形的对象里
			AI_situation[0] = every.shuiping(AI_count.shuiping, gamer);
			player_situation[0] = every.shuiping(player_count.shuiping, gam);


			AI_situation[1] = every.shuzhi(AI_count.shuzhi, gamer);
			player_situation[1] = every.shuzhi(player_count.shuzhi, gam);

			AI_situation[2] = every.zuoxie(AI_count.zuoxie, gamer);
			player_situation[2] = every.zuoxie(player_count.zuoxie, gam);

			AI_situation[3] = every.youxie(AI_count.youxie, gamer);
			player_situation[3] = every.youxie(player_count.youxie, gam);

			//记录完情形后，开始每个方向分别算分


			AI_score[0] = AI_situation[0].score(m, n);
			player_score[0] = player_situation[0].score(m, n);

			AI_score[1] = AI_situation[1].score(m, n);
			player_score[1] = player_situation[1].score(m, n);

			AI_score[2] = AI_situation[2].score(m, n);
			player_score[2] = player_situation[2].score(m, n);

			AI_score[3] = AI_situation[3].score(m, n);
			player_score[3] = player_situation[3].score(m, n);

			//把每个方向的分数加起来算总分

			for (int a = 0; a < 4; a++)
			{
				AI_all = AI_all + AI_score[a];
				player_all = player_all + player_score[a];
			}

			//如果分数是目前已遍历的棋子最高分的，取而代之

			if (AI_all >= AI_final_score)
			{
				AI_final_score = AI_all;
				AI_final_x = m;
				AI_final_y = n;

			}

			if (player_all >= player_final_score)
			{
				player_final_score = player_all;
				player_final_x = m;
				player_final_y = n;

			}

		}
	}

	//确定完AI和人各自的最佳棋点后，确定最终落子
	point final;


	//判断，分高的点先下
	if (AI_final_score > player_final_score + 100)
	{

		final.x = AI_final_x;
		final.y = AI_final_y;

	}

	else if (AI_final_score <= player_final_score + 100)
	{

		final.x = player_final_x;
		final.y = player_final_y;

	}
	
	if(AI_final_score== player_final_score)
	{
		final.x = Size_of_chessborad / 2;
		final.y = Size_of_chessborad / 2;
	}
	
	//将最终的点赋值全局变量
	x = final.x;
	y = final.y;


}



situation point::shuiping(int count, int player)
{
	situation a;

	//以不同的棋子数，分情况讨论

	//五子连珠

	if (count >= 5)
	{
		a.five_win++;
	}

	//4子
	if (count == 4)
	{
		//分别记录两个方向棋子个数

		int right = 0,
			left = 0;

		for (int p = 0; p < 4; p++)
		{
			if (chessbroad[x + p][y] == player)
			{
				right++;
			}

			if (chessbroad[x - p][y] == player)
			{
				left++;
			}
		}

		//判断各种情况

		if ((chessbroad[x - left - 1][y] == player + 1 || chessbroad[x - left - 1][y] == player - 1) && (x + right + 1) < Size_of_chessborad)
		{
			a.four_chong++;
		}

		if ((chessbroad[x + right + 1][y] == player + 1 || chessbroad[x + right + 1][y] == player - 1) && (x - left - 1) > 0)
		{
			a.four_chong++;
		}



		if (a.four_chong == 0 && (x + right + 1) < Size_of_chessborad && (x - left - 1) > 0)
		{
			a.four_live++;
		}

	}

	//3子

	if (count == 3)
	{

		int right = 0,
			left = 0;

		for (int p = 0; p < 3; p++)
		{
			if (chessbroad[x + p][y] == player)
			{
				right++;
			}

			if (chessbroad[x - p][y] == player)
			{
				left++;
			}
		}

		if ((chessbroad[x - left - 1][y] == player + 1 || chessbroad[x - left - 1][y] == player - 1) && (x + right + 2) < Size_of_chessborad)
		{
			a.three_sleep++;
		}

		if ((chessbroad[x + right + 1][y] == player + 1 || chessbroad[x + right + 1][y] == player - 1) && (x - left - 2) > 0)
		{
			a.three_sleep++;
		}



		if (a.four_chong == 0 && (x + right + 2) < Size_of_chessborad && (x - left - 2) > 0)
		{
			a.three_live++;
		}





	}

	//2子

	if (count == 2)
	{
		int right = 0,
			left = 0;

		for (int p = 0; p < 2; p++)
		{
			if (chessbroad[x + p][y] == player)
			{
				right++;
			}

			if (chessbroad[x - p][y] == player)
			{
				left++;
			}
		}

		if ((chessbroad[x - left - 1][y] == player + 1 || chessbroad[x - left - 1][y] == player - 1) && (x + right + 3) < Size_of_chessborad)
		{
			a.two_sleep++;
		}

		if ((chessbroad[x + right + 1][y] == player + 1 || chessbroad[x + right + 1][y] == player - 1) && (x - left - 3) > 0)
		{
			a.two_sleep++;
		}



		if (a.four_chong == 0 && (x + right + 3) < Size_of_chessborad && (x - left - 3) > 0)
		{
			a.two_live++;
		}

	}

	//1子无用

	return a;
}

//接下来三个方向同理

situation point::shuzhi(int count, int player)
{
	situation a;
	if (count >= 5)
		a.five_win++;


	if (count == 4)
	{
		int right = 0,
			left = 0;

		for (int p = 0; p < 4; p++)
		{
			if (chessbroad[x][y + p] == player)
			{
				right++;
			}

			if (chessbroad[x][y - p] == player)
			{
				left++;
			}
		}
		if ((chessbroad[x][y - left - 1] == player + 1 || chessbroad[x][y - left - 1] == player - 1) && (y + right + 1) < Size_of_chessborad)
		{
			a.four_chong++;
		}

		if ((chessbroad[x][y + right + 1] == player + 1 || chessbroad[x][y + right + 1] == player - 1) && (y - left - 1) > 0)
		{
			a.four_chong++;
		}



		if (a.four_chong == 0 && (y + right + 1) < Size_of_chessborad && (y - left - 1) > 0)
		{
			a.four_live++;
		}

	}

	if (count == 3)
	{

		int right = 0,
			left = 0;

		for (int p = 0; p < 3; p++)
		{
			if (chessbroad[x][y + p] == player)
			{
				right++;
			}

			if (chessbroad[x][y - p] == player)
			{
				left++;
			}
		}

		if ((chessbroad[x][y - left - 1] == player + 1 || chessbroad[x][y - left - 1] == player - 1) && (y + right + 2) < Size_of_chessborad)
		{
			a.three_sleep++;
		}

		if ((chessbroad[x][y + right + 1] == player + 1 || chessbroad[x][y + right + 1] == player - 1) && (y - left - 2) > 0)
		{
			a.three_sleep++;
		}



		if (a.three_sleep == 0 && (y + right + 2) < Size_of_chessborad && (y - left - 2) > 0)
		{
			a.three_live++;
		}





	}

	if (count == 2)
	{
		int right = 0,
			left = 0;

		for (int p = 0; p < 2; p++)
		{
			if (chessbroad[x][y + p] == player)
			{
				right++;
			}

			if (chessbroad[x][y - p] == player)
			{
				left++;
			}
		}

		if ((chessbroad[x][y - left - 1] == player + 1 || chessbroad[x][y - left - 1] == player - 1) && (y + right + 3) < Size_of_chessborad)
		{
			a.two_sleep++;
		}

		if ((chessbroad[x][y + right + 1] == player + 1 || chessbroad[x][y + right + 1] == player - 1) && (y - left - 3) > 0)
		{
			a.two_sleep++;
		}



		if (a.two_sleep == 0 && (y + right + 3) < Size_of_chessborad && (y - left - 3) > 0)
		{
			a.two_live++;
		}

	}


	return a;
}

situation point::zuoxie(int count, int player)
{
	situation a;
	if (count >= 5)
	{
		a.five_win++;
	}

	if (count == 4)
	{
		int right = 0,
			left = 0;

		for (int p = 0; p < 4; p++)
		{
			if (chessbroad[x - p][y + p] == player)
			{
				right++;
			}

			if (chessbroad[x + p][y - p] == player)
			{
				left++;
			}
		}

		if ((chessbroad[x + left + 1][y - left - 1] == player + 1 || chessbroad[x + left + 1][y - left - 1] == player - 1) && (y + right + 1) < Size_of_chessborad)
		{
			a.four_chong++;
		}

		if ((chessbroad[x - right - 1][y + right + 1] == player + 1 || chessbroad[x - right - 1][y + right + 1] == player - 1) && (y - left - 1) > 0)
		{
			a.four_chong++;
		}



		if (a.four_chong == 0 && (y + right + 1) < Size_of_chessborad && (y - left - 1) > 0)
		{
			a.four_live++;
		}

	}

	if (count == 3)
	{

		int right = 0,
			left = 0;

		for (int p = 0; p < 3; p++)
		{
			if (chessbroad[x - p][y + p] == player)
			{
				right++;
			}

			if (chessbroad[x + p][y - p] == player)
			{
				left++;
			}
		}

		if ((chessbroad[x + left + 1][y - left - 1] == player + 1 || chessbroad[x + left + 1][y - left - 1] == player - 1) && (y + right + 2) < Size_of_chessborad)
		{
			a.three_sleep++;
		}

		if ((chessbroad[x - right - 1][y + right + 1] == player + 1 || chessbroad[x - right - 1][y + right + 1] == player - 1) && (y - left - 2) > 0)
		{
			a.three_sleep++;
		}



		if (a.three_sleep == 0 && (y + right + 2) < Size_of_chessborad && (y - left - 2) > 0)
		{
			a.three_live++;
		}





	}

	if (count == 2)
	{
		int right = 0,
			left = 0;

		for (int p = 0; p < 2; p++)
		{
			if (chessbroad[x][y + p] == player)
			{
				right++;
			}

			if (chessbroad[x][y - p] == player)
			{
				left++;
			}
		}

		if ((chessbroad[x + left + 1][y - left - 1] == player + 1 || chessbroad[x + left + 1][y - left - 1] == player - 1) && (y + right + 3) < Size_of_chessborad)
		{
			a.two_sleep++;
		}

		if ((chessbroad[x - right - 1][y + right + 1] == player + 1 || chessbroad[x - right - 1][y + right + 1] == player - 1) && (y - left - 3) > 0)
		{
			a.two_sleep++;
		}



		if ((a.two_sleep == 0 && (y + right + 3) < Size_of_chessborad) && (y - left - 3) > 0)
		{
			a.two_live++;
		}

	}


	return a;
}

situation point::youxie(int count, int player)
{
	situation a;
	if (count >= 5)
	{
		a.five_win++;
	}

	if (count == 4)
	{
		int right = 0,
			left = 0;

		for (int p = 0; p < 4; p++)
		{
			if (chessbroad[x + p][y + p] == player)
			{
				right++;
			}

			if (chessbroad[x - p][y - p] == player)
			{
				left++;
			}
		}
		if ((chessbroad[x - left - 1][y - left - 1] == player + 1 || chessbroad[x - left - 1][y - left - 1] == player - 1) && (y + right + 1) < Size_of_chessborad)
		{
			a.four_chong++;
		}

		if ((chessbroad[x + right + 1][y + right + 1] == player + 1 || chessbroad[x + right + 1][y + right + 1] == player - 1) && (y - left - 1) > 0)
		{
			a.four_chong++;
		}



		if (a.four_chong == 0 && (y + right + 1) < Size_of_chessborad && (y - left - 1) > 0)
		{
			a.four_live++;
		}

	}

	if (count == 3)
	{

		int right = 0,
			left = 0;

		for (int p = 0; p < 3; p++)
		{
			if (chessbroad[x + p][y + p] == player)
			{
				right++;
			}

			if (chessbroad[x - p][y - p] == player)
			{
				left++;
			}
		}

		if ((chessbroad[x - left - 1][y - left - 1] == player + 1 || chessbroad[x - left - 1][y - left - 1] == player - 1) && (y + right + 2) < Size_of_chessborad)
		{
			a.three_sleep++;
		}

		if ((chessbroad[x + right + 1][y + right + 1] == player + 1 || chessbroad[x + right + 1][y + right + 1] == player - 1) && (y - left - 2) > 0)
		{
			a.three_sleep++;
		}



		if ((a.three_sleep == 0 && (y + right + 2) < Size_of_chessborad) && (y - left - 2) > 0)
		{
			a.three_live++;
		}





	}

	if (count == 2)
	{
		int right = 0,
			left = 0;

		for (int p = 0; p < 2; p++)
		{
			if (chessbroad[x + p][y + p] == player)
			{
				right++;
			}

			if (chessbroad[x - p][y - p] == player)
			{
				left++;
			}
		}

		if ((chessbroad[x - left - 1][y - left - 1] == player + 1 || chessbroad[x - left - 1][y - left - 1] == player - 1) && (y + right + 3) < Size_of_chessborad)
		{
			a.two_sleep++;
		}

		if ((chessbroad[x + right + 1][y + right + 1] == player + 1 || chessbroad[x + right + 1][y + right + 1] == player - 1) && (y - left - 3) > 0)
		{
			a.two_sleep++;
		}


		if (a.two_sleep == 0 && (y + right + 3) < Size_of_chessborad && (y - left - 3) > 0)
		{
			a.two_live++;
		}

	}


	return a;
}

//积分函数
int situation::score(int m, int n)
{
	//积分
	int score = 1000000000 * five_win + 100000 * four_live + 50 * four_chong + 20 * three_live + 2 * three_sleep + 1 * two_live + 1 * two_sleep;

	//若此处有棋子，当然不能下
	if (chessbroad[m][n] != 0)
	{
		score = -1;
	}

	return score;
}

//构造函数

point::point(int a, int b)
{
	x = a;
	y = b;
}



// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication2Dlg 对话框



CMFCApplication2Dlg::CMFCApplication2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication2Dlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT1, &CMFCApplication2Dlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication2Dlg::OnBnClickedButton2)
	ON_STN_CLICKED(IDB_BITMAP1, &CMFCApplication2Dlg::OnStnClickedBitmap1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_PROGRESS1, &CMFCApplication2Dlg::OnNMCustomdrawProgress1)
	ON_BN_CLICKED(IDC_CHECK1, &CMFCApplication2Dlg::OnBnClickedCheck1)
	ON_EN_CHANGE(IDC_RICHEDIT21, &CMFCApplication2Dlg::OnEnChangeRichedit21)
END_MESSAGE_MAP()


// CMFCApplication2Dlg 消息处理程序

BOOL CMFCApplication2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplication2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCApplication2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCApplication2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication2Dlg::OnBnClickedButton1()
{
	SetConsoleTitle (_T("ALAN's 五子棋"));

	//将选择窗口最小化
	ShowWindow(SW_MINIMIZE);

	//初始化
	init();

	//人机模式
	paly_PVP();

	
}


void CMFCApplication2Dlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CMFCApplication2Dlg::OnBnClickedButton2()
{

	SetConsoleTitle(_T("ALAN's 五子棋"));
	
	//新建CString对象
	CString linshi;
	
	//从对话框中获取CString类型的数字
	GetDlgItemText(IDC_STATIC, linshi);

	//将linshi转换为Int类型
	gaoxiao = _ttoi(linshi)-5;

	//将选择窗口最小化
	ShowWindow(SW_MINIMIZE);

	//初始化
	init();

	//双人模式
	paly_PVP();
	
}


void CMFCApplication2Dlg::OnStnClickedBitmap1()
{
	// TODO: 在此添加控件通知处理程序代码
}
