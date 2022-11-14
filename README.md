# Mo

输入序列：Stack InputList(n);

输出序列：int OutputList[];

或者用向量？oj不知道让不让#include<Vector>，数不大，摆一下（x）

当前积木：要有数+判断有没有当前积木，摆的想法↓
  
struct CurBlock{int Current; bool DoHave;} 

空地：int EmptyPlace[];

指令：  
inbox  
outbox  
add(x)  
sub(x)  
copyto(x)  
copyfrom(x)  
jump(x)  
jumpifzero(x)  

类型void，bool，int，摆地想了一下用int吧，来得到顺利执行（0）、错误情况（表里的1或2）、游戏结束（如404）等信息。

四个关卡：Beat1
  
返回对应的输入/输出序列、空地数、指令集限制

处理输入：
  
1.读取输入，大概存一个char Order[]、int Param[]吗
  
2.对输入序列/空地执行对应命令
