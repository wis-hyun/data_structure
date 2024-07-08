// B_programcode.h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>  

#define STACK_SIZE 1000

// 스택 노드 정의
typedef struct StackNode {
    int data;
    struct StackNode *next;
} StackNode;

// 스택 구조체 정의
typedef struct {
    StackNode *top;
} StackType;

// 스택 관련 함수 선언
void initStack(StackType *s);
int isStackEmpty(StackType *s);
void push(StackType *s, int value);
int pop(StackType *s);
int peek(StackType *s);

// 연산자 우선순위 반환 함수
int precedence(char op);

// 중위식을 후위식으로 변환하는 함수
void infixToPostfix(const char* infix, char* postfix);

// 후위식을 계산하는 함수
int evalPostfix(char* postfix);
