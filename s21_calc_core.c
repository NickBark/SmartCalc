#include "s21_calc_core.h"

Stack* createNode(char* data, int priority, double value) {
    Stack* node = (Stack*)malloc(sizeof(Stack));
    if (!node) {
        exit(1);
    }
    node->data = data;
    node->priority = priority;
    node->value = value;
    node->next = NULL;

    return node;
}

void stackPush(Stack** stack, char* data, int priority, double value) {
    Stack* newNode = createNode(data, priority, value);
    if (!(*stack)) {
        (*stack) = newNode;
    } else {
        newNode->next = (*stack);
        (*stack) = newNode;
    }
}

void stackPop(Stack** stack) {
    Stack* tmp = (*stack);
    (*stack) = (*stack)->next;
    free(tmp);
}

int shuntingYard(const char* data, char* result, double* answer) {
    Priority pr = {};
    pr.priority = calloc(STRLEN, sizeof(int));
    pr.tokenNumb = 0;

    int ret = 0;
    char source[STRLEN] = {};
    strcpy(source, data);
    int numb = 0;
    int rows = 255;
    int columns = 255;

    char** res = calloc(rows, sizeof(char*));
    for (int i = 0; i < rows; i++) {
        res[i] = calloc(columns, sizeof(char));
    }

    numb = parsSourceStr(source, res);

    if (verification(res, numb)) {
        result = parsTokenArr(res, result, numb, &pr);
        *answer = calcStack(&result, &pr);
        if (!result) {
            fprintf(stderr, "ERROR = div by zero or something else\n");
            ret = 1;
        }
        // sprintf(result, "%.10lf", answer);
    } else {
        fprintf(stderr, "ERROR = bad input\n");
        result = NULL;
    }

    printf("\nresult str ==> : %s\n", result);

    for (int i = 0; i < rows; i++) free(res[i]);
    free(res);
    free(pr.priority);

    return ret;
}

char* parsTokenArr(char** arr, char* resultStr, int tokenNum, Priority* pr) {
    Stack* stack = calloc(STRLEN, sizeof(Stack));
    Stack* stackPrior = calloc(STRLEN, sizeof(Stack));
    int stackNum = 0;
    int prior = 0;

    stackPriority(&stackPrior, arr, tokenNum);
    for (int i = 0; i < tokenNum; i++) {
        prior = stackPrior->priority;
        stackPop(&stackPrior);

        if (prior == 0) {
            strcat(resultStr, arr[i]);
            strcat(resultStr, " ");
            pr->priority[pr->tokenNumb++] = prior;
        } else if (prior == 1 || prior == 7) {
            stackPush(&stack, arr[i], prior, 0);
            stackNum++;
        } else if (prior >= 3 && prior <= 6) {
            if (stackNum) {
                // не равен 5 (pow), потому что степень считается справа на лево
                while (stack->priority >= prior && prior != 5) {
                    strcat(resultStr, stack->data);
                    strcat(resultStr, " ");
                    pr->priority[pr->tokenNumb++] = stack->priority;
                    stackPop(&stack);
                    stackNum--;
                }
            }
            stackPush(&stack, arr[i], prior, 0);
            stackNum++;
        } else if (prior == 2) {
            while (stack->priority != 1 && stackNum != 0) {
                strcat(resultStr, stack->data);
                strcat(resultStr, " ");
                pr->priority[pr->tokenNumb++] = stack->priority;
                stackPop(&stack);
                stackNum--;
            }
            if (stackNum) {
                stackPop(&stack);
                stackNum--;
            } else {
                fprintf(stderr, "ERROR = not correct\n");
            }

            if (stack->priority == 7) {
                strcat(resultStr, stack->data);
                strcat(resultStr, " ");
                pr->priority[pr->tokenNumb++] = stack->priority;
                stackPop(&stack);
                stackNum--;
            }
        }
        if (i == (tokenNum - 1)) {
            while (stackNum) {
                if (stack->priority == 1 || stack->priority == 2)
                    fprintf(stderr, "ERROR = not correct\n");
                strcat(resultStr, stack->data);
                strcat(resultStr, " ");
                pr->priority[pr->tokenNumb++] = stack->priority;
                stackPop(&stack);
                stackNum--;
            }
        }
    }

    strcat(resultStr, "\0");

    free(stack);
    free(stackPrior);

    return resultStr;
}
// x+1*sin(x)
// x 1 + x sin *
double calcStack(char** str, Priority* pr) {
    double result = 0;
    Stack* calc = calloc(STRLEN, sizeof(Stack));
    char* token = 0;
    char source[STRLEN] = {};
    double tmp = 0;
    char op[255] = {};

    strcpy(source, (*str));

    token = strtok(source, " ");
    for (int i = 0; i < pr->tokenNumb; i++) {
        if (pr->priority[i] == 0) {
            stackPush(&calc, token, pr->priority[i], atof(token));

        } else if (pr->priority[i] >= 3 && pr->priority[i] <= 5) {
            tmp = calc->value;
            result = calc->next->value;

            if (!strcmp(token, "+")) {
                result += tmp;
            } else if (!strcmp(token, "-")) {
                result -= tmp;
            } else if (!strcmp(token, "*")) {
                result *= tmp;
            } else if (!strcmp(token, "/")) {
                if (tmp == 0.) {
                    printf("!\n");
                    (*str) = NULL;
                    break;
                }
                result /= tmp;
            } else if (!strcmp(token, "%") || !strcmp(token, "mod")) {
                result = (long)result % (long)tmp;
            } else if (!strcmp(token, "^")) {
                result = pow(result, tmp);
            }

            stackPop(&calc);
            stackPop(&calc);
            stackPush(&calc, op, 0, result);
        } else if (pr->priority[i] == 6 || pr->priority[i] == 7) {
            tmp = calc->value;

            if (!strcmp(token, "+")) {
            } else if (!strcmp(token, "-")) {
                result = -tmp;
            } else if (!strcmp(token, "sin")) {
                result = sin(tmp);
            } else if (!strcmp(token, "cos")) {
                result = cos(tmp);
            } else if (!strcmp(token, "tan")) {
                result = tan(tmp);
            } else if (!strcmp(token, "acos")) {
                result = acos(tmp);
            } else if (!strcmp(token, "asin")) {
                result = asin(tmp);
            } else if (!strcmp(token, "atan")) {
                result = atan(tmp);
            } else if (!strcmp(token, "sqrt")) {
                result = sqrt(tmp);
            } else if (!strcmp(token, "ln")) {
                result = log(tmp);
            } else if (!strcmp(token, "log")) {
                result = log10(tmp);
            }

            stackPop(&calc);
            stackPush(&calc, op, 0, result);
        }

        token = strtok(NULL, " ");
    }

    if ((*str)) {
        result = calc->value;
        stackPop(&calc);
    }
    free(calc);

    return result;
}

