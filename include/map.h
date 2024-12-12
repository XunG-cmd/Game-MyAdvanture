//created by 裴思琦

#pragma once

#include<graphics.h>

struct ELEMENT_ON_MAP
{
	int x;
	int y;
	PIMAGE img;
};

void moveX(ELEMENT_ON_MAP* rabbitOnMap, int x, PIMAGE background);
void moveY(ELEMENT_ON_MAP* rabbitOnMap, int y, PIMAGE background);
void freshMap(ELEMENT_ON_MAP* rabbitOnMap, PIMAGE background);
void exclamation(ELEMENT_ON_MAP* rabbitOnMap, PIMAGE background);

const int MAP_SPEED = 4;

void mapMove(int level)
{
	//定义兔子指针
	ELEMENT_ON_MAP rabbit;
	ELEMENT_ON_MAP* rabbitOnMap = &rabbit;

	//初始化
	rabbitOnMap->img = newimage();
	PIMAGE background = newimage();
	getimage(background, "assets/MAP2.png");
	getimage(rabbitOnMap->img, "assets/rabbitOnMap1.png");

	//分关卡操作（以下仅介绍其一）
	if (level == 1)
	{
		//初始化位置
		rabbitOnMap->x = 55;
		rabbitOnMap->y = 150;
		freshMap(rabbitOnMap, background);

		//开始移动
		moveY(rabbitOnMap, 70, background);
		delay_ms(250);
		moveX(rabbitOnMap, 140, background);
		delay_ms(500);
	}
	//同上
	if (level == 2)
	{
		rabbitOnMap->x = 310;
		rabbitOnMap->y = 220;
		freshMap(rabbitOnMap, background);

		moveX(rabbitOnMap, 55, background);
		delay_ms(250);
		moveY(rabbitOnMap, -70, background);
		delay_ms(500);
	}
	//同上
	if (level == 3)
	{
		rabbitOnMap->x = 430;
		rabbitOnMap->y = 150;
		freshMap(rabbitOnMap, background);

		moveY(rabbitOnMap, 70, background);
		delay_ms(250);
		moveX(rabbitOnMap, 95, background);
		delay_ms(250);
		moveY(rabbitOnMap, 145, background);
		delay_ms(500);
	}
	exclamation(rabbitOnMap, background);
	delay_ms(500);
	delimage(rabbit.img);
	delimage(background);
	return;
}

//x方向移动
void moveX(ELEMENT_ON_MAP* rabbitOnMap, int x, PIMAGE background)
{
	//若移动距离小于速度，一帧到位
	if (x <= MAP_SPEED && x >= -MAP_SPEED)
	{
		rabbitOnMap->x += x;
		freshMap(rabbitOnMap, background);
	}
	//移动距离大于速度，且为正
	else if (x > 0)
	{
		//按速度移动一帧，并进行递归
		rabbitOnMap->x += MAP_SPEED;
		freshMap(rabbitOnMap, background);
		moveX(rabbitOnMap, x - MAP_SPEED, background);
	}
	//移动距离大于速度，且为负
	else
	{
		rabbitOnMap->x -= MAP_SPEED;
		freshMap(rabbitOnMap, background);
		moveX(rabbitOnMap, x + MAP_SPEED, background);
	}
}


//y方向移动
void moveY(ELEMENT_ON_MAP* rabbitOnMap, int y, PIMAGE background)
{
	if (y <= MAP_SPEED && y >= -MAP_SPEED)
	{
		rabbitOnMap->y += y;
		freshMap(rabbitOnMap, background);
	}
	else if (y > 0)
	{
		rabbitOnMap->y += MAP_SPEED;
		freshMap(rabbitOnMap, background);
		moveY(rabbitOnMap, y - MAP_SPEED, background);
	}
	else
	{
		rabbitOnMap->y -= MAP_SPEED;
		freshMap(rabbitOnMap, background);
		moveY(rabbitOnMap, y + MAP_SPEED, background);
	}
}

//地图刷新并延迟
void freshMap(ELEMENT_ON_MAP* rabbitOnMap, PIMAGE background)
{
	cleardevice();
	putimage(0, 0, background);
	putimage_transparent(NULL, rabbitOnMap->img, rabbitOnMap->x, rabbitOnMap->y, BLACK);
	delay_ms(50);
}

//移动到位后操作，两帧交替显示
void exclamation(ELEMENT_ON_MAP* rabbitOnMap, PIMAGE background)
{
	getimage(rabbitOnMap->img, "assets/rabbitOnMap2.png");
	freshMap(rabbitOnMap, background);
	delay_ms(450);
	getimage(rabbitOnMap->img, "assets/rabbitOnMap1.png");
	freshMap(rabbitOnMap, background);
	delay_ms(450);
	getimage(rabbitOnMap->img, "assets/rabbitOnMap2.png");
	freshMap(rabbitOnMap, background);
	delay_ms(450);
	getimage(rabbitOnMap->img, "assets/rabbitOnMap1.png");
	freshMap(rabbitOnMap, background);
	delay_ms(450);
	getimage(rabbitOnMap->img, "assets/rabbitOnMap2.png");
	freshMap(rabbitOnMap, background);
	delay_ms(450);
}
