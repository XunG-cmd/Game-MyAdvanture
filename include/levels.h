#pragma once
#include "bitAdventure.h"
#include "tutorial.h"
#include "handler.h"
#include "collision.h"
#include "multithreadMusic.h"
#include "save.h"
#include <stdio.h>
#include <stdlib.h>

#define GAME_NONE 0
#define GAME_DEAD 1
#define GAME_EXIT 2
void refresh(CHARACTER rabbit, PIMAGE background, PIMAGE buffer);
void refresh(CHARACTER rabbit, PIMAGE background, PIMAGE buffer, TUTORIAL_UI tutorial);
//�쳣�жϲ�Ҫ��, ���ַ�, ��Դͷ.
//�����, �ȶ���
//�߼�˼·Ҫ���
//���ñ����ʼ��
//�ǵ������Խ��
//�ǵò�Ҫ��ѭ��


void initCharacter(CHARACTER* rabbit);
void initBackground(imageOnDevice* image);
void initCoinTemplate(imageOnDevice* image);
void roadGeneration(imageOnDevice* image, bool generateCoin);
void canteenGeneration(imageOnDevice* image);
void canteenGeneration_temp(imageOnDevice* image);
void canteenGeneration_temp(imageOnDevice* image);
void weaponGenerate(imageOnDevice* image);
//���ɵ������ϰ���ģ��
void lakeGeneration_temp(imageOnDevice* image);
//ˢ�±����ͽ�ɫ
void refresh(CHARACTER rabbit, PIMAGE background, PIMAGE buffer);
//��һ���ϰ���λ�ñ仯����ʾ
void obstacleRefresh(imageOnDevice* image, int count, int obstacleSpeed);
//��һ�ؽ��λ�ñ仯����ʾ
void coinRefresh(imageOnDevice* image, int count, int obstacleSpeed);
//�ڶ����ϰ���+���λ�ñ仯����ʾ(��ʱ����)
void obstacleRefresh2(imageOnDevice* image, int count, int obstacleSpeed);
//�ڶ���:������ǵ�ǰλ��,������
void damaChaser(imageOnDevice* image);
//������:����Ļ�ҷ����ֺڶ�
void gooseEmerge(imageOnDevice* image, int count, int gooseSpeed);
//������:����Ļ�ҷ����ִ�ڶ�
//��Ҫ��������
void bigGooseEmerge(imageOnDevice* image, int gooseSpeed);
//������:����С�ڶ�->˳ʱ��0
void littleGooseEmerge0(imageOnDevice* image, int gooseSpeed);
//������:����С�ڶ�->��ʱ��1
void littleGooseEmerge1(imageOnDevice* image, int gooseSpeed);
//������:����С�ڶ�->˳ʱ��2
void littleGooseEmerge2(imageOnDevice* image, int gooseSpeed);
//������:����С�ڶ�->��ʱ��3
void littleGooseEmerge3(imageOnDevice* image, int gooseSpeed);
//������:����С�ڶ�->˳ʱ��+��ʱ��4
void littleGooseEmerge4(imageOnDevice* image, int gooseSpeed);
//�ڶ���:ˢ������,�ж�ʧѪ
void weaponChaser(imageOnDevice* image, int knifeSpeed);
//ˢ�½�ɫѪ����
void refreshAdd(imageOnDevice* image, int count);
//ˢ���ַ���
void refreshString(int color, int number, int set);
//ˢ�³��ܻ���+������ʱ
void delayJudge(imageOnDevice image, int count);
//�����ɫͼ��
void delCharacterImage(imageOnDevice image);
//����ϰ�ͼ��
void delObstacleImage(imageOnDevice image);


/********************************************************��ʼ��**************************************************************/
//��ʼ����ɫ���ͼ��
void initCharacter(CHARACTER* rabbit) {
	//���ܻ���
	rabbit->superStar[0] = newimage(50, 10);
	rabbit->superStar[1] = newimage(50, 10);
	setfillcolor(LIGHTBLUE, rabbit->superStar[1]);
	bar(0, 0, 50, 10, rabbit->superStar[1]);

	//�볬�ܻ���
	rabbit->superStarHalf[0] = newimage(50, 10);
	rabbit->superStarHalf[1] = newimage(50, 10);
	setfillcolor(BLUE, rabbit->superStarHalf[1]);
	bar(0, 0, 50, 10, rabbit->superStarHalf[1]);

	//Ѫ����;
	rabbit->blood = newimage(50, 10);
	setfillcolor(RED, rabbit->blood);
	bar(0, 0, 50 / rabbit->bloodValue, 10, rabbit->blood);

	//��������
	rabbit->skill = newimage(50, 10);
	setfillcolor(BLUE, rabbit->skill);
	bar(0, 0, 1, 10, rabbit->skill);
}

//��ʼ������ͼ��
void initBackground(imageOnDevice* image) {
	//��������
	image->background = newimage();
	image->buffer = newimage(640, 480);
	if (image->level == 1)
		getimage(image->background, "assets/ROAD3.0.png");
	else if (image->level == 2)
		getimage(image->background, "assets/CANTEEN3.0.png");
	else if (image->level == 3)
		getimage(image->background, "assets/NORTHLAKE3.0.png");
}

//��ʼ�����ģ��+�����ʾ+·����ʾ+Ѫ����ʾ
void initCoinTemplate(imageOnDevice* image) {
	//��Һ��ܲ�
	image->templateCoin.height = 50;
	image->templateCoin.img[0] = newimage();
	getimage(image->templateCoin.img[0], "assets/coin01.png");
	image->templateCoin.img[1] = newimage();
	getimage(image->templateCoin.img[1], "assets/coin03.png");
	image->templateCoin.img[2] = newimage();
	getimage(image->templateCoin.img[2], "assets/coin02.png");
	image->templateCoin.img[3] = newimage();
	getimage(image->templateCoin.img[3], "assets/coin03.png");
	image->templateCoin.img[4] = newimage();
	getimage(image->templateCoin.img[4], "assets/carrot00.png");
	image->templateCoin.img[5] = newimage();
	getimage(image->templateCoin.img[5], "assets/carrot01.png");
	image->templateCoin.jumpAvaliable = 1;
	image->templateCoin.rollAvaliable = 1;
	image->templateCoin.width = 50;

	image->coinboxs = newimage();
	getimage(image->coinboxs, "assets/coin02.png");

	image->distance = newimage();
	getimage(image->distance, "assets/distance.png");

	image->heart = newimage();
	getimage(image->heart, "assets/blood.png");

	image->kill = newimage();
	getimage(image->kill, "assets/kill.png");
}


/********************************************************�����ϰ�**************************************************************/
//���ɵ�һ���ϰ���
void roadGeneration(imageOnDevice* image, bool generateCoin) {
	image->templateNumber = 4;
	for (int i = 0; i < image->templateNumber; i++) {
		image->frameNumber[i] = 2;
	}
	//ѧ���ϰ���
	image->templateObstacle[0].height = 120;
	image->templateObstacle[0].img[0] = newimage();
	getimage(image->templateObstacle[0].img[0], "assets/boy00.png");
	image->templateObstacle[0].img[1] = newimage();
	getimage(image->templateObstacle[0].img[1], "assets/boy01.png");
	image->templateObstacle[0].img[2] = newimage();
	getimage(image->templateObstacle[0].img[2], "assets/boy02.png");
	image->templateObstacle[0].img[3] = newimage();
	getimage(image->templateObstacle[0].img[3], "assets/boy03.png");
	image->templateObstacle[0].jumpAvaliable = 0;
	image->templateObstacle[0].rollAvaliable = 0;
	image->templateObstacle[0].width = 50;


	image->templateObstacle[1].height = 120;
	image->templateObstacle[1].img[0] = newimage();
	getimage(image->templateObstacle[1].img[0], "assets/girl00.png");
	image->templateObstacle[1].img[1] = newimage();
	getimage(image->templateObstacle[1].img[1], "assets/girl01.png");
	image->templateObstacle[1].img[2] = newimage();
	getimage(image->templateObstacle[1].img[2], "assets/girl02.png");
	image->templateObstacle[1].img[3] = newimage();
	getimage(image->templateObstacle[1].img[3], "assets/girl03.png");
	image->templateObstacle[1].jumpAvaliable = 0;
	image->templateObstacle[1].rollAvaliable = 0;
	image->templateObstacle[1].width = 40;


	image->templateObstacle[2].height = 120;
	image->templateObstacle[2].img[0] = newimage();
	getimage(image->templateObstacle[2].img[0], "assets/Pang00.png");
	image->templateObstacle[2].img[1] = newimage();
	getimage(image->templateObstacle[2].img[1], "assets/Pang01.png");
	image->templateObstacle[2].img[2] = newimage();
	getimage(image->templateObstacle[2].img[2], "assets/Pang02.png");
	image->templateObstacle[2].img[3] = newimage();
	getimage(image->templateObstacle[2].img[3], "assets/Pang03.png");
	image->templateObstacle[2].jumpAvaliable = 0;
	image->templateObstacle[2].rollAvaliable = 0;
	image->templateObstacle[2].width = 60;


	image->templateObstacle[3].height = 120;
	image->templateObstacle[3].img[0] = newimage();
	getimage(image->templateObstacle[3].img[0], "assets/student30.png");
	image->templateObstacle[3].img[1] = newimage();
	getimage(image->templateObstacle[3].img[1], "assets/student30.png");
	image->templateObstacle[3].img[2] = newimage();
	getimage(image->templateObstacle[3].img[2], "assets/student31.png");
	image->templateObstacle[3].img[3] = newimage();
	getimage(image->templateObstacle[3].img[3], "assets/student31.png");
	image->templateObstacle[3].jumpAvaliable = 0;
	image->templateObstacle[3].rollAvaliable = 0;
	image->templateObstacle[3].width = 100;

	//����������ǹ�� ˳�������ϰ�������λ�� �Լ��ϰ��� FREQUENCY * SPEED = 100����/��
	track characterTrack[TRACK_NUMBER];
	track laneAllow[TRACK_NUMBER];
	characterTrack[0].startPosition = 640;								//5s���ֵ�һ��ѧ���ϰ���->ֱ�ӳ���20:04 3/18
	characterTrack[0].lane = 2;
	image->countObstacle = 0;											//�ϰ�������
	image->coinNumber = 0;												//���������&��Һ��ܲ�����

	//���������
	//�����������
	bool moveCommand[TRACK_NUMBER];
	for (int i = 0; i < TRACK_NUMBER; i++) {
		moveCommand[i] = rand() % 2;
	}

	//��λ���->�ϰ���λ��  //ƽ��һ�����ռ 250 - 50 = 200 ���� ��ռ 6000~7500) (+ 540) ���� ����1�������
	for (int i = 0; i < TRACK_NUMBER; i++) {
		characterTrack[i].length = 250 + rand() % 50;
		if (i != 0) {
			characterTrack[i].startPosition = characterTrack[i - 1].startPosition + characterTrack[i - 1].length - 50;
			if (characterTrack[i - 1].lane == 3 || characterTrack[i - 1].lane == 1)
				characterTrack[i].lane = 2;
			else {
				if (moveCommand[i])
					characterTrack[i].lane = characterTrack[i - 1].lane + 1;
				else
					characterTrack[i].lane = characterTrack[i - 1].lane - 1;
			}
		}

		if (generateCoin) {
			//�ڹ���ڲ���Χ������test  (*)
			int tempPosition = characterTrack[i].startPosition;
			do {
				image->templateCoin.x = tempPosition;
				tempPosition += 180;
				image->templateCoin.lane = characterTrack[i].lane;
				image->coin[image->coinNumber++] = image->templateCoin;
			} while (image->templateCoin.x + 180 <= characterTrack[i].startPosition + characterTrack[i].length);
		}

		//�ϰ�������λ��
		laneAllow[i].lane = characterTrack[i].lane;
		laneAllow[i].startPosition = characterTrack[i].startPosition + characterTrack[i].length;
		if (i > 3) {
			int j = i;
			while (characterTrack[--j].lane != characterTrack[i].lane);
			//��ʱ�Ѿ�������һ��ͬlane��track����
			laneAllow[j].length = characterTrack[i].startPosition - characterTrack[j].startPosition - characterTrack[j].length;
			int temp = 0;
			int countIngroup = 0;
			int tempPosition = 40;
			do {
				temp = rand() % 4;
				for (int j = 0; j < 4; j++)
					image->copyObstacle[image->countObstacle].img[j] = image->templateObstacle[temp].img[j];
				image->copyObstacle[image->countObstacle].x = tempPosition + laneAllow[j].startPosition;
				tempPosition += 100;									//��ʱ��λΪ��һ���ϰ���λ��
				image->copyObstacle[image->countObstacle++].lane = laneAllow[j].lane - 1;
			} while (tempPosition + 50 <= laneAllow[j].length);

		}

	}
}

