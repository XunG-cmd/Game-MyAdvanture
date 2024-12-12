//code created by ��˼��

#pragma once

#include "bitAdventure.h"
#include "multithreadMusic.h"
#include <string.h>
//�����Ӧ����ֵ
const int KEY_UP = 294;
const int KEY_LEFT = 293;
const int KEY_DOWN = 296;
const int KEY_RIGHT = 295;
const int KEY_SPACE = 32;

//����֡�ٶȼ���Ծ�߶�ϵ��
const int CHARACTER_SPEED = 8;
const int HEIGHT_LEVEL = 8;


//***********************����ԭ��"include/character.cpp"**************************
/*
void action(CHARACTER* rabbit)
input: rabbit ��ɫ�ṹ��ָ��
operation: ��ȡ��ɫ״̬���ݴ˶Խ�ɫ�ṹ��������иı�
output: ��

bool keyDetect(CHARACTER * rabbit , int level)
input: rabbit ��ɫ�ṹ��ָ��
		  level �ؿ����
operation: ���������룬���˸ı��ɫ״̬
output: �Ƿ���Esc��
*/
void action(CHARACTER* rabbit);
bool keyDetect(CHARACTER* rabbit, int level);
void initializeSkin(CHARACTER* rabbit);
void doubleJump(CHARACTER* rabbit);
//**************************************END***************************************

//��ȡ��ɫ״̬���ݴ˶Խ�ɫ�ṹ��������иı�
void action(CHARACTER* rabbit)
{
	//״̬Ϊ��Ծʱ
	if (rabbit->state == JUMP)
	{
		//�����Σ�ͨ����֡���ָı�߶�
		if (rabbit->jumpTime < HEIGHT_LEVEL)
		{
			rabbit->jumpTime++;
			rabbit->h += (HEIGHT_LEVEL - rabbit->jumpTime) + 5;
			rabbit->jumpState = UP;
			putimage(rabbit->img, 0, 0, rabbit->frameSet[JUMP][1][rabbit->skin]);
		}
		//�½��Σ�ͨ����֡���ָı�߶�
		else if (rabbit->jumpTime >= HEIGHT_LEVEL && rabbit->jumpTime < 2 * HEIGHT_LEVEL)
		{
			rabbit->h -= (rabbit->jumpTime - HEIGHT_LEVEL) + 5;
			rabbit->jumpTime++;
			rabbit->jumpState = DOWN;
			putimage(rabbit->img, 0, 0, rabbit->frameSet[JUMP][2][rabbit->skin]);
		}
		//�����Ծ����λ
		else
		{
			rabbit->jumpTime = 0;
			rabbit->h = 0;
			rabbit->state = RUN;
		}

		//�м�Σ�����ͼ��
		if (rabbit->jumpTime > 0.8 * HEIGHT_LEVEL && rabbit->jumpTime < 1.2 * HEIGHT_LEVEL)
			putimage(rabbit->img, 0, 0, rabbit->frameSet[RUN][1][rabbit->skin]);
	}

	//״̬Ϊ���ϱ��ʱ
	if (rabbit->state == UP)
	{
		putimage(rabbit->img, 0, 0, rabbit->frameSet[RUN][1][rabbit->skin]);
		rabbit->fixY -= 30;				//��������ֵ�����뵽����y������

		//�������ʱ����λ
		if (rabbit->fixY == -120)
		{
			rabbit->fixY = 0;
			rabbit->state = RUN;
			rabbit->lane--;
		}
	}

	//״̬Ϊ���±��ʱ��ͬ��
	if (rabbit->state == DOWN)
	{
		putimage(rabbit->img, 0, 0, rabbit->frameSet[RUN][1][rabbit->skin]);
		rabbit->fixY += 30;

		if (rabbit->fixY == 120)
		{
			rabbit->fixY = 0;
			rabbit->state = RUN;
			rabbit->lane++;
		}
	}

	//״̬Ϊ�ܶ�ʱ��ÿ6��ѭ���л�һ֡
	if (rabbit->state == RUN)
		if (rabbit->frame <= 6)
			putimage(rabbit->img, 0, 0, rabbit->frameSet[RUN][1][rabbit->skin]);
		else if (rabbit->frame <= 12)
			putimage(rabbit->img, 0, 0, rabbit->frameSet[RUN][2][rabbit->skin]);
		else
			rabbit->frame = 1;

	//״̬Ϊ����ʱ��ÿ3��ѭ���л�һ֡
	if (rabbit->state == ROLL)
	{
		if (rabbit->frame <= 3)
			putimage(rabbit->img, 0, 0, rabbit->frameSet[ROLL][1][rabbit->skin]);
		else if (rabbit->frame <= 6)
			putimage(rabbit->img, 0, 0, rabbit->frameSet[ROLL][2][rabbit->skin]);
		else if (rabbit->frame <= 9)
			putimage(rabbit->img, 0, 0, rabbit->frameSet[ROLL][3][rabbit->skin]);
		else if (rabbit->frame <= 12)
			putimage(rabbit->img, 0, 0, rabbit->frameSet[ROLL][4][rabbit->skin]);
		else
			rabbit->frame = 1;

		//��ʼ����ʱ����ɫ���ڿ��У���������ֵ
		if (rabbit->h - rabbit->fixY >= 20 && rabbit->h != 0)
			rabbit->fixY += 20;
		//��غ�λ
		else
		{
			rabbit->jumpTime = 0;
			rabbit->h = 0;
			rabbit->fixY = 0;
		}
	}
}

