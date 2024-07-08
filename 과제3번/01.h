//01.h

#include <stdio.h>
#include <stdlib.h>

// 노드 정의
typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

// 리스트 정의
typedef struct {
    Node* head;
} LinkedList;

Node* createNode(int data);
void insert(LinkedList* list, int data);
void printList(LinkedList* list);
void selectionSort(LinkedList* list);
Node* findMiddle(Node* left, Node* right);
void binarySearch(LinkedList* list, int target);
