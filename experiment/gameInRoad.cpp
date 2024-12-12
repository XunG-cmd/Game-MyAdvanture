#include "bitAdventure.h"
#include "character.h"
#include "collision.h"
#include <stdio.h>
#include <stdlib.h>
void refresh(CHARACTER rabbit, PIMAGE background, PIMAGE buffer);
//�쳣�жϲ�Ҫ��, ���ַ�, ��Դͷ.
//�����, �ȶ���
//�߼�˼·Ҫ���
//���ñ����ʼ��
//�ǵ������Խ��
//�ǵò�Ҫ��ѭ��

int main(){
	initgraph(640, 480);
	//��ʼ����ͣ״̬
	bool showdialog = false;
	
	//��������
	int jumpTime = 0;
	int changeLaneTime = 0;
	CHARACTER rabbit;
	rabbit.img = newimage();
	getimage(rabbit.img, "../../bit-adventure/assets/rabbit1.1.png");
	rabbit.state = RUN;
	rabbit.frame = 1;

	//��������
	PIMAGE background = newimage();
	PIMAGE buffer = newimage(640, 480);
	getimage(background, "../../bit-adventure/assets/ROAD3.0.png");

	//���������&��Һ��ܲ�
	setfillcolor(YELLOW);
	fillellipsef(20, 20, 40, 40);

	OBSTACLE testTrack;
	testTrack.height = 50;
	testTrack.img[0] = newimage();
	getimage(testTrack.img[0], 0, 0, 40, 40);
	testTrack.jumpAvaliable = 1;
	testTrack.rollAvaliable = 1;
	testTrack.width = 50;

	//ѧ���ϰ���
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

	//����������ǹ�� ˳�������ϰ�������λ�� �Լ��ϰ��� FREQUENCY * SPEED = 100����/��
	track characterTrack[TRACK_NUMBER];
	track laneAllow[TRACK_NUMBER];
	characterTrack[0].startPosition = 640 + FREQUENCY * SPEED * 5;		//5s���ֵ�һ��ѧ���ϰ���
	characterTrack[0].lane = 2;
	int countObstacle = 0;						//�ϰ�������
	int testCountTrack = 0;						//���������&��Һ��ܲ�����
	//���ӡˢ���еĸ�ӡƷ
	OBSTACLE studentObstacle[200];				//200��δ֪���ѧ���ϰ���,������
	OBSTACLE trackTest[TRACK_NUMBER * 6];		//ÿ���������������

	
	
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

		//�ڹ���ڲ���Χ������test  (*)
		int tempPosition = characterTrack[i].startPosition;
		do {
			testTrack.x = tempPosition;
			tempPosition += 60;								//track��,�����20����
			testTrack.lane = characterTrack[i].lane;
			trackTest[testCountTrack++] = testTrack;
		} while (testTrack.x + 50 <= characterTrack[i].startPosition + characterTrack[i].length);
		//end
		
		//�ϰ�������λ��
		laneAllow[i].lane = characterTrack[i].lane;			// 1 + rand() % 3;//
		laneAllow[i].startPosition = characterTrack[i].startPosition + characterTrack[i].length;
		if (i > 3) {
			int j = i;
			while (characterTrack[--j].lane != characterTrack[i].lane);
															//��ʱ�Ѿ�������һ��ͬlane��track����
			laneAllow[j].length = characterTrack[i].startPosition - characterTrack[j].startPosition - characterTrack[j].length;
			int temp = 0;
			int countIngroup = 0;
			tempPosition = 40;
			do {
				temp = rand() % 4;
				studentObstacle[countObstacle].img[0] = student[temp].img[0];
				studentObstacle[countObstacle].img[1] = student[temp].img[1];
				studentObstacle[countObstacle].x = tempPosition + laneAllow[j].startPosition;
				tempPosition += 100;						//��ʱ��λΪ��һ���ϰ���λ��
				studentObstacle[countObstacle++].lane = laneAllow[j].lane - 1;
			} while (tempPosition + 50 <= laneAllow[j].length);

		}
		
	}
	

	
	


	int count = 0;								//ѭ����
	int obstacleSpeed = 12;						//�ϰ����ƶ��ٶ�
	for (count = 0; count < 580; count++) {// ege::delay_fps(20)
		if (count == 200) obstacleSpeed = 14;
		if (count == 400) obstacleSpeed = 16;	//������ 12*200 + 14*200 + 16*180 = 8080������
		//�ı������ж�״̬
		action(&rabbit);
		keyDetect(&rabbit, 1);
		//�ж���������״̬
		
			//return COLL_DEAD;
		refresh(rabbit, background, buffer);
		int tempPosition = rabbit.x;
		for (int i = 0; i < countObstacle; i++){
			if (rabbit.lane == studentObstacle[i].lane + 1 && studentObstacle[i].x + 10 < tempPosition + rabbit.width && tempPosition + rabbit.width < studentObstacle[i].x + studentObstacle[i].width - 10)
				return COLL_DEAD;
			if (studentObstacle[i].x > -60 )//&& studentObstacle[i].x < 640)//Խ��ԭ����ϰ������ʧ
				putimage_transparent(NULL, studentObstacle[i].img[count % 4 / 2], studentObstacle[i].x -= obstacleSpeed, laneYBase(studentObstacle[i]) - 30, BLACK);
		}
		
		for (int i = 0; i < testCountTrack; i++) {
			if (trackTest[i].x >= rabbit.x + 40 && trackTest[i].x <= rabbit.x + 80 && trackTest[i].lane == rabbit.lane) {
				trackTest[i].appear = 0;
			}
			if (trackTest[i].x > -60 && trackTest[i].appear == 1)//&& studentObstacle[i].x < 640)//Խ��ԭ��Ĺ�����Է������ʧ
				putimage_transparent(NULL, trackTest[i].img[0], trackTest[i].x -= obstacleSpeed, laneYBase(trackTest[i]) - 30, BLACK);

		}
		delay_ms(50);
	}

	return COLL_NONE;
}



//���������ػ�

void refresh(CHARACTER rabbit, PIMAGE background, PIMAGE buffer)
{
	cleardevice();
	putimage(0, 0, background);
	putimage_transparent(NULL, rabbit.img, rabbit.x, Y(rabbit), BLACK);
	putimage(buffer, 0, 0, 640 - SPEED, 480, background, SPEED, 0);
	putimage(buffer, 640 - SPEED, 0, SPEED, 480, background, 0, 0);
	putimage(background, 0, 0, buffer);
}

//********************************created by ����Դ*******************************************************************************