//���ɵڶ��غ��ܲ�
void canteenGeneration(imageOnDevice* image) {
	//����������ǹ�� ˳�������ϰ�������λ�� �Լ��ϰ��� FREQUENCY * SPEED = 100����/��
	track characterTrack[TRACK_NUMBER];
	characterTrack[0].startPosition = 640; 		//5s���ֵ�һ���ϰ���
	characterTrack[0].lane = 2;
	image->countObstacle = 0;					//�ϰ�������
	image->coinNumber = 0;						//���������&��Һ��ܲ�����

	//���������
	//�����������
	bool moveCommand[TRACK_NUMBER];
	for (int i = 0; i < TRACK_NUMBER; i++) {
		moveCommand[i] = rand() % 2;
	}
	int weapon = 0;
	//��λ���->�ϰ���λ��  //ƽ��һ�����ռ 350~400 - 50 ���� ��ռ 9000~10500) (+ 540) ���� 
	for (int i = 0; i < TRACK_NUMBER; i++) {
		characterTrack[i].length = 350 + rand() % 50;
		if (i != 0) {
			characterTrack[i].startPosition = characterTrack[i - 1].startPosition + characterTrack[i - 1].length - 50;
			if (characterTrack[i - 1].lane == 3 || characterTrack[i - 1].lane == 1)
				characterTrack[i].lane = 2;
			else {
				if (moveCommand[i])
					characterTrack[i].lane = characterTrack[i - 1].lane + 1;
				else
					characterTrack[i].lane = characterTrack[i - 1].lane - 1;
			}
		}

		//�ڹ���ڲ���Χ������test  (*)
		int tempPosition = characterTrack[i].startPosition;
		for (int k = 1; image->templateCoin.x + 50 <= characterTrack[i].startPosition + characterTrack[i].length; k++) {
			image->templateCoin.x = tempPosition;
			tempPosition += 50;								//track��,�����20����
			image->templateCoin.lane = characterTrack[i].lane;
			image->templateCoin.h = 20;
			image->coin[image->coinNumber++] = image->templateCoin;
		}
	}
}

//���ɵڶ����ϰ���ģ��
void canteenGeneration_temp(imageOnDevice* image) {
	image->templateNumber = 3;
	image->frameNumber[0] = 8;			//�˵�
	image->frameNumber[1] = 2;			//�͹�
	image->frameNumber[2] = 4;			//����

	//�ϰ���ģ��
	//�˵�
	image->templateObstacle[0].height = 80;
	image->templateObstacle[0].img[0] = newimage();
	getimage(image->templateObstacle[0].img[0], "assets/KNIFE00.png");
	image->templateObstacle[0].img[1] = newimage();
	getimage(image->templateObstacle[0].img[1], "assets/KNIFE01.png");
	image->templateObstacle[0].img[2] = newimage();
	getimage(image->templateObstacle[0].img[2], "assets/KNIFE02.png");
	image->templateObstacle[0].img[3] = newimage();
	getimage(image->templateObstacle[0].img[3], "assets/KNIFE03.png");
	image->templateObstacle[0].img[4] = newimage();
	getimage(image->templateObstacle[0].img[4], "assets/KNIFE04.png");
	image->templateObstacle[0].img[5] = newimage();
	getimage(image->templateObstacle[0].img[5], "assets/KNIFE05.png");
	image->templateObstacle[0].img[6] = newimage();
	getimage(image->templateObstacle[0].img[6], "assets/KNIFE06.png");
	image->templateObstacle[0].img[7] = newimage();
	getimage(image->templateObstacle[0].img[7], "assets/KNIFE07.png");
	image->templateObstacle[0].jumpAvaliable = 0;
	image->templateObstacle[0].rollAvaliable = 1;
	image->templateObstacle[0].width = 50;

	//�͹�
	image->templateObstacle[1].height = 30;
	image->templateObstacle[1].img[0] = newimage();
	getimage(image->templateObstacle[1].img[0], "assets/POT00.png");
	image->templateObstacle[1].img[1] = newimage();
	getimage(image->templateObstacle[1].img[1], "assets/POT01.png");
	image->templateObstacle[1].jumpAvaliable = 1;
	image->templateObstacle[1].rollAvaliable = 0;
	image->templateObstacle[1].width = 60;

	//����
	image->templateObstacle[2].height = 120;
	image->templateObstacle[2].img[0] = newimage();
	getimage(image->templateObstacle[2].img[0], "assets/NEWAUNT03.png");
	image->templateObstacle[2].img[1] = newimage();
	getimage(image->templateObstacle[2].img[1], "assets/NEWAUNT02.png");
	image->templateObstacle[2].img[2] = newimage();
	getimage(image->templateObstacle[2].img[2], "assets/NEWAUNT01.png");
	image->templateObstacle[2].img[3] = newimage();
	getimage(image->templateObstacle[2].img[3], "assets/NEWAUNT00.png");
	image->templateObstacle[2].jumpAvaliable = 0;
	image->templateObstacle[2].rollAvaliable = 0;
	image->templateObstacle[2].width = 50;
	image->templateObstacle[2].h = 0;
	image->templateObstacle[2].x = -50;
}

//�ڶ���:���һ��ʱ��,��������ӳ�һ�Ѳ˵���һ���͹�
void weaponGenerate(imageOnDevice* image) {
	//���طɵ�,Ʋ����Ƶ��
	if (image->count % image->difficulty == 0) {
		//�����ҵ����ʵ�λ��,�ں��ض�������,��ʼ�ɵ�
		if (image->templateObstacle[2].x < 100 && image->templateObstacle[2].fixY < 20 && image->templateObstacle[2].fixY > -20) {
			//�ֳַ��컭�,������
			if (image->templateObstacle[2].lane == 2) {
				//��ǰһ�ѵ�
				image->templateObstacle[0].lane = 2;
				image->templateObstacle[0].x = image->templateObstacle[2].x + 100;
				image->copyObstacle[image->countKnife++] = image->templateObstacle[0];
				//�������ѵ�
				image->templateObstacle[0].x = image->templateObstacle[2].x + 50;
				image->templateObstacle[0].lane = 3;
				image->copyObstacle[image->countKnife++] = image->templateObstacle[0];
				image->templateObstacle[0].lane = 1;
				image->copyObstacle[image->countKnife++] = image->templateObstacle[0];
			}
			else {
				//��ǰһ�ѵ�
				image->templateObstacle[0].lane = image->templateObstacle[2].lane;
				image->templateObstacle[0].x = image->templateObstacle[2].x + 100;
				image->copyObstacle[image->countKnife++] = image->templateObstacle[0];
				//����һ�ѵ�
				image->templateObstacle[0].x = image->templateObstacle[2].x + 50;
				image->templateObstacle[0].lane = 2;
				image->copyObstacle[image->countKnife++] = image->templateObstacle[0];
				//���һ�ѵ�
				image->templateObstacle[0].x = image->templateObstacle[2].x;
				image->templateObstacle[0].lane = 4 - image->templateObstacle[2].lane;
				image->copyObstacle[image->countKnife++] = image->templateObstacle[0];
			}
		}
		//����������׷������,��æ֮��,��ʼƲ��
		else if (image->templateObstacle[2].x < image->rabbit.x && (image->templateObstacle[2].fixY < -30 || image->templateObstacle[2].fixY > 30)) {
			//ƽ�׹��Ǵ��������ܵ�
			if (image->templateObstacle[2].laneNext == 2) {
				//��ǰһ�ڹ�
				image->templateObstacle[1].x = image->templateObstacle[2].x + 200;
				image->templateObstacle[1].lane = image->templateObstacle[2].laneNext;
				image->copyObstacle[image->countPot++] = image->templateObstacle[1];
				//�������ڹ�
				image->templateObstacle[1].x = image->templateObstacle[2].x + 150;
				image->templateObstacle[1].lane = 3;
				image->copyObstacle[image->countPot++] = image->templateObstacle[1];
				image->templateObstacle[1].lane = 1;
				image->copyObstacle[image->countPot++] = image->templateObstacle[1];
			}
			else {
				//��ǰһ�ڹ�
				image->templateObstacle[1].lane = image->templateObstacle[2].laneNext;
				image->templateObstacle[1].x = image->templateObstacle[2].x + 100;
				image->copyObstacle[image->countPot++] = image->templateObstacle[1];
				//����һ�ڹ�
				image->templateObstacle[1].x = image->templateObstacle[2].x + 50;
				image->templateObstacle[1].lane = 2;
				image->copyObstacle[image->countPot++] = image->templateObstacle[1];
			}
		}
	}
}

