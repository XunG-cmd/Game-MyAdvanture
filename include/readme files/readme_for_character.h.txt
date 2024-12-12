void action(CHARACTER* rabbit, int skin)

input: rabbit 角色结构体指针
          skin 皮肤编号

operation: 获取角色状态并据此对角色结构体参数进行改变

output: 无


bool keyDetect(CHARACTER * rabbit , int level, int skin)

input: rabbit 角色结构体指针
          level 关卡序号
          skin 皮肤编号

operation: 检测键盘输入，依此改变角色状态

output: 是否按下Esc键


void doubleJump(CHARACTER * rabbit)

input: rabbit 角色结构体指针

operation: 修改跳跃时间以达到二段跳（当且仅当用于检测到COLL_KILL时调用）

output: 无