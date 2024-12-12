//created by 裴思琦
#pragma once
#include<graphics.h>

//按钮结构体
struct BUTTON
{
	int x=220;
	int y;
	int width = 200;
	int height = 70;
	PIMAGE img=newimage();
};

//商店中按钮结构体
struct BUTTON_IN_SHOP
{
	int x;
	int y;
	int width = 95;
	int height = 32;
	PIMAGE img = newimage();
	int word;
	int lastWord;
	int state = NULL;
	int lastState;
	int price;
};

//判断鼠标是否在按钮上
bool onButton(mouse_msg mouse, BUTTON button)
{
	return mouse.x > button.x&& mouse.x < button.x + button.width && mouse.y>button.y&& mouse.y < button.y + button.height;
}

bool onButton(mouse_msg mouse, BUTTON_IN_SHOP button)
{
	return mouse.x > button.x&& mouse.x < button.x + button.width && mouse.y>button.y&& mouse.y < button.y + button.height;
}

//初始化按钮
void initializeButton(BUTTON* button, int x, int y, int width, int height, const char* address)
{
	button->x = x;
	button->y = y;
	button->width = width;
	button->height = height;
	getimage(button->img, address);
}

void initializeButton(BUTTON_IN_SHOP* button, int x, int y, int price)
{
	button->x = x;
	button->y = y;
	button->price = price;
}