#include"include/menu.h"
#include"include/dialog.h"
#include"include/map.h"
#include"include/infiniteMap.h"
#include"include/levels.h"
#include"include/handler.h"
#include"include/multithreadMusic.h"

//渐变放图
void putimage_gradient(LPCSTR path);
//故事模式
void storyMode();
//无尽模式
void infiniteMode();

//调试用：空格键模拟成功，其他任意键模拟失败
int stimulateGame();
#define GAME_NONE 0
#define GAME_DEAD 1

int main() {
	initgraph(640, 480, 0);
	setcaption("北理工大冒险");

	int returnValue = -1;
	while (returnValue != MENU_EXIT) {
		returnValue = menu();
		switch (returnValue) {
		case MENU_STORY:
			storyMode();
			break;
		case MENU_INFINITE:
			infiniteMode();
			break;
		default:
			break;
		}
	}

	closegraph();
	return 0;
}

void storyMode() {
	MUSIC bgm;
	bgm.OpenFile("music/dialog.mp3");
	bgm.Play();
	//祥和气氛
	putimage_gradient("assets/GATE1.0.png");
	showDialog("-1.txt");
	
	//天有异象
	putimage_gradient("assets/SKY.png");
	showDialog("-2.txt");
	
	//疏桐园
	putimage_gradient("assets/SHUTONGYUAN.png");
	showDialog("-3.txt");

	//宿舍场景
	putimage_gradient("assets/DORM2.0.png");
	showDialog("1.txt");

	//宿舍外场景
	putimage_gradient("assets/FALL DOWN.png");
	showDialog("2.txt");

	//和神对话
	putimage_gradient("assets/DIALOG WITH GODnew.png");
	showDialog("3.txt");

	//出宿舍后地图
	putimage_gradient("assets/MAP2.png");
	mapMove(1);
	showDialog("4.txt");

	bgm.Pause();
	int gameResult = -1;
	while (gameResult != GAME_NONE) {
		gameResult = gameInRoad_story();
		switch (gameResult)
		{
		case GAME_DEAD:
			switch (gameover("GAMEOVER1.png"))
			{
			case GAMEOVER_PLAYAGAIN:
				continue;
			case GAMEOVER_EXIT:
				return;
			}
		case GAME_NONE:
			break;
		case GAME_EXIT:
			return;
		}
	}

	bgm.Play(0);
	//移动到食堂
	putimage_gradient("assets/MAP2.png");
	mapMove(2);

	//食堂门前
	putimage_gradient("assets/BETWEEN 1 AND 2.png");
	showDialog("5.txt");

	bgm.Pause();
	gameResult = -1;
	while (gameResult != GAME_NONE) {
		gameResult = gameInCanteen_story();
		switch (gameResult)
		{
		case GAME_DEAD:
			switch (gameover("GAMEOVER2.png"))
			{
			case GAMEOVER_PLAYAGAIN:
				continue;
			case GAMEOVER_EXIT:
				return;
			}
		case GAME_NONE:
			break;
		case GAME_EXIT:
			return;
		}
	}

	bgm.Play(0);
	//食堂通关后
	putimage_gradient("assets/BETWEEN 2AND 3.png");
	showDialog("6.txt");

	//移动到北湖
	putimage_gradient("assets/MAP2.png");
	mapMove(3);

	//北湖白鹅对话
	putimage_gradient("assets/NL dialog background2.png");
	showDialog("7.txt");

	//北湖白鹅指黑鹅
	putimage_gradient("assets/look at black swan.png");
	showDialog("8.txt");

	bgm.Pause();
	gameResult = -1;
	while (gameResult != GAME_NONE) {
		gameResult = gameInLake_story();
		switch (gameResult)
		{
		case GAME_DEAD:
			switch (gameover("GAMEOVER3.png"))
			{
			case GAMEOVER_PLAYAGAIN:
				continue;
			case GAMEOVER_EXIT:
				return;
			}
		case GAME_NONE:
			break;
		case GAME_EXIT:
			return;
		}
	}

	bgm.Play(0);
	//打败黑鹅后
	putimage_gradient("assets/look at lake.png");
	showDialog("9.txt");

	//与锦鲤对话
	putimage_gradient("assets/DIALOG WITH FISH.png");
	showDialog("10.txt");

	//回到现实
	putimage_gradient("assets/CLASSROOM.png");
	showDialog("11.txt");

	//制作组名单
	putimage_gradient("assets/LAST.png");
	getch();
	bgm.Stop();
	bgm.Close();
}

void infiniteMode() {
	putimage_gradient("assets/MAP2.png");
	int returnValue[2] = {-1, 0}, gameResult = -1;
	do {
		infiniteMap(returnValue);
		switch(returnValue[0]) {
		case INFINITE_ROAD:
			gameResult = -1;
			while(gameResult != GAME_DEAD && gameResult != GAME_EXIT) {
				gameResult = gameinRoad_infinite(returnValue[1]);
			}
			break;
		case INFINITE_CANTEEN:
			gameResult = -1;
			while(gameResult != GAME_DEAD && gameResult != GAME_EXIT) {
				gameResult = gameInCanteen_infinite(returnValue[1]);
			}
			break;
		case INFINITE_NORTHLAKE:
			gameResult = -1;
			while(gameResult != GAME_DEAD && gameResult != GAME_EXIT) {
				gameResult = gameInLake_infinite(returnValue[1]);
			}
			break;
		}
	} while (*returnValue != INFINITE_HOME);
}

void putimage_gradient(LPCSTR path) {
	PIMAGE image = newimage();
	getimage(image, path);
	for (int i = 0; i < 250; i += 10) {
		putimage_alphablend(NULL, image, 0, 0, i);
		delay_ms(50);
	}
	cleardevice();
	putimage(0, 0, image);
	delimage(image);
}

int stimulateGame() {
	PIMAGE image = newimage();
	getimage(image, "assets/coming soon.png");
	putimage(0, 0, image);
	char ch = getch();
	//游戏成功
	if (ch == ' ') return GAME_NONE;
	//游戏失败
	return GAME_DEAD;
}