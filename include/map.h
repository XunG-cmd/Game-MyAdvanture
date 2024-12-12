//created by ��˼��

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
	//��������ָ��
	ELEMENT_ON_MAP rabbit;
	ELEMENT_ON_MAP* rabbitOnMap = &rabbit;

	//��ʼ��
	rabbitOnMap->img = newimage();
	PIMAGE background = newimage();
	getimage(background, "assets/MAP2.png");
	getimage(rabbitOnMap->img, "assets/rabbitOnMap1.png");

	//�ֹؿ����������½�������һ��
	if (level == 1)
	{
		//��ʼ��λ��
		rabbitOnMap->x = 55;
		rabbitOnMap->y = 150;
		freshMap(rabbitOnMap, background);

		//��ʼ�ƶ�
		moveY(rabbitOnMap, 70, background);
		delay_ms(250);
		moveX(rabbitOnMap, 140, background);
		delay_ms(500);
	}
	//ͬ��
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
	//ͬ��
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

//x�����ƶ�
void moveX(ELEMENT_ON_MAP* rabbitOnMap, int x, PIMAGE background)
{
	//���ƶ�����С���ٶȣ�һ֡��λ
	if (x <= MAP_SPEED && x >= -MAP_SPEED)
	{
		rabbitOnMap->x += x;
		freshMap(rabbitOnMap, background);
	}
	//�ƶ���������ٶȣ���Ϊ��
	else if (x > 0)
	{
		//���ٶ��ƶ�һ֡�������еݹ�
		rabbitOnMap->x += MAP_SPEED;
		freshMap(rabbitOnMap, background);
		moveX(rabbitOnMap, x - MAP_SPEED, background);
	}
	//�ƶ���������ٶȣ���Ϊ��
	else
	{
		rabbitOnMap->x -= MAP_SPEED;
		freshMap(rabbitOnMap, background);
		moveX(rabbitOnMap, x + MAP_SPEED, background);
	}
}


//y�����ƶ�
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

//��ͼˢ�²��ӳ�
void freshMap(ELEMENT_ON_MAP* rabbitOnMap, PIMAGE background)
{
	cleardevice();
	putimage(0, 0, background);
	putimage_transparent(NULL, rabbitOnMap->img, rabbitOnMap->x, rabbitOnMap->y, BLACK);
	delay_ms(50);
}

//�ƶ���λ���������֡������ʾ
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
