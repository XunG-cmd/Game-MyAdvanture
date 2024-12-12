#pragma once
//created by 裴思琦

#pragma once

#include<graphics.h>
#include"character.h"

//教程信息结构体
struct TUTORIAL_UI
{
	int x;
	int y=30;
	int frame=1;
	int state = 1;
	int rabbitLastState = RUN;
	int rabbitLastX = 50;
	int finish = 0;
	PIMAGE img;
};

//执行教程，判断教程是否完成
bool getTutorial(int level,TUTORIAL_UI * tutorial , CHARACTER * rabbit)
{
	//在第一关且第一关教程未完成
	if (level == 1 && tutorial->finish != 1)
	{
		//目前所属教程阶段
		switch (tutorial->state)
		{
			//第一阶段：向上变道
		case 1:
			tutorial->x = 288;
			//根据frame更改帧
			if (tutorial->frame <= 10)
				getimage(tutorial->img, "assets/UP01.png");
			else if (tutorial->frame <= 20)
				getimage(tutorial->img, "assets/UP00.png");
			else
				tutorial->frame = 1;

			//完成教程，进入下一阶段
			if (tutorial->rabbitLastState == RUN && rabbit->state == UP)
				tutorial->state++;
			break;


			//第二阶段：向下变道，同上
		case 2:
			tutorial->x = 288;
			if (tutorial->frame <= 10)
				getimage(tutorial->img, "assets/DOWN01.png");
			else if (tutorial->frame <= 20)
				getimage(tutorial->img, "assets/DOWN00.png");
			else
				tutorial->frame = 1;

			if (tutorial->rabbitLastState == RUN && rabbit->state == DOWN)
				tutorial->state++;
			break;


			//第三阶段：左移，同上
		case 3:
			tutorial->x = 288;
			if (tutorial->frame <= 10)
				getimage(tutorial->img, "assets/LEFT01.png");
			else if (tutorial->frame <= 20)
				getimage(tutorial->img, "assets/LEFT00.png");
			else
				tutorial->frame = 1;

			if (tutorial->rabbitLastState == RUN && rabbit->x < tutorial->rabbitLastX)
				tutorial->state++;
			break;


			//第四阶段：右移，同上
		case 4:
			tutorial->x = 288;
			if (tutorial->frame <= 10)
				getimage(tutorial->img, "assets/RIGHT01.png");
			else if (tutorial->frame <= 20)
				getimage(tutorial->img, "assets/RIGHT00.png");
			else
				tutorial->frame = 1;

			//完成所有教程，重置
			if (tutorial->rabbitLastState == RUN && rabbit->x > tutorial->rabbitLastX)
			{
				tutorial->state = 1;
				tutorial->finish = 1;
				tutorial->x = 1000;
			}
			break;
		}
	}
	//在第二关且第二关教程未完成，同上
	else if (level == 2 && tutorial->finish != 2)
	{
		switch (tutorial->state)
		{
		case 1:
			tutorial->x = 288;
			if (tutorial->frame <= 10)
				getimage(tutorial->img, "assets/CTRL01.png");
			else if (tutorial->frame <= 20)
				getimage(tutorial->img, "assets/CTRL00.png");
			else
				tutorial->frame = 1;

			if (tutorial->rabbitLastState == RUN && rabbit->state == ROLL)
				tutorial->state++;
			break;


		case 2:
			tutorial->x = 220;
			if (tutorial->frame <= 10)
				getimage(tutorial->img, "assets/SPACE01.png");
			else if (tutorial->frame <= 20)
				getimage(tutorial->img, "assets/SPACE00.png");
			else
				tutorial->frame = 1;

			if (tutorial->rabbitLastState == RUN && rabbit->state == JUMP)
				tutorial->state++;
			break;


		case 3:
			tutorial->x = 188;
			if (tutorial->frame <= 10)
				getimage(tutorial->img, "assets/SPACE CTRL01.png");
			else if (tutorial->frame <= 20)
				getimage(tutorial->img, "assets/SPACE CTRL00.png");
			else
				tutorial->frame = 1;

			if (tutorial->rabbitLastState == JUMP && rabbit->state == ROLL)
			{
				tutorial->state = 1;
				tutorial->finish = 2;
				tutorial->x = 1000;
			}
			break;
		}
	}
	//若教程已完成
	else
		return 1;

	//更新
	tutorial->rabbitLastState = rabbit->state;
	tutorial->rabbitLastX = rabbit->x;
	tutorial->frame++;
	return 0;
}