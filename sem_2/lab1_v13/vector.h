#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

/*
    Хэдер, представляющий интерфейс для работы с векторами
*/
typedef void (*SumVectorElements)(void* result, const void* a, const void* b);

typedef void (*PrintVectorElement)(const void* el);

typedef struct {
    void* data;       // Указатель на элементы
    size_t size;      // Количество элементов
    size_t elemSize;  // Размер одного элемента
    SumVectorElements sumElements; // Функция сложения
    PrintVectorElement printElement; // Функция вывода
} Vector;

typedef struct {
    char name[20]; // Имя вектора
    Vector vector; // Сам вектор
} NamedVector;

typedef struct {
    NamedVector* vectors; // Динамический массив именованных векторов
    size_t size;
} VectorCollection;

//начинаем названия функций с имени хэдера, чтобы было понятно, какую библиотеку используем

void vectorInit(Vector* v, size_t elemSize, SumVectorElements sumElements, PrintVectorElement printElement);

void vectorPushBack(Vector* v, const void* elem);

void vectorFree(Vector* v);

void vectorSum(Vector* res, const Vector* v1, const Vector* v2);

void vectorPrintElements(const Vector* v);

void vectorAddToCollection(VectorCollection* collection, const char* name, size_t elemSize, SumVectorElements addFunc, PrintVectorElement printFunc);

Vector* vectorFindInCollection(VectorCollection* collection, const char* name);

//необходимо добавить еще функции согласно заданию!

#endif
