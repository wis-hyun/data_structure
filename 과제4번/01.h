// 01.h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 10

// 노드 정의
typedef struct {
    int x, y;
} Node;

// 스택 정의
typedef struct {
    Node nodes[SIZE * SIZE];
    int top;
} Stack;

void initStack(Stack* s);
bool isEmpty(Stack* s);
void push(Stack* s, int x, int y);
Node pop(Stack* s);
void printMaze();
bool isValidMove(int x, int y);
bool solveMaze(Stack* s, int x, int y);

