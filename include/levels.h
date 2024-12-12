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
//异常中断不要愁, 二分法, 找源头.
//随机数, 先定好
//逻辑思路要清楚
//所用必须初始化
//记得数组别越界
//记得不要死循环


void initCharacter(CHARACTER* rabbit);
void initBackground(imageOnDevice* image);
void initCoinTemplate(imageOnDevice* image);
void roadGeneration(imageOnDevice* image, bool generateCoin);
void canteenGeneration(imageOnDevice* image);
void canteenGeneration_temp(imageOnDevice* image);
void canteenGeneration_temp(imageOnDevice* image);
void weaponGenerate(imageOnDevice* image);
//生成第三关障碍物模板
void lakeGeneration_temp(imageOnDevice* image);
//刷新背景和角色
void refresh(CHARACTER rabbit, PIMAGE background, PIMAGE buffer);
//第一关障碍物位置变化及显示
void obstacleRefresh(imageOnDevice* image, int count, int obstacleSpeed);
//第一关金币位置变化及显示
void coinRefresh(imageOnDevice* image, int count, int obstacleSpeed);
//第二关障碍物+金币位置变化及显示(暂时不用)
void obstacleRefresh2(imageOnDevice* image, int count, int obstacleSpeed);
//第二关:获得主角当前位置,大妈变轨
void damaChaser(imageOnDevice* image);
//第三关:在屏幕右方出现黑鹅
void gooseEmerge(imageOnDevice* image, int count, int gooseSpeed);
//第三关:在屏幕右方出现大黑鹅
//需要条件触发
void bigGooseEmerge(imageOnDevice* image, int gooseSpeed);
//第三关:过来小黑鹅->顺时针0
void littleGooseEmerge0(imageOnDevice* image, int gooseSpeed);
//第三关:过来小黑鹅->逆时针1
void littleGooseEmerge1(imageOnDevice* image, int gooseSpeed);
//第三关:过来小黑鹅->顺时针2
void littleGooseEmerge2(imageOnDevice* image, int gooseSpeed);
//第三关:过来小黑鹅->逆时针3
void littleGooseEmerge3(imageOnDevice* image, int gooseSpeed);
//第三关:过来小黑鹅->顺时针+逆时针4
void littleGooseEmerge4(imageOnDevice* image, int gooseSpeed);
//第二关:刷新武器,判定失血
void weaponChaser(imageOnDevice* image, int knifeSpeed);
//刷新角色血和蓝
void refreshAdd(imageOnDevice* image, int count);
//刷新字符串
void refreshString(int color, int number, int set);
//刷新超能护盾+决定延时
void delayJudge(imageOnDevice image, int count);
//清除角色图像
void delCharacterImage(imageOnDevice image);
//清除障碍图像
void delObstacleImage(imageOnDevice image);


/********************************************************初始化**************************************************************/
//初始化角色相关图像
void initCharacter(CHARACTER* rabbit) {
	//超能护盾
	rabbit->superStar[0] = newimage(50, 10);
	rabbit->superStar[1] = newimage(50, 10);
	setfillcolor(LIGHTBLUE, rabbit->superStar[1]);
	bar(0, 0, 50, 10, rabbit->superStar[1]);

	//半超能护盾
	rabbit->superStarHalf[0] = newimage(50, 10);
	rabbit->superStarHalf[1] = newimage(50, 10);
	setfillcolor(BLUE, rabbit->superStarHalf[1]);
	bar(0, 0, 50, 10, rabbit->superStarHalf[1]);

	//血量块;
	rabbit->blood = newimage(50, 10);
	setfillcolor(RED, rabbit->blood);
	bar(0, 0, 50 / rabbit->bloodValue, 10, rabbit->blood);

	//技能蓝条
	rabbit->skill = newimage(50, 10);
	setfillcolor(BLUE, rabbit->skill);
	bar(0, 0, 1, 10, rabbit->skill);
}

//初始化背景图像
void initBackground(imageOnDevice* image) {
	//背景缓存
	image->background = newimage();
	image->buffer = newimage(640, 480);
	if (image->level == 1)
		getimage(image->background, "assets/ROAD3.0.png");
	else if (image->level == 2)
		getimage(image->background, "assets/CANTEEN3.0.png");
	else if (image->level == 3)
		getimage(image->background, "assets/NORTHLAKE3.0.png");
}

//初始化金币模板+金币显示+路程显示+血量显示
void initCoinTemplate(imageOnDevice* image) {
	//金币胡萝卜
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


/********************************************************生成障碍**************************************************************/
//生成第一关障碍物
void roadGeneration(imageOnDevice* image, bool generateCoin) {
	image->templateNumber = 4;
	for (int i = 0; i < image->templateNumber; i++) {
		image->frameNumber[i] = 2;
	}
	//学生障碍物
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

	//随机生成主角轨道 顺带生成障碍物允许位置 以及障碍物 FREQUENCY * SPEED = 100像素/秒
	track characterTrack[TRACK_NUMBER];
	track laneAllow[TRACK_NUMBER];
	characterTrack[0].startPosition = 640;								//5s出现第一个学生障碍物->直接出现20:04 3/18
	characterTrack[0].lane = 2;
	image->countObstacle = 0;											//障碍物数量
	image->coinNumber = 0;												//轨道测试物&金币胡萝卜数量

	//随机数生成
	//轨道上移下移
	bool moveCommand[TRACK_NUMBER];
	for (int i = 0; i < TRACK_NUMBER; i++) {
		moveCommand[i] = rand() % 2;
	}

	//定位轨道->障碍物位置  //平均一条轨道占 250 - 50 = 200 像素 共占 6000~7500) (+ 540) 像素 理论1分钟完成
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
			//在轨道内部范围内生成test  (*)
			int tempPosition = characterTrack[i].startPosition;
			do {
				image->templateCoin.x = tempPosition;
				tempPosition += 180;
				image->templateCoin.lane = characterTrack[i].lane;
				image->coin[image->coinNumber++] = image->templateCoin;
			} while (image->templateCoin.x + 180 <= characterTrack[i].startPosition + characterTrack[i].length);
		}

		//障碍物允许位置
		laneAllow[i].lane = characterTrack[i].lane;
		laneAllow[i].startPosition = characterTrack[i].startPosition + characterTrack[i].length;
		if (i > 3) {
			int j = i;
			while (characterTrack[--j].lane != characterTrack[i].lane);
			//此时已经到了上一条同lane的track上了
			laneAllow[j].length = characterTrack[i].startPosition - characterTrack[j].startPosition - characterTrack[j].length;
			int temp = 0;
			int countIngroup = 0;
			int tempPosition = 40;
			do {
				temp = rand() % 4;
				for (int j = 0; j < 4; j++)
					image->copyObstacle[image->countObstacle].img[j] = image->templateObstacle[temp].img[j];
				image->copyObstacle[image->countObstacle].x = tempPosition + laneAllow[j].startPosition;
				tempPosition += 100;									//此时定位为下一个障碍物位置
				image->copyObstacle[image->countObstacle++].lane = laneAllow[j].lane - 1;
			} while (tempPosition + 50 <= laneAllow[j].length);

		}

	}
}