//���ɵ������ϰ���ģ��
void lakeGeneration_temp(imageOnDevice* image) {
	image->templateNumber = 3;
	image->frameNumber[0] = 3;			//��ڶ�
	image->frameNumber[1] = 5;			//�ڶ�
	image->frameNumber[2] = 4;			//С�ڶ�

	//��ڶ�
	image->templateObstacle[0].height = 70;
	image->templateObstacle[0].img[0] = newimage();
	getimage(image->templateObstacle[0].img[0], "assets/BIG BLACK00.png");
	image->templateObstacle[0].img[1] = newimage();
	getimage(image->templateObstacle[0].img[1], "assets/BIG BLACK01.png");
	image->templateObstacle[0].img[2] = newimage();
	getimage(image->templateObstacle[0].img[2], "assets/BIG BLACK02.png");
	image->templateObstacle[0].width = 60;
	image->templateObstacle[0].x = 720;
	image->templateObstacle[0].direction = 0;						//����:0��1��
	image->templateObstacle[0].lane = 2;

	//�ڶ�
	image->templateObstacle[1].height = 50;
	image->templateObstacle[1].img[0] = newimage();
	getimage(image->templateObstacle[1].img[0], "assets/BLACK SWAN00.png");
	image->templateObstacle[1].img[1] = newimage();
	getimage(image->templateObstacle[1].img[1], "assets/BLACK SWAN01.png");
	image->templateObstacle[1].img[2] = newimage();
	getimage(image->templateObstacle[1].img[2], "assets/BLACK SWAN02.png");
	image->templateObstacle[1].img[3] = newimage();
	getimage(image->templateObstacle[1].img[3], "assets/BLACK SWAN03.png");
	image->templateObstacle[1].img[4] = newimage();
	getimage(image->templateObstacle[1].img[4], "assets/BLACK SWAN04.png");
	image->templateObstacle[1].width = 50;

	//С�ڶ�
	image->templateObstacle[2].height = 35;
	image->templateObstacle[2].img[0] = newimage();
	getimage(image->templateObstacle[2].img[0], "assets/LITTLE SWAN01.png");//����
	image->templateObstacle[2].img[1] = newimage();
	getimage(image->templateObstacle[2].img[1], "assets/LITTLE SWAN11.png");
	image->templateObstacle[2].img[2] = newimage();
	getimage(image->templateObstacle[2].img[2], "assets/LITTLE SWAN00.png");//����
	image->templateObstacle[2].img[3] = newimage();
	getimage(image->templateObstacle[2].img[3], "assets/LITTLE SWAN10.png");
	image->templateObstacle[2].width = 35;
	image->templateObstacle[2].h = 0;
	image->templateObstacle[2].x = 640;

	//�ڶ� �̳�
	image->templateObstacle[3].height = 50;
	image->templateObstacle[3].img[0] = newimage();
	getimage(image->templateObstacle[3].img[0], "assets/hint00.png");
	image->templateObstacle[3].img[1] = newimage();
	getimage(image->templateObstacle[3].img[1], "assets/hint01.png");
	image->templateObstacle[3].img[2] = newimage();
	getimage(image->templateObstacle[3].img[2], "assets/hint02.png");
	image->templateObstacle[3].width = 50;
	//����˺ڶ�ͼ������ -3/22 12:06 
}

/********************************************************ˢ��ͼ��**************************************************************/
//ˢ�±����ͽ�ɫ
void refresh(CHARACTER rabbit, PIMAGE background, PIMAGE buffer)
{
	cleardevice();
	putimage(0, 0, background);
	putimage_transparent(NULL, rabbit.img, rabbit.x, Y(rabbit), BLACK);
	putimage(buffer, 0, 0, 640 - SPEED, 480, background, SPEED, 0);
	putimage(buffer, 640 - SPEED, 0, SPEED, 480, background, 0, 0);
	putimage(background, 0, 0, buffer);
}

//ˢ�½̳̱����ͽ�ɫ
void refresh(CHARACTER rabbit, PIMAGE background, PIMAGE buffer, TUTORIAL_UI tutorial)
{
	cleardevice();
	putimage(0, 0, background);
	putimage_transparent(NULL, rabbit.img, rabbit.x, Y(rabbit), BLACK);
	putimage_transparent(NULL, tutorial.img, tutorial.x, tutorial.y, BLACK);
	putimage(buffer, 0, 0, 640 - SPEED, 480, background, SPEED, 0);
	putimage(buffer, 640 - SPEED, 0, SPEED, 480, background, 0, 0);
	putimage(background, 0, 0, buffer);
}

//��һ���ϰ���λ�ñ仯����ʾ
void obstacleRefresh(imageOnDevice* image, int count, int obstacleSpeed) {
	//�ϰ���
	int tempPosition = image->rabbit.x;
	for (int i = 0; i < image->countObstacle; i++) {
		if (image->copyObstacle[i].lane == -1)
			image->copyObstacle[i].lane = 0;
		if (image->rabbit.superState == NORMAL && \
			image->rabbit.lane == image->copyObstacle[i].lane + 1 && \
			image->copyObstacle[i].x + 10 < tempPosition + image->rabbit.width && \
			tempPosition + image->rabbit.width < image->copyObstacle[i].x + image->copyObstacle[i].width - 10 && \
			image->copyObstacle[i].appear == 1)
		{
			image->rabbit.bloodValue--;
			image->rabbit.coin = 0;
			image->copyObstacle[i].appear = 0;
		}
		if (image->copyObstacle[i].x > -60)//&& studentObstacle[i].x < 640)//Խ��ԭ����ϰ������ʧimage->templateObstacle[2].img[3]
			putimage_transparent(NULL, image->copyObstacle[i].img[count % 12 / 3], image->copyObstacle[i].x -= obstacleSpeed, laneYBase(image->copyObstacle[i]) - 30, BLACK);
	}
}

//��һ�ؽ��λ�ñ仯����ʾ
void coinRefresh(imageOnDevice* image, int count, int obstacleSpeed) {
	for (int i = 0; i < image->coinNumber; i++) {
		if (image->coin[i].x >= image->rabbit.x + 40 && \
			image->coin[i].x <= image->rabbit.x + 75 && \
			image->coin[i].lane == image->rabbit.lane && \
			image->rabbit.skin != 2) {										 //�ڻ�ȡӲ�ҷ�Χ��
			if (image->rabbit.coin < 50 && image->coin[i].appear == 1) {
				playMusicOnce("music/coin.mp3");
				image->rabbit.coin++;
				image->rabbit.save++;
			}
			image->coin[i].appear = 0;
		}
		//����֮�÷�������:���ս��(���շ�Χ����,��·����)
		else if (image->coin[i].x >= image->rabbit.x + 10 && \
			image->coin[i].x <= image->rabbit.x + 90 && \
			image->rabbit.skin == 2) {										 //�ڻ�ȡӲ�ҷ�Χ��
			if (image->rabbit.coin < 50 && image->coin[i].appear == 1) {
				playMusicOnce("music/coin.mp3");
				image->rabbit.coin++;
				image->rabbit.save++;
			}
			image->coin[i].appear = 0;
		}
		if (image->coin[i].x > -60 && image->coin[i].appear == 1)//&& studentObstacle[i].x < 640)//Խ��ԭ��Ĺ�����Է������ʧ
			putimage_transparent(NULL, image->coin[i].img[count % 8 / 4], image->coin[i].x -= obstacleSpeed, Y(image->coin[i]), BLACK);
	}
}

//�ڶ��ؽ��λ�ñ仯����ʾ
void obstacleRefresh2(imageOnDevice* image, int count, int obstacleSpeed) {
	for (int i = 0; i < image->coinNumber; i++) {
		if (image->coin[i].x >= image->rabbit.x + 40 && \
			image->coin[i].x <= image->rabbit.x + 75 && \
			image->coin[i].lane == image->rabbit.lane && \
			image->rabbit.skin != 2) {										 //�ڻ�ȡӲ�ҷ�Χ��
			if (image->coin[i].appear == 1) {			//image->rabbit.coin < 50 && 
				playMusicOnce("music/coin.mp3");
				image->rabbit.coin += 1;
				image->rabbit.save += 2;
			}
			image->coin[i].appear = 0;
		}
		//����֮�÷�������:���ս��(���շ�Χ����,��·����)
		else if (image->coin[i].x >= image->rabbit.x + 10 && \
			image->coin[i].x <= image->rabbit.x + 90 && \
			image->rabbit.skin == 2) {										 //�ڻ�ȡӲ�ҷ�Χ��
			if (image->rabbit.coin < 50 && image->coin[i].appear == 1) {
				playMusicOnce("music/coin.mp3");
				image->rabbit.coin += 1;
				image->rabbit.save += 2;
			}
			image->coin[i].appear = 0;
		}
		if (image->coin[i].x > -60 && image->coin[i].appear == 1)//&& studentObstacle[i].x < 640)//Խ��ԭ��Ĺ�����Է������ʧ
			putimage_transparent(NULL, image->coin[i].img[count % 6 / 3 + 4], image->coin[i].x -= obstacleSpeed, Y(image->coin[i]), BLACK);
	}
}

//�ڶ���:������ǵ�ǰλ��,������
void damaChaser(imageOnDevice* image) {
	//���߽��,����һ��
	if (image->templateObstacle[2].x > 640) {
		image->templateObstacle[2].lane = image->rabbit.lane;							//ȫ����ʼ��
		image->templateObstacle[2].laneNext = image->rabbit.lane;
		image->templateObstacle[2].x = -50;											//x����,ʹ�ô����߹�ȥ֮��Ż������һ������
		image->templateObstacle[2].fixY = 0;
		putimage_transparent(NULL, image->templateObstacle[2].img[image->count % 8 / 4], -50, Y(image->templateObstacle[2]), BLACK);
	}
	//�����߽�,�ж�����
	else {
		//���ȷ���ú�,�ɴ�������ӵ����λ��ȷ��������һ�����
		if (image->templateObstacle[2].fixY > 120 || image->templateObstacle[2].fixY < -120) {		//Ŀ����֮ǰ���������,�в����ж���
			image->templateObstacle[2].lane = image->templateObstacle[2].laneNext;					//Ŀ����,�л����
			image->templateObstacle[2].fixY = 0;														//����ֵ����
		}
		if (image->rabbit.lane != image->templateObstacle[2].lane && \
			image->rabbit.x > image->templateObstacle[2].x&& \
			image->templateObstacle[2].fixY == 0)
			image->templateObstacle[2].laneNext = image->rabbit.lane;									//�����ȶ���->�����ڴ���ǰ����ͬ���->����Ѱ���µ�Ŀ��

		int detalLane = image->templateObstacle[2].laneNext - image->templateObstacle[2].lane;		//������������,���Ǹ���Ŀ����
		image->templateObstacle[2].fixY += (detalLane == 2 || detalLane == -2) ? detalLane * 6 : detalLane * 8;
		putimage_transparent(NULL, image->templateObstacle[2].img[image->count % 16 / 4], image->templateObstacle[2].x += 9/*���������ٶ�*/, Y(image->templateObstacle[2]), BLACK);	/*******Ͷ***֮***Ӱ********/
	}
	if (image->templateObstacle[2].fixY > 80 || image->templateObstacle[2].fixY < -80) {				//�쵽��һ�������
		if (image->templateObstacle[2].x + 30 < image->rabbit.x && \
			image->rabbit.x < image->templateObstacle[2].x + 70 && \
			image->templateObstacle[2].laneNext == image->rabbit.lane && \
			image->rabbit.superState == NORMAL)
			image->rabbit.bloodValue = 0;															//ץ������->gg
	}
	else if (image->templateObstacle[2].fixY < 40 && image->templateObstacle[2].fixY > -40) {			//���߳�ԭ���
		if (image->templateObstacle[2].x + 10 < image->rabbit.x && \
			image->rabbit.x < image->templateObstacle[2].x + 70 && \
			image->templateObstacle[2].lane == image->rabbit.lane && \
			image->rabbit.superState == NORMAL)
			image->rabbit.bloodValue = 0;															//��һ��ͷ,ŶС����ԭ��������->gg
	}
}

