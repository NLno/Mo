# Mo

输入序列：Stack InputList(n);

输出序列：int OutputList[];

或者用向量？oj 不知道让不让#include<Vector>，数不大，摆一下（x）

当前积木：要有数+判断有没有当前积木，摆的想法 ↓

struct CurBlock{int Current; bool DoHave;}

空地：int EmptyPlace[];

##### 指令：（就按原来名字全小写）

inbox  
outbox  
add(x)  
sub(x)  
copyto(x)  
copyfrom(x)  
jump(x)  
jumpifzero(x)

类型 void，bool，int，摆地想了一下用 int 吧，来得到顺利执行（0）、错误情况（表里的 1 或 2）、游戏结束（如 404）等信息。

##### 四个关卡：Beat1

返回对应的输入/输出序列、空地数、指令集限制

##### 处理输入：

1.读取输入，大概存一个 char Order[]、int Param[]吗

2.对输入序列/空地执行对应命令

#### 其他用到的变量及说明

## level_msg.txt (已修改，可不用看)

包含关卡的信息，包括 input，output，可用的指令，可用的空地数。

第一行为关卡序号(0 - 3)，第二行为 input，第三行为 output，第四行为可用的空地数，第五行为可用的指令。

信息之间用空格区分，不要加标点符号。

还剩下一个自定义关卡的信息没有写入。

在 oj 上提交时需要修改此部分代码，首先是注释输出信息，其次是直接在文件中加入关卡信息。

## level.txt

用于读取游戏关卡的完成情况，每一行表示一个关卡，W 表示通关，F 表示未通关。

在 oj 上提交时需要注释此部分代码。

## main.cpp

### 变量含义

input: 输入的数字序列

output_goal: 通关要求的输出数字序列

output: 执行用户输入指令后实际的输出数字序列

output_show: 实际上为 output 的倒序，用于在命令行输出时更加方便

emptyPlace: 用于储存空地上的数字

places: 可用的空地数, 默认为 0

present: 当前机器人所有的数字

whether_inbox: 机器人是否有数字，0 表示有，1 表示没有，默认为 0

whether_emptyPlace[3]: 空地上是否有数字(我采用的空地序号为 1，2，3，不知道 oj 上会不会是 0, 1，2)，0 表示有，1 表示没有，默认{1, 1, 1}

whether_present_zero: 当前的数字是否为 0，0 表示不为 0，1 表示为 0

level_complete: 关卡完成情况，oj 上不用

### 函数含义

exist: 判断该空地是否可用, 返回 true 表示不可用，返回 false 表示可用

#### 用户可用的指令

inbox, outbox, add, sub, copyto, copyfrom, jump, jumpifzero

inbox，outbox 的输出值没有意义(默认设为 0)

返回值为 0 表示正常

inbox 返回 100 时表示输入序列中没有数字，游戏结束

返回值为 404 表示错误

jump, jumpifzero 返回跳到的指令数

#### CLI

begin: 展示开始界面(oj 上注释)，让用户选择关卡，返回字符类型的关卡标号(1 - 4)

show_level_msg: 显示关卡信息，oj 上需要重构

以下部分可以 oj 上可以全部注释

show_end, show_input, show_output, show_empty, show_present 只用于 show_level 中显示对应信息

show_level: 用于展示每个指令操作后的关卡状态

### cmd 结构

用于储存用户输出的指令信息

name: 指令的字符串

num: 对应的操作数，inbox, outbox 默认为 0

order: 指令对应的顺序(在可用的函数中的顺序)(从 1 开始)

\*func: 指令对应的函数(均为要求输入一个 int，返回一个 int)

### main

首先根据用户输入，得到 cmd 的所有信息，之后在执行指令

\*func[8]: 对应的 8 个函数

name[8]: 对应的 8 个函数的字符串类型名字

numOforder[4]: 每一关可用的指令类型数量，默认为{2, 8, 8, 2}(第四关没有设计，随便写的)

number_order: 用户想用的总的指令数(重复计数)

cnt: 用于标记用户输入的指令是否有误

msg: 函数返回值
