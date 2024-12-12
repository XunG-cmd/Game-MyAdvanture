//Created by 黄泽源&裴思琦&段宇皓
#pragma once
#include<graphics.h>
#include<string>
#include"button.h"
#include"save.h"
#include"multithreadMusic.h"

#define PAUSE_CONTINUE 1
#define PAUSE_EXIT 2

#define GAMEOVER_PLAYAGAIN 1
#define GAMEOVER_EXIT 2

int pause();
int gameover(std::string scene);
void refreshGameover(PIMAGE background, BUTTON playAgain, BUTTON exit);
void refreshPause(PIMAGE background, BUTTON continueBtn, BUTTON exit);

int pause() {
	//背景
	PIMAGE black = newimage(640, 480);
	setfillcolor(BLACK, black);
	bar(0, 0, 640, 480, black);
	//备份当前图片
	PIMAGE background = newimage();
	getimage(background, 0, 0, 640, 480);
	//将遮罩写入窗口
	putimage_alphablend(background, black, 0, 0, 0xA0);
	delimage(black);
	mouse_msg mouse = { 0 };
	while(mousemsg()) {mouse = getmouse();} //丢弃掉显示菜单前的鼠标事件
	BUTTON continueBtn, exit;
	continueBtn.y = 100;
	getimage(continueBtn.img, "assets/CONTINUE01.png");
	exit.y = 320;
	getimage(exit.img, "assets/EXIT01.png");
	refreshPause(background, continueBtn, exit);

	int returnValue;
	while (1) {
		mouse = getmouse();
		if (mouse.is_down() && mouse.is_left()) {
			if (onButton(mouse, continueBtn)) {
				getimage(continueBtn.img, "assets/CONTINUE00.png");
				playMusicOnce("music/buttonPress.mp3");
			}
			if (onButton(mouse, exit)) {
				getimage(exit.img, "assets/EXIT00.png");
				playMusicOnce("music/buttonPress.mp3");
			}
		}
		else if (mouse.is_up() && mouse.is_left()) {
			if (onButton(mouse, continueBtn)) { returnValue = PAUSE_CONTINUE; break; }
			if (onButton(mouse, exit)) { returnValue = PAUSE_EXIT; break; }
		}
		else {
			if (onButton(mouse, continueBtn)) {
				getimage(continueBtn.img, "assets/CONTINUE02.png");
			}
			else {
				getimage(continueBtn.img, "assets/CONTINUE01.png");
			}
			if (onButton(mouse, exit)) {
				getimage(exit.img, "assets/EXIT03.png");
			}
			else {
				getimage(exit.img, "assets/EXIT01.png");
			}
		}
		refreshPause(background, continueBtn, exit);
	}

	delimage(background);
	delimage(continueBtn.img);
	delimage(exit.img);
	return returnValue;
}

void refreshPause(PIMAGE background, BUTTON continueBtn, BUTTON exit) {
	cleardevice();
	putimage(0, 0, background);
	putimage_transparent(NULL, continueBtn.img, continueBtn.x, continueBtn.y, BLACK);
	putimage_transparent(NULL, exit.img, exit.x, exit.y, BLACK);
}

int gameover(std::string scene) {
	MUSIC gameover; // 定义一个音乐对象
	gameover.OpenFile("music/gameover.mp3"); // 打开文件
	gameover.Play(0);
	mouse_msg mouse = { 0 }; //定义鼠标事件
	//先显示红色遮罩
	PIMAGE red = newimage(640, 480);
	setfillcolor(RED, red);
	bar(0, 0, 640, 480, red);
	putimage(0, 0, red);
	delimage(red);

	PIMAGE background = newimage(640, 480);
	//如果没有特别指定背景图片
	if (scene == "<nc>") {
		setfillcolor(EGERGB(150, 150, 150), background);
		bar(0, 0, 640, 480, background);
	}
	else {
		std::string assetPath = "assets/";
		getimage(background, (assetPath + scene).c_str());
	}
	//渐变绘制背景图像
	for (int i = 0; i < 150; i += 5) {
		delay_ms(50);
		putimage_alphablend(NULL, background, 0, 0, i);
	}
	//最后直接填充，避开透明绘制时的边界情况
	putimage(0, 0, background);
	//如果指定背景图，需要按任意键继续，灰色图直接显示菜单
	if (scene != "<nc>") getch();

	PIMAGE header = newimage();
	getimage(header, "assets/GAME OVERnew.png");
	putimage_transparent(background, header, (640 - getwidth(header)) / 2, 20, BLACK);
	delimage(header);
	BUTTON playAgain, exit;
	playAgain.y = 200;
	getimage(playAgain.img, "assets/PLAY AGAIN01.png");
	exit.y = 300;
	getimage(exit.img, "assets/EXIT01.png");
	while(mousemsg()) {mouse = getmouse();} //丢弃掉显示菜单前的鼠标事件
	refreshGameover(background, playAgain, exit);

	int returnValue;
	while (1) {
		mouse = getmouse();
		if (mouse.is_down() && mouse.is_left()) {
			if (onButton(mouse, playAgain)) {
				getimage(playAgain.img, "assets/PLAY AGAIN00.png");
				playMusicOnce("music/buttonPress.mp3");
			}
			if (onButton(mouse, exit)) {
				getimage(exit.img, "assets/EXIT00.png");
				playMusicOnce("music/buttonPress.mp3");
			}
		}
		else if (mouse.is_up() && mouse.is_left()) {
			if (onButton(mouse, playAgain)) { returnValue = GAMEOVER_PLAYAGAIN; break; }
			if (onButton(mouse, exit)) { returnValue = GAMEOVER_EXIT; break; }
		}
		else {
			if (onButton(mouse, playAgain)) {
				getimage(playAgain.img, "assets/PLAY AGAIN02.png");
			}
			else {
				getimage(playAgain.img, "assets/PLAY AGAIN01.png");
			}
			if (onButton(mouse, exit)) {
				getimage(exit.img, "assets/EXIT03.png");
			}
			else {
				getimage(exit.img, "assets/EXIT01.png");
			}
		}
		refreshGameover(background, playAgain, exit);
	}

	delimage(background);
	delimage(playAgain.img);
	delimage(exit.img);
	return returnValue;
}