//�ڶ���:ˢ������,�ж�ʧѪ
void weaponChaser(imageOnDevice* image, int knifeSpeed) {
	//ˢ�²˵�
	for (int i = 0; i < image->countKnife; i++) {
		if (image->copyObstacle[i].x <= 640)
			putimage_transparent(NULL, image->copyObstacle[i].img[image->count % 8], image->copyObstacle[i].x += knifeSpeed/*�ɵ��ٶ� = 2V���� */, Y(image->copyObstacle[i]), BLACK);
		//�ж�ʧѪ
		if (image->copyObstacle[i].x - image->rabbit.x < 30 && \
			image->copyObstacle[i].x - image->rabbit.x > -30 && \
			image->copyObstacle[i].hurt == 0 && \
			image->copyObstacle[i].lane == image->rabbit.lane && \
			image->rabbit.superState == NORMAL && \
			image->rabbit.state != ROLL)
		{
			image->copyObstacle[i].hurt = 1;
			image->rabbit.bloodValue -= 1;
		}
	}
	//ˢ���͹�
	for (int i = 150; i < image->countPot; i++) {
		if (image->copyObstacle[i].x > 640)
			image->copyObstacle[i].direction = 0;											//inverse the direction
		if (image->copyObstacle[i].direction)
			putimage_transparent(NULL, image->copyObstacle[i].img[image->count % 4 / 2], image->copyObstacle[i].x += knifeSpeed/*���ٶ� = 2V���� */, Y(image->copyObstacle[i]), BLACK);
		else
			putimage_transparent(NULL, image->copyObstacle[i].img[image->count % 4 / 2], image->copyObstacle[i].x -= knifeSpeed/*���ٶ� = 2V���� */, Y(image->copyObstacle[i]), BLACK);
		//�ж�ʧѪ
		if (image->copyObstacle[i].x - image->rabbit.x < 30 && \
			image->copyObstacle[i].x - image->rabbit.x > -30 && \
			image->copyObstacle[i].hurt == 0 && \
			image->copyObstacle[i].lane == image->rabbit.lane && \
			image->rabbit.superState == NORMAL && \
			image->rabbit.state != JUMP)
		{
			image->copyObstacle[i].hurt = 1;
			image->rabbit.bloodValue -= 1;
		}
	}
}

//������:����Ļ�ҷ����ֺڶ�
void gooseEmerge(imageOnDevice* image, int count, int gooseSpeed) {
	/*appear:ֻ��һ��Ѫ;direction:�������ͷ�ؼ�*/
	//��ʱ����,�ս����
	if (image->count <= count) {
		image->templateObstacle[1].x = 640;
		image->templateObstacle[1].direction = 0;						//����:0��1��
		image->templateObstacle[1].lane = 2;
	}

	//Ȼ��,�ߵ���̨����
	else if (image->count > count&& image->templateObstacle[1].direction == 0) {
		if (image->templateObstacle[1].x >= 540) {
			image->rabbit.protect = PROTECT_ON;							//��������ģʽ//ֻ�ܿ���,ֻ��״̬ 
			image->gooseNumber = 8;
			putimage_transparent(NULL, image->templateObstacle[1].img[image->count % 15 / 3], \
				image->templateObstacle[1].x -= 5, laneYBase(image->templateObstacle[1]) - 30, BLACK);
		}
		else {
			putimage_transparent(NULL, image->templateObstacle[1].img[image->count % 12 / 3], \
				image->templateObstacle[1].x, laneYBase(image->templateObstacle[1]) - 30, BLACK);
			if (image->time % 5 == 0)
				littleGooseEmerge0(image, gooseSpeed);						 //Сde�Ǹ�����!!!->˳ʱ��0
			else if (image->time % 5 == 1)
				littleGooseEmerge1(image, gooseSpeed);						 //Сde�Ǹ�����!!!->��ʱ��1
			else if (image->time % 5 == 2)
				littleGooseEmerge3(image, gooseSpeed);						 //Сde�Ǹ�����!!!->˳ʱ��2
			else if (image->time % 5 == 3)
				littleGooseEmerge2(image, gooseSpeed);						 //Сde�Ǹ�����!!!->��ʱ��3
		}

		//��������,��ͷ���������
		if (image->rabbit.state == JUMP && image->rabbit.jumpState == DOWN) {
			if (image->rabbit.lane == image->templateObstacle[1].lane && \
				image->templateObstacle[1].x - image->rabbit.x > 45 && \
				image->templateObstacle[1].x - image->rabbit.x < 65 && \
				image->templateObstacle[1].direction == 0)
			{
				playMusicOnce("music/killMedium.mp3");
				image->templateObstacle[1].direction = 1;					//��Ǻ���
				doubleJump(&image->rabbit);
			}
		}
	}

	//��������һԾ,�����������
	else if (image->count > count&& image->templateObstacle[1].direction == 1) {
		putimage_transparent(NULL, image->templateObstacle[1].img[4], \
			image->templateObstacle[1].x += 5, laneYBase(image->templateObstacle[1]) - 30, BLACK);
	}
	if (image->templateObstacle[1].x > 700) {
		image->time++;
		image->templateObstacle[1].direction = 0;							//�ڶ����¿�ʼ
	}
	
	//С�ܲ���û�˷���
	if (image->gooseNumber == 0)
		image->rabbit.protect = PROTECT_OFF;
}

//������:����Ļ�ҷ�����***������***�ڶ�
void bigGooseEmerge(imageOnDevice* image, int gooseSpeed) {
	/*appear:ֻ��һ��Ѫ;direction:�������ͷ�ؼ�*/
	image->rabbit.protect = PROTECT_ON;									//��������ģʽ
	//Ȼ��,�ߵ���̨����
	if (image->templateObstacle[0].direction == 0) {
		image->rabbit.protect = 1;										//��������ģʽ
		if (image->templateObstacle[0].x >= 540)
			putimage_transparent(NULL, image->templateObstacle[0].img[image->count % 9 / 3], \
				image->templateObstacle[0].x -= 5, laneYBase(image->templateObstacle[0]) - 30, BLACK);
		else {
			putimage_transparent(NULL, image->templateObstacle[0].img[image->count % 9 / 3], \
				image->templateObstacle[0].x, laneYBase(image->templateObstacle[0]) - 30, BLACK);
			littleGooseEmerge4(image, gooseSpeed);
		}
		//������ͷ���������
		if (image->rabbit.state == JUMP && image->rabbit.jumpState == DOWN) {
			if (image->rabbit.lane == image->templateObstacle[0].lane && \
				image->templateObstacle[0].x - image->rabbit.x > 45 && \
				image->templateObstacle[0].x - image->rabbit.x < 65 && \
				image->templateObstacle[0].direction == 0)
			{
				playMusicOnce("music/killLarge.mp3");
				image->templateObstacle[0].direction = 1;					//��Ǻ���
				doubleJump(&image->rabbit);
			}
		}
	}
	//��������һԾ,�����������
	else if (image->templateObstacle[0].direction == 1) {
		putimage_transparent(NULL, image->templateObstacle[0].img[image->count % 9 / 3], \
			image->templateObstacle[0].x += 5, laneYBase(image->templateObstacle[0]) - 30, BLACK);
	}
	if (image->templateObstacle[0].x > 720)
		image->time++;														//�����γ���,�Ѳ��ٿ���,��ζ��С���ӵ�ʤ��
	//С�ܲ���û�˷���
	if (image->gooseNumber == 0)
		image->rabbit.protect = PROTECT_OFF;
	//����˴���޷����������� 
}

//������:����С�ڶ�->˳ʱ��0
void littleGooseEmerge0(imageOnDevice* image, int gooseSpeed) {
	//û��ʼ��,���ȳ�ʼ��
	if (image->init[image->time] == 0) {
		image->gooseNumber = 5;
		for (int i = 0; i < 5; i++) {
			image->templateObstacle[2].lane = 3;
			image->templateObstacle[2].x = 640 + i * 130;
			image->copyObstacle[i] = image->templateObstacle[2];
			image->copyObstacle[i].direction = 0;
		}
		image->init[image->time] = 1;
	}
	else {
		//����ѭ����ʽ->ˢ�·�ʽ
		for (int i = 0; i < 5; i++) {
			if (image->copyObstacle[i].x < -35 && image->copyObstacle[i].lane == 3) {
				image->copyObstacle[i].hurt = 0;									//�����Թ�������
				image->copyObstacle[i].lane = 1;
				image->copyObstacle[i].direction = 1;
				image->copyObstacle[i].x = -35;									//������,���ϳ�
			}
			else if (image->copyObstacle[i].x > 640 && image->copyObstacle[i].lane == 1) {
				image->copyObstacle[i].hurt = 0;									//�����Թ�������
				image->copyObstacle[i].lane = 3;
				image->copyObstacle[i].direction = 0;
				image->copyObstacle[i].x = 640;									//������,���³�
			}
			if (image->copyObstacle[i].appear == 1 && image->copyObstacle[i].direction == 0)		//����
				putimage_transparent(NULL, image->copyObstacle[i].img[image->count % 6 / 3], \
					image->copyObstacle[i].x -= gooseSpeed, laneYBase(image->copyObstacle[i]) - 30, BLACK);
			else if (image->copyObstacle[i].appear == 1 && image->copyObstacle[i].direction == 1)	//����
				putimage_transparent(NULL, image->copyObstacle[i].img[image->count % 6 / 3 + 2], \
					image->copyObstacle[i].x += gooseSpeed, laneYBase(image->copyObstacle[i]) - 30, BLACK);

			switch(isCollide(&image->rabbit, image->copyObstacle[i])) {
			//�жϻ�ɱ
			//������ͷ������С��
			case COLL_KILL:
				image->copyObstacle[i].appear = 0;								//һֻС����ʧ,����������1
				image->gooseNumber--;
				image->killNumber++;
				playMusicOnce("music/coin.mp3");
				image->rabbit.coin += 3;
				image->rabbit.save += 3;
				doubleJump(&image->rabbit);
				break;
			//�ж�ʧѪ
			//С�칰��
			case COLL_HURT:
				image->copyObstacle[i].hurt = 1;									//ʧѪflag
				image->rabbit.bloodValue--;
				break;
			}
		}
	}
}

