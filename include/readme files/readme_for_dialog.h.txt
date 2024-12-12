void showDialog(std::string script)

input: script 对话脚本文件名

operation: 在当前页面绘制一个半透明遮罩层，显示对话，按任意键继续，播放完成即返回

output: 无

tip: 大背景图片需要调用者绘制

appendix: 对话脚本格式
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