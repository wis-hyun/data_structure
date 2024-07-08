// A_programcode.h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define STACK_SIZE 100

typedef struct {
    int elements[STACK_SIZE];
    int top;
} StackType;

// 스택 관련 함수 선언
void initStack(StackType *s);
int isStackEmpty(StackType *s);
int isStackFull(StackType *s);
void push(StackType *s, int value);
int pop(StackType *s);
int peek(StackType *s);

// 연산자 우선순위 함수 선언
int precedence(int op);

// 중위식을 후위식으로 변환하는 함수 선언
void infixToPostfix(const char* infix, char* postfix);

// 후위식을 계산하는 함수 선언
int evalPostfix(char* postfix);