void stackPriority(Stack** stackPrior, char** arr, int tokenNum) {
    for (int i = tokenNum - 1; i >= 0; i--) {
        if (!strcmp(arr[i], "+") || !strcmp(arr[i], "-")) {
            if (i == 0 || !strcmp(arr[i - 1], "(") || isOp(arr[i - 1])) {
                stackPush(stackPrior, arr[i], priority(arr[i], 1), 0);
                continue;
            }
        }
        stackPush(stackPrior, arr[i], priority(arr[i], 0), 0);
    }
}

int isOp(char* str) {
    return !strcmp(str, "+") || !strcmp(str, "-") || !strcmp(str, "/") ||
           !strcmp(str, "*") || !strcmp(str, "%") || !strcmp(str, "mod");
}

int priority(char* str, int uno) {
    int ret = 0;

    char func[9][STRLEN] = {
        "sin", "cos", "tan", "acos", "asin", "atan", "sqrt", "ln", "log",
    };

    if (uno) {
        ret = 6;
    } else if (!strcmp(str, " ")) {
        ret = -1;
    } else if (!strcmp(str, "(")) {
        ret = 1;
    } else if (!strcmp(str, ")")) {
        ret = 2;
    } else if (!strcmp(str, "+") || !strcmp(str, "-")) {
        ret = 3;
    } else if (!strcmp(str, "*") || !strcmp(str, "/") || !strcmp(str, "%") ||
               !strcmp(str, "mod")) {
        ret = 4;
    } else if (!strcmp(str, "^")) {
        ret = 5;
    } else {
        for (int i = 0; i < 9; i++) {
            if (!strcmp(str, func[i])) {
                ret = 7;  // функция
                break;
            }
        }
    }

    return ret;
}

// 1 = OK
// 0 = FALSE
int verification(char** arr, int numb) {
    char correct[SIZE_OF_CORRECT][STRLEN] = {
        "sin", "cos", "tan", "acos", "asin", "atan", "sqrt", "ln", "log", "mod",
        "(",   ")",   "+",   "-",    "/",    "*",    "%",    "x",  " ",   "^"};
    int tokenStatus = 0;

    for (int i = 0; i < numb; i++) {
        if (*arr[i] == 0) break;
        tokenStatus = 0;
        for (int j = 0; j < SIZE_OF_CORRECT; j++) {
            if (!strcmp(arr[i], correct[j])) {
                tokenStatus = 1;
                break;
            }
        }
        if (!tokenStatus) {
            for (size_t k = 0; k < strlen(arr[i]); k++) {
                if ((arr[i][k] >= '0' && arr[i][k] <= '9') ||
                    arr[i][k] == '.' || arr[i][k] == ',') {
                    // if (arr[i][k] == '.' || arr[i][k] == ',') arr[i][k] =
                    // '.';
                    tokenStatus = 1;
                } else {
                    tokenStatus = 0;
                    break;
                }
            }
        }
        if (!tokenStatus) {
            break;
        }
    }
    return tokenStatus;
}

// Возвращает количество токенов
int parsSourceStr(char* source, char** parsArr) {
    int numb = 0;
    char* ptr = source;
    // Разделители
    char sep[20] = " ()+-/*x^%";

    while (*ptr != '\0') {
        if (isSep(ptr, sep)) {
            parsArr[numb][0] = *ptr;
            parsArr[numb][1] = '\0';
            ptr++;
            numb++;
        } else {
            int i = 0;
            for (; *ptr != '\0' && !isSep(ptr, sep); i++) {
                parsArr[numb][i] = *ptr++;
            }
            parsArr[numb][i] = '\0';
            numb++;
        }
    }

    return numb;
}

void printArr(char** arr, int numb) {
    for (int i = 0; i < numb; i++) {
        for (size_t j = 0; j < strlen(arr[i]); j++) {
            printf("%c", arr[i][j]);
        }
        printf("\n");
    }
}

int isSep(char* ptr, char* sep) {
    int ret = 0;
    for (size_t i = 0; i < strlen(sep); i++) {
        if (*ptr == sep[i]) {
            ret = 1;
        }
    }
    return ret;
}

void printStack(Stack* stack, int count) {
    for (int i = 0; i < count; i++) {
        printf("stack: %s\n", stack->data);
        stackPop(&stack);
    }
}