//生成第二关胡萝卜
void canteenGeneration(imageOnDevice* image) {
	//随机生成主角轨道 顺带生成障碍物允许位置 以及障碍物 FREQUENCY * SPEED = 100像素/秒
	track characterTrack[TRACK_NUMBER];
	characterTrack[0].startPosition = 640; 		//5s出现第一个障碍物
	characterTrack[0].lane = 2;
	image->countObstacle = 0;					//障碍物数量
	image->coinNumber = 0;						//轨道测试物&金币胡萝卜数量

	//随机数生成
	//轨道上移下移
	bool moveCommand[TRACK_NUMBER];
	for (int i = 0; i < TRACK_NUMBER; i++) {
		moveCommand[i] = rand() % 2;
	}
	int weapon = 0;
	//定位轨道->障碍物位置  //平均一条轨道占 350~400 - 50 像素 共占 9000~10500) (+ 540) 像素 
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

		//在轨道内部范围内生成test  (*)
		int tempPosition = characterTrack[i].startPosition;
		for (int k = 1; image->templateCoin.x + 50 <= characterTrack[i].startPosition + characterTrack[i].length; k++) {
			image->templateCoin.x = tempPosition;
			tempPosition += 50;								//track宽,误差在20以内
			image->templateCoin.lane = characterTrack[i].lane;
			image->templateCoin.h = 20;
			image->coin[image->coinNumber++] = image->templateCoin;
		}
	}
}

//生成第二关障碍物模板
void canteenGeneration_temp(imageOnDevice* image) {
	image->templateNumber = 3;
	image->frameNumber[0] = 8;			//菜刀
	image->frameNumber[1] = 2;			//油锅
	image->frameNumber[2] = 4;			//大妈

	//障碍物模板
	//菜刀
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

	//油锅
	image->templateObstacle[1].height = 30;
	image->templateObstacle[1].img[0] = newimage();
	getimage(image->templateObstacle[1].img[0], "assets/POT00.png");
	image->templateObstacle[1].img[1] = newimage();
	getimage(image->templateObstacle[1].img[1], "assets/POT01.png");
	image->templateObstacle[1].jumpAvaliable = 1;
	image->templateObstacle[1].rollAvaliable = 0;
	image->templateObstacle[1].width = 60;

	//大妈
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

//第二关:间隔一段时间,大妈随机扔出一把菜刀或一口油锅
void weaponGenerate(imageOnDevice* image) {
	//调控飞刀,撇锅的频率
	if (image->count % image->difficulty == 0) {
		//大妈找到合适的位置,摆好特定的姿势,开始飞刀
		if (image->templateObstacle[2].x < 100 && image->templateObstacle[2].fixY < 20 && image->templateObstacle[2].fixY > -20) {
			//手持方天画戟,纳命来
			if (image->templateObstacle[2].lane == 2) {
				//身前一把刀
				image->templateObstacle[0].lane = 2;
				image->templateObstacle[0].x = image->templateObstacle[2].x + 100;
				image->copyObstacle[image->countKnife++] = image->templateObstacle[0];
				//身旁两把刀
				image->templateObstacle[0].x = image->templateObstacle[2].x + 50;
				image->templateObstacle[0].lane = 3;
				image->copyObstacle[image->countKnife++] = image->templateObstacle[0];
				image->templateObstacle[0].lane = 1;
				image->copyObstacle[image->countKnife++] = image->templateObstacle[0];
			}
			else {
				//身前一把刀
				image->templateObstacle[0].lane = image->templateObstacle[2].lane;
				image->templateObstacle[0].x = image->templateObstacle[2].x + 100;
				image->copyObstacle[image->countKnife++] = image->templateObstacle[0];
				//身旁一把刀
				image->templateObstacle[0].x = image->templateObstacle[2].x + 50;
				image->templateObstacle[0].lane = 2;
				image->copyObstacle[image->countKnife++] = image->templateObstacle[0];
				//身后一把刀
				image->templateObstacle[0].x = image->templateObstacle[2].x;
				image->templateObstacle[0].lane = 4 - image->templateObstacle[2].lane;
				image->copyObstacle[image->countKnife++] = image->templateObstacle[0];
			}
		}
		//大妈来不及追赶兔子,慌忙之下,开始撇锅
		else if (image->templateObstacle[2].x < image->rabbit.x && (image->templateObstacle[2].fixY < -30 || image->templateObstacle[2].fixY > 30)) {
			//平底锅是带回旋功能的
			if (image->templateObstacle[2].laneNext == 2) {
				//身前一口锅
				image->templateObstacle[1].x = image->templateObstacle[2].x + 200;
				image->templateObstacle[1].lane = image->templateObstacle[2].laneNext;
				image->copyObstacle[image->countPot++] = image->templateObstacle[1];
				//身旁两口锅
				image->templateObstacle[1].x = image->templateObstacle[2].x + 150;
				image->templateObstacle[1].lane = 3;
				image->copyObstacle[image->countPot++] = image->templateObstacle[1];
				image->templateObstacle[1].lane = 1;
				image->copyObstacle[image->countPot++] = image->templateObstacle[1];
			}
			else {
				//身前一口锅
				image->templateObstacle[1].lane = image->templateObstacle[2].laneNext;
				image->templateObstacle[1].x = image->templateObstacle[2].x + 100;
				image->copyObstacle[image->countPot++] = image->templateObstacle[1];
				//身旁一口锅
				image->templateObstacle[1].x = image->templateObstacle[2].x + 50;
				image->templateObstacle[1].lane = 2;
				image->copyObstacle[image->countPot++] = image->templateObstacle[1];
			}
		}
	}
}

//生成第三关障碍物模板
void lakeGeneration_temp(imageOnDevice* image) {
	image->templateNumber = 3;
	image->frameNumber[0] = 3;			//大黑鹅
	image->frameNumber[1] = 5;			//黑鹅
	image->frameNumber[2] = 4;			//小黑鹅

	//大黑鹅
	image->templateObstacle[0].height = 70;
	image->templateObstacle[0].img[0] = newimage();
	getimage(image->templateObstacle[0].img[0], "assets/BIG BLACK00.png");
	image->templateObstacle[0].img[1] = newimage();
	getimage(image->templateObstacle[0].img[1], "assets/BIG BLACK01.png");
	image->templateObstacle[0].img[2] = newimage();
	getimage(image->templateObstacle[0].img[2], "assets/BIG BLACK02.png");
	image->templateObstacle[0].width = 60;
	image->templateObstacle[0].x = 720;
	image->templateObstacle[0].direction = 0;						//方向:0左1右
	image->templateObstacle[0].lane = 2;

	//黑鹅
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

	//小黑鹅
	image->templateObstacle[2].height = 35;
	image->templateObstacle[2].img[0] = newimage();
	getimage(image->templateObstacle[2].img[0], "assets/LITTLE SWAN01.png");//朝左
	image->templateObstacle[2].img[1] = newimage();
	getimage(image->templateObstacle[2].img[1], "assets/LITTLE SWAN11.png");
	image->templateObstacle[2].img[2] = newimage();
	getimage(image->templateObstacle[2].img[2], "assets/LITTLE SWAN00.png");//朝右
	image->templateObstacle[2].img[3] = newimage();
	getimage(image->templateObstacle[2].img[3], "assets/LITTLE SWAN10.png");
	image->templateObstacle[2].width = 35;
	image->templateObstacle[2].h = 0;
	image->templateObstacle[2].x = 640;

	//黑鹅 教程
	image->templateObstacle[3].height = 50;
	image->templateObstacle[3].img[0] = newimage();
	getimage(image->templateObstacle[3].img[0], "assets/hint00.png");
	image->templateObstacle[3].img[1] = newimage();
	getimage(image->templateObstacle[3].img[1], "assets/hint01.png");
	image->templateObstacle[3].img[2] = newimage();
	getimage(image->templateObstacle[3].img[2], "assets/hint02.png");
	image->templateObstacle[3].width = 50;
	//解决了黑鹅图像问题 -3/22 12:06 
}

/********************************************************刷新图像**************************************************************/
//刷新背景和角色
void refresh(CHARACTER rabbit, PIMAGE background, PIMAGE buffer)
{
	cleardevice();
	putimage(0, 0, background);
	putimage_transparent(NULL, rabbit.img, rabbit.x, Y(rabbit), BLACK);
	putimage(buffer, 0, 0, 640 - SPEED, 480, background, SPEED, 0);
	putimage(buffer, 640 - SPEED, 0, SPEED, 480, background, 0, 0);
	putimage(background, 0, 0, buffer);
}

//刷新教程背景和角色
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

//第一关障碍物位置变化及显示
void obstacleRefresh(imageOnDevice* image, int count, int obstacleSpeed) {
	//障碍物
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
		if (image->copyObstacle[i].x > -60)//&& studentObstacle[i].x < 640)//越过原点的障碍物会消失image->templateObstacle[2].img[3]
			putimage_transparent(NULL, image->copyObstacle[i].img[count % 12 / 3], image->copyObstacle[i].x -= obstacleSpeed, laneYBase(image->copyObstacle[i]) - 30, BLACK);
	}
}

