//code created by 裴思琦
#pragma once
#include <stdio.h>
#include <string.h>

//获取金钱数
int getMoney()
{
	FILE* MONEY;
	char saveString[100];
	int money = 0;
	//打开存档文件
	MONEY = fopen("save/MONEY.txt", "r+");
	fgets(saveString, 100, MONEY);
	//将得到的字符串转换为数字
	for (int i = 0; saveString[i] != '\0'; i++)
	{
		money *= 10;
		money += saveString[i] - '0';
	}
	//关闭文件并返回
	fclose(MONEY);
	return money;
}

//获取金钱数字符串
char* getMoneyStr()
{
	FILE* MONEY;
	char saveString[100];
	//打开存档文件
	MONEY = fopen("save/MONEY.txt", "r+");
	fgets(saveString, 100, MONEY);
	fclose(MONEY);
	return saveString;
}

//增加金钱（可为负数）
int addMoney(int amount)
{
	//获取当前金钱数
	int money = getMoney();
	//当操作后金钱数非负
	if (money + amount >= 0)
	{
		//写入新值
		FILE* MONEY;
		MONEY = fopen("save/MONEY.txt", "w+");
		money += amount;
		fprintf(MONEY, "%d", money);
		fclose(MONEY);
		//返回1，说明操作成功
		return 1;
	}
	//当操作后为负
	else
		//返回0，说明操作失败
		return 0;
}

//检查皮肤是否获得
int skinAvaliable(int num)
{
	FILE* SKIN;
	char fileName[100] = "save/SKIN", number[2] , resultString[2];
	//根据得到的编号得出存档文件名
	number[0] = num + '0';
	number[1] = '\0';
	strcat(fileName, number);
	strcat(fileName, ".txt");
	SKIN = fopen(fileName, "r+");
	//得到字符串值，为"1\0"或"0\0"
	fgets(resultString, 2, SKIN);
	fclose(SKIN);
	//返回转换出的数字，为1或0
	return resultString[0]-'0';
}

//保存皮肤解锁
int saveSkinPurchase(int num)
{
	//如果该编号皮肤未解锁
	if (!skinAvaliable(num))
	{
		FILE* SKIN;
		char fileName[100] = "save/SKIN", number[2];
		//根据得到的编号得出存档文件名
		number[0] = num + '0';
		number[1] = '\0';
		strcat(fileName, number);
		strcat(fileName, ".txt");
		SKIN = fopen(fileName, "w+");
		//将值改为1，即获得
		fprintf(SKIN, "%d", 1);
		fclose(SKIN);
		//返回1，说明操作成功
		return 1;
	}
	//如果该编号皮肤已解锁
	else
		//返回0，说明操作失败
		return 0;
}

char* getHighScoreStr(int level)
{
	FILE* HIGHSCORE;
	char fileName[100] = "save/HIGHSCORE", number[2], saveString[100];
	//根据得到的编号得出存档文件名
	number[0] = level + '0';
	number[1] = '\0';
	strcat(fileName, number);
	strcat(fileName, ".txt");
	HIGHSCORE = fopen(fileName, "r+");
	fgets(saveString, 100, HIGHSCORE);
	fclose(HIGHSCORE);
	return saveString;
}

//获取最高分
int getHighScore(int level)
{
	char saveString[100];
	int highscore = 0;
	strcpy(saveString, getHighScoreStr(level));
	//将得到的字符串转换为数字
	for (int i = 0; saveString[i] != '\0'; i++)
	{
		highscore *= 10;
		highscore += saveString[i] - '0';
	}
	return highscore;
}

int writeHighScore(int level, int highscore)
{
	//如果要写入的最高分大于原最高分
	if (getHighScore(level) < highscore)
	{
		FILE* HIGHSCORE;
		char fileName[100] = "save/HIGHSCORE", number[2];
		//根据得到的编号得出存档文件名
		number[0] = level + '0';
		number[1] = '\0';
		strcat(fileName, number);
		strcat(fileName, ".txt");
		HIGHSCORE = fopen(fileName, "w+");
		fprintf(HIGHSCORE, "%d", highscore);
		fclose(HIGHSCORE);
		//返回1，说明操作成功
		return 1;
	}
	//如果不是最高分
	else
		//返回0，说明操作失败
		return 0;
}