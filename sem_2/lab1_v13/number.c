#include "number.h"

/*
    с-код, реализующий интерфейс для работы с int
*/

void numberSum(void *result, const void *a, const void *b)
{
    *(int *)result = *(const int *)a + *(const int *)b;
}

void numberMult(void *result, const void *a, const void *b)
{
    *(int *)result = *(const int *)a * *(const int *)b;
}

void numberPrint(const void *elem)
{
    printf("%d ", *(const int *)elem);
}
