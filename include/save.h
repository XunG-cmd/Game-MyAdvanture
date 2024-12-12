//code created by ��˼��
#pragma once
#include <stdio.h>
#include <string.h>

//��ȡ��Ǯ��
int getMoney()
{
	FILE* MONEY;
	char saveString[100];
	int money = 0;
	//�򿪴浵�ļ�
	MONEY = fopen("save/MONEY.txt", "r+");
	fgets(saveString, 100, MONEY);
	//���õ����ַ���ת��Ϊ����
	for (int i = 0; saveString[i] != '\0'; i++)
	{
		money *= 10;
		money += saveString[i] - '0';
	}
	//�ر��ļ�������
	fclose(MONEY);
	return money;
}

//��ȡ��Ǯ���ַ���
char* getMoneyStr()
{
	FILE* MONEY;
	char saveString[100];
	//�򿪴浵�ļ�
	MONEY = fopen("save/MONEY.txt", "r+");
	fgets(saveString, 100, MONEY);
	fclose(MONEY);
	return saveString;
}

//���ӽ�Ǯ����Ϊ������
int addMoney(int amount)
{
	//��ȡ��ǰ��Ǯ��
	int money = getMoney();
	//���������Ǯ���Ǹ�
	if (money + amount >= 0)
	{
		//д����ֵ
		FILE* MONEY;
		MONEY = fopen("save/MONEY.txt", "w+");
		money += amount;
		fprintf(MONEY, "%d", money);
		fclose(MONEY);
		//����1��˵�������ɹ�
		return 1;
	}
	//��������Ϊ��
	else
		//����0��˵������ʧ��
		return 0;
}

//���Ƥ���Ƿ���
int skinAvaliable(int num)
{
	FILE* SKIN;
	char fileName[100] = "save/SKIN", number[2] , resultString[2];
	//���ݵõ��ı�ŵó��浵�ļ���
	number[0] = num + '0';
	number[1] = '\0';
	strcat(fileName, number);
	strcat(fileName, ".txt");
	SKIN = fopen(fileName, "r+");
	//�õ��ַ���ֵ��Ϊ"1\0"��"0\0"
	fgets(resultString, 2, SKIN);
	fclose(SKIN);
	//����ת���������֣�Ϊ1��0
	return resultString[0]-'0';
}

//����Ƥ������
int saveSkinPurchase(int num)
{
	//����ñ��Ƥ��δ����
	if (!skinAvaliable(num))
	{
		FILE* SKIN;
		char fileName[100] = "save/SKIN", number[2];
		//���ݵõ��ı�ŵó��浵�ļ���
		number[0] = num + '0';
		number[1] = '\0';
		strcat(fileName, number);
		strcat(fileName, ".txt");
		SKIN = fopen(fileName, "w+");
		//��ֵ��Ϊ1�������
		fprintf(SKIN, "%d", 1);
		fclose(SKIN);
		//����1��˵�������ɹ�
		return 1;
	}
	//����ñ��Ƥ���ѽ���
	else
		//����0��˵������ʧ��
		return 0;
}

char* getHighScoreStr(int level)
{
	FILE* HIGHSCORE;
	char fileName[100] = "save/HIGHSCORE", number[2], saveString[100];
	//���ݵõ��ı�ŵó��浵�ļ���
	number[0] = level + '0';
	number[1] = '\0';
	strcat(fileName, number);
	strcat(fileName, ".txt");
	HIGHSCORE = fopen(fileName, "r+");
	fgets(saveString, 100, HIGHSCORE);
	fclose(HIGHSCORE);
	return saveString;
}

//��ȡ��߷�
int getHighScore(int level)
{
	char saveString[100];
	int highscore = 0;
	strcpy(saveString, getHighScoreStr(level));
	//���õ����ַ���ת��Ϊ����
	for (int i = 0; saveString[i] != '\0'; i++)
	{
		highscore *= 10;
		highscore += saveString[i] - '0';
	}
	return highscore;
}

int writeHighScore(int level, int highscore)
{
	//���Ҫд�����߷ִ���ԭ��߷�
	if (getHighScore(level) < highscore)
	{
		FILE* HIGHSCORE;
		char fileName[100] = "save/HIGHSCORE", number[2];
		//���ݵõ��ı�ŵó��浵�ļ���
		number[0] = level + '0';
		number[1] = '\0';
		strcat(fileName, number);
		strcat(fileName, ".txt");
		HIGHSCORE = fopen(fileName, "w+");
		fprintf(HIGHSCORE, "%d", highscore);
		fclose(HIGHSCORE);
		//����1��˵�������ɹ�
		return 1;
	}
	//���������߷�
	else
		//����0��˵������ʧ��
		return 0;
}