//������:����С�ڶ�->��ʱ��1
void littleGooseEmerge1(imageOnDevice* image, int gooseSpeed) {
	//û��ʼ��,���ȳ�ʼ��
	if (image->init[image->time] == 0) {
		image->gooseNumber = 5;
		for (int i = 0; i < 5; i++) {
			image->templateObstacle[2].lane = 1;
			image->templateObstacle[2].x = 640 + i * 130;
			image->copyObstacle[i] = image->templateObstacle[2];
			image->copyObstacle[i].direction = 0;
		}
		image->init[image->time] = 1;
	}
	else {
		//����ѭ����ʽ->ˢ�·�ʽ
		for (int i = 0; i < 5; i++) {
			if (image->copyObstacle[i].x < -35 && image->copyObstacle[i].lane == 1) {
				image->copyObstacle[i].hurt = 0;									//�����Թ�������
				image->copyObstacle[i].lane = 3;
				image->copyObstacle[i].direction = 1;
				image->copyObstacle[i].x = -35;									//������,���ϳ�
			}
			else if (image->copyObstacle[i].x > 640 && image->copyObstacle[i].lane == 3) {
				image->copyObstacle[i].hurt = 0;									//�����Թ�������
				image->copyObstacle[i].lane = 1;
				image->copyObstacle[i].direction = 0;
				image->copyObstacle[i].x = 640;									//������,���³�
			}
			if (image->copyObstacle[i].appear == 1 && image->copyObstacle[i].direction == 0)		//����
				putimage_transparent(NULL, image->copyObstacle[i].img[image->count % 6 / 3], \
					image->copyObstacle[i].x -= gooseSpeed, laneYBase(image->copyObstacle[i]) - 30, BLACK);
			else if (image->copyObstacle[i].appear == 1 && image->copyObstacle[i].direction == 1)	//����
				putimage_transparent(NULL, image->copyObstacle[i].img[image->count % 6 / 3 +2], \
					image->copyObstacle[i].x += gooseSpeed, laneYBase(image->copyObstacle[i]) - 30, BLACK);

			char path[50] = "music/coin.mp3";
			switch(isCollide(&image->rabbit, image->copyObstacle[i])) {
			//�жϻ�ɱ
			//������ͷ������С��
			case COLL_KILL:
				image->copyObstacle[i].appear = 0;								//һֻС����ʧ,����������1
				image->gooseNumber--;
				image->killNumber++;
				playMusicOnce("music/coin.mp3");
				image->rabbit.coin += 3;
				image->rabbit.save += 3;
				doubleJump(&image->rabbit);
				break;
			//�ж�ʧѪ
			//С�칰��
			case COLL_HURT:
				image->copyObstacle[i].hurt = 1;									//ʧѪflag
				image->rabbit.bloodValue--;
				break;
			}
		}
	}
}

//������:����С�ڶ�->˳ʱ��2
void littleGooseEmerge2(imageOnDevice* image, int gooseSpeed) {
	//û��ʼ��,���ȳ�ʼ��
	if (image->init[image->time] == 0) {
		image->gooseNumber = 8;
		for (int i = 0; i < 8; i++) {
			image->templateObstacle[2].lane = 3;
			image->templateObstacle[2].x = 640 + i * 130;
			image->copyObstacle[i] = image->templateObstacle[2];
			image->copyObstacle[i].direction = 0;
		}
		image->init[image->time] = 1;
	}
	else {
		//����ѭ����ʽ->ˢ�·�ʽ
		for (int i = 0; i < 8; i++) {
			if (image->copyObstacle[i].x < -35 && image->copyObstacle[i].lane == 3) {
				image->copyObstacle[i].hurt = 0;									//�����Թ�������
				image->copyObstacle[i].lane = 1;
				image->copyObstacle[i].direction = 1;
				image->copyObstacle[i].x = -35;									//������,���ϳ�
			}
			else if (image->copyObstacle[i].x > 640 && image->copyObstacle[i].lane == 1) {
				image->copyObstacle[i].hurt = 0;									//�����Թ�������
				image->copyObstacle[i].lane = 3;
				image->copyObstacle[i].direction = 0;
				image->copyObstacle[i].x = 640;									//������,���³�
			}
			if (image->copyObstacle[i].appear == 1 && image->copyObstacle[i].direction == 0)		//����
				putimage_transparent(NULL, image->copyObstacle[i].img[image->count % 6 / 3], \
					image->copyObstacle[i].x -= gooseSpeed, laneYBase(image->copyObstacle[i]) - 30, BLACK);
			else if (image->copyObstacle[i].appear == 1 && image->copyObstacle[i].direction == 1)	//����
				putimage_transparent(NULL, image->copyObstacle[i].img[image->count % 6 / 3 + 2], \
					image->copyObstacle[i].x += gooseSpeed, laneYBase(image->copyObstacle[i]) - 30, BLACK);

			char path[50] = "music/coin.mp3";
			switch(isCollide(&image->rabbit, image->copyObstacle[i])) {
			//�жϻ�ɱ
			//������ͷ������С��
			case COLL_KILL:
				image->copyObstacle[i].appear = 0;								//һֻС����ʧ,����������1
				image->gooseNumber--;
				image->killNumber++;
				playMusicOnce("music/coin.mp3");
				image->rabbit.coin += 3;
				image->rabbit.save += 3;
				doubleJump(&image->rabbit);
				break;
			//�ж�ʧѪ
			//С�칰��
			case COLL_HURT:
				image->copyObstacle[i].hurt = 1;									//ʧѪflag
				image->rabbit.bloodValue--;
				break;
			}
		}
	}
}

//������:����С�ڶ�->��ʱ��3
void littleGooseEmerge3(imageOnDevice* image, int gooseSpeed) {
	//û��ʼ��,���ȳ�ʼ��
	if (image->init[image->time] == 0) {
		image->gooseNumber = 8;
		for (int i = 0; i < 8; i++) {
			image->templateObstacle[2].lane = 1;
			image->templateObstacle[2].x = 640 + i * 130;
			image->copyObstacle[i] = image->templateObstacle[2];
			image->copyObstacle[i].direction = 0;
		}
		image->init[image->time] = 1;
	}
	else {
		//����ѭ����ʽ->ˢ�·�ʽ
		for (int i = 0; i < 8; i++) {
			if (image->copyObstacle[i].x < -35 && image->copyObstacle[i].lane == 1) {
				image->copyObstacle[i].hurt = 0;									//�����Թ�������
				image->copyObstacle[i].lane = 3;
				image->copyObstacle[i].direction = 1;
				image->copyObstacle[i].x = -35;									//������,���ϳ�
			}
			else if (image->copyObstacle[i].x > 640 && image->copyObstacle[i].lane == 3) {
				image->copyObstacle[i].hurt = 0;									//�����Թ�������
				image->copyObstacle[i].lane = 1;
				image->copyObstacle[i].direction = 0;
				image->copyObstacle[i].x = 640;									//������,���³�
			}
			if (image->copyObstacle[i].appear == 1 && image->copyObstacle[i].direction == 0)		//����
				putimage_transparent(NULL, image->copyObstacle[i].img[image->count % 6 / 3], \
					image->copyObstacle[i].x -= gooseSpeed, laneYBase(image->copyObstacle[i]) - 30, BLACK);
			else if (image->copyObstacle[i].appear == 1 && image->copyObstacle[i].direction == 1)	//����
				putimage_transparent(NULL, image->copyObstacle[i].img[image->count % 6 / 3 + 2], \
					image->copyObstacle[i].x += gooseSpeed, laneYBase(image->copyObstacle[i]) - 30, BLACK);

			switch(isCollide(&image->rabbit, image->copyObstacle[i])) {
			//�жϻ�ɱ
			//������ͷ������С��
			case COLL_KILL:
				image->copyObstacle[i].appear = 0;								//һֻС����ʧ,����������1
				image->gooseNumber--;
				image->killNumber++;
				playMusicOnce("music/coin.mp3");
				image->rabbit.coin += 3;
				image->rabbit.save += 3;
				doubleJump(&image->rabbit);
				break;
			//�ж�ʧѪ
			//С�칰��
			case COLL_HURT:
				image->copyObstacle[i].hurt = 1;									//ʧѪflag
				image->rabbit.bloodValue--;
				break;
			}
		}
	}
}

//������:����С�ڶ�->˳ʱ��+��ʱ��4
void littleGooseEmerge4(imageOnDevice* image, int gooseSpeed) {
	//û��ʼ��,���ȳ�ʼ��
	if (image->init[image->time] == 0) {
		image->gooseNumber = 10;
		for (int i = 0; i < 5; i++) {										    //��ʱ���
			image->templateObstacle[2].lane = 1;
			image->templateObstacle[2].x = 640 + i * 120;
			image->copyObstacle[i] = image->templateObstacle[2];
			image->copyObstacle[i].direction = 0;
		}
		for (int i = 5; i < 10; i++) {									    	//˳ʱ���
			image->templateObstacle[2].lane = 3;
			image->templateObstacle[2].x = 640 + (i - 5) * 120;
			image->copyObstacle[i] = image->templateObstacle[2];
			image->copyObstacle[i].direction = 0;
		}
		image->init[image->time] = 1;
	}
	else {
		//����ѭ����ʽ->ˢ�·�ʽ
		for (int i = 0; i < 10; i++) {
			//��ʱ���
			if (image->copyObstacle[i].x < -35 && image->copyObstacle[i].lane == 1 && i >= 0 && i < 5) {
				image->copyObstacle[i].hurt = 0;									//һ·��������һ�ξ���
				image->copyObstacle[i].lane = 3;
				image->copyObstacle[i].direction = 1;
				image->copyObstacle[i].x = -35;									//������,���³�
			}
			else if (image->copyObstacle[i].x > 640 && image->copyObstacle[i].lane == 3 && i >= 0 && i < 5) {
				image->copyObstacle[i].hurt = 0;									//һ·��������һ�ξ���
				image->copyObstacle[i].lane = 1;
				image->copyObstacle[i].direction = 0;
				image->copyObstacle[i].x = 640;									//������,���ϳ�
			}
			//˳ʱ���
			if (image->copyObstacle[i].x < -35 && image->copyObstacle[i].lane == 3 && i >= 5 && i < 10) {
				image->copyObstacle[i].hurt = 0;									//һ·��������һ�ξ���
				image->copyObstacle[i].lane = 1;
				image->copyObstacle[i].direction = 1;
				image->copyObstacle[i].x = -35;									//������,���ϳ�
			}
			else if (image->copyObstacle[i].x > 640 && image->copyObstacle[i].lane == 1 && i >= 5 && i < 10) {
				image->copyObstacle[i].hurt = 0;									//һ·��������һ�ξ���
				image->copyObstacle[i].lane = 3;
				image->copyObstacle[i].direction = 0;
				image->copyObstacle[i].x = 640;									//������,���³�
			}

			if (image->copyObstacle[i].appear == 1 && image->copyObstacle[i].direction == 0)		//����
				putimage_transparent(NULL, image->copyObstacle[i].img[image->count % 6 / 3], \
					image->copyObstacle[i].x -= gooseSpeed, laneYBase(image->copyObstacle[i]) - 30, BLACK);
			else if (image->copyObstacle[i].appear == 1 && image->copyObstacle[i].direction == 1)	//����
				putimage_transparent(NULL, image->copyObstacle[i].img[image->count % 6 / 3 + 2], \
					image->copyObstacle[i].x += gooseSpeed, laneYBase(image->copyObstacle[i]) - 30, BLACK);

			switch(isCollide(&image->rabbit, image->copyObstacle[i])) {
			//�жϻ�ɱ
			//������ͷ������С��
			case COLL_KILL:
				image->copyObstacle[i].appear = 0;								//һֻС����ʧ,����������1
				image->gooseNumber--;
				image->killNumber++;
				playMusicOnce("music/coin.mp3");
				image->rabbit.coin += 3;
				image->rabbit.save += 3;
				doubleJump(&image->rabbit);
				break;
			//�ж�ʧѪ
			//С�칰��
			case COLL_HURT:
				image->copyObstacle[i].hurt = 1;									//ʧѪflag
				image->rabbit.bloodValue--;
				break;
			}
		}
	}
}