//第一关金币位置变化及显示
void coinRefresh(imageOnDevice* image, int count, int obstacleSpeed) {
	for (int i = 0; i < image->coinNumber; i++) {
		if (image->coin[i].x >= image->rabbit.x + 40 && \
			image->coin[i].x <= image->rabbit.x + 75 && \
			image->coin[i].lane == image->rabbit.lane && \
			image->rabbit.skin != 2) {										 //在获取硬币范围内
			if (image->rabbit.coin < 50 && image->coin[i].appear == 1) {
				playMusicOnce("music/coin.mp3");
				image->rabbit.coin++;
				image->rabbit.save++;
			}
			image->coin[i].appear = 0;
		}
		//金焰之兔发动技能:吸收金币(吸收范围更广,三路并吸)
		else if (image->coin[i].x >= image->rabbit.x + 10 && \
			image->coin[i].x <= image->rabbit.x + 90 && \
			image->rabbit.skin == 2) {										 //在获取硬币范围内
			if (image->rabbit.coin < 50 && image->coin[i].appear == 1) {
				playMusicOnce("music/coin.mp3");
				image->rabbit.coin++;
				image->rabbit.save++;
			}
			image->coin[i].appear = 0;
		}
		if (image->coin[i].x > -60 && image->coin[i].appear == 1)//&& studentObstacle[i].x < 640)//越过原点的轨道测试方块会消失
			putimage_transparent(NULL, image->coin[i].img[count % 8 / 4], image->coin[i].x -= obstacleSpeed, Y(image->coin[i]), BLACK);
	}
}

//第二关金币位置变化及显示
void obstacleRefresh2(imageOnDevice* image, int count, int obstacleSpeed) {
	for (int i = 0; i < image->coinNumber; i++) {
		if (image->coin[i].x >= image->rabbit.x + 40 && \
			image->coin[i].x <= image->rabbit.x + 75 && \
			image->coin[i].lane == image->rabbit.lane && \
			image->rabbit.skin != 2) {										 //在获取硬币范围内
			if (image->coin[i].appear == 1) {			//image->rabbit.coin < 50 && 
				playMusicOnce("music/coin.mp3");
				image->rabbit.coin += 1;
				image->rabbit.save += 2;
			}
			image->coin[i].appear = 0;
		}
		//金焰之兔发动技能:吸收金币(吸收范围更广,三路并吸)
		else if (image->coin[i].x >= image->rabbit.x + 10 && \
			image->coin[i].x <= image->rabbit.x + 90 && \
			image->rabbit.skin == 2) {										 //在获取硬币范围内
			if (image->rabbit.coin < 50 && image->coin[i].appear == 1) {
				playMusicOnce("music/coin.mp3");
				image->rabbit.coin += 1;
				image->rabbit.save += 2;
			}
			image->coin[i].appear = 0;
		}
		if (image->coin[i].x > -60 && image->coin[i].appear == 1)//&& studentObstacle[i].x < 640)//越过原点的轨道测试方块会消失
			putimage_transparent(NULL, image->coin[i].img[count % 6 / 3 + 4], image->coin[i].x -= obstacleSpeed, Y(image->coin[i]), BLACK);
	}
}

//第二关:获得主角当前位置,大妈变轨
void damaChaser(imageOnDevice* image) {
	//超边界就,再来一个
	if (image->templateObstacle[2].x > 640) {
		image->templateObstacle[2].lane = image->rabbit.lane;							//全部初始化
		image->templateObstacle[2].laneNext = image->rabbit.lane;
		image->templateObstacle[2].x = -50;											//x重置,使得大妈走过去之后才会出现下一个大妈
		image->templateObstacle[2].fixY = 0;
		putimage_transparent(NULL, image->templateObstacle[2].img[image->count % 8 / 4], -50, Y(image->templateObstacle[2]), BLACK);
	}
	//不超边界,判断运行
	else {
		//轨道确定好后,由大妈和兔子的相对位置确定大妈下一条轨道
		if (image->templateObstacle[2].fixY > 120 || image->templateObstacle[2].fixY < -120) {		//目标达成之前轨道数不变,有差距才有动力
			image->templateObstacle[2].lane = image->templateObstacle[2].laneNext;					//目标达成,切换轨道
			image->templateObstacle[2].fixY = 0;														//修正值归零
		}
		if (image->rabbit.lane != image->templateObstacle[2].lane && \
			image->rabbit.x > image->templateObstacle[2].x&& \
			image->templateObstacle[2].fixY == 0)
			image->templateObstacle[2].laneNext = image->rabbit.lane;									//大妈稳定后->兔子在大妈前方不同轨道->大妈寻找新的目标

		int detalLane = image->templateObstacle[2].laneNext - image->templateObstacle[2].lane;		//不跟着兔子走,而是跟着目标走
		image->templateObstacle[2].fixY += (detalLane == 2 || detalLane == -2) ? detalLane * 6 : detalLane * 8;
		putimage_transparent(NULL, image->templateObstacle[2].img[image->count % 16 / 4], image->templateObstacle[2].x += 9/*大妈行走速度*/, Y(image->templateObstacle[2]), BLACK);	/*******投***之***影********/
	}
	if (image->templateObstacle[2].fixY > 80 || image->templateObstacle[2].fixY < -80) {				//快到下一条轨道了
		if (image->templateObstacle[2].x + 30 < image->rabbit.x && \
			image->rabbit.x < image->templateObstacle[2].x + 70 && \
			image->templateObstacle[2].laneNext == image->rabbit.lane && \
			image->rabbit.superState == NORMAL)
			image->rabbit.bloodValue = 0;															//抓个正着->gg
	}
	else if (image->templateObstacle[2].fixY < 40 && image->templateObstacle[2].fixY > -40) {			//刚走出原轨道
		if (image->templateObstacle[2].x + 10 < image->rabbit.x && \
			image->rabbit.x < image->templateObstacle[2].x + 70 && \
			image->templateObstacle[2].lane == image->rabbit.lane && \
			image->rabbit.superState == NORMAL)
			image->rabbit.bloodValue = 0;															//猛一回头,哦小子你原来在这里->gg
	}
}

