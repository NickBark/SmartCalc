#ifndef CORE_H
#define CORE_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define STRLEN 255
#define SIZE_OF_CORRECT 20

typedef struct Point {
    double x;
    double y;
} Point;

typedef struct Stack {
    char* data;
    int priority;
    double value;
    struct Stack* next;
} Stack;

typedef struct Priority {
    int* priority;
    int tokenNumb;
} Priority;

// Функции стека
Stack* createNode(char* data, int priority, double value);
void stackPush(Stack** stack, char* data, int priority, double value);
void stackPop(Stack** stack);

// Алгоритм Дейкстры ("сортировочная станция")
int shuntingYard(const char* data, char* result, double* answer);

// Доп
void printArr(char** arr, int numb);
int isSep(char* ptr, char* sep);
int parsSourceStr(char* source, char** parsArr);
int verification(char** arr, int numb);
char* parsTokenArr(char** arr, char* resultStr, int tokenNum, Priority* pr);
int priority(char* str, int uno);
void stackPriority(Stack** stackPrior, char** arr, int tokenNum);
int isOp(char* str);
double calcStack(char** str, Priority* pr);
void printStack(Stack* stack, int count);

#endif  // CORE_H
