//01.h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NAME_LEN 20

typedef struct _person {
    int id;
    char name[NAME_LEN];
    struct _person* next;
} Person;

typedef struct _list {
    Person* head;
    Person* tail;
} SList;

typedef SList List;

void Init(List* plist);
void Insert(List* plist, int id, const char* name);
void PrintList(List* plist);
void Remove(List* plist, Person* before, Person* target);
Person* Shift(List* plist, Person* current, Person** before);