//第二关:刷新武器,判定失血
void weaponChaser(imageOnDevice* image, int knifeSpeed) {
	//刷新菜刀
	for (int i = 0; i < image->countKnife; i++) {
		if (image->copyObstacle[i].x <= 640)
			putimage_transparent(NULL, image->copyObstacle[i].img[image->count % 8], image->copyObstacle[i].x += knifeSpeed/*飞刀速度 = 2V大妈 */, Y(image->copyObstacle[i]), BLACK);
		//判定失血
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
	//刷新油锅
	for (int i = 150; i < image->countPot; i++) {
		if (image->copyObstacle[i].x > 640)
			image->copyObstacle[i].direction = 0;											//inverse the direction
		if (image->copyObstacle[i].direction)
			putimage_transparent(NULL, image->copyObstacle[i].img[image->count % 4 / 2], image->copyObstacle[i].x += knifeSpeed/*锅速度 = 2V大妈 */, Y(image->copyObstacle[i]), BLACK);
		else
			putimage_transparent(NULL, image->copyObstacle[i].img[image->count % 4 / 2], image->copyObstacle[i].x -= knifeSpeed/*锅速度 = 2V大妈 */, Y(image->copyObstacle[i]), BLACK);
		//判定失血
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

//第三关:在屏幕右方出现黑鹅
void gooseEmerge(imageOnDevice* image, int count, int gooseSpeed) {
	/*appear:只扣一次血;direction:挨揍就缩头回家*/
	//到时间了,空降骑兵
	if (image->count <= count) {
		image->templateObstacle[1].x = 640;
		image->templateObstacle[1].direction = 0;						//方向:0左1右
		image->templateObstacle[1].lane = 2;
	}

	//然后,走到舞台中央
	else if (image->count > count&& image->templateObstacle[1].direction == 0) {
		if (image->templateObstacle[1].x >= 540) {
			image->rabbit.protect = PROTECT_ON;							//开启保护模式//只管开启,只是状态 
			image->gooseNumber = 8;
			putimage_transparent(NULL, image->templateObstacle[1].img[image->count % 15 / 3], \
				image->templateObstacle[1].x -= 5, laneYBase(image->templateObstacle[1]) - 30, BLACK);
		}
		else {
			putimage_transparent(NULL, image->templateObstacle[1].img[image->count % 12 / 3], \
				image->templateObstacle[1].x, laneYBase(image->templateObstacle[1]) - 30, BLACK);
			if (image->time % 5 == 0)
				littleGooseEmerge0(image, gooseSpeed);						 //小de们给我上!!!->顺时针0
			else if (image->time % 5 == 1)
				littleGooseEmerge1(image, gooseSpeed);						 //小de们给我上!!!->逆时针1
			else if (image->time % 5 == 2)
				littleGooseEmerge3(image, gooseSpeed);						 //小de们给我上!!!->顺时针2
			else if (image->time % 5 == 3)
				littleGooseEmerge2(image, gooseSpeed);						 //小de们给我上!!!->逆时针3
		}

		//兔子跳落,用头部攻击大鹅
		if (image->rabbit.state == JUMP && image->rabbit.jumpState == DOWN) {
			if (image->rabbit.lane == image->templateObstacle[1].lane && \
				image->templateObstacle[1].x - image->rabbit.x > 45 && \
				image->templateObstacle[1].x - image->rabbit.x < 65 && \
				image->templateObstacle[1].direction == 0)
			{
				playMusicOnce("music/killMedium.mp3");
				image->templateObstacle[1].direction = 1;					//标记后退
				doubleJump(&image->rabbit);
			}
		}
	}

	//兔子纵身一跃,大鹅寿终正寝
	else if (image->count > count&& image->templateObstacle[1].direction == 1) {
		putimage_transparent(NULL, image->templateObstacle[1].img[4], \
			image->templateObstacle[1].x += 5, laneYBase(image->templateObstacle[1]) - 30, BLACK);
	}
	if (image->templateObstacle[1].x > 700) {
		image->time++;
		image->templateObstacle[1].direction = 0;							//黑鹅重新开始
	}
	
	//小弟不在没了防护
	if (image->gooseNumber == 0)
		image->rabbit.protect = PROTECT_OFF;
}

//第三关:在屏幕右方出现***大大大大大***黑鹅
void bigGooseEmerge(imageOnDevice* image, int gooseSpeed) {
	/*appear:只扣一次血;direction:挨揍就缩头回家*/
	image->rabbit.protect = PROTECT_ON;									//开启保护模式
	//然后,走到舞台中央
	if (image->templateObstacle[0].direction == 0) {
		image->rabbit.protect = 1;										//开启保护模式
		if (image->templateObstacle[0].x >= 540)
			putimage_transparent(NULL, image->templateObstacle[0].img[image->count % 9 / 3], \
				image->templateObstacle[0].x -= 5, laneYBase(image->templateObstacle[0]) - 30, BLACK);
		else {
			putimage_transparent(NULL, image->templateObstacle[0].img[image->count % 9 / 3], \
				image->templateObstacle[0].x, laneYBase(image->templateObstacle[0]) - 30, BLACK);
			littleGooseEmerge4(image, gooseSpeed);
		}
		//兔子用头部攻击大鹅
		if (image->rabbit.state == JUMP && image->rabbit.jumpState == DOWN) {
			if (image->rabbit.lane == image->templateObstacle[0].lane && \
				image->templateObstacle[0].x - image->rabbit.x > 45 && \
				image->templateObstacle[0].x - image->rabbit.x < 65 && \
				image->templateObstacle[0].direction == 0)
			{
				playMusicOnce("music/killLarge.mp3");
				image->templateObstacle[0].direction = 1;					//标记后退
				doubleJump(&image->rabbit);
			}
		}
	}
	//兔子纵身一跃,大鹅寿终正寝
	else if (image->templateObstacle[0].direction == 1) {
		putimage_transparent(NULL, image->templateObstacle[0].img[image->count % 9 / 3], \
			image->templateObstacle[0].x += 5, laneYBase(image->templateObstacle[0]) - 30, BLACK);
	}
	if (image->templateObstacle[0].x > 720)
		image->time++;														//第六次出现,已不再可能,意味着小兔子的胜利
	//小弟不在没了防护
	if (image->gooseNumber == 0)
		image->rabbit.protect = PROTECT_OFF;
	//解决了大鹅无法靠近的问题 
}

//第三关:过来小黑鹅->顺时针0
void littleGooseEmerge0(imageOnDevice* image, int gooseSpeed) {
	//没初始化,就先初始化
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
		//设置循环方式->刷新方式
		for (int i = 0; i < 5; i++) {
			if (image->copyObstacle[i].x < -35 && image->copyObstacle[i].lane == 3) {
				image->copyObstacle[i].hurt = 0;									//还可以攻击兔子
				image->copyObstacle[i].lane = 1;
				image->copyObstacle[i].direction = 1;
				image->copyObstacle[i].x = -35;									//左下入,左上出
			}
			else if (image->copyObstacle[i].x > 640 && image->copyObstacle[i].lane == 1) {
				image->copyObstacle[i].hurt = 0;									//还可以攻击兔子
				image->copyObstacle[i].lane = 3;
				image->copyObstacle[i].direction = 0;
				image->copyObstacle[i].x = 640;									//右上入,右下出
			}
			if (image->copyObstacle[i].appear == 1 && image->copyObstacle[i].direction == 0)		//朝左
				putimage_transparent(NULL, image->copyObstacle[i].img[image->count % 6 / 3], \
					image->copyObstacle[i].x -= gooseSpeed, laneYBase(image->copyObstacle[i]) - 30, BLACK);
			else if (image->copyObstacle[i].appear == 1 && image->copyObstacle[i].direction == 1)	//朝右
				putimage_transparent(NULL, image->copyObstacle[i].img[image->count % 6 / 3 + 2], \
					image->copyObstacle[i].x += gooseSpeed, laneYBase(image->copyObstacle[i]) - 30, BLACK);

			switch(isCollide(&image->rabbit, image->copyObstacle[i])) {
			//判断击杀
			//兔子用头部攻击小鹅
			case COLL_KILL:
				image->copyObstacle[i].appear = 0;								//一只小鹅消失,数量仅减少1
				image->gooseNumber--;
				image->killNumber++;
				playMusicOnce("music/coin.mp3");
				image->rabbit.coin += 3;
				image->rabbit.save += 3;
				doubleJump(&image->rabbit);
				break;
			//判断失血
			//小鹅拱兔
			case COLL_HURT:
				image->copyObstacle[i].hurt = 1;									//失血flag
				image->rabbit.bloodValue--;
				break;
			}
		}
	}
}

//第三关:过来小黑鹅->逆时针1
void littleGooseEmerge1(imageOnDevice* image, int gooseSpeed) {
	//没初始化,就先初始化
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
		//设置循环方式->刷新方式
		for (int i = 0; i < 5; i++) {
			if (image->copyObstacle[i].x < -35 && image->copyObstacle[i].lane == 1) {
				image->copyObstacle[i].hurt = 0;									//还可以攻击兔子
				image->copyObstacle[i].lane = 3;
				image->copyObstacle[i].direction = 1;
				image->copyObstacle[i].x = -35;									//左下入,左上出
			}
			else if (image->copyObstacle[i].x > 640 && image->copyObstacle[i].lane == 3) {
				image->copyObstacle[i].hurt = 0;									//还可以攻击兔子
				image->copyObstacle[i].lane = 1;
				image->copyObstacle[i].direction = 0;
				image->copyObstacle[i].x = 640;									//右上入,右下出
			}
			if (image->copyObstacle[i].appear == 1 && image->copyObstacle[i].direction == 0)		//朝左
				putimage_transparent(NULL, image->copyObstacle[i].img[image->count % 6 / 3], \
					image->copyObstacle[i].x -= gooseSpeed, laneYBase(image->copyObstacle[i]) - 30, BLACK);
			else if (image->copyObstacle[i].appear == 1 && image->copyObstacle[i].direction == 1)	//朝右
				putimage_transparent(NULL, image->copyObstacle[i].img[image->count % 6 / 3 +2], \
					image->copyObstacle[i].x += gooseSpeed, laneYBase(image->copyObstacle[i]) - 30, BLACK);

			char path[50] = "music/coin.mp3";
			switch(isCollide(&image->rabbit, image->copyObstacle[i])) {
			//判断击杀
			//兔子用头部攻击小鹅
			case COLL_KILL:
				image->copyObstacle[i].appear = 0;								//一只小鹅消失,数量仅减少1
				image->gooseNumber--;
				image->killNumber++;
				playMusicOnce("music/coin.mp3");
				image->rabbit.coin += 3;
				image->rabbit.save += 3;
				doubleJump(&image->rabbit);
				break;
			//判断失血
			//小鹅拱兔
			case COLL_HURT:
				image->copyObstacle[i].hurt = 1;									//失血flag
				image->rabbit.bloodValue--;
				break;
			}
		}
	}
}

//第三关:过来小黑鹅->顺时针2
void littleGooseEmerge2(imageOnDevice* image, int gooseSpeed) {
	//没初始化,就先初始化
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
		//设置循环方式->刷新方式
		for (int i = 0; i < 8; i++) {
			if (image->copyObstacle[i].x < -35 && image->copyObstacle[i].lane == 3) {
				image->copyObstacle[i].hurt = 0;									//还可以攻击兔子
				image->copyObstacle[i].lane = 1;
				image->copyObstacle[i].direction = 1;
				image->copyObstacle[i].x = -35;									//左下入,左上出
			}
			else if (image->copyObstacle[i].x > 640 && image->copyObstacle[i].lane == 1) {
				image->copyObstacle[i].hurt = 0;									//还可以攻击兔子
				image->copyObstacle[i].lane = 3;
				image->copyObstacle[i].direction = 0;
				image->copyObstacle[i].x = 640;									//右上入,右下出
			}
			if (image->copyObstacle[i].appear == 1 && image->copyObstacle[i].direction == 0)		//朝左
				putimage_transparent(NULL, image->copyObstacle[i].img[image->count % 6 / 3], \
					image->copyObstacle[i].x -= gooseSpeed, laneYBase(image->copyObstacle[i]) - 30, BLACK);
			else if (image->copyObstacle[i].appear == 1 && image->copyObstacle[i].direction == 1)	//朝右
				putimage_transparent(NULL, image->copyObstacle[i].img[image->count % 6 / 3 + 2], \
					image->copyObstacle[i].x += gooseSpeed, laneYBase(image->copyObstacle[i]) - 30, BLACK);

			char path[50] = "music/coin.mp3";
			switch(isCollide(&image->rabbit, image->copyObstacle[i])) {
			//判断击杀
			//兔子用头部攻击小鹅
			case COLL_KILL:
				image->copyObstacle[i].appear = 0;								//一只小鹅消失,数量仅减少1
				image->gooseNumber--;
				image->killNumber++;
				playMusicOnce("music/coin.mp3");
				image->rabbit.coin += 3;
				image->rabbit.save += 3;
				doubleJump(&image->rabbit);
				break;
			//判断失血
			//小鹅拱兔
			case COLL_HURT:
				image->copyObstacle[i].hurt = 1;									//失血flag
				image->rabbit.bloodValue--;
				break;
			}
		}
	}
}

