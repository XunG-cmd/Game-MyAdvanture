bool getTutorial(int level,TUTORIAL_UI * tutorial , CHARACTER * rabbit)

input: level 所在关卡序号
          tutorial 教程结构体指针
          rabbit 角色结构体指针

operation: 执行教程，依据角色状态判断教程是否完成

output: 当前关卡教程是否完成