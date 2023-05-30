#ifndef CORE_H
#define CORE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct Point {
    double x;
    double y;
} Point;

typedef struct Stack {
    char* data;
    struct Stack* next;
} Stack;

// Функции стека
Stack* createNode(char* data);
void stackPush(Stack** stack, char* data);
void stackPop(Stack** stack);

// Алгоритм Дейкстры ("сортировочная станция")
char* shuntingYard(const char* data);

#endif  // CORE_H
