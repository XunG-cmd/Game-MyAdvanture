//created by 黄泽源
#include<iostream>
#include<fstream>
#include<string>
#include<codecvt>
#include<locale>
#include<graphics.h>
void showDialog(std::string script)
{
	//空行
	std::string noContent = "<nc>";
	//图片文件根目录
	std::string assetPath = "assets/";
	//脚本文件根目录
	std::string dialogPath = "dialog/";
	//统一声明读入的行，以便复用
	std::string line;

	//准备文字背景和字体
	setbkmode(TRANSPARENT);
	setfont(24, 0, "微软雅黑");
	setcolor(BLACK);
	//读取对话框源文件
	PIMAGE dialogBackgroundSource = newimage();
	getimage(dialogBackgroundSource, "assets/DIALOG BOX1.0.png");
	//trick，截下背景然后和半透明的对话框源文件混合。这样不用重画背景
	PIMAGE dialogBackground = newimage();
	getimage(dialogBackground, 0, 480 - getheight(dialogBackgroundSource), 640, getheight(dialogBackgroundSource));
	putimage_alphatransparent(dialogBackground, dialogBackgroundSource, 0, 0, BLACK, 0x80);
	delimage(dialogBackgroundSource);
	putimage(0, 480 - getheight(dialogBackground), dialogBackground);

	//输入流，脚本文件需要用GB2312编码保存
	std::ifstream input(dialogPath + script);
	//计数器，0 -> 名字，1 -> 空行 2~6 -> 文字
	int counter = 0;
	while (std::getline(input, line)) {
		//四行一停
		if (counter == 6) {
			while(kbhit()) {getch();} //丢弃掉显示对话前的键盘事件
			if (line != noContent) {
				PIMAGE tachie = newimage();
				getimage(tachie, (assetPath + line).c_str());
				int tachieX = 640 - getwidth(tachie);
				int tachieY = 528 - getheight(dialogBackground) - getheight(tachie);
				PIMAGE tachieBackgroundBackup = newimage();
				getimage(tachieBackgroundBackup, tachieX, tachieY, getwidth(tachie), getheight(tachie));
				putimage_transparent(NULL, tachie, tachieX, tachieY, BLACK);
				getch();
				putimage(tachieX, tachieY, tachieBackgroundBackup);
				delimage(tachie);
				delimage(tachieBackgroundBackup);
			}
			else {
				getch();
			}
			counter = 0;
			putimage(0, 480 - getheight(dialogBackground), dialogBackground);
		}
		else {
			if (counter == 1) counter++;
			if (line != noContent)outtextrect(20, 490 - getheight(dialogBackground) + counter * 30, 600, 30, line.c_str());
			counter++;
		}
	}
	delimage(dialogBackground);
}
/*
对话脚本格式
小明                                                    说话人
Lorem ipsum dolor sit amet, consectetur adipisicing     内容占满四行
elit, sed do eiusmod tempor incididunt ut labore et
dolore magna aliqua. Ut enim ad minim veniam, quis
nostrud exercitation ullamco laboris nisi ut aliquip
xiaoming.png                                            立绘名称
小明
Lorem ipsum dolor sit amet, consectetur adipisicing
elit, sed do eiusmod tempor incididunt ut labore et
<nc>                                                    没满四行用<nc>补位
<nc>
xiaoming.png
神秘声音
Lorem ipsum dolor sit amet, consectetur adipisicing
elit, sed do eiusmod tempor incididunt ut labore et
dolore magna aliqua. Ut enim ad minim veniam, quis
nostrud exercitation ullamco laboris nisi ut aliquip
<nc>                                                    没有立绘也用<nv>补位
*/