//第三关:过来小黑鹅->逆时针3
void littleGooseEmerge3(imageOnDevice* image, int gooseSpeed) {
	//没初始化,就先初始化
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
		//设置循环方式->刷新方式
		for (int i = 0; i < 8; i++) {
			if (image->copyObstacle[i].x < -35 && image->copyObstacle[i].lane == 1) {
				image->copyObstacle[i].hurt = 0;									//还可以攻击兔子
				image->copyObstacle[i].lane = 3;
				image->copyObstacle[i].direction = 1;
				image->copyObstacle[i].x = -35;									//左下入,左上出
			}
			else if (image->copyObstacle[i].x > 640 && image->copyObstacle[i].lane == 3) {
				image->copyObstacle[i].hurt = 0;									//还可以攻击兔子
				image->copyObstacle[i].lane = 1;
				image->copyObstacle[i].direction = 0;
				image->copyObstacle[i].x = 640;									//右上入,右下出
			}
			if (image->copyObstacle[i].appear == 1 && image->copyObstacle[i].direction == 0)		//朝左
				putimage_transparent(NULL, image->copyObstacle[i].img[image->count % 6 / 3], \
					image->copyObstacle[i].x -= gooseSpeed, laneYBase(image->copyObstacle[i]) - 30, BLACK);
			else if (image->copyObstacle[i].appear == 1 && image->copyObstacle[i].direction == 1)	//朝右
				putimage_transparent(NULL, image->copyObstacle[i].img[image->count % 6 / 3 + 2], \
					image->copyObstacle[i].x += gooseSpeed, laneYBase(image->copyObstacle[i]) - 30, BLACK);

			switch(isCollide(&image->rabbit, image->copyObstacle[i])) {
			//判断击杀
			//兔子用头部攻击小鹅
			case COLL_KILL:
				image->copyObstacle[i].appear = 0;								//一只小鹅消失,数量仅减少1
				image->gooseNumber--;
				image->killNumber++;
				playMusicOnce("music/coin.mp3");
				image->rabbit.coin += 3;
				image->rabbit.save += 3;
				doubleJump(&image->rabbit);
				break;
			//判断失血
			//小鹅拱兔
			case COLL_HURT:
				image->copyObstacle[i].hurt = 1;									//失血flag
				image->rabbit.bloodValue--;
				break;
			}
		}
	}
}

