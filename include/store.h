//code created by 裴思琦

#pragma once
#include"multithreadMusic.h"
//宏定义显示文字（类）
#define EQUIPPED 0
#define EQUIP 1
#define BUY 2

//增补宏定义鼠标与按钮关系
#define ON 1

int buy(int num, int price);
void freshShop(PIMAGE counter, BUTTON_IN_SHOP* button, BUTTON home, PIMAGE coinbox);
void freshBuy(PIMAGE window, BUTTON buy, BUTTON cancel);
void insufficient();

//商城主函数
int store(CHARACTER* rabbit)
{
	//初始化
	BUTTON_IN_SHOP button[9];
	BUTTON home;
	PIMAGE counter = newimage();
	PIMAGE coinbox = newimage();
	PIMAGE light[2] = { newimage() ,newimage() };
	mouse_msg mouse = { 0 };
	int ifchange = 0, homeState, lastHomeState;
	getimage(counter, "assets/Counter.png");
	getimage(coinbox, "assets/coinboxs.png");
	getimage(light[0], "assets/light00.png");
	getimage(light[1], "assets/light01.png");
	initializeButton(&button[0], 40, 135, 0);
	initializeButton(&button[1], 270, 135, 300);
	initializeButton(&button[2], 510, 135, 500);
	initializeButton(&button[3], 40, 293, 500);
	initializeButton(&button[4], 270, 293, 800);
	initializeButton(&button[5], 510, 293, 800);
	initializeButton(&button[6], 40, 450, 1000);
	initializeButton(&button[7], 270, 450, 1200);
	initializeButton(&button[8], 510, 450, 1500);
	initializeButton(&home, 0, 0, 35, 35, "assets/HOME01.png");
	setbkmode(TRANSPARENT);
	setfont(35, 0, "impact");
	setcolor(EGERGB(255, 200, 0));
	setfillcolor(EGERGB(255, 255, 0));

	//根据状态初始化按钮图像
	for (int i = 0; i <= 8; i++)
	{
		//若是默认皮肤或皮肤已解锁，显示equipe按钮
		if (i == 0 || skinAvaliable(i)==1)
		{
			getimage(button[i].img, "assets/equipe01.png");
		}
		//若未解锁
		else
		{
			//按价格分类，显示对应价格
			switch (button[i].price)
			{
			case 300:
				getimage(button[i].img, "assets/3hundred01.png");
				break;

			case 500:
				getimage(button[i].img, "assets/5hundred01.png");
				break;

			case 800:
				getimage(button[i].img, "assets/8hundred01.png");
				break;

			case 1000:
				getimage(button[i].img, "assets/10hundred01.png");
				break;

			case 1200:
				getimage(button[i].img, "assets/12hundred01.png");
				break;

			case 1500:
				getimage(button[i].img, "assets/15hundred01.png");
				break;
			}
		}
	}
	//将目前皮肤显示为已装备并刷新
	getimage(button[rabbit->skin].img, "assets/equipped.png");
	freshShop(counter, button, home, coinbox);

	while (1)
	{
		//获取鼠标输入
		mouse = getmouse();
		ifchange = 0;

		for (int i = 0; i <= 8; i++)
		{
			//若是默认皮肤或皮肤已解锁，将文字设为EQUIP
			if (i==0 || skinAvaliable(i))
			{
				button[i].word = EQUIP;
			}
			//若未解锁，将文字设为BUY
			else
			{
				button[i].word = BUY;
			}

			//如果鼠标在第i个按钮上
			if (onButton(mouse, button[i]))
			{
				//若鼠标按下
				if (mouse.is_down() && mouse.is_left())
				{
					//对应状态设为DOWN
					button[i].state = DOWN;
					playMusicOnce("music/buttonPress.mp3");
				}
				//若鼠标抬起
				else if (mouse.is_up() && mouse.is_left())
				{
					//如果文字为BUY
					if(button[i].word==BUY)
					{
						//如果顺利完成购买
						if (buy(i, button[i].price))
						{
							MUSIC getskin;
							getskin.OpenFile("../../bit-adventure/music/�����?��?.mp3");
							getskin.Play(0);
							//将文字设为EQUIP，保存皮肤解锁，减掉金币
							button[i].word = EQUIP;
							saveSkinPurchase(i);
							addMoney(-button[i].price);

							//获取皮肤对应图片文件地址，并获取图片
							char skinAddress[100]= "assets/rabbitrun1.", skinNumStr[2]="0";
							skinNumStr[0] = i + '0';
							skinNumStr[1] = '\0';
							strcat(skinAddress, skinNumStr);
							strcat(skinAddress, ".png");
							getimage(rabbit->img, skinAddress);
							
							//闪烁几个循环
							for (int j = 0; j <5; j++)
							{
								freshShop(counter, button, home, coinbox);
								putimage_transparent(NULL, light[0], 215, 135, BLACK);
								putimage_transparent(NULL, rabbit->img, 290, 215, BLACK);
								delay_ms(500);
								freshShop(counter, button, home, coinbox);
								putimage_transparent(NULL, light[1], 215, 135, BLACK);
								putimage_transparent(NULL, rabbit->img, 290, 215, BLACK);
								delay_ms(500);
							}
							getskin.Stop();
							getskin.Close();
						}
						ifchange = 1;
					}
					//如果文字不是BUY，即EQUIPE或EQUIPPED
					else
					{
						//将装备皮肤编号设为i
						rabbit->skin = i;
					}
				}
				//如果鼠标只是放在上面
				else
				{
					//对应状态设为ON
					button[i].state = ON;
				}
			}
			//如果没放在这个按钮上
			else
			{
				//对应状态设为NULL
				button[i].state = NULL;
			}
		}
		//将目前皮肤显示为已装备
		button[rabbit->skin].word = EQUIPPED;

		for (int i = 0; i <= 8; i++)
		{
			//检测按钮文字，设置对应图片
			switch (button[i].word)
			{
			case EQUIPPED:
				getimage(button[i].img, "assets/equipped.png");
				break;

			case EQUIP:
				//检测按钮状态，设置对应图片
				switch (button[i].state)
				{
				case NULL:
					getimage(button[i].img, "assets/equipe01.png");
					break;

				case ON:
					getimage(button[i].img, "assets/equipe02.png");
					break;

				case DOWN:
					getimage(button[i].img, "assets/equipe00.png");
					break;
				}
				break;

			case BUY:
				switch (button[i].state)
				{
				case NULL:
					//检测按钮对应价格，设置对应图片
					switch (button[i].price)
					{
					case 300:
						getimage(button[i].img, "assets/3hundred01.png");
						break;

					case 500:
						getimage(button[i].img, "assets/5hundred01.png");
						break;

					case 800:
						getimage(button[i].img, "assets/8hundred01.png");
						break;

					case 1000:
						getimage(button[i].img, "assets/10hundred01.png");
						break;

					case 1200:
						getimage(button[i].img, "assets/12hundred01.png");
						break;

					case 1500:
						getimage(button[i].img, "assets/15hundred01.png");
						break;
					}
					break;

				case ON:
					switch (button[i].price)
					{
					case 300:
						getimage(button[i].img, "assets/3hundred02.png");
						break;

					case 500:
						getimage(button[i].img, "assets/5hundred02.png");
						break;

					case 800:
						getimage(button[i].img, "assets/8hundred02.png");
						break;

					case 1000:
						getimage(button[i].img, "assets/10hundred02.png");
						break;

					case 1200:
						getimage(button[i].img, "assets/12hundred02.png");
						break;

					case 1500:
						getimage(button[i].img, "assets/15hundred02.png");
						break;
					}
					break;

				case DOWN:
					switch (button[i].price)
					{
					case 300:
						getimage(button[i].img, "assets/3hundred00.png");
						break;

					case 500:
						getimage(button[i].img, "assets/5hundred00.png");
						break;

					case 800:
						getimage(button[i].img, "assets/8hundred00.png");
						break;

					case 1000:
						getimage(button[i].img, "assets/10hundred00.png");
						break;

					case 1200:
						getimage(button[i].img, "assets/12hundred00.png");
						break;

					case 1500:
						getimage(button[i].img, "assets/15hundred00.png");
						break;
					}
					break;
				}
				break;
			}
		}

		//如果鼠标在HOME按钮上
		if (onButton(mouse, home))
		{
			//如果鼠标按下
			if (mouse.is_down() && mouse.is_left())
			{
				//设定当前状态，更改图片
				homeState = 1;
				getimage(home.img, "assets/HOME00.png");
				playMusicOnce("music/buttonPress.mp3");
			}
			//如果鼠标抬起
			else if (mouse.is_up() && mouse.is_left())
			{
				//返回装备的皮肤编号
				return rabbit->skin;
			}
			//若只是放在上面
			else
			{
				//设定当前状态，更改图片
				homeState = 2;
				getimage(home.img, "assets/HOME02.png");
			}
		}
		//若不在HOME上面
		else
		{
			//设定当前状态，更改图片
			homeState = 3;
			getimage(home.img, "assets/HOME01.png");
		}

		for (int i = 0; i <= 8; i++)
		{
			//如果出现了任何状态改变
			if (button[i].state != button[i].lastState || button[i].word != button[i].lastWord || homeState!=lastHomeState)
			{
				//设定此次循环后需刷新屏幕
				ifchange = 1;
			}
			//更新laststate
			button[i].lastState = button[i].state;
			button[i].lastWord = button[i].word;
			lastHomeState = homeState;
		}

		//如果需要刷新屏幕
		if (ifchange)
		{
			//刷新屏幕
			freshShop(counter, button, home, coinbox);
		}
	}
}

