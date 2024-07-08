//인공지능공학부 2315028 김성현, 01, 240518-240523
#include "01.h"


// 스택 초기화 함수
void initStack(Stack* s) {
    s->top = -1;
}

// 스택이 비었는지 확인하는 함수
bool isEmpty(Stack* s) {
    return s->top == -1;
}

// 스택에 노드를 넣는 함수
void push(Stack* s, int x, int y) {
    if (s->top < SIZE * SIZE - 1) {
        s->top++;
        s->nodes[s->top].x = x;
        s->nodes[s->top].y = y;
    }
}

// 스택에서 노드를 빼는 함수
Node pop(Stack* s) {
    Node node = {-1, -1};
    if (!isEmpty(s)) {
        node = s->nodes[s->top];
        s->top--;
    }
    return node;
}

// 미로 정의 (0은 길, 1은 벽)
int maze[SIZE][SIZE] = {
    {1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 1, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 1, 1, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 1, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 0, 1}
};

// 시작 위치와 출구 위치 정의
int startX = 0, startY = 1;  // 시작 위치를 (0, 1)으로 
int endX = 9, endY = 8;      // 출구 위치를 (9, 8)으로 

// 방향 벡터 (상, 하, 좌, 우)
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

// 미로를 출력하는 함수
void printMaze() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (maze[i][j] == 2) {
                printf(". ");
            } else if (maze[i][j] == 1) {
                printf("# ");
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

// 유효한 이동인지 확인하는 함수
bool isValidMove(int x, int y) {
    return x >= 0 && x < SIZE && y >= 0 && y < SIZE && maze[x][y] == 0;
}

// 미로를 푸는 함수
bool solveMaze(Stack* s, int x, int y) {
    push(s, x, y);

    while (!isEmpty(s)) {
        Node current = pop(s);
        x = current.x;
        y = current.y;

        // 현재 위치가 출구인지 확인
        if (x == endX && y == endY) {
            maze[x][y] = 2;
            return true;
        }

        // 현재 위치를 방문한 것으로 표시
        maze[x][y] = 2;
        printMaze();

        // 가능한 모든 방향을 탐색
        for (int i = 0; i < 4; i++) {
            int newX = x + dx[i];
            int newY = y + dy[i];

            if (isValidMove(newX, newY)) {
                //maze[newX][newY] = 2;  // 이동 전에 방문 표시
                push(s, newX, newY);
            }
        }
    }

    return false;
}

int main() {
    Stack s;
    initStack(&s);

    // 미로를 풀려고 시도
    if (solveMaze(&s, startX, startY)) {
        printMaze();
        printf("Successfully solved the maze! \n");
    } else {
        printf("don't solve the maze. \n");
    }
    return 0;
}