void refreshGameover(PIMAGE background, BUTTON playAgain, BUTTON exit) {
	cleardevice();
	putimage(0, 0, background);
	putimage_transparent(NULL, playAgain.img, playAgain.x, playAgain.y, BLACK);
	putimage_transparent(NULL, exit.img, exit.x, exit.y, BLACK);
}


void gameover(int level, std::string scene, int score, int money)
{
	//先显示红色遮罩
	PIMAGE red = newimage(640, 480);
	setfillcolor(RED, red);
	bar(0, 0, 640, 480, red);
	putimage(0, 0, red);
	delimage(red);

	PIMAGE background = newimage(640, 480);
	//如果没有特别指定背景图片
	if (scene == "<nc>") {
		setfillcolor(EGERGB(150, 150, 150), background);
		bar(0, 0, 640, 480, background);
	}
	else {
		std::string assetPath = "assets/";
		getimage(background, (assetPath + scene).c_str());
	}
	//渐变绘制背景图像
	for (int i = 0; i < 150; i += 5) {
		delay_ms(50);
		putimage_alphablend(NULL, background, 0, 0, i);
	}
	//最后直接填充，避开透明绘制时的边界情况
	putimage(0, 0, background);
	//如果指定背景图，需要按任意键继续，灰色图直接显示菜单
	if (scene != "<nc>") getch();

	PIMAGE header = newimage();
	getimage(header, "assets/GAME OVERnew.png");
	putimage_transparent(background, header, (640 - getwidth(header)) / 2, 20, BLACK);
	delimage(header);

	PIMAGE coin = newimage();
	getimage(coin, "assets/coin02.png");
	char scoreStr[10], moneyStr[10];
	int tempScore, tempMoney;

	setbkmode(TRANSPARENT);
	setfont(80, 0, "impact");
	setcolor(BLACK);
	settextjustify(CENTER_TEXT, CENTER_TEXT);

	//播放音频
	MUSIC victory; // 定义一个音乐对象
	victory.OpenFile("music/victory.mp3"); // 打开文件
	victory.Play(0);
	for (tempScore = 0; tempScore <= score; tempScore++)
	{
		putimage(0, 0, background);
		sprintf(scoreStr, "%d", tempScore);
		outtextxy(320, 180, scoreStr);
		delay_ms(0.5);
	}
	//写入最高分（若是）
	if (score > getHighScore(level))
	{
		delay_ms(250);
		PIMAGE highScore = newimage();
		getimage(highScore, "assets/high score.png");
		writeHighScore(level, score);
		putimage_transparent(NULL, highScore, 195, 105, BLACK);
		putimage_transparent(background, highScore, 195, 105, BLACK);
	}
	delay_ms(500);

	//实现数值增长效果
	putimage_transparent(background, coin, 270, 290, BLACK);
	for (tempMoney = 0; tempMoney <= money; tempMoney++)
	{
		putimage(0, 0, background);
		sprintf(moneyStr, "%d", tempMoney);
		setfont(80, 0, "impact");
		setcolor(BLACK);
		outtextxy(320, 180, scoreStr);
		setfont(40, 0, "impact");
		setcolor(EGERGB(255, 200, 0));
		outtextxy(335, 304, moneyStr);
		delay_ms(8);
	}
	//增加金币
	addMoney(money);


	BUTTON exit;
	exit.y = 370;
	getimage(exit.img, "assets/EXIT01.png");
	mouse_msg mouse = { 0 };
	while(mousemsg()) {mouse = getmouse();} //丢弃掉显示菜单前的鼠标事件
	putimage_transparent(NULL, exit.img, exit.x, exit.y, BLACK);
	while (1) {
		mouse = getmouse();
		if (mouse.is_down() && mouse.is_left()) {
			if (onButton(mouse, exit)) {
				getimage(exit.img, "assets/EXIT00.png");
				playMusicOnce("music/buttonPress.mp3");
			}
		}
		else if (mouse.is_up() && mouse.is_left()) {
			if (onButton(mouse, exit)) { break; }
		}
		else {
			if (onButton(mouse, exit)) {
				getimage(exit.img, "assets/EXIT03.png");
			}
			else {
				getimage(exit.img, "assets/EXIT01.png");
			}
		}
		putimage_transparent(NULL, exit.img, exit.x, exit.y, BLACK);
	}

	settextjustify(LEFT_TEXT, TOP_TEXT);
	delimage(background);
	delimage(exit.img);
	return;
}
