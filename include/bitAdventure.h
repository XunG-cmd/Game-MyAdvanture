#pragma once
#include<graphics.h>
  //定义角色状态
#define JUMP 1
#define RUN 0
#define ROLL 2
#define UP -1
#define DOWN -2

#define NORMAL 0
#define SUPER 1
#define HALF_SUPER 2				//超能状态但是正常速度

#define COLL_NONE 0
#define COLL_DEAD 1
#define COLL_KILL 2
//确定地图结构
#define LANE1_Y 240					//1号道（最上方）纵坐标
#define LANE_Y_DIFF 120				//每道间纵坐标差
//大鹅受不受保护
#define PROTECT_OFF 0
#define PROTECT_ON 1


//定义帧速度及跳跃高度系数
const int SPEED = 5;
const int FREQUENCY = 20;

//定义轨道参数
const int TRACK_HEIGHT = 120;
const int T_GAME_1 = 50;           //游戏时长(秒)
const int TRACK_NUMBER = 30;
const int OBCTACLE_NUMBER = 300;


//初始化角色,需要赋像
struct CHARACTER
{
	int x = 50;						//图像左边线横坐标
	int lane = 2;					//所在道数
	int height = 50;				//图像高度
	int width = 60;					//图像宽度
	int h = 0;						//角色跳起高度
	PIMAGE img = newimage(60, 50);	//角色图像
	int state = RUN;				//角色状态使用宏定义
	int frame = 0;					//当前显示帧的编号
	int fixY = 0;					//纵坐标修正，仅适用于变道及由跳起变下蹲时
	int jumpTime = 0;				//跳跃时已滞空时间
	int jumpState;					//跳跃状态，为UP或DOWN
	int skin = 0;					//皮肤编号，0为默认皮肤
	bool protect = PROTECT_OFF;		//保护大黑鹅不受兔子攻击,鹅崽挂掉之后保护去掉
	int superState = NORMAL;		//超能状态
	int bloodValue = 2;				//血量值
	int bloodLimit = 2;				//血量上限
	int coin = 0;					//兜里的钢镚
	int save = 0;					//卡里的储蓄
	PIMAGE blood;
	PIMAGE skill;
	PIMAGE superStar[2];
	PIMAGE superStarHalf[2];
	PIMAGE frameSet[4][6][10];		//所有角色图像，第一维为状态，第二维为帧编号，第三维为皮肤编号
};

//初始化障碍物,定x,定lane,定像,定跨越特性
struct OBSTACLE
{
	int x = 0;
	int lane = 2;
	int laneNext = 2;
	int height = 0;
	int width = 50;
	int h = 0;
	PIMAGE img[8];
	bool jumpAvaliable = 0;			//是否可通过跳跃跨过障碍
	bool rollAvaliable = 0;			//是否可下蹲/滚动跳跃跨过障碍
	bool appear = 1;
	bool hurt = 0;
	bool direction = 1;				//油锅等障碍物的方向:0左1右
	int fixY = 0;					//追逐兔子时候变道
};


struct ENEMY
{
	int x = 0;
	int lane = 2;
	int height = 0;
	int width = 50;
	int h = 30;
	PIMAGE img[8];
	bool jumpAvaliable = 0;			//是否可通过跳跃跨过障碍
	bool rollAvaliable = 0;			//是否可下蹲/滚动跳跃跨过障碍
	bool appear = 1;
	bool direction = 1;				//小黑鹅的方向
	bool hurt = 0;
};

struct track {
	int startPosition;
	int length;				//单位是几个周期,一周期50ms
	int lane;
};

//传递图像信息的结构体(同样包括图片基本信息)
//段宇皓
//3月14
struct imageOnDevice {
	int level;
	int templateNumber;
	int frameNumber[4];
	int countObstacle = 0;					//障碍物数量
	int countKnife = 0;
	int countPot = 150;
	int coinNumber = 0;						//轨道测试物&金币胡萝卜数量
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
	int difficulty = 20;					//难度系数分为三级 -> 20 /16 /13 ->越来越难
	int count;								//此时帧数为多少
	int time = 0;							//大鹅第几次出击
	int period[100] = { 0 };				//每次花多少时间消灭大鹅   3/22 13:11
	int killNumber = 0;						//杀掉的小鹅
	bool init[200] = { 0 };
	int gooseNumber = 0;
	MUSIC mus[10];
};

/* 本文件中两个重载，分别对应两个个结构体所对应的putimage（）将图片下边线与所在道的底线重合时所需的y坐标
这样在输入putimage（）纵坐标时可以使用laneYBase（）减去图片与底线间距即可 */
int laneYBase(OBSTACLE obstacle)
{
	return LANE1_Y + (obstacle.lane - 1) * LANE_Y_DIFF - obstacle.height;
}
int laneYBase(ENEMY enemy)
{
	return LANE1_Y + (enemy.lane - 1) * LANE_Y_DIFF - enemy.height;
}
//角色的纵坐标
int Y(CHARACTER character)
{
	return LANE1_Y + (character.lane - 1) * LANE_Y_DIFF - character.height - character.h + character.fixY - 30;
}
//障碍物纵坐标
int Y(OBSTACLE obstacle)
{
	return LANE1_Y + (obstacle.lane - 1) * LANE_Y_DIFF - obstacle.height + obstacle.fixY - 30;
}