//ˢ�½�ɫѪ����
void refreshAdd(imageOnDevice* image, int count) {
	//�жϳ���״̬

	if (image->rabbit.coin >= 50) {
		image->rabbit.coin = 0;
		image->rabbit.superState = SUPER;
		image->tempCount = count;
		image->rabbit.bloodValue++;
	}

	//�ص�����״̬
	if (count == image->tempCount + 100)
		image->rabbit.superState = HALF_SUPER;
	if (count == image->tempCount + 120)
		image->rabbit.superState = NORMAL;

	//��ʾѪ����
	for (int i = 0; i < image->rabbit.bloodValue; i++) {
		putimage_transparent(NULL, image->rabbit.blood, image->rabbit.x + 50 / image->rabbit.bloodLimit * i, Y(image->rabbit) - 15, BLACK);
	}
	//��ʾ����
	for (int i = 0; i < image->rabbit.coin; i++) {
		putimage_transparent(NULL, image->rabbit.skill, image->rabbit.x + i, Y(image->rabbit) - 25, BLACK);
	}
}

//ˢ���ַ���
void refreshString(int color, int number, int set) {
	setbkmode(TRANSPARENT);
	setfont(30, 0, "impact");
	setcolor(color);
	//��ʵ�������ַ��������,������û��
	if (number < 100)
		xyprintf(set + 15, 5, "%d", number);
	else if (number > 100 && number < 1000)
		xyprintf(set + 10, 5, "%d", number);
	else if (number > 1000 && number < 1100)
		xyprintf(set + 5, 5, "%d,0%d", number / 1000, number % 1000);
	else if (number > 1100 && number < 10000)
		xyprintf(set + 5, 5, "%d,%d", number / 1000, number % 1000);
	else if (number > 10000 && number < 10100)
		xyprintf(set, 5, "%d,0%d", number / 1000, number % 1000);
	else if (number > 10100 && number < 100000)
		xyprintf(set, 5, "%d,%d", number / 1000, number % 1000);
	else if (number > 100000 && number < 100100) {
		setfont(25, 0, "impact");
		xyprintf(set, 7, "%d,0%d", number / 1000, number % 1000);
	}
	else if (number > 100100 && number < 1000000) {
		setfont(25, 0, "impact");
		xyprintf(set, 7, "%d,%d", number / 1000, number % 1000);
	}
	else {
		xyprintf(set, 5, "%d e6", number / 1000000);
		xyprintf(set, 37, "%d", number);
	}

}

//ˢ�³��ܻ���+������ʱ
void delayJudge(imageOnDevice image, int count) {
	if (image.rabbit.superState == SUPER) {
		putimage_transparent(NULL, image.rabbit.superStar[count % 12 / 6], image.rabbit.x, Y(image.rabbit) - 25, BLACK);
		delay_ms(30);
	}
	else if (image.rabbit.superState == HALF_SUPER) {
		putimage_transparent(NULL, image.rabbit.superStarHalf[count % 12 / 6], image.rabbit.x, Y(image.rabbit) - 25, BLACK);
		delay_ms(50);
	}
	else if (image.rabbit.superState == NORMAL)
		delay_ms(50);
}

/********************************************************���ͼ��**************************************************************/
//�����ɫͼ��
void delCharacterImage(imageOnDevice image) {
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 5; j++)
			for (int k = 0; k < 9; k++)
				delimage(image.rabbit.frameSet[i][j][k]);
	delimage(image.rabbit.blood);
	delimage(image.rabbit.skill);
	delimage(image.rabbit.superStar[0]);
	delimage(image.rabbit.superStar[1]);
	delimage(image.rabbit.superStarHalf[0]);
	delimage(image.rabbit.superStarHalf[1]);
}

//����ϰ�ͼ��
void delObstacleImage(imageOnDevice image) {
	for (int i = 0; i < image.templateNumber; i++)
		for (int j = 0; j < image.frameNumber[i]; j++)
			delimage(image.templateObstacle[i].img[j]);

}

/********************************************************the end**************************************************************/

int gameInRoad_story() {
	imageOnDevice imageOnRoad;
	imageOnRoad.rabbit.bloodLimit = 2;
	imageOnRoad.rabbit.bloodValue = 2;
	imageOnRoad.level = 1;
	initCharacter(&imageOnRoad.rabbit);	//��ʼ����ɫ���ͼ��
	initBackground(&imageOnRoad);				//��ʼ������ͼ��
	initCoinTemplate(&imageOnRoad);			//��ʼ�����ģ��
	int changeLaneTime = 0;									//���ʱ��
	imageOnRoad.rabbit.coin = 0;							//�Ѷ��Ϳ�
	initializeSkin(&imageOnRoad.rabbit);
	TUTORIAL_UI tutorial;
	tutorial.img = newimage();
	roadGeneration(&imageOnRoad, false);				//�ϰ�������
	refresh(imageOnRoad.rabbit, imageOnRoad.background, imageOnRoad.buffer, tutorial);

	MUSIC road; // ����һ�����ֶ���
	road.OpenFile("music/road.mp3"); // ���ļ�
	//���Ž̳�
	int count = 0;
	while (getTutorial(1, &tutorial, &imageOnRoad.rabbit) == 0)
	{
		if (road.GetPlayStatus() == MUSIC_MODE_STOP)
			road.Play();
		action(&imageOnRoad.rabbit);
		if (keyDetect(&imageOnRoad.rabbit, 1))
		{
			road.Pause();
			switch (pause()) {
			case PAUSE_CONTINUE:
				road.Play();
				break;
			case PAUSE_EXIT:
				road.Close();
				delimage(imageOnRoad.background);
				delimage(imageOnRoad.buffer);
				delCharacterImage(imageOnRoad);
				delObstacleImage(imageOnRoad);
				return GAME_EXIT;
			}
		}
		refresh(imageOnRoad.rabbit, imageOnRoad.background, imageOnRoad.buffer, tutorial);
		imageOnRoad.rabbit.frame++;
		delay_ms(50);
		count++;
	}
	int countTemp = count;
	//��ʽ����
	int obstacleSpeed = 12;									//�ϰ����ƶ��ٶ�
	imageOnRoad.tempCount = 0;
	for (count = countTemp; count < countTemp + 400; count++)
	{
		if (road.GetPlayStatus() == MUSIC_MODE_STOP)
			road.Play();
		if (count == countTemp + 145) obstacleSpeed = 20;
		if (count == countTemp + 300) obstacleSpeed = 26;				//������ 12*200 + 14*200 + 16*180 = 8080������
		action(&imageOnRoad.rabbit);						//�ı������ж�״̬
		if (keyDetect(&imageOnRoad.rabbit, 1))				//�жϰ���+��ͣ
		{
			road.Pause();
			switch (pause()) {
			case PAUSE_CONTINUE:
				road.Play();
				break;
			case PAUSE_EXIT:
				road.Close();
				delimage(imageOnRoad.background);
				delimage(imageOnRoad.buffer);
				delCharacterImage(imageOnRoad);
				delObstacleImage(imageOnRoad);
				return GAME_EXIT;
			}
		}
		refresh(imageOnRoad.rabbit, imageOnRoad.background, imageOnRoad.buffer);
		imageOnRoad.rabbit.frame++;
		obstacleRefresh(&imageOnRoad, count, obstacleSpeed);
		refreshAdd(&imageOnRoad, count);
		delayJudge(imageOnRoad, count);
		if (imageOnRoad.rabbit.bloodValue == 0)
		{
			road.Close();
			delimage(imageOnRoad.background);
			delimage(imageOnRoad.buffer);
			delCharacterImage(imageOnRoad);
			delObstacleImage(imageOnRoad);
			return GAME_DEAD;
		}
	}
	road.Close();

	//���سɹ�
	MUSIC victory; // ����һ�����ֶ���
	victory.OpenFile("music/victory.mp3"); // ���ļ�
	victory.Play(0);
	for (int count = 0; count < 100; count++) {

		imageOnRoad.rabbit.x += 12;
		refresh(imageOnRoad.rabbit, imageOnRoad.background, imageOnRoad.buffer);
		imageOnRoad.rabbit.frame++;
		obstacleRefresh(&imageOnRoad, count, obstacleSpeed);
		refreshAdd(&imageOnRoad, count);
		imageOnRoad.rabbit.superState = SUPER;
		delayJudge(imageOnRoad, count);
	}
	victory.Close();

	delimage(imageOnRoad.background);
	delimage(imageOnRoad.buffer);
	delCharacterImage(imageOnRoad);
	delObstacleImage(imageOnRoad);

	return GAME_NONE;
}

