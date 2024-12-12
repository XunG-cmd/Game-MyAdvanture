#include "bitAdventure.h"
#include "character.h"
#include "collision.h"
#include <stdio.h>
#include <stdlib.h>
void refresh(CHARACTER rabbit, PIMAGE background, PIMAGE buffer);
//异常中断不要愁, 二分法, 找源头.
//随机数, 先定好
//逻辑思路要清楚
//所用必须初始化
//记得数组别越界
//记得不要死循环

int main(){
	initgraph(640, 480);
	//初始化暂停状态
	bool showdialog = false;

	//主角兔子
	int jumpTime = 0;
	int changeLaneTime = 0;
	CHARACTER rabbit;
	rabbit.img = newimage();
	getimage(rabbit.img, "../../bit-adventure/assets/rabbit1.1.png");
	rabbit.state = RUN;
	rabbit.frame = 1;

	//背景缓存
	PIMAGE background = newimage();
	PIMAGE buffer = newimage(640, 480);
	getimage(background, "../../bit-adventure/assets/CANTEEN3.0.png");

	//轨道测试物&金币胡萝卜
	setfillcolor(YELLOW);
	fillellipsef(20, 20, 40, 40);

	OBSTACLE testTrack;
	testTrack.height = 50;
	testTrack.img[0] = newimage();
	getimage(testTrack.img[0], 0, 0, 40, 40);
	testTrack.jumpAvaliable = 1;
	testTrack.rollAvaliable = 1;
	testTrack.width = 50;

	OBSTACLE knife;
	knife.height = 80;
	knife.img[0] = newimage();
	getimage(knife.img[0], "../bit-adventure/assets/KNIFE00.png");
	knife.img[1] = newimage();
	getimage(knife.img[1], "../bit-adventure/assets/KNIFE02.png");
	knife.img[2] = newimage();
	getimage(knife.img[2], "../bit-adventure/assets/KNIFE03.png");
	knife.img[3] = newimage();
	getimage(knife.img[3], "../bit-adventure/assets/KNIFE04.png");
	knife.img[4] = newimage();
	getimage(knife.img[4], "../bit-adventure/assets/KNIFE05.png");
	knife.img[5] = newimage();
	getimage(knife.img[5], "../bit-adventure/assets/KNIFE06.png");
	knife.img[6] = newimage();
	getimage(knife.img[6], "../bit-adventure/assets/KNIFE07.png");
	knife.img[7] = newimage();
	getimage(knife.img[7], "../bit-adventure/assets/KNIFE08.png");
	knife.jumpAvaliable = 0;
	knife.rollAvaliable = 1;
	knife.width = 50;
	knife.x = 1200;
	//油锅
	OBSTACLE pot;
	pot.height = 30;
	pot.img[0] = newimage();
	getimage(pot.img[0], "../bit-adventure/assets/POT00.png");
	pot.img[1] = newimage();
	getimage(pot.img[1], "../bit-adventure/assets/POT01.png");
	pot.jumpAvaliable = 1;
	pot.rollAvaliable = 0;
	pot.width = 60;


	//大妈
	OBSTACLE dama;
	dama.height = 120;
	dama.img[0] = newimage();
	getimage(dama.img[0], "../bit-adventure/assets/AUNTnew00.png");
	dama.img[1] = newimage();
	getimage(dama.img[1], "../bit-adventure/assets/AUNTnew01.png");
	dama.jumpAvaliable = 0;
	dama.rollAvaliable = 0;
	dama.width = 50;
	dama.x = 1200;

	//随机生成主角轨道 顺带生成障碍物允许位置 以及障碍物 FREQUENCY * SPEED = 100像素/秒
	track characterTrack[TRACK_NUMBER];
	track laneAllow[TRACK_NUMBER];
	characterTrack[0].startPosition = 640 + FREQUENCY * SPEED * 5;		//5s出现第一个学生障碍物
	characterTrack[0].lane = 2;
	int countObstacle = 0;						//障碍物数量
	int testCountTrack = 0;						//轨道测试物&金币胡萝卜数量
	int countWeapon = 0;						//锅刀数量
	//雕版印刷术中的复印品
	OBSTACLE studentObstacle[200];				//200个未知身份学生障碍物,待赋象
	OBSTACLE trackTest[TRACK_NUMBER * 6];		//每条轨道最多六个物块



	//随机数生成
	//轨道上移下移
	bool moveCommand[TRACK_NUMBER];
	for (int i = 0; i < TRACK_NUMBER; i++) {
		moveCommand[i] = rand() % 2;
	}

	//同学的样子1234
	int randomImage[TRACK_NUMBER * 20];
	for (int i = 0; i < TRACK_NUMBER * 10; i++) {
		randomImage[i] = rand() % 8;
	}

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
		/*
		do {
			testTrack.x = tempPosition;
			tempPosition += 100;								//track宽,误差在20以内
			testTrack.lane = characterTrack[i].lane;
			trackTest[testCountTrack++] = testTrack;
		} while (testTrack.x + 50 <= characterTrack[i].startPosition + characterTrack[i].length);
		*/
		
		//end
		for (int k = 1; testTrack.x + 50 <= characterTrack[i].startPosition + characterTrack[i].length; k++) {
			testTrack.x = tempPosition;
			tempPosition += 100;								//track宽,误差在20以内
			testTrack.lane = characterTrack[i].lane;
			trackTest[testCountTrack++] = testTrack;
			if (k / 2 == 1) {
				if (randomImage[i] == 1) {
					pot.x = testTrack.x + 40;
					pot.lane = testTrack.lane;
					studentObstacle[countWeapon++] = pot;
				}
				else {
					knife.x = testTrack.x + 40;
					knife.lane = testTrack.lane;
					studentObstacle[countWeapon++] = knife;
				}
			}

		}
		

		//障碍物允许位置
		laneAllow[i].lane = characterTrack[i].lane;			// 1 + rand() % 3;//
		laneAllow[i].startPosition = characterTrack[i].startPosition + characterTrack[i].length;
		if (i > 3) {
			int j = i;
			while (characterTrack[--j].lane != characterTrack[i].lane);
			//此时已经到了上一条同lane的track上了
			laneAllow[j].length = characterTrack[i].startPosition - characterTrack[j].startPosition - characterTrack[j].length;
			int temp = 0;
			int countIngroup = 0;
			tempPosition = 60;
			/*
			do {
				dama.x = tempPosition + laneAllow[j].startPosition;
				tempPosition += 100;						//此时定位为下一个障碍物位置
				dama.lane = laneAllow[j].lane;
				studentObstacle[countObstacle++] = dama;
			} while (tempPosition + 70 <= laneAllow[j].length);
		
			*/
			for (int k = 1; tempPosition + 70 <= laneAllow[j].length; k++) {
				dama.x = tempPosition + laneAllow[j].startPosition;
				tempPosition += 100;						//此时定位为下一个障碍物位置
				dama.lane = laneAllow[j].lane;
				studentObstacle[countObstacle++] = dama;
			}
		}

	}

	int count = 0;								//循环数
	int obstacleSpeed = 12;						//障碍物移动速度
	for (count = 0; count < 750; count++) {// ege::delay_fps(20)
		if (count == 200) obstacleSpeed = 14;
		if (count == 400) obstacleSpeed = 16;	
		if (count == 600) obstacleSpeed = 18;	//共行走 12*200 + 14*200 + 16*200 + 18*150 = 11100格像素
		//改变兔子行动状态
		action(&rabbit);
		keyDetect(&rabbit, 2);
		//判断兔子生存状态

		//return COLL_DEAD;
		refresh(rabbit, background, buffer);
		int tempPosition = rabbit.x;
		for (int i = 0; i < countObstacle; i++) {
			//奔跑状态遇见锅刀大妈都挂掉
			
			if (rabbit.state == RUN) {
				xyprintf(rabbit.x, Y(rabbit) - 45, "RUN");
				if (rabbit.lane == studentObstacle[i].lane && studentObstacle[i].x + 10 < tempPosition + rabbit.width && tempPosition + rabbit.width < studentObstacle[i].x + studentObstacle[i].width - 10)
					xyprintf(rabbit.x, Y(rabbit) - 30, "DEAD");
				else {
					xyprintf(rabbit.x, Y(rabbit) - 15, "ALIVE");
				}
			}
			//跳跃状态遇见刀和大妈就挂掉->只判断jumpAvaliable == 0 的障碍物
			if (rabbit.state == JUMP) {
				xyprintf(rabbit.x, Y(rabbit) - 45, "JUMP");
				if (studentObstacle[i].jumpAvaliable == 0 && rabbit.lane == studentObstacle[i].lane && studentObstacle[i].x + 10 < tempPosition + rabbit.width && tempPosition + rabbit.width < studentObstacle[i].x + studentObstacle[i].width - 10)
					xyprintf(rabbit.x, Y(rabbit) - 30, "DEAD");
				else {
					xyprintf(rabbit.x, Y(rabbit) - 15, "ALIVE");
				}
			}
			//滚动状态遇见锅和大妈就挂掉->只判断rollAvaliable == 0 的障碍物
			if (rabbit.state == ROLL) {
				xyprintf(rabbit.x, Y(rabbit) - 45, "ROLL");
				if (studentObstacle[i].rollAvaliable == 0 && rabbit.lane == studentObstacle[i].lane && studentObstacle[i].x + 10 < tempPosition + rabbit.width && tempPosition + rabbit.width < studentObstacle[i].x + studentObstacle[i].width - 10)
					xyprintf(rabbit.x, Y(rabbit) - 30, "DEAD");
				else {
					xyprintf(rabbit.x, Y(rabbit) - 15, "ALIVE");
				}
			}
		/*	*/
			
			//return COLL_DEAD;
			if (studentObstacle[i].x > -60)//&& studentObstacle[i].x < 640)//越过原点的障碍物会消失
				putimage_transparent(NULL, studentObstacle[i].img[count % 4 / 2], studentObstacle[i].x -= obstacleSpeed, laneYBase(studentObstacle[i]) - 30, BLACK);
		}

		for (int i = 0; i < testCountTrack; i++) {
			if (trackTest[i].x >= rabbit.x + 40 && trackTest[i].x <= rabbit.x + 80 && trackTest[i].lane == rabbit.lane) {
				trackTest[i].appear = 0;
			}
			if (trackTest[i].x > -60 && trackTest[i].appear == 1)//&& studentObstacle[i].x < 640)//越过原点的轨道测试方块会消失
				putimage_transparent(NULL, trackTest[i].img[0], trackTest[i].x -= obstacleSpeed, laneYBase(trackTest[i]) - 30, BLACK);

		}
		delay_ms(50);
	}

	return COLL_NONE;
}


//由新坐标重画

void refresh(CHARACTER rabbit, PIMAGE background, PIMAGE buffer)
{
	cleardevice();
	putimage(0, 0, background);
	putimage_transparent(NULL, rabbit.img, rabbit.x, Y(rabbit), BLACK);
	putimage(buffer, 0, 0, 640 - SPEED, 480, background, SPEED, 0);
	putimage(buffer, 640 - SPEED, 0, SPEED, 480, background, 0, 0);
	putimage(background, 0, 0, buffer);
}

//********************************created by 黄泽源*******************************************************************************