//第三关:过来小黑鹅->顺时针+逆时针4
void littleGooseEmerge4(imageOnDevice* image, int gooseSpeed) {
	//没初始化,就先初始化
	if (image->init[image->time] == 0) {
		image->gooseNumber = 10;
		for (int i = 0; i < 5; i++) {										    //逆时针队
			image->templateObstacle[2].lane = 1;
			image->templateObstacle[2].x = 640 + i * 120;
			image->copyObstacle[i] = image->templateObstacle[2];
			image->copyObstacle[i].direction = 0;
		}
		for (int i = 5; i < 10; i++) {									    	//顺时针队
			image->templateObstacle[2].lane = 3;
			image->templateObstacle[2].x = 640 + (i - 5) * 120;
			image->copyObstacle[i] = image->templateObstacle[2];
			image->copyObstacle[i].direction = 0;
		}
		image->init[image->time] = 1;
	}
	else {
		//设置循环方式->刷新方式
		for (int i = 0; i < 10; i++) {
			//逆时针队
			if (image->copyObstacle[i].x < -35 && image->copyObstacle[i].lane == 1 && i >= 0 && i < 5) {
				image->copyObstacle[i].hurt = 0;									//一路攻击兔子一次就行
				image->copyObstacle[i].lane = 3;
				image->copyObstacle[i].direction = 1;
				image->copyObstacle[i].x = -35;									//左上入,左下出
			}
			else if (image->copyObstacle[i].x > 640 && image->copyObstacle[i].lane == 3 && i >= 0 && i < 5) {
				image->copyObstacle[i].hurt = 0;									//一路攻击兔子一次就行
				image->copyObstacle[i].lane = 1;
				image->copyObstacle[i].direction = 0;
				image->copyObstacle[i].x = 640;									//右下入,右上出
			}
			//顺时针队
			if (image->copyObstacle[i].x < -35 && image->copyObstacle[i].lane == 3 && i >= 5 && i < 10) {
				image->copyObstacle[i].hurt = 0;									//一路攻击兔子一次就行
				image->copyObstacle[i].lane = 1;
				image->copyObstacle[i].direction = 1;
				image->copyObstacle[i].x = -35;									//左下入,左上出
			}
			else if (image->copyObstacle[i].x > 640 && image->copyObstacle[i].lane == 1 && i >= 5 && i < 10) {
				image->copyObstacle[i].hurt = 0;									//一路攻击兔子一次就行
				image->copyObstacle[i].lane = 3;
				image->copyObstacle[i].direction = 0;
				image->copyObstacle[i].x = 640;									//右上入,右下出
			}

			if (image->copyObstacle[i].appear == 1 && image->copyObstacle[i].direction == 0)		//朝左
				putimage_transparent(NULL, image->copyObstacle[i].img[image->count % 6 / 3], \
					image->copyObstacle[i].x -= gooseSpeed, laneYBase(image->copyObstacle[i]) - 30, BLACK);
			else if (image->copyObstacle[i].appear == 1 && image->copyObstacle[i].direction == 1)	//朝右
				putimage_transparent(NULL, image->copyObstacle[i].img[image->count % 6 / 3 + 2], \
					image->copyObstacle[i].x += gooseSpeed, laneYBase(image->copyObstacle[i]) - 30, BLACK);

			switch(isCollide(&image->rabbit, image->copyObstacle[i])) {
			//判断击杀
			//兔子用头部攻击小鹅
			case COLL_KILL:
				image->copyObstacle[i].appear = 0;								//一只小鹅消失,数量仅减少1
				image->gooseNumber--;
				image->killNumber++;
				playMusicOnce("music/coin.mp3");
				image->rabbit.coin += 3;
				image->rabbit.save += 3;
				doubleJump(&image->rabbit);
				break;
			//判断失血
			//小鹅拱兔
			case COLL_HURT:
				image->copyObstacle[i].hurt = 1;									//失血flag
				image->rabbit.bloodValue--;
				break;
			}
		}
	}
}

