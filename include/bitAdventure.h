#pragma once
#include<graphics.h>
  //�����ɫ״̬
#define JUMP 1
#define RUN 0
#define ROLL 2
#define UP -1
#define DOWN -2

#define NORMAL 0
#define SUPER 1
#define HALF_SUPER 2				//����״̬���������ٶ�

#define COLL_NONE 0
#define COLL_DEAD 1
#define COLL_KILL 2
//ȷ����ͼ�ṹ
#define LANE1_Y 240					//1�ŵ������Ϸ���������
#define LANE_Y_DIFF 120				//ÿ�����������
//����ܲ��ܱ���
#define PROTECT_OFF 0
#define PROTECT_ON 1


//����֡�ٶȼ���Ծ�߶�ϵ��
const int SPEED = 5;
const int FREQUENCY = 20;

//����������
const int TRACK_HEIGHT = 120;
const int T_GAME_1 = 50;           //��Ϸʱ��(��)
const int TRACK_NUMBER = 30;
const int OBCTACLE_NUMBER = 300;


//��ʼ����ɫ,��Ҫ����
struct CHARACTER
{
	int x = 50;						//ͼ������ߺ�����
	int lane = 2;					//���ڵ���
	int height = 50;				//ͼ��߶�
	int width = 60;					//ͼ����
	int h = 0;						//��ɫ����߶�
	PIMAGE img = newimage(60, 50);	//��ɫͼ��
	int state = RUN;				//��ɫ״̬ʹ�ú궨��
	int frame = 0;					//��ǰ��ʾ֡�ı��
	int fixY = 0;					//�������������������ڱ������������¶�ʱ
	int jumpTime = 0;				//��Ծʱ���Ϳ�ʱ��
	int jumpState;					//��Ծ״̬��ΪUP��DOWN
	int skin = 0;					//Ƥ����ţ�0ΪĬ��Ƥ��
	bool protect = PROTECT_OFF;		//������ڶ첻�����ӹ���,���̹ҵ�֮�󱣻�ȥ��
	int superState = NORMAL;		//����״̬
	int bloodValue = 2;				//Ѫ��ֵ
	int bloodLimit = 2;				//Ѫ������
	int coin = 0;					//����ĸ��G
	int save = 0;					//����Ĵ���
	PIMAGE blood;
	PIMAGE skill;
	PIMAGE superStar[2];
	PIMAGE superStarHalf[2];
	PIMAGE frameSet[4][6][10];		//���н�ɫͼ�񣬵�һάΪ״̬���ڶ�άΪ֡��ţ�����άΪƤ�����
};

//��ʼ���ϰ���,��x,��lane,����,����Խ����
struct OBSTACLE
{
	int x = 0;
	int lane = 2;
	int laneNext = 2;
	int height = 0;
	int width = 50;
	int h = 0;
	PIMAGE img[8];
	bool jumpAvaliable = 0;			//�Ƿ��ͨ����Ծ����ϰ�
	bool rollAvaliable = 0;			//�Ƿ���¶�/������Ծ����ϰ�
	bool appear = 1;
	bool hurt = 0;
	bool direction = 1;				//�͹����ϰ���ķ���:0��1��
	int fixY = 0;					//׷������ʱ����
};


struct ENEMY
{
	int x = 0;
	int lane = 2;
	int height = 0;
	int width = 50;
	int h = 30;
	PIMAGE img[8];
	bool jumpAvaliable = 0;			//�Ƿ��ͨ����Ծ����ϰ�
	bool rollAvaliable = 0;			//�Ƿ���¶�/������Ծ����ϰ�
	bool appear = 1;
	bool direction = 1;				//С�ڶ�ķ���
	bool hurt = 0;
};

struct track {
	int startPosition;
	int length;				//��λ�Ǽ�������,һ����50ms
	int lane;
};

//����ͼ����Ϣ�Ľṹ��(ͬ������ͼƬ������Ϣ)
//�����
//3��14
struct imageOnDevice {
	int level;
	int templateNumber;
	int frameNumber[4];
	int countObstacle = 0;					//�ϰ�������
	int countKnife = 0;
	int countPot = 150;
	int coinNumber = 0;						//���������&��Һ��ܲ�����
	int tempCount;
	PIMAGE background;
	PIMAGE buffer;
	PIMAGE coinboxs;
	PIMAGE distance;
	PIMAGE heart;
	PIMAGE kill;
	CHARACTER rabbit;
	OBSTACLE templateObstacle[4];
	OBSTACLE copyObstacle[300];
	OBSTACLE templateCoin;
	OBSTACLE coin[300];
	int difficulty = 20;					//�Ѷ�ϵ����Ϊ���� -> 20 /16 /13 ->Խ��Խ��
	int count;								//��ʱ֡��Ϊ����
	int time = 0;							//���ڼ��γ���
	int period[100] = { 0 };				//ÿ�λ�����ʱ��������   3/22 13:11
	int killNumber = 0;						//ɱ����С��
	bool init[200] = { 0 };
	int gooseNumber = 0;
	MUSIC mus[10];
};

/* ���ļ����������أ��ֱ��Ӧ�������ṹ������Ӧ��putimage������ͼƬ�±��������ڵ��ĵ����غ�ʱ�����y����
����������putimage����������ʱ����ʹ��laneYBase������ȥͼƬ����߼�༴�� */
int laneYBase(OBSTACLE obstacle)
{
	return LANE1_Y + (obstacle.lane - 1) * LANE_Y_DIFF - obstacle.height;
}
int laneYBase(ENEMY enemy)
{
	return LANE1_Y + (enemy.lane - 1) * LANE_Y_DIFF - enemy.height;
}
//��ɫ��������
int Y(CHARACTER character)
{
	return LANE1_Y + (character.lane - 1) * LANE_Y_DIFF - character.height - character.h + character.fixY - 30;
}
//�ϰ���������
int Y(OBSTACLE obstacle)
{
	return LANE1_Y + (obstacle.lane - 1) * LANE_Y_DIFF - obstacle.height + obstacle.fixY - 30;
}