int gameinRoad_infinite(int skin) {
	imageOnDevice imageOnRoad;
	imageOnRoad.rabbit.bloodLimit = 2;
	imageOnRoad.rabbit.bloodValue = 2;
	imageOnRoad.level = 1;
	initCharacter(&imageOnRoad.rabbit);	//��ʼ����ɫ���ͼ��
	initBackground(&imageOnRoad);				//��ʼ������ͼ��
	initCoinTemplate(&imageOnRoad);			//��ʼ�����ģ��
	int changeLaneTime = 0;									//���ʱ��
	imageOnRoad.rabbit.coin = 0;							//�Ѷ��Ϳ�
	imageOnRoad.rabbit.skin = skin;
	initializeSkin(&imageOnRoad.rabbit);
	int lastMoney;
	imageOnRoad.rabbit.save = lastMoney = getMoney();
	//��ʽ����
	int obstacleSpeed = 12;									//�ϰ����ƶ��ٶ�
	imageOnRoad.tempCount = 0;
	imageOnRoad.time = 0;
	MUSIC road; // ����һ�����ֶ���
	road.OpenFile("music/road.mp3"); // ���ļ�
	while (1) {
		//������Ƶ
		if (road.GetPlayStatus() == MUSIC_MODE_STOP)
			road.Play();
		roadGeneration(&imageOnRoad, true);
		refresh(imageOnRoad.rabbit, imageOnRoad.background, imageOnRoad.buffer);
		imageOnRoad.rabbit.frame++;
		for (imageOnRoad.count = 0; imageOnRoad.count < 550; imageOnRoad.count++)
		{
			if (imageOnRoad.count == 180 && imageOnRoad.time == 0) obstacleSpeed = 16;
			if (imageOnRoad.count == 400 && imageOnRoad.time == 0) obstacleSpeed = 16;				//������ 12*200 + 14*200 + 16*180 = 8080������
			if (imageOnRoad.time != 0) obstacleSpeed = 16 + 3 * imageOnRoad.time;
			action(&imageOnRoad.rabbit);						//�ı������ж�״̬
			if (keyDetect(&imageOnRoad.rabbit, 1))				//�жϰ���+��ͣ
			{
				road.Pause();
				switch (pause()) {
				case PAUSE_CONTINUE:
					road.Play();
					break;
				case PAUSE_EXIT:
					road.Close();
					delimage(imageOnRoad.background);
					delimage(imageOnRoad.buffer);
					delCharacterImage(imageOnRoad);
					delObstacleImage(imageOnRoad);
					return GAME_EXIT;
				}
			}
			refresh(imageOnRoad.rabbit, imageOnRoad.background, imageOnRoad.buffer);
			imageOnRoad.rabbit.frame++;
			obstacleRefresh(&imageOnRoad, imageOnRoad.count, obstacleSpeed);
			coinRefresh(&imageOnRoad, imageOnRoad.count, obstacleSpeed);
			refreshAdd(&imageOnRoad, imageOnRoad.count + imageOnRoad.time * 550);

			//��ʾ���
			putimage_transparent(NULL, imageOnRoad.coinboxs, 545, 5, BLACK);
			refreshString(EGERGB(255, 215, 0), imageOnRoad.rabbit.save, 575);
			//��ʾ���
			int distance = imageOnRoad.count + 550 * imageOnRoad.time;
			putimage_transparent(NULL, imageOnRoad.distance, 455, 5, BLACK);
			refreshString(GREEN, distance, 485);

			//��ʾ����ֵ
			putimage_transparent(NULL, imageOnRoad.heart, 370, 5, BLACK);
			setbkmode(TRANSPARENT);
			setfont(30, 0, "impact");
			setcolor(RED);
			xyprintf(420, 5, "%d", imageOnRoad.rabbit.bloodValue);

			delayJudge(imageOnRoad, imageOnRoad.count);
			//�浵
			if (imageOnRoad.rabbit.bloodValue == 0) {
				road.Close();
				delimage(imageOnRoad.background);
				delimage(imageOnRoad.buffer);
				delCharacterImage(imageOnRoad);
				delObstacleImage(imageOnRoad);
				gameover(1, "GAMEOVER1.png", distance, imageOnRoad.rabbit.save - lastMoney);
				return GAME_DEAD;
			}
		}
		imageOnRoad.time++;
	}
	road.Close();
	delimage(imageOnRoad.background);
	delimage(imageOnRoad.buffer);
	delCharacterImage(imageOnRoad);
	delObstacleImage(imageOnRoad);

	return GAME_NONE;
}

int gameInCanteen_story() {
	imageOnDevice imageInCanteen;
	imageInCanteen.rabbit.bloodLimit = 10;
	imageInCanteen.rabbit.bloodValue = 10;
	imageInCanteen.level = 2;
	initCharacter(&imageInCanteen.rabbit);	//��ʼ����ɫ���ͼ��
	initBackground(&imageInCanteen);				//��ʼ������ͼ��
	initCoinTemplate(&imageInCanteen);				//��ʼ�����ģ��
	int changeLaneTime = 0;											//���ʱ��
	imageInCanteen.rabbit.coin = 0;									//�Ѷ��Ϳ�
	initializeSkin(&imageInCanteen.rabbit);
	TUTORIAL_UI tutorial;
	tutorial.img = newimage();
	canteenGeneration_temp(&imageInCanteen);		//�����ϰ���
	refresh(imageInCanteen.rabbit, imageInCanteen.background, imageInCanteen.buffer, tutorial);
	imageInCanteen.rabbit.x = 50;
	MUSIC canteen; // ����һ�����ֶ���
	canteen.OpenFile("music/canteen.mp3"); // ���ļ�
	//���Ž̳�
	while (getTutorial(2, &tutorial, &imageInCanteen.rabbit) == 0)
	{
		if (canteen.GetPlayStatus() == MUSIC_MODE_STOP)
			canteen.Play();
		action(&imageInCanteen.rabbit);
		if (keyDetect(&imageInCanteen.rabbit, 2))
		{
			canteen.Pause();
			switch (pause()) {
			case PAUSE_CONTINUE:
				canteen.Play();
				break;
			case PAUSE_EXIT:
				canteen.Close();
				delimage(imageInCanteen.background);
				delimage(imageInCanteen.buffer);
				delCharacterImage(imageInCanteen);
				delObstacleImage(imageInCanteen);
				return GAME_EXIT;
			}
		}
		refresh(imageInCanteen.rabbit, imageInCanteen.background, imageInCanteen.buffer, tutorial);
		imageInCanteen.rabbit.frame++;
		delay_ms(50);
	}

	imageInCanteen.templateObstacle[2].lane = imageInCanteen.rabbit.lane;  //ȫ����ʼ��
	imageInCanteen.templateObstacle[2].x = -50;
	imageInCanteen.templateObstacle[2].fixY = 0;
	putimage_transparent(NULL, imageInCanteen.templateObstacle[2].img[imageInCanteen.count % 4 / 2], -50, Y(imageInCanteen.templateObstacle[2]), BLACK);
	//���ܵ���Ӧλ��
	imageInCanteen.rabbit.state = RUN;
	for (imageInCanteen.count = 0; imageInCanteen.count < 50; imageInCanteen.count++) {
		if (canteen.GetPlayStatus() == MUSIC_MODE_STOP)
			canteen.Play();
		action(&imageInCanteen.rabbit);								//�ı������ж�״̬
		if (keyDetect(&imageInCanteen.rabbit, 2))					//�жϰ���
		{
			canteen.Pause();
			switch (pause()) {
			case PAUSE_CONTINUE:
				canteen.Play();
				break;
			case PAUSE_EXIT:
				canteen.Close();
				delimage(imageInCanteen.background);
				delimage(imageInCanteen.buffer);
				delCharacterImage(imageInCanteen);
				delObstacleImage(imageInCanteen);
				return GAME_EXIT;
			}
		}
		if (imageInCanteen.rabbit.x < 420) {
			imageInCanteen.rabbit.x += 10;
			refresh(imageInCanteen.rabbit, imageInCanteen.background, imageInCanteen.buffer);
			imageInCanteen.rabbit.frame++;
			delay_ms(40);
		}
		else {
			refresh(imageInCanteen.rabbit, imageInCanteen.background, imageInCanteen.buffer);
			imageInCanteen.rabbit.frame++;
			delay_ms(50);
		}
	}
	//��ʽ����
	for (imageInCanteen.count = 0; imageInCanteen.count < 750; imageInCanteen.count++) {
		//������Ƶ
		if (canteen.GetPlayStatus() == MUSIC_MODE_STOP)
			canteen.Play();
		action(&imageInCanteen.rabbit);								//�ı������ж�״̬
		if (keyDetect(&imageInCanteen.rabbit, 2))					//�жϰ���
		{
			canteen.Pause();
			switch (pause()) {
			case PAUSE_CONTINUE:
				canteen.Play();
				break;
			case PAUSE_EXIT:
				canteen.Close();
				delimage(imageInCanteen.background);
				delimage(imageInCanteen.buffer);
				delCharacterImage(imageInCanteen);
				delObstacleImage(imageInCanteen);
				return GAME_EXIT;
			}
		}
		refresh(imageInCanteen.rabbit, imageInCanteen.background, imageInCanteen.buffer);
		imageInCanteen.rabbit.frame++;
		if (imageInCanteen.count < 700)								//�������������ʱ��
			damaChaser(&imageInCanteen);			//���ð��һ����׷���ᵫ���������Ĵ���
		weaponGenerate(&imageInCanteen);			//�ɵ�,Ʋ��
		weaponChaser(&imageInCanteen, 15);				//��ˢ��
		refreshAdd(&imageInCanteen, imageInCanteen.count);
		delayJudge(imageInCanteen, imageInCanteen.count);
		if (imageInCanteen.rabbit.bloodValue == 0)
		{
			delimage(imageInCanteen.background);
			delimage(imageInCanteen.buffer);
			delCharacterImage(imageInCanteen);
			delObstacleImage(imageInCanteen);
			return GAME_DEAD;
		}
	}

	//���سɹ�
	MUSIC victory; // ����һ�����ֶ���
	victory.OpenFile("music/victory.mp3"); // ���ļ�
	victory.Play(0);
	for (int count = 0; count < 100 && imageInCanteen.rabbit.x < 640; count++) {
		imageInCanteen.rabbit.x += 12;
		refresh(imageInCanteen.rabbit, imageInCanteen.background, imageInCanteen.buffer);
		imageInCanteen.rabbit.frame++;
		refreshAdd(&imageInCanteen, count);
		imageInCanteen.rabbit.superState = SUPER;
		delayJudge(imageInCanteen, count);
	}
	victory.Close();
	canteen.Close();

	delimage(imageInCanteen.background);
	delimage(imageInCanteen.buffer);
	delCharacterImage(imageInCanteen);
	delObstacleImage(imageInCanteen);

	return GAME_NONE;
}