//刷新角色血和蓝
void refreshAdd(imageOnDevice* image, int count) {
	//判断超级状态

	if (image->rabbit.coin >= 50) {
		image->rabbit.coin = 0;
		image->rabbit.superState = SUPER;
		image->tempCount = count;
		image->rabbit.bloodValue++;
	}

	//回到正常状态
	if (count == image->tempCount + 100)
		image->rabbit.superState = HALF_SUPER;
	if (count == image->tempCount + 120)
		image->rabbit.superState = NORMAL;

	//显示血量条
	for (int i = 0; i < image->rabbit.bloodValue; i++) {
		putimage_transparent(NULL, image->rabbit.blood, image->rabbit.x + 50 / image->rabbit.bloodLimit * i, Y(image->rabbit) - 15, BLACK);
	}
	//显示蓝条
	for (int i = 0; i < image->rabbit.coin; i++) {
		putimage_transparent(NULL, image->rabbit.skill, image->rabbit.x + i, Y(image->rabbit) - 25, BLACK);
	}
}

//刷新字符串
void refreshString(int color, int number, int set) {
	setbkmode(TRANSPARENT);
	setfont(30, 0, "impact");
	setcolor(color);
	//其实可以用字符串处理的,我懒就没用
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

//刷新超能护盾+决定延时
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

/********************************************************清除图像**************************************************************/
//清除角色图像
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

//清除障碍图像
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
	initCharacter(&imageOnRoad.rabbit);	//初始化角色相关图像
	initBackground(&imageOnRoad);				//初始化背景图像
	initCoinTemplate(&imageOnRoad);			//初始化金币模板
	int changeLaneTime = 0;									//变轨时长
	imageOnRoad.rabbit.coin = 0;							//把兜掏空
	initializeSkin(&imageOnRoad.rabbit);
	TUTORIAL_UI tutorial;
	tutorial.img = newimage();
	roadGeneration(&imageOnRoad, false);				//障碍物生成
	refresh(imageOnRoad.rabbit, imageOnRoad.background, imageOnRoad.buffer, tutorial);

	MUSIC road; // 定义一个音乐对象
	road.OpenFile("music/road.mp3"); // 打开文件
	//播放教程
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
	//正式闯关
	int obstacleSpeed = 12;									//障碍物移动速度
	imageOnRoad.tempCount = 0;
	for (count = countTemp; count < countTemp + 400; count++)
	{
		if (road.GetPlayStatus() == MUSIC_MODE_STOP)
			road.Play();
		if (count == countTemp + 145) obstacleSpeed = 20;
		if (count == countTemp + 300) obstacleSpeed = 26;				//共行走 12*200 + 14*200 + 16*180 = 8080格像素
		action(&imageOnRoad.rabbit);						//改变兔子行动状态
		if (keyDetect(&imageOnRoad.rabbit, 1))				//判断案件+暂停
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

	//闯关成功
	MUSIC victory; // 定义一个音乐对象
	victory.OpenFile("music/victory.mp3"); // 打开文件
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
	initCharacter(&imageOnRoad.rabbit);	//初始化角色相关图像
	initBackground(&imageOnRoad);				//初始化背景图像
	initCoinTemplate(&imageOnRoad);			//初始化金币模板
	int changeLaneTime = 0;									//变轨时长
	imageOnRoad.rabbit.coin = 0;							//把兜掏空
	imageOnRoad.rabbit.skin = skin;
	initializeSkin(&imageOnRoad.rabbit);
	int lastMoney;
	imageOnRoad.rabbit.save = lastMoney = getMoney();
	//正式闯关
	int obstacleSpeed = 12;									//障碍物移动速度
	imageOnRoad.tempCount = 0;
	imageOnRoad.time = 0;
	MUSIC road; // 定义一个音乐对象
	road.OpenFile("music/road.mp3"); // 打开文件
	while (1) {
		//播放音频
		if (road.GetPlayStatus() == MUSIC_MODE_STOP)
			road.Play();
		roadGeneration(&imageOnRoad, true);
		refresh(imageOnRoad.rabbit, imageOnRoad.background, imageOnRoad.buffer);
		imageOnRoad.rabbit.frame++;
		for (imageOnRoad.count = 0; imageOnRoad.count < 550; imageOnRoad.count++)
		{
			if (imageOnRoad.count == 180 && imageOnRoad.time == 0) obstacleSpeed = 16;
			if (imageOnRoad.count == 400 && imageOnRoad.time == 0) obstacleSpeed = 16;				//共行走 12*200 + 14*200 + 16*180 = 8080格像素
			if (imageOnRoad.time != 0) obstacleSpeed = 16 + 3 * imageOnRoad.time;
			action(&imageOnRoad.rabbit);						//改变兔子行动状态
			if (keyDetect(&imageOnRoad.rabbit, 1))				//判断案件+暂停
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

			//显示金币
			putimage_transparent(NULL, imageOnRoad.coinboxs, 545, 5, BLACK);
			refreshString(EGERGB(255, 215, 0), imageOnRoad.rabbit.save, 575);
			//显示里程
			int distance = imageOnRoad.count + 550 * imageOnRoad.time;
			putimage_transparent(NULL, imageOnRoad.distance, 455, 5, BLACK);
			refreshString(GREEN, distance, 485);

			//显示生命值
			putimage_transparent(NULL, imageOnRoad.heart, 370, 5, BLACK);
			setbkmode(TRANSPARENT);
			setfont(30, 0, "impact");
			setcolor(RED);
			xyprintf(420, 5, "%d", imageOnRoad.rabbit.bloodValue);

			delayJudge(imageOnRoad, imageOnRoad.count);
			//存档
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
	initCharacter(&imageInCanteen.rabbit);	//初始化角色相关图像
	initBackground(&imageInCanteen);				//初始化背景图像
	initCoinTemplate(&imageInCanteen);				//初始化金币模板
	int changeLaneTime = 0;											//变轨时长
	imageInCanteen.rabbit.coin = 0;									//把兜掏空
	initializeSkin(&imageInCanteen.rabbit);
	TUTORIAL_UI tutorial;
	tutorial.img = newimage();
	canteenGeneration_temp(&imageInCanteen);		//生成障碍物
	refresh(imageInCanteen.rabbit, imageInCanteen.background, imageInCanteen.buffer, tutorial);
	imageInCanteen.rabbit.x = 50;
	MUSIC canteen; // 定义一个音乐对象
	canteen.OpenFile("music/canteen.mp3"); // 打开文件
	//播放教程
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

	imageInCanteen.templateObstacle[2].lane = imageInCanteen.rabbit.lane;  //全部初始化
	imageInCanteen.templateObstacle[2].x = -50;
	imageInCanteen.templateObstacle[2].fixY = 0;
	putimage_transparent(NULL, imageInCanteen.templateObstacle[2].img[imageInCanteen.count % 4 / 2], -50, Y(imageInCanteen.templateObstacle[2]), BLACK);
	//先跑到相应位置
	imageInCanteen.rabbit.state = RUN;
	for (imageInCanteen.count = 0; imageInCanteen.count < 50; imageInCanteen.count++) {
		if (canteen.GetPlayStatus() == MUSIC_MODE_STOP)
			canteen.Play();
		action(&imageInCanteen.rabbit);								//改变兔子行动状态
		if (keyDetect(&imageInCanteen.rabbit, 2))					//判断按键
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
	//正式闯关
	for (imageInCanteen.count = 0; imageInCanteen.count < 750; imageInCanteen.count++) {
		//播放音频
		if (canteen.GetPlayStatus() == MUSIC_MODE_STOP)
			canteen.Play();
		action(&imageInCanteen.rabbit);								//改变兔子行动状态
		if (keyDetect(&imageInCanteen.rabbit, 2))					//判断按键
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
		if (imageInCanteen.count < 700)								//留给最后清屏的时间
			damaChaser(&imageInCanteen);			//身后冒出一个穷追不舍但并不聪明的大妈
		weaponGenerate(&imageInCanteen);			//飞刀,撇锅
		weaponChaser(&imageInCanteen, 15);				//并刷新
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

	//闯关成功
	MUSIC victory; // 定义一个音乐对象
	victory.OpenFile("music/victory.mp3"); // 打开文件
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
	initCharacter(&imageInCanteen.rabbit);	//初始化角色相关图像
	initBackground(&imageInCanteen);				//初始化背景图像
	initCoinTemplate(&imageInCanteen);				//初始化金币模板
	int changeLaneTime = 0;											//变轨时长
	imageInCanteen.rabbit.coin = 0;									//把兜掏空
	imageInCanteen.rabbit.skin = skin;
	initializeSkin(&imageInCanteen.rabbit);
	canteenGeneration_temp(&imageInCanteen);		//生成障碍物
	refresh(imageInCanteen.rabbit, imageInCanteen.background, imageInCanteen.buffer);
	imageInCanteen.rabbit.frame++;
	imageInCanteen.rabbit.x = 50;
	int lastMoney;
	imageInCanteen.rabbit.save = lastMoney = getMoney();

	imageInCanteen.templateObstacle[2].lane = imageInCanteen.rabbit.lane;  //全部初始化
	imageInCanteen.templateObstacle[2].x = -50;
	imageInCanteen.templateObstacle[2].fixY = 0;
	putimage_transparent(NULL, imageInCanteen.templateObstacle[2].img[imageInCanteen.count % 4 / 2], -50, Y(imageInCanteen.templateObstacle[2]), BLACK);
	//先跑到相应位置
	imageInCanteen.rabbit.state = RUN;
	MUSIC canteen; // 定义一个音乐对象
	canteen.OpenFile("music/canteen.mp3"); // 打开文件
	for (imageInCanteen.count = 0; imageInCanteen.count < 50; imageInCanteen.count++) {
		if (canteen.GetPlayStatus() == MUSIC_MODE_STOP)
			canteen.Play();
		action(&imageInCanteen.rabbit);								//改变兔子行动状态
		if (keyDetect(&imageInCanteen.rabbit, 2))					//判断按键
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
	//正式闯关
	int partTime = 850;
	int knifeSpeed = 15;
	while (1) {
		canteenGeneration(&imageInCanteen);
		refresh(imageInCanteen.rabbit, imageInCanteen.background, imageInCanteen.buffer);
		imageInCanteen.rabbit.frame++;
		for (imageInCanteen.count = 0; imageInCanteen.count < partTime; imageInCanteen.count++) {
			int distance = imageInCanteen.count + partTime * imageInCanteen.time;//也就是现在的帧count Now
			if (canteen.GetPlayStatus() == MUSIC_MODE_STOP)
				canteen.Play();
			action(&imageInCanteen.rabbit);								//改变兔子行动状态
			if (keyDetect(&imageInCanteen.rabbit, 2))					//判断按键
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
			damaChaser(&imageInCanteen);				//身后冒出一个穷追不舍但并不聪明的大妈
			weaponGenerate(&imageInCanteen);			//飞刀,撇锅
			weaponChaser(&imageInCanteen, knifeSpeed);				//并刷新
			obstacleRefresh2(&imageInCanteen, imageInCanteen.count, 12);
			refreshAdd(&imageInCanteen, distance);

			//显示金币
			putimage_transparent(NULL, imageInCanteen.coinboxs, 545, 5, BLACK);
			refreshString(EGERGB(255, 215, 0), imageInCanteen.rabbit.save, 575);
			//显示里程
			putimage_transparent(NULL, imageInCanteen.distance, 455, 5, BLACK);
			refreshString(GREEN, distance, 485);

			//显示生命值
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
	initCharacter(&imageInLake.rabbit);			//初始化角色相关图像
	initBackground(&imageInLake);						//初始化背景图像
	int changeLaneTime = 0;											//变轨时长
	imageInLake.rabbit.coin = 0;									//把兜掏空
	initializeSkin(&imageInLake.rabbit);
	lakeGeneration_temp(&imageInLake);					//生成障碍物
	refresh(imageInLake.rabbit, imageInLake.background, imageInLake.buffer);



	//正式闯关
	MUSIC lake; // 定义一个音乐对象
	lake.OpenFile("music/lake.mp3"); // 打开文件
	imageInLake.count = 0;
	while (1) {
		if (lake.GetPlayStatus() == MUSIC_MODE_STOP)
			lake.Play();
		action(&imageInLake.rabbit);								//改变兔子行动状态
		if (keyDetect(&imageInLake.rabbit, 2))						//判断按键
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
		if (imageInLake.time < 4)									//0123出现黑鹅
			gooseEmerge(&imageInLake, 30, 10);				//30帧出现
		if (imageInLake.time == 4)									//4,出现大黑鹅,小黑鹅分两路跑
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

	//闯关成功
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
	initCharacter(&imageInLake.rabbit);			//初始化角色相关图像
	initBackground(&imageInLake);						//初始化背景图像
	initCoinTemplate(&imageInLake);					//初始化金币模板
	int changeLaneTime = 0;											//变轨时长
	imageInLake.rabbit.coin = 0;									//把兜掏空
	imageInLake.rabbit.skin = skin;
	initializeSkin(&imageInLake.rabbit);
	lakeGeneration_temp(&imageInLake);					//生成障碍物
	refresh(imageInLake.rabbit, imageInLake.background, imageInLake.buffer);
	int lastMoney;
	imageInLake.rabbit.save = lastMoney = getMoney();

	//正式闯关
	int gooseSpeed = 10;
	imageInLake.count = 0;
	MUSIC road; // 定义一个音乐对象
	road.OpenFile("music/road.mp3"); // 打开文件

	while (1) {
		if (road.GetPlayStatus() == MUSIC_MODE_STOP)
			road.Play(0);
		action(&imageInLake.rabbit);								//改变兔子行动状态
		if (keyDetect(&imageInLake.rabbit, 3))						//判断按键
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
		if (imageInLake.time % 5 < 4)									//0123出现黑鹅
			gooseEmerge(&imageInLake, 30, gooseSpeed);				//30帧出现
		if (imageInLake.time % 5 == 4)									//4,出现大黑鹅,小黑鹅分两路跑
			bigGooseEmerge(&imageInLake, gooseSpeed);
		
		//review 8:19 3/21
//显示金币
		putimage_transparent(NULL, imageInLake.coinboxs, 545, 5, BLACK);
		refreshString(EGERGB(255, 215, 0), imageInLake.rabbit.save, 575);

		//显示杀敌数
		putimage_transparent(NULL, imageInLake.kill, 455, 5, BLACK);
		refreshString(BLACK, imageInLake.killNumber, 490);

		//显示生命值
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
