//인공지능공학부 2315028 김성현, 02, 240517-240523

#include "02.h"

//List초기화함수
void Init(List* list) {
    list->head = NULL;
    list->tail = NULL;
}
//새로운 참가자 List에 추가
void Insert(List* list, int id, const char* name) {
    Person* newPerson = (Person*)malloc(sizeof(Person));
    newPerson->id = id;
    strcpy(newPerson->name, name);
    newPerson->prev = list->tail;
    newPerson->next = NULL;
    if (list->tail != NULL) {
        list->tail->next = newPerson;
    }
    list->tail = newPerson;
    if (list->head == NULL) {
        list->head = newPerson;
    }
}
//List에서 참가자 제거
void Remove(List* list, Person* target) {
    if (target->prev != NULL) {
        target->prev->next = target->next;
    } else {
        list->head = target->next;
    }
    if (target->next != NULL) {
        target->next->prev = target->prev;
    } else {
        list->tail = target->prev;
    }
    free(target);
}
//List에 모든참가자 출력
void PrintList(List* list) {
    Person* current = list->head;
    while (current != NULL) {
        printf("[%d-%s]",current->id, current->name);
        current = current->next;
    }
    printf("\n");
}
// 다음 순서로 이동하는 함수
Person* Shift(List* list, Person* current, int direction) {
    if (direction % 2 == 1) {  // 홀수번째일 때
        for (int i = 0; i < 2; i++) {
            current = current->next;
            if (current == NULL) {
                current = list->head;
            }
        }
    } else {  // 짝수번째일 때
        for (int i = 0; i < 7; i++) {
            current = current->prev;
            if (current == NULL) {
                current = list->tail;
            }
        }
    }
    return current;
}

int main() {
    srand((unsigned int)time(NULL));

    List list;
    Init(&list);
    // 20명의 게임참가자 이름
    char names[20][NAME_LEN] = {
        "Kim", "Lee", "Choi", "Yoon", "Park",
        "Jung", "Kang", "Han", "Cho", "Lim",
        "Seo", "Song", "Shin", "Oh", "Jin",
        "Moon", "Jeon", "Jo", "Hwang", "Ha"
    };
    // 20명의 참가자의 인덱스
    for (int i = 0; i < 20; i++) {
        Insert(&list, i + 1, names[i]);
    }

    int remaining = 20;
    Person* current = list.head;

    printf("start game!\n");

    // 처음사람을 랜덤으로 선택
    int firstPerson = rand() % 20 + 1; // 1부터 20 사이의 랜덤한 인덱스 선택
    current = list.head;
    // 처음사람의 정보를 찾음
    while (current->id != firstPerson) {
        current = current->next;
    }
    printf("first : %d, name: %s\n", current->id, current->name);

    // 첫번째 사람을 제거
    Remove(&list, current);
    remaining--;  // 남은 사람 수를 감소시킴
    // 현재 리스트의 상태 출력
    printf("left person : ");
    PrintList(&list);

    // 남은사람이 4명이상일때 반복
    int gameCount = 1;
    while (remaining > 4) {
        
        printf("Game %d\n", gameCount);
        // 현재 위치에서 3번째 또는 8번째 사람을 찾음
        Person* target = Shift(&list, current, gameCount);
        // 제거할 사람의 정보 출력
        printf("remove person : %d, name: %s\n", target->id, target->name);
        Remove(&list, target);
        remaining--;  // 남은 사람 수를 감소시킴

        // 현재 남은 사람
        printf("left person : ");
        PrintList(&list);

        // 다음 순서로 이동
        current = Shift(&list, current, gameCount);
        gameCount++;
        
    }
    printf("last winner 4 : ");
    PrintList(&list);

    return 0;
}