int gameInCanteen_infinite(int skin) {
	imageOnDevice imageInCanteen;
	imageInCanteen.rabbit.bloodLimit = 10;
	imageInCanteen.rabbit.bloodValue = 10;
	imageInCanteen.level = 2;
	initCharacter(&imageInCanteen.rabbit);	//��ʼ����ɫ���ͼ��
	initBackground(&imageInCanteen);				//��ʼ������ͼ��
	initCoinTemplate(&imageInCanteen);				//��ʼ�����ģ��
	int changeLaneTime = 0;											//���ʱ��
	imageInCanteen.rabbit.coin = 0;									//�Ѷ��Ϳ�
	imageInCanteen.rabbit.skin = skin;
	initializeSkin(&imageInCanteen.rabbit);
	canteenGeneration_temp(&imageInCanteen);		//�����ϰ���
	refresh(imageInCanteen.rabbit, imageInCanteen.background, imageInCanteen.buffer);
	imageInCanteen.rabbit.frame++;
	imageInCanteen.rabbit.x = 50;
	int lastMoney;
	imageInCanteen.rabbit.save = lastMoney = getMoney();

	imageInCanteen.templateObstacle[2].lane = imageInCanteen.rabbit.lane;  //ȫ����ʼ��
	imageInCanteen.templateObstacle[2].x = -50;
	imageInCanteen.templateObstacle[2].fixY = 0;
	putimage_transparent(NULL, imageInCanteen.templateObstacle[2].img[imageInCanteen.count % 4 / 2], -50, Y(imageInCanteen.templateObstacle[2]), BLACK);
	//���ܵ���Ӧλ��
	imageInCanteen.rabbit.state = RUN;
	MUSIC canteen; // ����һ�����ֶ���
	canteen.OpenFile("music/canteen.mp3"); // ���ļ�
	for (imageInCanteen.count = 0; imageInCanteen.count < 50; imageInCanteen.count++) {
		if (canteen.GetPlayStatus() == MUSIC_MODE_STOP)
			canteen.Play();
		action(&imageInCanteen.rabbit);								//�ı������ж�״̬
		if (keyDetect(&imageInCanteen.rabbit, 2))					//�жϰ���
		{
			canteen.Pause();
			switch (pause()) {
			case PAUSE_CONTINUE:
				canteen.Play();
				break;
			case PAUSE_EXIT:
				canteen.Close();
				delimage(imageInCanteen.background);
				delimage(imageInCanteen.buffer);
				delCharacterImage(imageInCanteen);
				delObstacleImage(imageInCanteen);
				return GAME_EXIT;
			}
		}
		if (imageInCanteen.rabbit.x < 420) {
			imageInCanteen.rabbit.x += 10;
			refresh(imageInCanteen.rabbit, imageInCanteen.background, imageInCanteen.buffer);
			imageInCanteen.rabbit.frame++;
			delay_ms(40);
		}
		else {
			refresh(imageInCanteen.rabbit, imageInCanteen.background, imageInCanteen.buffer);
			imageInCanteen.rabbit.frame++;
			delay_ms(50);
		}
	}
	imageInCanteen.time = 0;
	//��ʽ����
	int partTime = 850;
	int knifeSpeed = 15;
	while (1) {
		canteenGeneration(&imageInCanteen);
		refresh(imageInCanteen.rabbit, imageInCanteen.background, imageInCanteen.buffer);
		imageInCanteen.rabbit.frame++;
		for (imageInCanteen.count = 0; imageInCanteen.count < partTime; imageInCanteen.count++) {
			int distance = imageInCanteen.count + partTime * imageInCanteen.time;//Ҳ�������ڵ�֡count Now
			if (canteen.GetPlayStatus() == MUSIC_MODE_STOP)
				canteen.Play();
			action(&imageInCanteen.rabbit);								//�ı������ж�״̬
			if (keyDetect(&imageInCanteen.rabbit, 2))					//�жϰ���
			{
				canteen.Pause();
				switch (pause()) {
				case PAUSE_CONTINUE:
					canteen.Play();
					break;
				case PAUSE_EXIT:
					canteen.Close();
					delimage(imageInCanteen.background);
					delimage(imageInCanteen.buffer);
					delCharacterImage(imageInCanteen);
					delObstacleImage(imageInCanteen);
					return GAME_EXIT;
				}
			}
			refresh(imageInCanteen.rabbit, imageInCanteen.background, imageInCanteen.buffer);
			imageInCanteen.rabbit.frame++;
			damaChaser(&imageInCanteen);				//���ð��һ����׷���ᵫ���������Ĵ���
			weaponGenerate(&imageInCanteen);			//�ɵ�,Ʋ��
			weaponChaser(&imageInCanteen, knifeSpeed);				//��ˢ��
			obstacleRefresh2(&imageInCanteen, imageInCanteen.count, 12);
			refreshAdd(&imageInCanteen, distance);

			//��ʾ���
			putimage_transparent(NULL, imageInCanteen.coinboxs, 545, 5, BLACK);
			refreshString(EGERGB(255, 215, 0), imageInCanteen.rabbit.save, 575);
			//��ʾ���
			putimage_transparent(NULL, imageInCanteen.distance, 455, 5, BLACK);
			refreshString(GREEN, distance, 485);

			//��ʾ����ֵ
			putimage_transparent(NULL, imageInCanteen.heart, 370, 5, BLACK);
			setbkmode(TRANSPARENT);
			setfont(30, 0, "impact");
			setcolor(RED);
			xyprintf(420, 5, "%d", imageInCanteen.rabbit.bloodValue);

			delayJudge(imageInCanteen, distance);
			if (imageInCanteen.rabbit.bloodValue <= 0) {
				canteen.Close();
				delimage(imageInCanteen.background);
				delimage(imageInCanteen.buffer);
				delCharacterImage(imageInCanteen);
				delObstacleImage(imageInCanteen);
				gameover(2, "GAMEOVER2.png", distance, imageInCanteen.rabbit.save - lastMoney);
				return GAME_DEAD;
			}
		}
		imageInCanteen.time++;
		knifeSpeed++;
	}

	canteen.Close();
	delimage(imageInCanteen.background);
	delimage(imageInCanteen.buffer);
	delCharacterImage(imageInCanteen);
	delObstacleImage(imageInCanteen);

	return GAME_NONE;
}

int gameInLake_story() {
	imageOnDevice imageInLake;
	imageInLake.rabbit.bloodLimit = 10;
	imageInLake.rabbit.bloodValue = 10;
	imageInLake.rabbit.x = 50;
	imageInLake.level = 3;
	initCharacter(&imageInLake.rabbit);			//��ʼ����ɫ���ͼ��
	initBackground(&imageInLake);						//��ʼ������ͼ��
	int changeLaneTime = 0;											//���ʱ��
	imageInLake.rabbit.coin = 0;									//�Ѷ��Ϳ�
	initializeSkin(&imageInLake.rabbit);
	lakeGeneration_temp(&imageInLake);					//�����ϰ���
	refresh(imageInLake.rabbit, imageInLake.background, imageInLake.buffer);



	//��ʽ����
	MUSIC lake; // ����һ�����ֶ���
	lake.OpenFile("music/lake.mp3"); // ���ļ�
	imageInLake.count = 0;
	while (1) {
		if (lake.GetPlayStatus() == MUSIC_MODE_STOP)
			lake.Play();
		action(&imageInLake.rabbit);								//�ı������ж�״̬
		if (keyDetect(&imageInLake.rabbit, 2))						//�жϰ���
		{
			lake.Pause();
			switch (pause()) {
			case PAUSE_CONTINUE:
				lake.Play();
				break;
			case PAUSE_EXIT:
				lake.Close();
				delimage(imageInLake.background);
				delimage(imageInLake.buffer);
				delCharacterImage(imageInLake);
				delObstacleImage(imageInLake);
				return GAME_EXIT;
			}
		}
		refresh(imageInLake.rabbit, imageInLake.background, imageInLake.buffer);
		imageInLake.rabbit.frame++;
		refreshAdd(&imageInLake, imageInLake.count);
		if (imageInLake.time < 4)									//0123���ֺڶ�
			gooseEmerge(&imageInLake, 30, 10);				//30֡����
		if (imageInLake.time == 4)									//4,���ִ�ڶ�,С�ڶ����·��
			bigGooseEmerge(&imageInLake, 10);
		if (imageInLake.time == 5)
			break;													//review 18:07 3/18 return->break
		delayJudge(imageInLake, imageInLake.count);
		if (imageInLake.rabbit.bloodValue == 0)
		{
			delay_ms(1000);
			lake.Close();
			delimage(imageInLake.background);
			delimage(imageInLake.buffer);
			delCharacterImage(imageInLake);
			delObstacleImage(imageInLake);
			return GAME_DEAD;
		}
		imageInLake.count++;
	}

	//���سɹ�
	for (int count = 0; count < 100 && imageInLake.rabbit.x < 640; count++) {
		if (lake.GetPlayStatus() == MUSIC_MODE_STOP)
			lake.Play();
		imageInLake.rabbit.x += 12;
		refresh(imageInLake.rabbit, imageInLake.background, imageInLake.buffer);
		imageInLake.rabbit.frame++;
		refreshAdd(&imageInLake, count);
		imageInLake.rabbit.superState = SUPER;
		delayJudge(imageInLake, count);
	}
	lake.Close();
	delimage(imageInLake.background);
	delimage(imageInLake.buffer);
	delCharacterImage(imageInLake);
	delObstacleImage(imageInLake);

	return GAME_NONE;
}

int gameInLake_infinite(int skin) {
	imageOnDevice imageInLake;
	imageInLake.rabbit.bloodLimit = 10;
	imageInLake.rabbit.bloodValue = 10;
	imageInLake.rabbit.x = 50;
	imageInLake.level = 3;
	initCharacter(&imageInLake.rabbit);			//��ʼ����ɫ���ͼ��
	initBackground(&imageInLake);						//��ʼ������ͼ��
	initCoinTemplate(&imageInLake);					//��ʼ�����ģ��
	int changeLaneTime = 0;											//���ʱ��
	imageInLake.rabbit.coin = 0;									//�Ѷ��Ϳ�
	imageInLake.rabbit.skin = skin;
	initializeSkin(&imageInLake.rabbit);
	lakeGeneration_temp(&imageInLake);					//�����ϰ���
	refresh(imageInLake.rabbit, imageInLake.background, imageInLake.buffer);
	int lastMoney;
	imageInLake.rabbit.save = lastMoney = getMoney();

	//��ʽ����
	int gooseSpeed = 10;
	imageInLake.count = 0;
	MUSIC road; // ����һ�����ֶ���
	road.OpenFile("music/road.mp3"); // ���ļ�

	while (1) {
		if (road.GetPlayStatus() == MUSIC_MODE_STOP)
			road.Play(0);
		action(&imageInLake.rabbit);								//�ı������ж�״̬
		if (keyDetect(&imageInLake.rabbit, 3))						//�жϰ���
		{
			road.Pause();
			switch (pause()) {
			case PAUSE_CONTINUE:
				road.Play();
				break;
			case PAUSE_EXIT:
				road.Close();
				delimage(imageInLake.background);
				delimage(imageInLake.buffer);
				delCharacterImage(imageInLake);
				delObstacleImage(imageInLake);
				return GAME_EXIT;
			}
		}
		refresh(imageInLake.rabbit, imageInLake.background, imageInLake.buffer);
		imageInLake.rabbit.frame++;
		refreshAdd(&imageInLake, imageInLake.count);
		gooseSpeed = 10 + imageInLake.time / 5 * 3;
		if (imageInLake.time % 5 < 4)									//0123���ֺڶ�
			gooseEmerge(&imageInLake, 30, gooseSpeed);				//30֡����
		if (imageInLake.time % 5 == 4)									//4,���ִ�ڶ�,С�ڶ����·��
			bigGooseEmerge(&imageInLake, gooseSpeed);
		
		//review 8:19 3/21
//��ʾ���
		putimage_transparent(NULL, imageInLake.coinboxs, 545, 5, BLACK);
		refreshString(EGERGB(255, 215, 0), imageInLake.rabbit.save, 575);

		//��ʾɱ����
		putimage_transparent(NULL, imageInLake.kill, 455, 5, BLACK);
		refreshString(BLACK, imageInLake.killNumber, 490);

		//��ʾ����ֵ
		putimage_transparent(NULL, imageInLake.heart, 370, 5, BLACK);
		setbkmode(TRANSPARENT);
		setfont(30, 0, "impact");
		setcolor(RED);
		xyprintf(420, 5, "%d", imageInLake.rabbit.bloodValue);

		//test
		xyprintf(0, 0, "%d", imageInLake.gooseNumber);
		delayJudge(imageInLake, imageInLake.count);
		if (imageInLake.rabbit.bloodValue <= 0) {
			road.Close();
			delimage(imageInLake.background);
			delimage(imageInLake.buffer);
			delCharacterImage(imageInLake);
			delObstacleImage(imageInLake);
			gameover(3, "GAMEOVER3.png", imageInLake.killNumber * 50, imageInLake.rabbit.save - lastMoney);
			return GAME_DEAD;
		}													//review 19:10 3/18
		imageInLake.count++;

	}


	delimage(imageInLake.background);
	delimage(imageInLake.buffer);
	delCharacterImage(imageInLake);
	delObstacleImage(imageInLake);

	return GAME_NONE;
}
