//인공지능공학부 2315028 김성현, A_programcode, 240510

#include "A_programcode.h"

//스택 초기화
void initStack(StackType *s){
    s->top = -1;
}
//스택 비어있는지 확인
int isStackEmpty(StackType *s){
    return s->top == -1;
}
//스택 가득차있는지 확인
int isStackFull(StackType *s){
    return s->top == STACK_SIZE-1;
}
//스택에 값을 추가
void push(StackType *s, int value){
    if(!isStackFull(s)){
        s->elements[++s->top]=value;
    }else{
        printf("스택이 가득 찼습니다.\n");
    }
}
//스택에서 값 꺼내기
int pop(StackType *s){
    if(!isStackEmpty(s)){
        return s->elements[s->top--];
    }else{
        printf("스택이 비어있습니다.\n");
        exit(1);
    }
}
//스택의 상단 값을 확인
int peek(StackType *s){
    if(!isStackEmpty(s)){
        return s->elements[s->top];
    }else{
        printf("스택이 비어있습니다.\n");
        exit(1);
    }
}
//연산자 우선순위 반환함수
int precedence(int op){
    switch(op){
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

//중위수식을 후위수식으로 변환하는 함수
void infixTopostfix(char *infix, char *postfix){
    StackType stack;
    initStack(&stack);
    int i=0, j=0;
    while(infix[i]!= '\0'){
        //숫자처리
        if(isdigit(infix[i])){
            while(isdigit(infix[i])){
                postfix[j++] = infix[i++];
            }
            postfix[j++]=' ';
            //여는괄호 처리
        }else if (infix[i]=='('||infix[i]=='['||infix[i]=='{'){
            push(&stack, infix[i]);
            i++;
            //닫는괄호 처리
        }else if(infix[i]==')'||infix[i]==']'||infix[i]=='}'){
            char expected_open;
            if(infix[i]==')'){
                expected_open = '(';
            }else if (infix[i]==']'){
                expected_open = '[';
            }else{
                expected_open = '{';
            }
            //연산자 처리
            while(!isStackEmpty(&stack)&&peek(&stack) != expected_open){
                postfix[j++] = pop(&stack);
                postfix[j++] = ' ';
            }
            pop(&stack);
            i++;
    //스택에 남아있는 연산자 처리
    }else{
        while (!isStackEmpty(&stack)&& precedence(peek(&stack))>= precedence(infix[i])){
            postfix[j++] = pop(&stack);
            postfix[j++] = ' ';
        }
        push(&stack, infix[i]);
        i++;
        }
    }
    //스택에 남은 연산자들을 추가
    while (!isStackEmpty(&stack)){
        postfix[j++] = pop(&stack);
        postfix[j++] = ' ';
    }
    postfix[j-1] = '\0'; //마지막 공백을 제거
}

//후위수식 계산하는 함수
int evalPostfix(char *postfix){
    StackType stack;
    initStack(&stack);
    // 문자열을 토큰으로 분리
    char *token = strtok(postfix, " ");
    while(token != NULL){
        //숫자 처리
        if(isdigit(token[0])){
            int value = atoi(token); //'atoi'함수, 문자열을 정수로 반환
            push(&stack, value);
        // 연산자 처리
        }else{
            int op2 = pop(&stack);
            int op1 = pop(&stack);
            int result = 0;

            switch(token[0]){
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
        token = strtok(NULL, " ");
    }
    return pop(&stack);
}

int main(){
    char infix[] = "[3*(20+10)]-{20/5+[4*2]/2}+8";
    char postfix[STACK_SIZE];
    infixTopostfix(infix, postfix);
    printf("postfix : %s\n", postfix);
    int result = evalPostfix(postfix);
    printf("result : %d\n", result);
    return 0;
}