//02.h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NAME_LEN 20

typedef struct Person {
    int id;
    char name[NAME_LEN];
    struct Person* prev;
    struct Person* next;
} Person;

typedef struct List {
    Person* head;
    Person* tail;
} List;

void Init(List* list);
void Insert(List* list, int id, const char* name);
void Remove(List* list, Person* target);
void PrintList(List* list);
Person* Shift(List* list, Person* current, int direction);

