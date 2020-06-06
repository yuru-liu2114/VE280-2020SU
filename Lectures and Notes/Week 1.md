# Week 1


## 变量储存期限(storage duration)

- static（静态）：在整个程序开始时初始化，整个程序结束时消失

- automatic(local)：在某些"scope""code block"中有效（比方说函数中初始化的变量）

- dynamic（动态内存分配）：由程序员来规定何时开始和结束

  ```c++
  int *p= new int;
  delete p;
  ```
## Semantics(语义)

- reference semantics：只是initialize new variable时被调用，包括正常的变量和引用
  

note：会造成地址的初始化

- value semantics: 不会造成地址变化，为已经存在的变量（已经有固定的地址）赋值

- Since C++ only supports reference semantics in initialization, the association between a variable and a memory object can never be broken.
  
## Linux commands


问题：

1. 中间数字是什么？
2. execution指什么？
3. 怎么使用 alias rm='rm -i'

## Makefile

```c++
all: myexe

myexe: add.o incdec.o sub.o
    g++ -o myexe add.o incdec.o sub.o

add.o: add.cpp
    g++ -c add.cpp

incdec.o: incdec.cpp
    g++ -c incdec.cpp

sub.o: sub.cpp
    g++ -c sub.cpp

clean:
    rm -f myexe *.o
```



## Header Guard

To avoid multiple definition:

```c++
#ifndef ADD_H
#define ADD_H
#include "incdec.h"
int add(int,int);
#endif ADD_H
```








