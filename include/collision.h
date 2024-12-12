//created by 黄泽源
#pragma once
#include"bitAdventure.h"
#include<math.h>

#define COLL_NONE 0
#define COLL_HURT 1
#define COLL_KILL 2

struct ROUND {
    int centerX;
    int centerY;
    int radius;
};

ROUND toRound(CHARACTER c) {
    ROUND result;
    result.centerX = c.x + c.width/2;
    result.centerY = Y(c) + c.height/2;
    result.radius = (c.width > c.height ? c.height/2 : c.width/2);
    return result;
}

ROUND toRound(OBSTACLE o) {
    ROUND result;
    result.centerX = o.x + o.width/2;
    result.centerY = laneYBase(o)-30 + o.height/2;
    result.radius = (o.width > o.height ? o.height/2 : o.width/2);
    return result;
}

ROUND toRound(ENEMY e) {
    ROUND result;
    result.centerX = e.x + e.width/2;
    result.centerY = laneYBase(e)-30 + e.height/2;
    result.radius = (e.width > e.height ? e.height/2 : e.width /2);
    return result;
}

int square(int x) {
    return x*x;
}

int isCollide(CHARACTER* character, OBSTACLE obstacle) {
    ROUND roundCharacter = toRound(*character);
    ROUND roundObstacle = toRound(obstacle);

    //如果不在同一个lane上，则跳过
    if(character->lane != obstacle.lane) return COLL_NONE;
    //如果小鹅不存在，则跳过
    if(!obstacle.appear) return COLL_NONE;
    //如果已经计算过伤害，则跳过
    if(obstacle.hurt) return COLL_NONE;
    //如果水平距离过远（大于radius之和），则跳过
    if(abs(roundCharacter.centerX-roundObstacle.centerX) > (roundCharacter.radius+roundObstacle.radius)) return COLL_NONE;
    
    //精细比对
    int squareDistance = square(roundCharacter.centerX-roundObstacle.centerX) + square(roundCharacter.centerY-roundObstacle.centerY);
    if(squareDistance < square(roundCharacter.radius+roundObstacle.radius)) {
        if(character->state == JUMP && character->jumpState == DOWN) {
            //下落中撞击，则杀死敌人
            return COLL_KILL;
        } else {
            //否则自己受到伤害
            return COLL_HURT;
        }
    }
    return COLL_NONE;
}