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
	getimage(background, "../../bit-adventure/assets/ROAD3.0.png");

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

	//学生障碍物
	OBSTACLE student[4];
	student[0].height = 120;
	student[0].img[0] = newimage();
	getimage(student[0].img[0], "../bit-adventure/assets/student00.png");
	student[0].img[1] = newimage();
	getimage(student[0].img[1], "../bit-adventure/assets/student01.png");
	student[0].jumpAvaliable = 0;
	student[0].rollAvaliable = 0;
	student[0].width = 50;


	student[1].height = 120;
	student[1].img[0] = newimage();
	getimage(student[1].img[0], "../bit-adventure/assets/student10.png");
	student[1].img[1] = newimage();
	getimage(student[1].img[1], "../bit-adventure/assets/student11.png");
	student[1].jumpAvaliable = 0;
	student[1].rollAvaliable = 0;
	student[1].width = 40;


	student[2].height = 120;
	student[2].img[0] = newimage();
	getimage(student[2].img[0], "../bit-adventure/assets/student20.png");
	student[2].img[1] = newimage();
	getimage(student[2].img[1], "../bit-adventure/assets/student21.png");
	student[2].jumpAvaliable = 0;
	student[2].rollAvaliable = 0;
	student[2].width = 60;


	student[3].height = 120;
	student[3].img[0] = newimage();
	getimage(student[3].img[0], "../bit-adventure/assets/student30.png");
	student[3].img[1] = newimage();
	getimage(student[3].img[1], "../bit-adventure/assets/student31.png");
	student[3].jumpAvaliable = 0;
	student[3].rollAvaliable = 0;
	student[3].width = 100;

	//随机生成主角轨道 顺带生成障碍物允许位置 以及障碍物 FREQUENCY * SPEED = 100像素/秒
	track characterTrack[TRACK_NUMBER];
	track laneAllow[TRACK_NUMBER];
	characterTrack[0].startPosition = 640 + FREQUENCY * SPEED * 5;		//5s出现第一个学生障碍物
	characterTrack[0].lane = 2;
	int countObstacle = 0;						//障碍物数量
	int testCountTrack = 0;						//轨道测试物&金币胡萝卜数量
	//雕版印刷术中的复印品
	OBSTACLE studentObstacle[200];				//200个未知身份学生障碍物,待赋象
	OBSTACLE trackTest[TRACK_NUMBER * 6];		//每条轨道最多六个物块

	
	
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

		//在轨道内部范围内生成test  (*)
		int tempPosition = characterTrack[i].startPosition;
		do {
			testTrack.x = tempPosition;
			tempPosition += 60;								//track宽,误差在20以内
			testTrack.lane = characterTrack[i].lane;
			trackTest[testCountTrack++] = testTrack;
		} while (testTrack.x + 50 <= characterTrack[i].startPosition + characterTrack[i].length);
		//end
		
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
			tempPosition = 40;
			do {
				temp = rand() % 4;
				studentObstacle[countObstacle].img[0] = student[temp].img[0];
				studentObstacle[countObstacle].img[1] = student[temp].img[1];
				studentObstacle[countObstacle].x = tempPosition + laneAllow[j].startPosition;
				tempPosition += 100;						//此时定位为下一个障碍物位置
				studentObstacle[countObstacle++].lane = laneAllow[j].lane - 1;
			} while (tempPosition + 50 <= laneAllow[j].length);

		}
		
	}
	

	
	


	int count = 0;								//循环数
	int obstacleSpeed = 12;						//障碍物移动速度
	for (count = 0; count < 580; count++) {// ege::delay_fps(20)
		if (count == 200) obstacleSpeed = 14;
		if (count == 400) obstacleSpeed = 16;	//共行走 12*200 + 14*200 + 16*180 = 8080格像素
		//改变兔子行动状态
		action(&rabbit);
		keyDetect(&rabbit, 1);
		//判断兔子生存状态
		
			//return COLL_DEAD;
		refresh(rabbit, background, buffer);
		int tempPosition = rabbit.x;
		for (int i = 0; i < countObstacle; i++){
			if (rabbit.lane == studentObstacle[i].lane + 1 && studentObstacle[i].x + 10 < tempPosition + rabbit.width && tempPosition + rabbit.width < studentObstacle[i].x + studentObstacle[i].width - 10)
				return COLL_DEAD;
			if (studentObstacle[i].x > -60 )//&& studentObstacle[i].x < 640)//越过原点的障碍物会消失
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

