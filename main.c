#include "s21_calc_core.h"

// заранее расставить приоритет унарных операторов
// передавать в функцию priority указатель на стек (делать через два стека)

// ВАЖНО
//// Обработать деление на 0
////// Cделано, надо тестить

//// Обработать возведение в степень (a^b^c = a^(b^c))
////// Сделано, надо тестить

// ОШИБКИ
//// Не корректно конвертирует точку из qt в ядро, надо обрабатывать запятую

int main() {
    // Массив со строкой для поиска
    // char s1[240] = "2^(2^(1^3))^5";
    char s12[240] = "1/0";
    double ans = 0;
    // char s2[240] = {};
    char* s2 = calloc(255, sizeof(char));
    // printf("answer: %lf\n", shuntingYard(s1, s2));
    printf("answer: %d\n", shuntingYard(s12, s2, &ans));
    free(s2);
    // // Набор символов, которые должны входить в искомый сегмент
    // // char s2[10] = "+";
    // // printf("%s\n", strtok(s1, s2));

    // // Разделители
    // char sep[10] = " +-/%%";
    // // Переменная, в которую будут заноситься начальные адреса частей
    // // строки str
    // char *istr;

    // // Выделение первой части строки
    // istr = strtok(s1, sep);

    // // Выделение последующих частей
    // while (istr != NULL) {
    //     // Вывод очередной выделенной части
    //     printf("%s\n", istr);
    //     // Выделение очередной части строки
    //     istr = strtok(NULL, sep);
    // }

    return 0;
}