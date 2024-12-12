int pause()

input:  无

operation:  显示暂停菜单

output: 接下来的操作
        PAUSE_CONTINUE 表示按下“继续游戏”
        PAUSE_EXIT 表示按下“退出”


int gameover(std::string scene)

input: scene 游戏结束的背景图片路径

operation:  显示游戏结束菜单

output: 接下来的操作
        GAMEOVER_PLAYAGAIN 表示按下“重玩”
        GAMEOVER_EXIT 表示按下“退出”


void gameover(int level, std::string scene, int score, int money)

input: level 关卡编号
          scene 游戏结束的背景图片路径
          score 分数
          money 金币数

operation:  显示无尽模式游戏结束菜单并进行结算

output: 无