//인공지능공학부 2315028 김성현, B_programcode, 240510

#include "B_programcode.h"

// 스택 초기화
void initStack(StackType *s) {
    s->top = NULL;
}

// 스택이 비어있는지 확인
int isStackEmpty(StackType *s) {
    return s->top == NULL;
}

// 스택에 값 추가
void push(StackType *s, int value) {
    StackNode *newNode = (StackNode *)malloc(sizeof(StackNode));
    if (newNode == NULL) {
        printf("메모리 할당 오류\n");
        exit(1);
    }
    newNode->data = value;
    newNode->next = s->top;
    s->top = newNode;
}

// 스택에서 값 꺼내기
int pop(StackType *s) {
    if (isStackEmpty(s)) {  // 스택이 비어 있는지 확인
        printf("스택이 비어있습니다.\n");
        exit(1);
    }
    StackNode *temp = s->top;
    int result = temp->data;
    s->top = s->top->next;  // 상단 노드 제거
    free(temp);  // 메모리 해제
    return result;
}

// 스택의 상단 값 확인
int peek(StackType *s) {
    if (isStackEmpty(s)) {  // 스택이 비어 있는지 확인
        printf("스택이 비어있습니다.\n");
        exit(1);
    }
    return s->top->data;  // 상단 값 반환
}

// 연산자 우선순위 반환 함수
int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

// 중위식을 후위식으로 변환
void infixTopostfix(char *infix, char *postfix) {
    StackType stack;
    initStack(&stack);  // 스택 초기화
    int i = 0, j = 0;

    while (infix[i] != '\0') {  // 문자열 끝까지
        if (isdigit(infix[i])) {  // 피연산자
            while (isdigit(infix[i])) {
                postfix[j++] = infix[i++];
            }
            postfix[j++] = ' ';  // 공백 추가
        } else if (infix[i] == '(' || infix[i] == '[' || infix[i] == '{') {  // 여는 괄호
            push(&stack, infix[i]);
            i++;
        } else if (infix[i] == ')' || infix[i] == ']' || infix[i] == '}') {  // 닫는 괄호
            char expected_open = infix[i] == ')' ? '(' : (infix[i] == ']' ? '[' : '{');
            while (!isStackEmpty(&stack) && peek(&stack) != expected_open) {
                postfix[j++] = pop(&stack);
                postfix[j++] = ' ';
            }
            pop(&stack);  // 여는 괄호 제거
            i++;
        } else {  // 연산자
            while (!isStackEmpty(&stack) && precedence(peek(&stack)) >= precedence(infix[i])) {
                postfix[j++] = pop(&stack);
                postfix[j++] = ' ';
            }
            push(&stack, infix[i]);
            i++;
        }
    }

    // 스택에 남은 연산자들을 후위식에 추가
    while (!isStackEmpty(&stack)) {
        postfix[j++] = pop(&stack);
        postfix[j++] = ' ';
    }

    postfix[j - 1] = '\0';  // 마지막 공백 제거
}

// 후위식을 계산
int evalPostfix(char *postfix) {
    StackType stack;
    initStack(&stack);  // 스택 초기화
    char *token = strtok(postfix, " ");  // 토큰화

    while (token != NULL) {
        if (isdigit(token[0])) {  // 피연산자
            int value = atoi(token);
            push(&stack, value);
        } else {  // 연산자
            if (isStackEmpty(&stack)) {  // 스택이 비어있을 경우
                printf("스택이 비어있습니다.\n");
                exit(1);
            }

            int op2 = pop(&stack);  // 두 번째 피연산자
            int op1 = pop(&stack);  // 첫 번째 피연산자

            int result = 0;

            switch (token[0]) {
                case '+':
                    result = op1 + op2;
                    break;
                case '-':
                    result = op1 - op2;
                    break;
                case '*':
                    result = op1 * op2;
                    break;
                case '/':
                    result = op1 / op2;
                    break;
            }
            push(&stack, result);
        }

        token = strtok(NULL, " ");  // 다음 토큰으로 이동
    }

    if (isStackEmpty(&stack)) {  // 스택이 비어있을 경우
        printf("스택이 비어있습니다\n");
        exit(1);
    }

    return pop(&stack);
}

int main() {
    char infix[] = "2*(10+15*3-5)+{[30/3-(4/2)*3]+8}+6";
    char postfix[STACK_SIZE];  // 후위식 저장 배열

    infixTopostfix(infix, postfix);  // 중위식에서 후위식으로 변환
    printf("postfix : %s\n", postfix);

    int result = evalPostfix(postfix);  // 후위식을 계산하여 결과 도출
    printf("result : %d\n", result);

    return 0;
}