//刷新屏幕
void freshShop(PIMAGE counter, BUTTON_IN_SHOP* button, BUTTON home, PIMAGE coinbox)
{
	putimage(0, 0, counter);
	for (int i = 0; i < 9; i++)
	{
		putimage_transparent(NULL, button[i].img, button[i].x, button[i].y, BLACK);
	}
	putimage_transparent(NULL, coinbox, 550, 10, BLACK);
	putimage_transparent(NULL, home.img, 0, 0, BLACK);
	char moneyStr[10];
	sprintf(moneyStr, "%d", getMoney());
	outtextxy(575, 0, moneyStr);
}

//购买窗口
int buy(int num, int price)
{
	//初始化
	mouse_msg mouse = { 0 };
	PIMAGE window = newimage();
	BUTTON buy, cancel;
	//获取对应窗口图片地址
	char address[100] = "assets/";
	int len = strlen(address);
	int state, lastState=0;
	address[len] = num + '0';
	address[len + 1] = '\0';
	strcat(address, ".png");
	getimage(window, address);
	initializeButton(&buy, 175, 330, 95, 32, "assets/BUY01.png");
	initializeButton(&cancel, 370, 330, 95, 32, "assets/cancel01.png");
	freshBuy(window, buy, cancel);

	//以下过程同menu.h及infiniteMap.h中的按钮操作，不再解释
	while (1)
	{
		mouse = getmouse();
		if (onButton(mouse, buy))
		{
			if (mouse.is_down() && mouse.is_left())
			{
				state = 1;
				getimage(buy.img, "assets/BUY00.png");
				getimage(cancel.img, "assets/cancel01.png");
				playMusicOnce("music/buttonPress.mp3");
			}
			else if (mouse.is_up() && mouse.is_left())
			{
				//如果金币数大于等于价格
				if (getMoney() >= price)
				{
					//返回1，进行购买
					return 1;
				}
				else
				{
					//显示金币不足窗口，并返回0，不进行购买
					insufficient();
					return 0;
				}
			}
			else
			{
				state = 2;
				getimage(buy.img, "assets/BUY02.png");
				getimage(cancel.img, "assets/cancel01.png");
			}
		}
		else if (onButton(mouse, cancel))
		{
			if (mouse.is_down() && mouse.is_left())
			{
				state = 3;
				getimage(buy.img, "assets/BUY01.png");
				getimage(cancel.img, "assets/cancel00.png");
				playMusicOnce("music/buttonPress.mp3");
			}
			else if (mouse.is_up() && mouse.is_left())
			{
				return 0;
			}
			else
			{
				state = 4;
				getimage(buy.img, "assets/BUY01.png");
				getimage(cancel.img, "assets/cancel02.png");
			}
		}
		else
		{
			state = 5;
			getimage(buy.img, "assets/BUY01.png");
			getimage(cancel.img, "assets/cancel01.png");
		}

		if (state != lastState)
		{
			freshBuy(window, buy, cancel);
		}
		lastState = state;
	}
}

