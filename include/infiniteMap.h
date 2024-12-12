//code created by 裴思琦
#pragma once
#include "button.h"
#include "bitAdventure.h"
#include "save.h"
#include "store.h"
#include "multithreadMusic.h"

#define INFINITE_ROAD 1
#define INFINITE_CANTEEN 2
#define INFINITE_NORTHLAKE 3
#define INFINITE_HOME 4

void freshInfiniteMap(PIMAGE map, BUTTON shop, BUTTON road, BUTTON canteen, BUTTON northlake, BUTTON home, PIMAGE coinbox);

//无尽关卡地图操作
void infiniteMap(int returns[2])
{
	//初始化
	BUTTON shop, road, canteen, northlake, home;
	PIMAGE map = newimage();
	PIMAGE coinbox = newimage();
	mouse_msg mouse = { 0 };
	CHARACTER rabbit;
	rabbit.skin = returns[1];
	int state = 0, lastState = 0;
	getimage(map, "assets/MAP2.png");
	getimage(coinbox, "assets/coinbox.png");
	initializeButton(&shop, 58, 120, 50, 80, "assets/cloth0.png");
	initializeButton(&road, 246, 225, 50, 38, "assets/rabbitOnMap1.png");
	initializeButton(&canteen, 392, 110, 50, 38, "assets/rabbitOnMap1.png");
	initializeButton(&northlake, 525, 360, 50, 38, "assets/rabbitOnMap1.png");
	initializeButton(&home, 0, 0, 35, 35, "assets/HOME01.png");
	setbkmode(TRANSPARENT);
	setfont(40, 0, "impact");
	setcolor(EGERGB(255, 215, 0));

	freshInfiniteMap(map, shop, road, canteen, northlake, home, coinbox);

	while (1)
	{
		//获取鼠标消息并处理，具体方法同menu.h，请参考其中注释
		mouse = getmouse();
		if (onButton(mouse, shop))
		{
			if (mouse.is_down() && mouse.is_left())
			{
				state = 1;
				getimage(shop.img, "assets/cloth0.png");
				getimage(road.img, "assets/rabbitOnMap1.png");
				getimage(canteen.img, "assets/rabbitOnMap1.png");
				getimage(northlake.img, "assets/rabbitOnMap1.png");
				getimage(home.img, "assets/HOME01.png");
				playMusicOnce("music/buttonPress.mp3");
			}
			else if (mouse.is_up() && mouse.is_left())
			{
				state = 20;
				//???????
				store(&rabbit);
				//???????
				setfont(40, 0, "impact");
				setcolor(EGERGB(255, 215, 0));
			}
			else
			{
				state = 2;
				getimage(shop.img, "assets/cloth1.png");
				getimage(road.img, "assets/rabbitOnMap1.png");
				getimage(canteen.img, "assets/rabbitOnMap1.png");
				getimage(northlake.img, "assets/rabbitOnMap1.png");
				getimage(home.img, "assets/HOME01.png");
			}
		}
		else if (onButton(mouse, road))
		{
			if (mouse.is_down() && mouse.is_left())
			{
				state = 3;
				getimage(shop.img, "assets/cloth0.png");
				getimage(road.img, "assets/rabbitOnMap1.png");
				getimage(canteen.img, "assets/rabbitOnMap1.png");
				getimage(northlake.img, "assets/rabbitOnMap1.png");
				getimage(home.img, "assets/HOME01.png");
				playMusicOnce("music/buttonPress.mp3");
			}
			else if (mouse.is_up() && mouse.is_left())
			{
				returns[0] = INFINITE_ROAD;
				returns[1] = rabbit.skin;
				return;
			}
			else
			{
				state = 4;
				getimage(shop.img, "assets/cloth0.png");
				getimage(road.img, "assets/rabbitOnMap2.png");
				getimage(canteen.img, "assets/rabbitOnMap1.png");
				getimage(northlake.img, "assets/rabbitOnMap1.png");
				getimage(home.img, "assets/HOME01.png");
			}
		}
		else if (onButton(mouse, canteen))
		{
			if (mouse.is_down() && mouse.is_left())
			{
				state = 5;
				getimage(shop.img, "assets/cloth0.png");
				getimage(road.img, "assets/rabbitOnMap1.png");
				getimage(canteen.img, "assets/rabbitOnMap1.png");
				getimage(northlake.img, "assets/rabbitOnMap1.png");
				getimage(home.img, "assets/HOME01.png");
				playMusicOnce("music/buttonPress.mp3");
			}
			else if (mouse.is_up() && mouse.is_left())
			{
				returns[0] = INFINITE_CANTEEN;
				returns[1] = rabbit.skin;
				return;
			}
			else
			{
				state = 6;
				getimage(shop.img, "assets/cloth0.png");
				getimage(road.img, "assets/rabbitOnMap1.png");
				getimage(canteen.img, "assets/rabbitOnMap2.png");
				getimage(northlake.img, "assets/rabbitOnMap1.png");
				getimage(home.img, "assets/HOME01.png");
			}
		}
		else if (onButton(mouse, northlake))
		{
			if (mouse.is_down() && mouse.is_left())
			{
				state = 7;
				getimage(shop.img, "assets/cloth0.png");
				getimage(road.img, "assets/rabbitOnMap1.png");
				getimage(canteen.img, "assets/rabbitOnMap1.png");
				getimage(northlake.img, "assets/rabbitOnMap1.png");
				getimage(home.img, "assets/HOME01.png");
				playMusicOnce("music/buttonPress.mp3");
			}
			else if (mouse.is_up() && mouse.is_left())
			{
				returns[0] = INFINITE_NORTHLAKE;
				returns[1] = rabbit.skin;
				return;
			}
			else
			{
				state = 8;
				getimage(shop.img, "assets/cloth0.png");
				getimage(road.img, "assets/rabbitOnMap1.png");
				getimage(canteen.img, "assets/rabbitOnMap1.png");
				getimage(northlake.img, "assets/rabbitOnMap2.png");
				getimage(home.img, "assets/HOME01.png");
			}
		}
		else if (onButton(mouse, home))
		{
			if (mouse.is_down() && mouse.is_left())
			{
				state = 9;
				getimage(shop.img, "assets/cloth0.png");
				getimage(road.img, "assets/rabbitOnMap1.png");
				getimage(canteen.img, "assets/rabbitOnMap1.png");
				getimage(northlake.img, "assets/rabbitOnMap1.png");
				getimage(home.img, "assets/HOME00.png");
				playMusicOnce("music/buttonPress.mp3");
			}
			else if (mouse.is_up() && mouse.is_left())
			{
				returns[0] = INFINITE_HOME;
				returns[1] = rabbit.skin;
				return;
			}
			else
			{
				state = 10;
				getimage(shop.img, "assets/cloth0.png");
				getimage(road.img, "assets/rabbitOnMap1.png");
				getimage(canteen.img, "assets/rabbitOnMap1.png");
				getimage(northlake.img, "assets/rabbitOnMap1.png");
				getimage(home.img, "assets/HOME02.png");
			}
		}
		else
		{
		state = 0;
			getimage(shop.img, "assets/cloth0.png");
			getimage(road.img, "assets/rabbitOnMap1.png");
			getimage(canteen.img, "assets/rabbitOnMap1.png");
			getimage(northlake.img, "assets/rabbitOnMap1.png");
			getimage(home.img, "assets/HOME01.png");
		}
		if (state != lastState)
		{
			freshInfiniteMap(map, shop, road, canteen, northlake, home, coinbox);
			setfont(20, 0, "impact");
			setcolor(BLACK);
			switch (state)
			{
			case 1:
			case 2:
				setfont(25, 0, "impact");
				outtextxy(43, 190, "SKIN SHOP");
				break;
			case 3:
			case 4:
				outtextxy(236, 185, "HIGHSCORE");
				setfont(25, 0, "impact");
				outtextxy(251, 200, getHighScoreStr(1));
				break;

			case 5:
			case 6:
				outtextxy(442, 110, "HIGHSCORE");
				setfont(25, 0, "impact");
				outtextxy(457, 125, getHighScoreStr(2));
				break;

			case 7:
			case 8:
				outtextxy(495, 320, "HIGHSCORE");
				setfont(25, 0, "impact");
				outtextxy(515, 335, getHighScoreStr(3));
				break;
			}
			setfont(40, 0, "impact");
			setcolor(EGERGB(255, 215, 0));
		}
		lastState = state;
	}
}

//刷新地图
void freshInfiniteMap(PIMAGE map,BUTTON shop, BUTTON road, BUTTON canteen, BUTTON northlake, BUTTON home, PIMAGE coinbox)
{
	putimage(0, 0, map);
	putimage_transparent(NULL, shop.img, shop.x, shop.y, BLACK);
	putimage_transparent(NULL, road.img, road.x, road.y, BLACK);
	putimage_transparent(NULL, canteen.img, canteen.x, canteen.y, BLACK);
	putimage_transparent(NULL, northlake.img, northlake.x, northlake.y, BLACK);
	putimage_transparent(NULL, home.img, home.x, home.y, BLACK);
	putimage_transparent(NULL, coinbox, 500, 0, BLACK);
	//打印金币数
	outtextxy(550, 5, getMoneyStr());
}