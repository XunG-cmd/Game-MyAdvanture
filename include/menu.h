//created by 裴思琦

#pragma once

#include <graphics.h>
#include "./button.h"
#include "multithreadMusic.h"

//对三个返回值进行宏定义
#define MENU_STORY 1
#define MENU_INFINITE 2
#define MENU_EXIT 3

//开始菜单动画中的元素
struct ELEMENT_ON_MENU
{
	int x = 0;
	int y = 0;
	PIMAGE img = newimage();
	int alpha = 0x00;			//透明度
};

void freshAnimation(BUTTON start, BUTTON intro, BUTTON exit, PIMAGE background, ELEMENT_ON_MENU title, ELEMENT_ON_MENU fish, ELEMENT_ON_MENU others);
void freshMenu(BUTTON start, BUTTON intro, BUTTON exit);
void freshStart(BUTTON story, BUTTON infinite);

//完整开始菜单流程
int menu()
{
	//初始化
	PIMAGE background = newimage();
	PIMAGE introduction = newimage();
	ELEMENT_ON_MENU title, fish, others;
	BUTTON start, intro, exit, story, infinite;
	int state = 0, lastState = 0;
	getimage(background, "assets/HOMEBACKGROUND.png");
	getimage(title.img, "assets/TITLE.png");
	getimage(fish.img, "assets/FISH.png");
	getimage(others.img, "assets/OTHERS.png");
	getimage(start.img, "assets/START01.png");
	getimage(intro.img, "assets/INTRODUCTION01.png");
	getimage(exit.img, "assets/EXIT01.png");
	getimage(story.img, "assets/STORYMODE01.png");
	getimage(infinite.img, "assets/INFINITE MODE01.png");
	mouse_msg mouse = { 0 };
	title.y = 480;
	start.y = 512;
	intro.y = 600;
	exit.y = 688;
	story.y = 250;
	infinite.y = 350;
	title.alpha = 0xFF;
	setbkmode(TRANSPARENT);
	setfont(30, 0, "Microsoft Yahei");
	setcolor(EGERGB(125, 125, 125));
	freshAnimation(start, intro, exit, background, title, fish, others);

	MUSIC bgm;
	bgm.OpenFile("music/menu.mp3");
	bgm.Play();

	//将标题从下方移入
	for (int i = 0; i < 26; i++)
	{
		title.y -= 20;
		freshAnimation(start, intro, exit, background, title, fish, others);
		delay_ms(50);
	}
	//将背景元素浮现
	for (int i = 0; i < 16; i++)
	{
		others.alpha += 15;
		freshAnimation(start, intro, exit, background, title, fish, others);
		delay_ms(50);
	}
	//输出提示，等待按键
	outtextxy(180, 410, "Press any key to continue");
	getch();

	//标题上移
	for (int i = 0; i < 17; i++)
	{
		title.y -= 5;
		freshAnimation(start, intro, exit, background, title, fish, others);
		delay_ms(40);
	}
	//锦鲤浮现
	for (int i = 0; i < 16; i++)
	{
		fish.alpha += 10;
		freshAnimation(start, intro, exit, background, title, fish, others);
		delay_ms(50);
	}
	//将此时画面作为background，避免刷新过多导致卡顿
	getimage(background, 0, 0, 640, 480);

	//三个按钮从下方移入，且时间稍有错开
	start.y -= 15;
	freshAnimation(start, intro, exit, background, title, fish, others);
	delay_ms(50);
	start.y -= 15;
	freshAnimation(start, intro, exit, background, title, fish, others);
	delay_ms(50);
	start.y -= 15;
	intro.y -= 15;
	freshAnimation(start, intro, exit, background, title, fish, others);
	delay_ms(50);
	start.y -= 15;
	intro.y -= 15;
	freshAnimation(start, intro, exit, background, title, fish, others);
	delay_ms(50);
	for (int i = 0; i < 16; i++)
	{
		start.y -= 15;
		intro.y -= 15;
		exit.y -= 15;
		freshAnimation(start, intro, exit, background, title, fish, others);
		delay_ms(50);
	}
	intro.y -= 15;
	exit.y -= 15;
	freshAnimation(start, intro, exit, background, title, fish, others);
	delay_ms(50);
	intro.y -= 15;
	exit.y -= 15;
	freshAnimation(start, intro, exit, background, title, fish, others);
	delay_ms(50);
	exit.y -= 15;
	freshAnimation(start, intro, exit, background, title, fish, others);
	delay_ms(50);
	exit.y -= 15;
	freshAnimation(start, intro, exit, background, title, fish, others);
	delay_ms(50);
	while(mousemsg()) {mouse = getmouse();} //丢弃掉显示菜单前的鼠标事件

	while (1)
	{
		//获取鼠标消息
		mouse = getmouse();
		//如果鼠标在START上
		if (onButton(mouse, start))
		{
			//如果左键按下
			if (mouse.is_down() && mouse.is_left())
			{
				state = 1;
				//START按钮高亮
				getimage(start.img, "assets/START00.png");
				getimage(intro.img, "assets/INTRODUCTION01.png");
				getimage(exit.img, "assets/EXIT01.png");
				
				playMusicOnce("music/buttonPress.mp3");
			}
			//如果左键放开
			else if (mouse.is_up() && mouse.is_left())
			{
				//进入选择模式界面
				putimage(0, 0, background);
				freshStart(story, infinite);
				while (1)
				{
					//获取鼠标消息
					mouse = getmouse();
					if (onButton(mouse, story))
					{
						if (mouse.is_down() && mouse.is_left())
						{
							state = 2;
							getimage(story.img, "assets/STORYMODE00.png");
							getimage(infinite.img, "assets/INFINITE MODE01.png");
							playMusicOnce("music/buttonPress.mp3");
						}
						else if (mouse.is_up() && mouse.is_left())
						{
							delimage(background);
							delimage(introduction);
							delimage(title.img);
							delimage(fish.img);
							delimage(others.img);
							delimage(start.img);
							delimage(intro.img);
							delimage(exit.img);
							delimage(story.img);
							delimage(infinite.img);
							bgm.Stop();
							bgm.Close();
							return MENU_STORY;
						}
						else
						{
							state = 3;
							getimage(story.img, "assets/STORYMODE02.png");
							getimage(infinite.img, "assets/INFINITE MODE01.png");
						}
					}
					else if (onButton(mouse, infinite))
					{
						if (mouse.is_down() && mouse.is_left())
						{
							state = 4;
							getimage(story.img, "assets/STORYMODE01.png");
							getimage(infinite.img, "assets/INFINITE MODE00.png");
							playMusicOnce("music/buttonPress.mp3");
						}
						else if (mouse.is_up() && mouse.is_left())
						{
							delimage(background);
							delimage(introduction);
							delimage(title.img);
							delimage(fish.img);
							delimage(others.img);
							delimage(start.img);
							delimage(intro.img);
							delimage(exit.img);
							delimage(story.img);
							delimage(infinite.img);
							bgm.Stop();
							bgm.Close();
							return MENU_INFINITE;
						}
						else
						{
							state = 5;
							getimage(story.img, "assets/STORYMODE01.png");
							getimage(infinite.img, "assets/INFINITE MODE02.png");
						}
					}
					else
					{
						state = 6;
						getimage(story.img, "assets/STORYMODE01.png");
						getimage(infinite.img, "assets/INFINITE MODE01.png");
					}
					if (state != lastState)
					{
						freshStart(story, infinite);
					}
					lastState = state;
				}
			}
			//如果鼠标仅是放在START上
			else
			{
				state = 7;
				//START按钮放大
				getimage(start.img, "assets/START03.png");
				getimage(intro.img, "assets/INTRODUCTION01.png");
				getimage(exit.img, "assets/EXIT01.png");
			}
		}
		//如果鼠标在INTRODUCTION上，同上
		else if (onButton(mouse, intro))
		{
			if (mouse.is_down() && mouse.is_left())
			{
				state = 8;
				getimage(start.img, "assets/START01.png");
				getimage(intro.img, "assets/INTRODUCTION00NEW.png");
				getimage(exit.img, "assets/EXIT01.png");
				
				playMusicOnce("music/buttonPress.mp3");
			}
			else if (mouse.is_up() && mouse.is_left())
			{
				//放出介绍界面，等待按键后返回
                getimage(introduction, "assets/intro01.png");
                putimage(0, 0, introduction);
				outtextxy(350, 450, "Press any key to continue");
                getch();
                getimage(introduction, "assets/intro02.png");
                putimage(0, 0, introduction);
				outtextxy(350, 450, "Press any key to continue");
                getch();
                getimage(introduction, "assets/intro03.png");
                putimage(0, 0, introduction);
				outtextxy(350, 450, "Press any key to continue");
                getch();
                getimage(introduction, "assets/intro04.png");
                putimage(0, 0, introduction);
				outtextxy(350, 450, "Press any key to continue");
                getch();
                getimage(introduction, "assets/LAST.png");
                putimage(0, 0, introduction);
                getch();
				putimage(0, 0, background);
				freshMenu(start, intro, exit);
			}
			else
			{
				state = 9;
				getimage(start.img, "assets/START01.png");
				getimage(intro.img, "assets/INTRODUCTION02.png");
				getimage(exit.img, "assets/EXIT01.png");
			}
		}
		//如果鼠标在EXIT上，同上
		else if (onButton(mouse, exit))
		{
			if (mouse.is_down() && mouse.is_left())
			{
				state = 10;
				getimage(start.img, "assets/START01.png");
				getimage(intro.img, "assets/INTRODUCTION01.png");
				getimage(exit.img, "assets/EXIT00.png");
				
				playMusicOnce("music/buttonPress.mp3");
			}
			else if (mouse.is_up() && mouse.is_left())
			{
				delimage(background);
				delimage(introduction);
				delimage(title.img);
				delimage(fish.img);
				delimage(others.img);
				delimage(start.img);
				delimage(intro.img);
				delimage(exit.img);
				delimage(story.img);
				delimage(infinite.img);
				bgm.Stop();
				bgm.Close();
				return MENU_EXIT;
			}
			else
			{
				state = 11;
				getimage(start.img, "assets/START01.png");
				getimage(intro.img, "assets/INTRODUCTION01.png");
				getimage(exit.img, "assets/EXIT03.png");
			}
		}
		//如果鼠标不在按钮上
		else
		{
			state = 12;
			getimage(start.img, "assets/START01.png");
			getimage(intro.img, "assets/INTRODUCTION01.png");
			getimage(exit.img, "assets/EXIT01.png");
		}
		if (state != lastState)
		{
			freshMenu(start, intro, exit);
		}
		lastState = state;
		while(mousemsg()) {mouse = getmouse();} //丢弃掉显示菜单前的鼠标事件
	}
}

