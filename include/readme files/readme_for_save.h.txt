int getMoney()

input: 无

operation: 从存档文件获取金钱数

output: 金钱数


char* getMoneyStr()

input: 无

operation: 从存档文件获取金钱数字符串

output: 金钱数字符串指针


int addMoney(int amount)

input: 增加金钱数（可为负值）

operation: 增加存档中金钱数（若操作后结果为负数则不操作）

output: 操作是否成功（1/0）


int skinAvaliable(int num)

input: 皮肤编号

operation: 从存档文件检查皮肤是否获得

output: 皮肤是否获得（1/0）


int saveSkinPurchase(int num)

input: 皮肤编号

operation: 在存档文件中解锁皮肤（如操作前已解锁则不操作）

output: 操作是否成功（1/0）


int getHighScore(int level)

input: level 关卡编号（1-3）

operation: 从存档文件获取最高分

output: 最高分


char* getHighScoreStr(int level)

input: level 关卡编号（1-3）

operation: 从存档文件获取最高分字符串

output: 最高分字符串指针


int writeHighScore(int level, int highscore)

input: level 关卡编号（1-3）
          highscore 要写入的最高分

operation: 写入最高分

output: 操作是否成功（输入值是否大于原最高分）