//刷新购买窗口
void freshBuy(PIMAGE window, BUTTON buy, BUTTON cancel)
{
	putimage(120, 90, window);
	putimage_transparent(NULL, buy.img, buy.x, buy.y, BLACK);
	putimage_transparent(NULL, cancel.img, cancel.x, cancel.y, BLACK);
}

//金币不足提示窗口
void insufficient()
{
	//初始化
	mouse_msg mouse = { 0 };
	PIMAGE window = newimage();
	BUTTON back;
	getimage(window, "assets/INSUFFICIENT01.png");
	initializeButton(&back, 272, 290, 95, 32, "assets/BACK01.png");
	int state, lastState=0;

	putimage(140, 105, window);
	putimage_transparent(NULL, back.img, back.x, back.y, BLACK);

	//以下过程同menu.h及infiniteMap.h中的按钮操作，不再解释
	while (1)
	{
		mouse = getmouse();
		if (onButton(mouse, back))
		{
			if (mouse.is_down() && mouse.is_left())
			{
				state = 1;
				getimage(back.img, "assets/back00.png");
				playMusicOnce("music/buttonPress.mp3");
			}
			else if (mouse.is_up() && mouse.is_left())
			{
				return;
			}
			else
			{
				state = 2;
				getimage(back.img, "assets/back02.png");
			}
		}
		else
		{
			state = 3;
			getimage(back.img, "assets/back01.png");
		}

		if (state != lastState)
		{
			putimage_transparent(NULL, back.img, back.x, back.y, BLACK);
		}
		lastState = state;
	}
}