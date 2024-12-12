int isCollide(CHARACTER *character, OBSTACLE *obstacles, int countObstacle)

input:  character 角色结构体指针
        obstacles 储存该关卡中所有障碍的数组指针
        countObstacle 障碍数组长度

operation: 判断玩家是否与所在行中任何障碍发生碰撞

output: COLL_NONE 没有发生碰撞
        COLL_DEAD 发生碰撞，结果是玩家死亡


int isCollide(CHARACTER *character, ENEMY *enemies, int countEnemies)

input:  character 角色结构体指针
        enemies 储存该关卡中所有敌人的数组指针
        countEnemies 敌人数组长度

operation: 判断玩家是否与所在行中任何敌人发生碰撞

output: COLL_NONE 没有发生碰撞
        COLL_DEAD 发生碰撞，结果是玩家死亡
        COLL_KILL 发生碰撞，结果是杀死敌人