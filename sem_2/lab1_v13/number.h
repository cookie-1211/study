#ifndef NUMBER_H
#define NUMBER_H
#include <stdio.h>

/*
    Хэдер, представляющий интерфейс для работы с int
*/

// начинаем названия функций с имени хэдера, чтобы было понятно, какую библиотеку используем
void numberSum(void *result, const void *a, const void *b);

void numberMult(void *result, const void *a, const void *b);

void numberPrint(const void *elem);

#endif /*NUMBER_H*/