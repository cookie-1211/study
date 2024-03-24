#include "vector.h"
#include <stdlib.h>
#include <string.h>

/*
    с-код, реализующий интерфейс для работы с векторами
*/

void vectorInit(Vector *v, size_t elemSize, SumVectorElements sumEls, PrintVectorElement printElement)
{
    v->data = NULL;
    v->size = 0;
    v->elemSize = elemSize;
    v->sumElements = sumEls;
    v->printElement = printElement;
}

void vectorPushBack(Vector *v, const void *elem)
{
    //необходимо добавить проверку в подобные функции на то
    //что элементы, с которыми происходит работа соответствуют типу вектора
    v->data = realloc(v->data, (v->size + 1) * v->elemSize);
    memcpy((char *)v->data + v->size * v->elemSize, elem, v->elemSize);
    v->size++;
}

void vectorFree(Vector *v)
{
    free(v->data);
    v->data = NULL;
    v->size = 0;
    v->elemSize = 0;
}

void vectorSum(Vector *res, const Vector *v1, const Vector *v2)
{
    if (v1->size == v2->size && v1->elemSize == v2->elemSize && v1->sumElements != NULL)
    {
        vectorInit(res, v1->elemSize, v1->sumElements, v1->printElement);
        // Временное хранилище для результата сложения двух элементов
        void *tempResult = malloc(v1->elemSize);
        if (tempResult == NULL)
        {
            // Можно вставить обработку ошибки выделения памяти
            return;
        }

        for (size_t i = 0; i < v1->size; i++)
        {
            // Получаем указатели на текущие элементы обоих векторов
            const void *elem1 = (const char *)v1->data + i * v1->elemSize;
            const void *elem2 = (const char *)v2->data + i * v2->elemSize;

            // Складываем элементы callback функцией
            v1->sumElements(tempResult, elem1, elem2);

            // Добавляем результат в результирующий вектор
            vectorPushBack(res, tempResult);
        }
        free(tempResult); // Освобождаем временное хранилище
    }
    else
    {
        // Ошибка: векторы разной длины, разного размера элементов или функция сложения не определена
    }
}

void vectorPrintElements(const Vector *v)
{
    for (size_t i = 0; i < v->size; i++)
    {
        v->printElement((const char *)v->data + i * v->elemSize);
    }
}

void vectorAddToCollection(VectorCollection *collection, const char *name, size_t elemSize, SumVectorElements addFunc, PrintVectorElement printFunc)
{
    collection->vectors = realloc(collection->vectors, (collection->size + 1) * sizeof(NamedVector));
    NamedVector *newVec = &collection->vectors[collection->size];
    strncpy(newVec->name, name, sizeof(newVec->name));
    vectorInit(&newVec->vector, elemSize, addFunc, printFunc);
    collection->size++;
}

Vector *vectorFindInCollection(VectorCollection *collection, const char *name)
{
    for (size_t i = 0; i < collection->size; i++)
    {
        if (strcmp(collection->vectors[i].name, name) == 0)
        {
            return &collection->vectors[i].vector;
        }
    }
    return NULL; // Не найден
}