//刷新动画
void freshAnimation(BUTTON start, BUTTON intro, BUTTON exit, PIMAGE background, ELEMENT_ON_MENU title, ELEMENT_ON_MENU fish, ELEMENT_ON_MENU others)
{
	cleardevice();
	putimage(0, 0, background);
	putimage_alphatransparent(NULL, others.img, others.x, others.y, BLACK, others.alpha);
	putimage_alphatransparent(NULL, title.img, title.x, title.y, BLACK, title.alpha);
	putimage_alphatransparent(NULL, fish.img, fish.x, fish.y, BLACK, fish.alpha);
	putimage_transparent(NULL, start.img, start.x, start.y, BLACK);
	putimage_transparent(NULL, intro.img, intro.x, intro.y, BLACK);
	putimage_transparent(NULL, exit.img, exit.x, exit.y, BLACK);
}

//刷新界面
void freshMenu(BUTTON start, BUTTON intro, BUTTON exit)
{
	putimage_transparent(NULL, start.img, start.x, start.y, BLACK);
	putimage_transparent(NULL, intro.img, intro.x, intro.y, BLACK);
	putimage_transparent(NULL, exit.img, exit.x, exit.y, BLACK);
}

//刷新选择模式界面
void freshStart(BUTTON story, BUTTON infinite)
{
	putimage_transparent(NULL, story.img, story.x, story.y, BLACK);
	putimage_transparent(NULL, infinite.img, infinite.x, infinite.y, BLACK);
}