# Week 2

## lvalue and rvalue

```c++
int var1,var2;
var1+1=4; //error
var1+var2=5; //error
int sum= var1+var2; //error, int* can't be rvalue
```

只有分配过内存的variable才可做左值，`var1+1` and `var1+var2` are temporary results of expressions, and they just reside in some temporary registers for the duration of the computation. 

如果某函数`foo()`的return value 为 `int &r=a; return r`,则`foo()=4`也是对的 

`int*`类型无法做右值，只有`constant`才能做右值。

## Function Declarations and Definitions

- Declarations: 1 row, defined before called function
- Definitions: many rows, defined before or after called function
- in declarations,  formal parameter names aren't necessary. However in definitions, they are.

## Function Call Mechanisms

- called-by-value: 只传入值，variable 不会改变

```c++
int main() { … int a=4; f(a); … }
void f(int x) { x *= 2; } 
// then a=4 is unchanged.
```

- called-by-reference: 传入variable

```c++
void f(int& x) { x *= 2; }
// then a=8.
```

## Array

作为函数自变量时，实际上传入的是初地址，所以需要两个变量：

```c++
void add_one(int a[], unsigned int size) 
```

## Reference

- Need to be INITIALIZE with a VARIABLE

```c++
int& val1; //error
int& val2=1; //error
int val4;
int& val3=val4;
```

- No way to bind another object after initialization.（只能赋其值）

可以把reference理解为const pointer(what is const pointer???)

```c++
int iVal = 1024; 
int &refVal = iVal; 
int iVal2 = 10; 
refVal = iVal2; //iVal=10,refVal仍为iVal的引用
```

## Struct

declare the "type":

```c++
struct Grades { 
    char name[9]; 
    int midterm; 
    int final; 
};
```

declare object:

```c++
struct Grades alice;
struct Grades alice= {“Alice”, 60, 85}; //initialize
```

struct passed to a function:

Which of the following statements are true?
Select all the correct answers. 

-  A. If a struct is directly passed to a function, all the values of the struct will be copied. 
- B. If a struct is directly passed to a function, its member cannot be modified.
- C. Calling a function with a struct argument may be slow. 
- D. It is always better to use a pointer to a struct as an argument to a function.

**Passed by VALUE!**

If we directly pass the struct, it would pass by a copied value: `{"Alice",60,85}`，thus its member can't be modified.

If we pass by pointer, it would be faster, but member can be modified.