#ifndef CUSTOM_TYPE_H
#define CUSTOM_TYPE_H
#include <stdio.h>

/*
    Хэдер, представляющий интерфейс для работы с комплексными числами
*/

typedef struct
{
    int real;
    int imag;
} Complex;

// начинаем названия функций с имени хэдера, чтобы было понятно, какую библиотеку используем
void complexSum(void *result, const void *a, const void *b);

void complexMult(void *result, const void *a, const void *b);

void complexPrint(const void *elem);
#endif
