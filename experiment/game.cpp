#include <ege.h>
#include <graphics.h>
#include <bitAdventure.h>
#include <stdlib.h>
#include <stdio.h>

void refresh(CHARACTER rabbit, PIMAGE background, PIMAGE buffer);

void startGame() {

}
void dialogueInDormitory() {

}

int gameInRoad(){
	initgraph(640, 480);
	//初始化暂停状态
	bool showdialog = false;

	//元素和背景图换到这里定义，因为要调用newimage()初始化

	int jumpTime = 0;
	int changeLaneTime = 0;
	CHARACTER rabbit;
	rabbit.img = newimage();
	rabbit.state = RUN;
	rabbit.frame = 1;
	PIMAGE background = newimage();
	PIMAGE buffer = newimage(640, 480);
	getimage(background, "../../bit-adventure/assets/ROAD3.0.png");
	getimage(rabbit.img, "../../bit-adventure/assets/rabbit1.1.png");
	rabbit.height = 50;
	refresh(rabbit, background, buffer);
	//试验代码
	setfillcolor(YELLOW);
	fillellipsef(20, 20, 40, 40);

	OBSTACLE testTrack;
	testTrack.height = 50;
	testTrack.img[0] = newimage();
	getimage(testTrack.img[0], 0, 0, 40, 40);
	testTrack.jumpAvaliable = 0;
	testTrack.rollAvaliable = 0;
	testTrack.width = 50;
	testTrack.x = 1200;

	//画一个绿方块,作为障碍物允许位置
	setfillcolor(BROWN);
	fillellipsef(20, 20, 40, 40);

	OBSTACLE testObstacle;
	testObstacle.height = 50;
	testObstacle.img[0] = newimage();
	getimage(testObstacle.img[0], 0, 0, 40, 40);
	testObstacle.jumpAvaliable = 0;
	testObstacle.rollAvaliable = 0;
	testObstacle.width = 50;
	testObstacle.x = 1200;


	//testObstacle应为test2


	//结束
	/*
	rabbit.img = newimage();
	PIMAGE dialog = newimage();
	getimage(background, "../bit-adventure/assets/ROAD3.0.png");
	getimage(rabbit.img, "../bit-adventure/assets/rabbit1.1.png");
	getimage(dialog, "../assets/m/dialog.png");
	refresh(rabbit, background, buffer);
	*/
	

	//********************************created by 黄泽源*******************************************************************************

		//初始化障碍物

	OBSTACLE student[4];
	student[0].height = 120;
	student[0].img[0] = newimage();
	getimage(student[0].img[0], "../bit-adventure/assets/student00.png");
	student[0].img[1] = newimage();
	getimage(student[0].img[1], "../bit-adventure/assets/student01.png");
	student[0].jumpAvaliable = 0;
	student[0].rollAvaliable = 0;
	student[0].width = 50;
	student[0].x = 1200;


	student[1].height = 120;
	student[1].img[0] = newimage();
	getimage(student[1].img[0], "../bit-adventure/assets/student10.png");
	student[1].img[1] = newimage();
	getimage(student[1].img[1], "../bit-adventure/assets/student11.png");
	student[1].jumpAvaliable = 0;
	student[1].rollAvaliable = 0;
	student[1].width = 40;
	student[1].x = 1200;


	student[2].height = 120;
	student[2].img[0] = newimage();
	getimage(student[2].img[0], "../bit-adventure/assets/student20.png");
	student[2].img[1] = newimage();
	getimage(student[2].img[1], "../bit-adventure/assets/student21.png");
	student[2].jumpAvaliable = 0;
	student[2].rollAvaliable = 0;
	student[2].width = 60;
	student[2].x = 1200;


	student[3].height = 120;
	student[3].img[0] = newimage();
	getimage(student[3].img[0], "../bit-adventure/assets/student30.png");
	student[3].img[1] = newimage();
	getimage(student[3].img[1], "../bit-adventure/assets/student31.png");
	student[3].jumpAvaliable = 0;
	student[3].rollAvaliable = 0;
	student[3].width = 100;
	student[3].x = 1200;


	//随机生成主角轨道 顺带生成障碍物允许位置 以及障碍物
	track characterTrack[TRACK_NUMBER];
	track laneAllow[OBCTACLE_NUMBER];
	characterTrack[0].startTime = 0;
	int count = 0;
	int countObstacle = 0;
	OBSTACLE studentObstacle[200];//200个未知身份学生障碍物,待赋象
	OBSTACLE trackTest[1000];//for test (*)
	OBSTACLE obstacleTest[1000];//for test (*)
	int testCountTrack = 0;
	int testCountObstacle = 0;

	bool moveCommand[TRACK_NUMBER];
	for (int i = 0; i < TRACK_NUMBER; i++) {
		moveCommand[i] = rand() % 2;
	}
	int randomLane[TRACK_NUMBER * 20];
	for (int i = 0; i < TRACK_NUMBER * 10;i++) {
		randomLane[i] = rand() % 4;
	}
	characterTrack[0].lane = 2;
	//60个循环走起
	for (int i = 0; i < TRACK_NUMBER; i++) {
		//时间段随机生成
		characterTrack[i].laneStayTime = 45 + rand() % 25;
		if (i != 0) {
			characterTrack[i].startTime = characterTrack[i - 1].startTime + characterTrack[i - 1].laneStayTime - (10 + rand() % 10);
			//10~15为兔子活动的宽度,200像素

			//轨道随机生成
			//reasonable

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
		int tempPosition = 300 + characterTrack[i].startTime * SPEED;
		do {
			testTrack.x = tempPosition;
			tempPosition += 50;//track宽,误差在20以内
			testTrack.lane = characterTrack[i].lane;
			trackTest[testCountTrack++] = testTrack;
		} while (testTrack.x + 50 <= 300 + (characterTrack[i].startTime + characterTrack[i].laneStayTime) * SPEED);
		//end
		//障碍物允许位置
		
		laneAllow[i].lane = characterTrack[i].lane;// 1 + rand() % 3;//
		laneAllow[i].startTime = characterTrack[i].startTime + characterTrack[i].laneStayTime;
		if (i > 3) {
			int j = i;
			while (characterTrack[--j].lane != characterTrack[i].lane);
			laneAllow[j].laneStayTime = characterTrack[i].startTime - characterTrack[j].startTime - characterTrack[j].laneStayTime;
			//在允许范围内生成障碍物
				//test
				/*
		
			tempPosition = 350 + laneAllow[j].startTime * SPEED;
			do {
				testObstacle.x = tempPosition;//testObstacle应为test2,表示这一种测试方块
				tempPosition += 100;
				testObstacle.lane = laneAllow[j].lane;
				obstacleTest[testCountObstacle++] = testObstacle;
			} while (testObstacle.x + 150 <= 350 + (laneAllow[j].startTime + laneAllow[j].laneStayTime) * SPEED);
		
			*/
			int temp = 0;
			//障碍物不是很整齐,更自然,待调试
			int countIngroup = 0;
			tempPosition = 350 + laneAllow[j].startTime * SPEED;
			do {
				temp = 3;// randomLane[10 * i + countIngroup++];
				student[temp].x = tempPosition;
				tempPosition += 100;
				student[temp].lane = laneAllow[j].lane;
				studentObstacle[countObstacle++] = student[temp];
			} while (student[temp].x + 150 <=  350 + (laneAllow[j].startTime + laneAllow[j].laneStayTime) * SPEED);
		/*	*/
			
		}
	/*	*/

	}

	//********************************created by 段宇皓*******************************************************************************


	//人群涌来,兔子奋力地避让  进入主循环 周期50ms
	int obstacleSpeed = 12;

	for (count = 0; count < 600; count++) {//,ege::delay_fps(20)
		if (count == 200) obstacleSpeed = 14;
		if (count == 400) obstacleSpeed = 16;
		//上下左右移动的控制

		if (rabbit.state == JUMP)
		{
			if (jumpTime < HEIGHT_LEVEL)
			{
				jumpTime++;
				rabbit.h += (HEIGHT_LEVEL - jumpTime);
				getimage(rabbit.img, "../bit-adventure/assets/rabbit4.1.png");
			}
			else if (jumpTime >= HEIGHT_LEVEL && jumpTime < 2 * HEIGHT_LEVEL)
			{
				rabbit.h -= (jumpTime - HEIGHT_LEVEL);
				jumpTime++;
				getimage(rabbit.img, "../bit-adventure/assets/rabbit7.1.png");
			}
			else
			{
				jumpTime = 0;
				rabbit.h = 0;
				rabbit.state = RUN;
			}
			if (jumpTime > 0.8 * HEIGHT_LEVEL && jumpTime < 1.2 * HEIGHT_LEVEL)
				getimage(rabbit.img, "../bit-adventure/assets/rabbit1.1.png");
		}
		if (rabbit.state == UP)
		{
			getimage(rabbit.img, "../bit-adventure/assets/rabbit1.1.png");
			rabbit.fixY -= 30;
			if (rabbit.fixY == -120)
			{
				changeLaneTime = 0;
				rabbit.fixY = 0;
				rabbit.state = RUN;
				rabbit.lane--;
			}
		}
		if (rabbit.state == DOWN)
		{
			getimage(rabbit.img, "../bit-adventure/assets/rabbit1.1.png");
			rabbit.fixY += 30;
			if (rabbit.fixY == 120)
			{
				changeLaneTime = 0;
				rabbit.fixY = 0;
				rabbit.state = RUN;
				rabbit.lane++;
			}
		}
		if (rabbit.state == RUN)
			if (rabbit.frame <= 6)
				getimage(rabbit.img, "../bit-adventure/assets/rabbit1.1.png");
			else if (rabbit.frame <= 12)
				getimage(rabbit.img, "../bit-adventure/assets/rabbit3.1.png");
			else
				rabbit.frame = 1;
		if (rabbit.state == ROLL)
		{
			if (rabbit.frame <= 3)
				getimage(rabbit.img, "../bit-adventure/assets/rabbit6.1new.png");
			else if (rabbit.frame <= 6)
				getimage(rabbit.img, "../bit-adventure/assets/rabbit6.1.3.png");
			else if (rabbit.frame <= 9)
				getimage(rabbit.img, "../bit-adventure/assets/rabbit6.1.2.png");
			else if (rabbit.frame <= 12)
				getimage(rabbit.img, "../bit-adventure/assets/rabbit6.1.1.png");
			else
				rabbit.frame = 1;

			if (rabbit.h - rabbit.fixY >= 20 && rabbit.h != 0)
				rabbit.fixY += 20;
			else
			{
				jumpTime = 0;
				rabbit.h = 0;
				rabbit.fixY = 0;
			}
		}

		while (kbhit())
		{
			int k = getch();
			switch (k)
			{
			case KEY_UP:
				if (rabbit.lane != 1 && rabbit.state == RUN)
					rabbit.state = UP;
				break;
			case KEY_DOWN:
				if (rabbit.lane != 3 && rabbit.state == RUN)
					rabbit.state = DOWN;
				break;
			case KEY_SPACE:
				if (rabbit.state != UP && rabbit.state != DOWN)
					rabbit.state = JUMP;
				break;
			}
		}
		if (keystate(VK_LEFT) && rabbit.state != ROLL && rabbit.x >= SPEED)
			rabbit.x -= SPEED;
		if (keystate(VK_RIGHT) && rabbit.state != ROLL && rabbit.x <= 580 - SPEED)
			rabbit.x += SPEED;
		if (keystate(VK_CONTROL) && rabbit.state != UP && rabbit.state != DOWN)
		{
			if (rabbit.state == RUN)
				getimage(rabbit.img, "../bit-adventure/assets/rabbit5.1new.png");
			rabbit.state = ROLL;
		}
		else if (rabbit.state == ROLL)
		{
			rabbit.state = RUN;
			getimage(rabbit.img, "../bit-adventure/assets/rabbit5.1new.png");
		}
		if (keystate(VK_ESCAPE))
		{
			delimage(rabbit.img);
			delimage(background);
			closegraph();
		}

		//********************************created by裴思琦*******************************************************************************

		refresh(rabbit, background, buffer);
		rabbit.frame++;
		
		//对所有的障碍物重新定位

			for (int i = 0; i <= countObstacle; i++) {
			if (studentObstacle[i].x > -60)//&& studentObstacle[i].x < 640)//越过原点的障碍物会消失
				putimage_transparent(NULL, studentObstacle[i].img[count % 4 / 2], studentObstacle[i].x -= obstacleSpeed, laneYBase(studentObstacle[i]) - 30, BLACK);
			//
		}
/**/
		for (int i = 0; i <= testCountTrack; i++) {
			if (trackTest[i].x >= rabbit.x + 40 && trackTest[i].x <= rabbit.x + 80 && trackTest[i].lane == rabbit.lane) {
				trackTest[i].appear = 0;
			}
			if (trackTest[i].x > -60 && trackTest[i].appear == 1)//&& studentObstacle[i].x < 640)//越过原点的轨道测试方块会消失
				putimage_transparent(NULL, trackTest[i].img[0], trackTest[i].x -= obstacleSpeed, laneYBase(trackTest[i]) - 30, BLACK);

		}



		delay_ms(50);
	}
	closegraph();
	return 0;
}

void spotInWay1() {

}

//********************************created by 段宇皓*******************************************************************************
//void spotInWay2() {}



int gameInCanteen()
{
	//元素和背景图换到这里定义，因为要调用newimage()初始化
	initgraph(640, 480);
	int jumpTime = 0;
	int changeLaneTime = 0;
	CHARACTER rabbit;
	rabbit.img = newimage();
	rabbit.state = RUN;
	rabbit.frame = 1;
	PIMAGE background = newimage();
	PIMAGE buffer = newimage(640, 480);
	getimage(background, "../bit-adventure/assets/CANTEEN3.0.png");//KNIFE00
	getimage(rabbit.img, "../bit-adventure/assets/rabbit1.1.png");//KNIFE00
	rabbit.height = 50;
	refresh(rabbit, background, buffer);
	//间隔金币初始化
	setfillcolor(YELLOW);
	fillellipsef(20, 20, 40, 40);

	OBSTACLE testTrack;
	testTrack.height = 50;
	testTrack.img[0] = newimage();
	getimage(testTrack.img[0], 0, 0, 10, 40);
	testTrack.jumpAvaliable = 0;
	testTrack.rollAvaliable = 0;
	testTrack.width = 50;

	/*
	//作为障碍物允许位置
	setfillcolor(BROWN);
	fillellipsef(20, 20, 40, 40);

	OBSTACLE testObstacle;
	testObstacle.height = 50;
	testObstacle.img[0] = newimage();
	getimage(testObstacle.img[0], 0, 0, 40, 40);
	testObstacle.jumpAvaliable = 0;
	testObstacle.rollAvaliable = 0;
	testObstacle.width = 50;
	testObstacle.x = 1200;
	*/
	//testObstacle应为test2


	//********************************created by 黄泽源*******************************************************************************

	//初始化障碍物

	OBSTACLE weapon[2];
	//刀
	weapon[0].height = 40;
	weapon[0].lane = 2;
	weapon[0].img[0] = newimage();
	getimage(weapon[0].img[0], "../bit-adventure/assets/KNIFE00.png");
	weapon[0].img[1] = newimage();
	getimage(weapon[0].img[1], "../bit-adventure/assets/KNIFE01.png");
	weapon[0].img[2] = newimage();
	getimage(weapon[0].img[2], "../bit-adventure/assets/KNIFE02.png");
	weapon[0].img[3] = newimage();
	getimage(weapon[0].img[3], "../bit-adventure/assets/KNIFE03.png");
	weapon[0].img[4] = newimage();
	getimage(weapon[0].img[4], "../bit-adventure/assets/KNIFE04.png");
	weapon[0].img[5] = newimage();
	getimage(weapon[0].img[5], "../bit-adventure/assets/KNIFE05.png");
	weapon[0].img[6] = newimage();
	getimage(weapon[0].img[6], "../bit-adventure/assets/KNIFE06.png");
	weapon[0].img[7] = newimage();
	getimage(weapon[0].img[7], "../bit-adventure/assets/KNIFE07.png");
	weapon[0].jumpAvaliable = 0;
	weapon[0].rollAvaliable = 1;
	weapon[0].width = 50;
	weapon[0].h = 70;

	//刀
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
	getimage(dama.img[0], "../bit-adventure/assets/student20.png");
	dama.img[1] = newimage();
	getimage(dama.img[1], "../bit-adventure/assets/student21.png");
	dama.jumpAvaliable = 0;
	dama.rollAvaliable = 0;
	dama.width = 50;
	dama.x = 1200;
	//柱子和凳子可以当作障碍物
	//凳子可跳可滚

	//随机生成主角轨道 顺带生成障碍物允许位置 以及障碍物
	track characterTrack[TRACK_NUMBER];
	track laneAllow[OBCTACLE_NUMBER];
	characterTrack[0].startTime = 0;
	int count = 0;
	int countObstacle = 0;
	OBSTACLE damaObstacle[200];//50个大妈排序,待赋象
	int weaponX[50];
	OBSTACLE weaponObstacle[50];
	OBSTACLE trackTest[200];//for test (*)
	OBSTACLE obstacleTest[200];//for test (*)
	int testCountTrack = 0;
	int testCountObstacle = 0;

	bool moveCommand[OBCTACLE_NUMBER];//虽然数量是OBCTACLE_NUMBER但是表示的是TRACK_NUMBER
	for (int i = 0; i < OBCTACLE_NUMBER; i++) {
		moveCommand[i] = rand() % 2;
	}
	//60个循环走起
	//一共7轮,分别设置长度之比为4 5 6 7 8 9 10
	int tempTimeBase = 0;
	int tempPositionBase = 0;
	int tempPosition = 600;//角色轨道(知道为什么出现不了刀了,为什么tempPosition和tempPositionBase总是对不上号了,因为画大妈的时候动tempPosition值了)
	int tempPositionJ;
	int weaponCount = 0;
	int trackCount = 0;
	int i;//每一轮中的 内循环数
	for (int ring = 4; ring <= 10; ring++) {
		tempTimeBase += 30 * ring; //设置每一轮首刀的初始位置
		tempPositionBase = tempTimeBase * SPEED;//tempPosition - 1000;
		characterTrack[0].lane = 2;
		characterTrack[0].startTime = tempTimeBase;//相对每一轮的起始

		for (i = 0; i < ring; i++) {
			//一.由角色轨道滞留时间,决定角色轨道初始时间
			characterTrack[i].laneStayTime = 45 + rand() % 25;//时间段随机生成
			if (i != 0) {
				//确定每个角色轨道初始时间
				characterTrack[i].startTime = characterTrack[i - 1].startTime + characterTrack[i - 1].laneStayTime - (10 + rand() % 10);
				//10~20为兔子活动的宽度,200像素
				//轨道123随机生成
				if (characterTrack[i - 1].lane == 3 || characterTrack[i - 1].lane == 1)
					characterTrack[i].lane = 2;
				else {
					if (moveCommand[i + 10 * ring])
						characterTrack[i].lane = characterTrack[i - 1].lane + 1;
					else
						characterTrack[i].lane = characterTrack[i - 1].lane - 1;
				}
			}

			//二.在角色轨道内部范围内生成test  (*)未来作为胡萝卜位置
			tempPosition = tempPositionBase + characterTrack[i].startTime * SPEED;
			do {
				testTrack.x = tempPosition;
				tempPosition += 50;//track宽
				testTrack.lane = characterTrack[i].lane;
				trackTest[testCountTrack++] = testTrack;
			} while (tempPosition <= tempPositionBase + (characterTrack[i].startTime + characterTrack[i].laneStayTime) * SPEED);

			//三.角色轨道外部,障碍物允许范围
			laneAllow[i].lane = characterTrack[i].lane;// 1 + rand() % 3;//  
			laneAllow[i].startTime = characterTrack[i].startTime + characterTrack[i].laneStayTime;
			if (i > 1) {
				int j = i;
				while (characterTrack[--j].lane != characterTrack[i].lane);
				laneAllow[j].laneStayTime = characterTrack[i].startTime - characterTrack[j].startTime - characterTrack[j].laneStayTime;
				//在允许范围内生成大妈 兼带武器(大妈代替)
				/*	*/			tempPosition = tempPositionBase + laneAllow[j].startTime * SPEED;//50为修正值,根绝视觉效果做出调整
				do {
					dama.x = tempPosition;
					//xyprintf(0, 0, "testObstacle.x = %d", tempPosition);
					//delay_ms(1000);
					dama.lane = laneAllow[j].lane;
					obstacleTest[testCountObstacle++] = dama;
					for (int k = 1; k <= 3 && k != laneAllow[j].lane; k++) {
						if (moveCommand[ring * 12 + i]) {
							knife.lane = k;
							knife.x = tempPosition;
							obstacleTest[testCountObstacle++] = knife;
						}
						else {
							pot.lane = k;
							pot.x = tempPosition;
							obstacleTest[testCountObstacle++] = pot;
						}
					}
					tempPosition += 100;
				} while (dama.x + 135 <= tempPositionBase + (laneAllow[j].startTime + laneAllow[j].laneStayTime) * SPEED);
				//135为经验修正值,贼珍贵贼珍贵的呢

			}

		}


		//四.后面生成刀子和油锅
		//weaponX[weaponCount++] = tempPosition + 50;// tempPositionBase + 150 * (ring + 1);//SPEED * (characterTrack[i].startTime + characterTrack[i].laneStayTime);
		//xyprintf(0, 0, "%d__%d,%d", tempPositionBase, tempPosition + 50, weaponObstacle[weaponCount-1]);
		//delay_ms(1000);
																/*		*/


	}

	//********************************created by 段宇皓*******************************************************************************


	//人群涌来,兔子奋力地避让  进入主循环 周期50ms
	int obstacleSpeed = 12;

	for (count = 0; count < 900; count++) {
		if (count == 200) obstacleSpeed = 14;
		if (count == 400) obstacleSpeed = 16;
		if (count == 600) obstacleSpeed = 18;
		if (count == 800) obstacleSpeed = 20;
		//上下左右移动的控制

		if (rabbit.state == JUMP)
		{
			if (jumpTime < HEIGHT_LEVEL)
			{
				jumpTime++;
				rabbit.h += (HEIGHT_LEVEL - jumpTime);
				getimage(rabbit.img, "../bit-adventure/assets/rabbit4.1.png");
			}
			else if (jumpTime >= HEIGHT_LEVEL && jumpTime < 2 * HEIGHT_LEVEL)
			{
				rabbit.h -= (jumpTime - HEIGHT_LEVEL);
				jumpTime++;
				getimage(rabbit.img, "../bit-adventure/assets/rabbit7.1.png");
			}
			else
			{
				jumpTime = 0;
				rabbit.h = 0;
				rabbit.state = RUN;
			}
			if (jumpTime > 0.8 * HEIGHT_LEVEL && jumpTime < 1.2 * HEIGHT_LEVEL)
				getimage(rabbit.img, "../bit-adventure/assets/rabbit1.1.png");
		}
		if (rabbit.state == UP)
		{
			getimage(rabbit.img, "../bit-adventure/assets/rabbit1.1.png");
			rabbit.fixY -= 30;
			if (rabbit.fixY == -120)
			{
				changeLaneTime = 0;
				rabbit.fixY = 0;
				rabbit.state = RUN;
				rabbit.lane--;
			}
		}
		if (rabbit.state == DOWN)
		{
			getimage(rabbit.img, "../bit-adventure/assets/rabbit1.1.png");
			rabbit.fixY += 30;
			if (rabbit.fixY == 120)
			{
				changeLaneTime = 0;
				rabbit.fixY = 0;
				rabbit.state = RUN;
				rabbit.lane++;
			}
		}
		if (rabbit.state == RUN)
			if (rabbit.frame <= 6)
				getimage(rabbit.img, "../bit-adventure/assets/rabbit1.1.png");
			else if (rabbit.frame <= 12)
				getimage(rabbit.img, "../bit-adventure/assets/rabbit3.1.png");
			else
				rabbit.frame = 1;
		if (rabbit.state == ROLL)
		{
			if (rabbit.frame <= 3)
				getimage(rabbit.img, "../bit-adventure/assets/rabbit6.1new.png");
			else if (rabbit.frame <= 6)
				getimage(rabbit.img, "../bit-adventure/assets/rabbit6.1.3.png");
			else if (rabbit.frame <= 9)
				getimage(rabbit.img, "../bit-adventure/assets/rabbit6.1.2.png");
			else if (rabbit.frame <= 12)
				getimage(rabbit.img, "../bit-adventure/assets/rabbit6.1.1.png");
			else
				rabbit.frame = 1;

			if (rabbit.h - rabbit.fixY >= 20 && rabbit.h != 0)
				rabbit.fixY += 20;
			else
			{
				jumpTime = 0;
				rabbit.h = 0;
				rabbit.fixY = 0;
			}
		}

		while (kbhit())
		{
			int k = getch();
			switch (k)
			{
			case KEY_UP:
				if (rabbit.lane != 1 && rabbit.state == RUN)
					rabbit.state = UP;
				break;
			case KEY_DOWN:
				if (rabbit.lane != 3 && rabbit.state == RUN)
					rabbit.state = DOWN;
				break;
			case KEY_SPACE:
				if (rabbit.state != UP && rabbit.state != DOWN)
					rabbit.state = JUMP;
				break;
			}
		}
		if (keystate(VK_LEFT) && rabbit.state != ROLL && rabbit.x >= SPEED)
			rabbit.x -= SPEED;
		if (keystate(VK_RIGHT) && rabbit.state != ROLL && rabbit.x <= 580 - SPEED)
			rabbit.x += SPEED;
		if (keystate(VK_CONTROL) && rabbit.state != UP && rabbit.state != DOWN)
		{
			if (rabbit.state == RUN)
				getimage(rabbit.img, "../bit-adventure/assets/rabbit5.1new.png");
			rabbit.state = ROLL;
		}
		else if (rabbit.state == ROLL)
		{
			rabbit.state = RUN;
			getimage(rabbit.img, "../bit-adventure/assets/rabbit5.1new.png");
		}
		if (keystate(VK_ESCAPE))
		{
			delimage(rabbit.img);
			delimage(background);
			closegraph();
		}

		//********************************created by裴思琦*******************************************************************************

		refresh(rabbit, background, buffer);
		rabbit.frame++;

		//对所有的大妈重新定位
		for (int i = 0; i <= testCountObstacle; i++) {
			if (obstacleTest[i].x > -60)//&& studentObstacle[i].x < 640)//越过原点的障碍物会消失
				if (obstacleTest[i].rollAvaliable == 1)
					putimage_transparent(NULL, obstacleTest[i].img[count % 8], obstacleTest[i].x -= obstacleSpeed, laneYBase(obstacleTest[i]) - 30, BLACK);
				else if (obstacleTest[i].jumpAvaliable == 1)
					putimage_transparent(NULL, obstacleTest[i].img[count % 4 / 2], obstacleTest[i].x -= obstacleSpeed, laneYBase(obstacleTest[i]) - 30, BLACK);
				else
					putimage_transparent(NULL, obstacleTest[i].img[count % 4 / 2], obstacleTest[i].x -= obstacleSpeed, laneYBase(obstacleTest[i]) - 30, BLACK);
		}

		//对所有的角色轨道测试物重新定位
			for (int i = 0; i <= testCountTrack; i++) {
				if (trackTest[i].x >= rabbit.x + 40 && trackTest[i].x <= rabbit.x + 80 && trackTest[i].lane == rabbit.lane) {
					trackTest[i].appear = 0;
				}
				if (trackTest[i].x > -60 && trackTest[i].appear == 1)//&& studentObstacle[i].x < 640)//越过原点的轨道测试方块会消失
					putimage_transparent(NULL, trackTest[i].img[0], trackTest[i].x -= obstacleSpeed, laneYBase(trackTest[i]) - 30, BLACK);
			}
	/*
				//对所有的炊具重新定位
					for (int i = 0; i <= 10; i++) {
				if (weaponObstacle[i].x > -60)//&& studentObstacle[i].x < 640)//越过原点的障碍物会消失
					putimage_transparent(NULL, weapon[0].img[count % 8], weaponObstacle[i].x -= obstacleSpeed, laneYBase(weaponObstacle[i]) - 30, BLACK);
			}

			for (int i = 0; i < 7; i++) {         //weaponObstacle[i].img[0]weaponObstacle[i].x
				if (weaponObstacle[i].x > -60);//&& studentObstacle[i].x < 640)//越过原点的障碍物会消失
				//	putimage_transparent(NULL, weapon[0].img[count % 8], weaponX[i] -= obstacleSpeed, 100, BLACK);
				//	putimage_transparent(NULL, weapon[0].img[count % 8], weaponX[i] -= obstacleSpeed, 220, BLACK);
				//	putimage_transparent(NULL, weapon[0].img[count % 8], weaponX[i] -= obstacleSpeed, 340, BLACK);
					//putimage_transparent(NULL, weaponObstacle[i].img[count % 8], weaponObstacle[i].x -= obstacleSpeed, laneYBase(weaponObstacle[i]) - 30, BLACK);
			}
			*/

		delay_ms(50);
	}
	closegraph();
	return 1;

}

void spotInWay3() {

}
void gameInLake() {

}
void spotInLake() {

}
void spotInClass() {

}

int main()
{
	gameInRoad();
	//gameInCanteen();
	return 0;
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

