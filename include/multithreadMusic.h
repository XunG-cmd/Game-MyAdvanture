#pragma once
#include<Windows.h>
#include<math.h>
#include<time.h>
#include<string>
#include<iostream>
#include<graphics.h>
#pragma comment(lib, "winmm.lib")

DWORD WINAPI playOnceThread(LPVOID pram) {
    //创建随机数
    srand(time(0));
    //随机ID，避免和同时的线程冲突
    std::string ID = std::to_string(rand());
    //将路径重新转化成string，方面用加号连接
    std::string path = (char*)pram;
    //打开文件
    mciSendStringA(("open " + path + " alias " + ID).c_str(), NULL, 0, NULL);
    //播放文件，直到音乐结束才返回
    mciSendStringA(("play " + ID + " wait").c_str(), NULL, 0, NULL);
    return 0L;
}

void playMusicOnce(std::string path) {
    //转化成线程安全的char*格式
    char pram[50];
    path.copy(pram, path.size() + 1);
    pram[path.size()] = '\0';
    //创建线程
    CreateThread(NULL, 0, playOnceThread, pram, 0, NULL);
    //等待两毫秒，不然方法返回之后线程无法读取pram的值
    delay_ms(2);
}