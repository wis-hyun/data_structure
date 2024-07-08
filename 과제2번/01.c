//인공지능공학부 2315028 김성현, 01, 240511-240517
#include "01.h"

//List초기화함수
void Init(List* plist) {
    plist->head = NULL;
    plist->tail = NULL;
}
//새로운 참가자 List에 추가
void Insert(List* plist, int id, const char* name) {
    Person* newPerson = (Person*)malloc(sizeof(Person));
    newPerson->id = id;
    strncpy(newPerson->name, name, NAME_LEN);
    newPerson->name[NAME_LEN - 1] = '\0';
    newPerson->next = NULL;

    if (plist->head == NULL) {
        plist->head = newPerson;
        plist->tail = newPerson;
    }
    else {
        plist->tail->next = newPerson;
        plist->tail = newPerson;
    }
}
//List에 모든참가자 출력
void PrintList(List* plist) {
    Person* current_print = plist->head;
    while (current_print != NULL) {
        printf("[%d-%s]", current_print->id, current_print->name);
        current_print = current_print->next;
    }
    printf("\n");
}
//List에서 참가자 제거
void Remove(List* plist, Person* before, Person* target) {
    if (before == NULL) {
        plist->head = target->next;
    }
    else {
        before->next = target->next;
    }

    if (target == plist->tail) {
        plist->tail = before;
    }

    free(target);
}

// 다음 순서로 이동하는 함수
Person* Shift(List* plist, Person* current, Person** before) {
    if (current->next == NULL) {
        *before = NULL;
        return plist->head;
    } else {
        *before = current;
        return current->next;
    }
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
    Person* before = NULL;

    printf("start game!\n");

    // 처음사람을 랜덤으로 선택
    int firstPerson = rand() % 20 + 1; // 1부터 20 사이의 랜덤한 인덱스 선택
    current = list.head;
    while (current->id != firstPerson) {
        before = current;
        current = current->next;
    }
    printf("first : %d, name: %s\n", current->id, current->name);

    // 첫번째 사람을 제거
    Remove(&list, before, current);
    remaining--;  // 남은 사람 수를 감소시킴
    // 현재 리스트의 상태 출력
    printf("leaft person : ");
    PrintList(&list);
    // 다음 순서로 이동
    current = Shift(&list, current, &before);

    // 남은사람이 4명이상일때 반복
    while (remaining > 4) {
        // 현재 위치에서 3번째 사람을 찾음
        Person* target = current;
        Person* target_before = before;
        for (int i = 0; i < 3; i++) {
            target = Shift(&list, target, &target_before);
        }
        // 제거할 사람의 정보 출력
        printf("remove person : %d, name: %s\n", target->id, target->name);
        Remove(&list, target_before, target);
        remaining--;  // 남은 사람 수를 감소시킴

        // 현재 남은 사람
        printf("left person : ");
        PrintList(&list);

        // 다음 순서로 이동
        current = Shift(&list, current, &before);
    }

    printf("last winner 4 : ");
    PrintList(&list);

    // 메모리 해제
    Person* temp;
    while (list.head != NULL) {
        temp = list.head;
        list.head = list.head->next;
        free(temp);
    }

    return 0;
}