//���������룬���˸ı��ɫ״̬
bool keyDetect(CHARACTER* rabbit, int level)
{
	//�˲������ڼ�ⰴ�����
	while (kbhit())
	{
		int k = getch();
		if (rabbit->protect == PROTECT_OFF) {
			switch (k)
			{
				//�ϼ����
			case KEY_UP:
				if (rabbit->lane != 1 && rabbit->state == RUN)
					rabbit->state = UP;
				break;

				//�¼����
			case KEY_DOWN:
				if (rabbit->lane != 3 && rabbit->state == RUN)
					rabbit->state = DOWN;
				break;

				//�ո���
			case KEY_SPACE:
				if (level != 1 && rabbit->state != UP && rabbit->state != DOWN){
					playMusicOnce("music/jump.mp3");
					rabbit->state = JUMP;
				}
				break;
			}
		}
		else {
			switch (k)
			{
				//�ϼ����
			case KEY_UP:
				if (rabbit->lane != 1 && rabbit->state == RUN && rabbit->x < 450)
					rabbit->state =  UP;
				break;

				//�¼����
			case KEY_DOWN:
				if (rabbit->lane != 3 && rabbit->state == RUN && rabbit->x < 450)
					rabbit->state = DOWN;
				break;

				//�ո���
			case KEY_SPACE:
				if (level != 1 && rabbit->state != UP && rabbit->state != DOWN){
					playMusicOnce("music/jump.mp3");
					rabbit->state = JUMP;
				}
				break;
			}
		}
		
	}

	//�˲������ڼ����̰���
	//�������
	if (keystate(VK_LEFT) && rabbit->state != ROLL && rabbit->x >= CHARACTER_SPEED)
		rabbit->x -= CHARACTER_SPEED;

	//�Ҽ�����
	if (keystate(VK_RIGHT) && rabbit->state != ROLL && rabbit->x <= 580 - CHARACTER_SPEED && rabbit->protect == PROTECT_OFF)
		rabbit->x += CHARACTER_SPEED;
	else if (keystate(VK_RIGHT) && rabbit->state != ROLL && rabbit->x <= 580 - CHARACTER_SPEED && rabbit->protect == PROTECT_ON)
	{
		if((rabbit->lane == 2 && rabbit->x <= 450 )|| rabbit->lane != 2)
			rabbit->x += CHARACTER_SPEED;
	}

	//Ctrl������,�Ҳ��ڵ�һ��
	if (level != 1 && keystate(VK_CONTROL) && rabbit->state != UP && rabbit->state != DOWN)
	{
		if (rabbit->state == RUN)
			putimage(rabbit->img, 0, 0, rabbit->frameSet[ROLL][0][rabbit->skin]);

		rabbit->state = ROLL;
	}
	//Ctrl��δ���£�����ɫ״̬Ϊ������δ�ڿ��У��л�Ϊ�ܶ�
	else if (rabbit->state == ROLL && rabbit->fixY == 0)
	{
		rabbit->state = RUN;
		putimage(rabbit->img, 0, 0, rabbit->frameSet[ROLL][0][rabbit->skin]);
	}

	//Esc������
	if (keystate(VK_ESCAPE))
	{
		return true;
	}

	return false;
}

void initializeSkin(CHARACTER* rabbit)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			for (int k = 0; k < 9; k++)
			{
				rabbit->frameSet[i][j][k] = newimage();
			}
		}
	}
	for (int skin = 0; skin <= 8; skin++)
	{
		char address[10][100], skinStr[2];
		skinStr[1] = '\0';
		strcpy(address[1], "assets/rabbitrun1.");
		strcpy(address[2], "assets/rabbitrun2.");
		strcpy(address[3], "assets/rabbitjump1.");
		strcpy(address[4], "assets/rabbitjump2.");
		strcpy(address[5], "assets/rabbitroll0.");
		strcpy(address[6], "assets/rabbitroll1.");
		strcpy(address[7], "assets/rabbitroll2.");
		strcpy(address[8], "assets/rabbitroll3.");
		strcpy(address[9], "assets/rabbitroll4.");

		for (int i = 1; i < 10; i++)
		{
			skinStr[0] = skin + '0';
			strcat(address[i], skinStr);
			strcat(address[i], ".png");
		}

		getimage(rabbit->frameSet[RUN][1][skin], address[1]);
		getimage(rabbit->frameSet[RUN][2][skin], address[2]);
		getimage(rabbit->frameSet[JUMP][1][skin], address[3]);
		getimage(rabbit->frameSet[JUMP][2][skin], address[4]);
		getimage(rabbit->frameSet[ROLL][0][skin], address[5]);
		getimage(rabbit->frameSet[ROLL][1][skin], address[6]);
		getimage(rabbit->frameSet[ROLL][2][skin], address[7]);
		getimage(rabbit->frameSet[ROLL][3][skin], address[8]);
		getimage(rabbit->frameSet[ROLL][4][skin], address[9]);
	}
}

void doubleJump(CHARACTER* rabbit)
{
	rabbit->jumpTime = 2 * HEIGHT_LEVEL - rabbit->jumpTime;
}
