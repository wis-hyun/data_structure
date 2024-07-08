//인공지능공학부 2315028 김성현, 01, 240512-240518
#include "01.h"

// 노드를 생성하는 함수
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("메모리 할당 오류\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// 리스트에 값을 삽입하는 함수
void insert(LinkedList* list, int data) {
    Node* newNode = createNode(data);
    if (list->head == NULL) {
        list->head = newNode;
    } else {
        Node* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
        newNode->prev = current;
    }
}

// 리스트를 출력하는 함수
void printList(LinkedList* list) {
    Node* current = list->head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// 선택 정렬 함수
void selectionSort(LinkedList* list) {
    Node *current, *index;
    int temp;
    for (current = list->head; current != NULL; current = current->next) {
        for (index = current->next; index != NULL; index = index->next) {
            if (current->data > index->data) {
                temp = current->data;
                current->data = index->data;
                index->data = temp;
            }
        }
    }
}
// 중간 노드를 찾는 함수
Node* findMiddle(Node* start, Node* end) {
    if (start == NULL) return NULL;

    Node* slow = start;
    Node* fast = start;

    while (fast != end && fast->next != end) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

// 이진 탐색 함수
void binarySearch(LinkedList* list, int target) {
    Node* left = list->head;
    Node* right = NULL;

    // 오른쪽 경계 설정: 리스트의 마지막 노드를 찾음
    Node* current = list->head;
    while (current != NULL && current->next != NULL) {
        current = current->next;
    }
    right = current; // 오른쪽 경계를 리스트의 마지막 노드로 설정

    while (left != right && left != NULL) {
        Node* mid = findMiddle(left, right); // 왼쪽과 오른쪽 경계 사이의 중간 노드 찾기

        if (mid == NULL) { // 중간 노드를 찾지 못한 경우
            printf("false, no result in list.\n");
            return;
        }

        if (mid->data == target) { // 중간 노드의 데이터가 타겟 값과 같은 경우
            int index = 0;
            Node* temp = list->head;
            while (temp != mid) {
                index++;
                temp = temp->next;
            }
            printf("true, %d is located at index %d\n", target, index);
            return;
        } else if (mid->data < target) { // 중간 노드의 데이터가 타겟 값보다 작은 경우
            left = mid->next; // 왼쪽 경계를 중간 노드의 다음 노드로 이동
        } else { // 중간 노드의 데이터가 타겟 값보다 큰 경우
            right = mid; // 오른쪽 경계를 중간 노드로 이동
        }
    }

    if (left != NULL && left->data == target) { // 마지막 남은 노드를 검사
        int index = 0;
        Node* temp = list->head;
        while (temp != left) {
            index++;
            temp = temp->next;
        }
        printf("true, %d is located at index %d\n", target, index);
        return;
    }

    printf("false, no result in list.\n"); // 타겟 값을 찾지 못한 경우
}

int main() {
    int values[] = {66, 2, 67, 69, 8, 11, 43, 49, 5, 6, 70, 71, 73, 75, 48, 12, 14, 7, 15, 24, 26, 42, 51, 55, 56, 59, 1, 3, 80, 96, 99};
    LinkedList list;
    list.head = NULL;

    // 주어진 값으로 연결 리스트 생성
    for (int i = 0; i < sizeof(values) / sizeof(values[0]); i++) {
        insert(&list, values[i]);
    }

    printf("before : ");
    printList(&list);

    // 선택 정렬로 리스트 정렬
    selectionSort(&list);

    printf("after : ");
    printList(&list);

    // 이진 탐색 테스트
    binarySearch(&list, 3);
    binarySearch(&list, 97);
    binarySearch(&list, 96);
    binarySearch(&list, 111);
    binarySearch(&list, 15);
    binarySearch(&list, 9);
    binarySearch(&list, 66);
    binarySearch(&list, 120);
    binarySearch(&list, 99);
    binarySearch(&list, 59);

    return 0;
}
